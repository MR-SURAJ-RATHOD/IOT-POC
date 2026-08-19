#include <cstring>
#include <string>
#include <unity.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/at_parser.h"
#include "iotpoc/cellular/modem_state.h"
#include "iotpoc/cellular/network.h"
#include "iotpoc/cellular/pdp.h"
#include "iotpoc/cellular/reconnect.h"
#include "iotpoc/commands/relay_command.h"
#include "iotpoc/comm/line_framer.h"
#include "iotpoc/comm/modbus_rtu.h"
#include "iotpoc/hal/uart.h"
#include "iotpoc/mqtt/telemetry_json.h"
#include "iotpoc/mqtt/topics.h"
#include "iotpoc/rtos/app_fsm.h"
#include "iotpoc/rtos/backoff.h"
#include "iotpoc/sensors/analog.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::AtParser;
using iotpoc::cellular::AtStatus;
using iotpoc::cellular::ModemEvent;
using iotpoc::cellular::ModemState;
using iotpoc::cellular::ReconnectPolicy;
using iotpoc::cellular::build_pdp_command;
using iotpoc::cellular::mask_secret;
using iotpoc::cellular::modem_next_state;
using iotpoc::cellular::parse_rssi;
using iotpoc::cellular::registration_attached;
using iotpoc::commands::RelayCommand;
using iotpoc::commands::parse_relay_command;
using iotpoc::comm::LineFramer;
using iotpoc::comm::modbus_build_read_holding;
using iotpoc::comm::modbus_crc_ok;
using iotpoc::mqtt::build_telemetry_json;
using iotpoc::mqtt::topic_telemetry;
using iotpoc::rtos::AppEvent;
using iotpoc::rtos::AppState;
using iotpoc::rtos::ExponentialBackoff;
using iotpoc::rtos::app_next_state;
using iotpoc::sensors::AnalogVoltageSensor;
using iotpoc::sensors::SensorReading;
using iotpoc::sensors::analog_raw_to_volts;

class MockUart : public iotpoc::hal::IUart {
public:
    void set_canned(const char* text) { canned_ = text != nullptr ? text : ""; }

    bool write_bytes(const uint8_t* data, size_t length) override {
        tx_.append(reinterpret_cast<const char*>(data), length);
        rx_ = canned_;
        pos_ = 0;
        return true;
    }

    int read_byte(uint32_t) override {
        if (pos_ >= rx_.size()) {
            return -1;
        }
        return static_cast<unsigned char>(rx_[pos_++]);
    }

    void flush_input() override {}

    const std::string& tx() const { return tx_; }

private:
    std::string canned_;
    std::string rx_;
    std::string tx_;
    size_t pos_ = 0;
};

void test_relay_commands() {
    TEST_ASSERT_EQUAL(RelayCommand::On1, parse_relay_command(" on1\n"));
    TEST_ASSERT_EQUAL(RelayCommand::Off2, parse_relay_command("OFF2"));
    TEST_ASSERT_EQUAL(RelayCommand::Invalid, parse_relay_command("OPEN"));
}

void test_analog_conversion() {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 1.65f, analog_raw_to_volts(2048, 3.3f, 4096));
    AnalogVoltageSensor sensor("a", 1, 3.3f, 4095);
    TEST_ASSERT_TRUE(sensor.init());
    sensor.inject_raw(4095);
    SensorReading reading;
    TEST_ASSERT_TRUE(sensor.read(reading));
    TEST_ASSERT_FLOAT_WITHIN(0.05f, 3.3f, reading.value);
}

void test_modbus_crc() {
    uint8_t adu[8];
    size_t len = 0;
    TEST_ASSERT_TRUE(modbus_build_read_holding(1, 0, 1, adu, sizeof(adu), &len));
    TEST_ASSERT_EQUAL(8, static_cast<int>(len));
    TEST_ASSERT_TRUE(modbus_crc_ok(adu, len));
    adu[7] ^= 0xFF;
    TEST_ASSERT_FALSE(modbus_crc_ok(adu, len));
}

void test_line_framer() {
    char buf[16];
    LineFramer framer(buf, sizeof(buf));
    char* line = nullptr;
    TEST_ASSERT_FALSE(framer.feed('A', &line));
    TEST_ASSERT_FALSE(framer.feed('T', &line));
    TEST_ASSERT_TRUE(framer.feed('\n', &line));
    TEST_ASSERT_EQUAL_STRING("AT", line);
}

void test_at_parser_and_mask() {
    char buf[32];
    AtParser parser(buf, sizeof(buf));
    char* line = nullptr;
    const char* sample = "OK\n";
    bool got = false;
    for (size_t i = 0; sample[i] != '\0'; ++i) {
        if (parser.feed(static_cast<uint8_t>(sample[i]), &line)) {
            got = AtParser::is_ok(line);
        }
    }
    TEST_ASSERT_TRUE(got);
    char secret[] = "IMSI:123456789012345";
    mask_secret(secret);
    TEST_ASSERT_TRUE(std::strchr(secret, '*') != nullptr);
}

void test_at_client_ok() {
    MockUart uart;
    uart.set_canned("AT\r\nOK\r\n");
    char line[64];
    char resp[64];
    AtClient client(uart, line, sizeof(line));
    TEST_ASSERT_EQUAL(AtStatus::Ok, client.send_command("AT", resp, sizeof(resp), 200));
    TEST_ASSERT_TRUE(uart.tx().find("AT") != std::string::npos);
}

void test_modem_and_reconnect() {
    ModemState s = ModemState::CheckAt;
    s = modem_next_state(s, ModemEvent::AtOk);
    TEST_ASSERT_EQUAL(ModemState::CheckSim, s);
    s = modem_next_state(s, ModemEvent::SimReady);
    s = modem_next_state(s, ModemEvent::Registered);
    s = modem_next_state(s, ModemEvent::PdpOk);
    /* signal state auto-advances to PDP in the table */
    ReconnectPolicy policy;
    s = ModemState::Ready;
    const uint32_t d1 = policy.on_link_lost(s);
    const uint32_t d2 = policy.on_link_lost(s);
    TEST_ASSERT_TRUE(d2 >= d1);
    TEST_ASSERT_EQUAL(ModemState::Backoff, s);
}

void test_registration_and_rssi() {
    TEST_ASSERT_TRUE(registration_attached("+CEREG: 0,1"));
    TEST_ASSERT_FALSE(registration_attached("+CEREG: 0,2"));
    TEST_ASSERT_EQUAL(18, parse_rssi("+CSQ: 18,99"));
}

void test_pdp_and_topics_json() {
    char cmd[80];
    TEST_ASSERT_TRUE(build_pdp_command("internet", cmd, sizeof(cmd)));
    TEST_ASSERT_TRUE(std::strstr(cmd, "internet") != nullptr);
    char topic[64];
    TEST_ASSERT_TRUE(topic_telemetry("dev1", topic, sizeof(topic)));
    TEST_ASSERT_EQUAL_STRING("devices/dev1/telemetry", topic);
    SensorReading reading;
    reading.sensor_id = "adc";
    reading.quantity = iotpoc::sensors::Quantity::Voltage;
    reading.value = 1.25f;
    reading.unit = "V";
    reading.quality = iotpoc::sensors::Quality::Ok;
    reading.timestamp_ms = 0;
    reading.error = iotpoc::sensors::SensorError::None;
    char json[192];
    TEST_ASSERT_TRUE(build_telemetry_json(reading, "dev1", json, sizeof(json)));
    TEST_ASSERT_TRUE(std::strstr(json, "\"schema\":1") != nullptr);
}

void test_backoff_and_app_fsm() {
    ExponentialBackoff backoff(100, 800, 2);
    TEST_ASSERT_EQUAL(100, backoff.next_delay_ms());
    TEST_ASSERT_EQUAL(200, backoff.next_delay_ms());
    TEST_ASSERT_EQUAL(400, backoff.next_delay_ms());
    AppState a = AppState::Idle;
    a = app_next_state(a, AppEvent::Start);
    a = app_next_state(a, AppEvent::Ready);
    TEST_ASSERT_EQUAL(AppState::Run, a);
    a = app_next_state(a, AppEvent::LinkLost);
    TEST_ASSERT_EQUAL(AppState::Reconnect, a);
}

void setUp() {}
void tearDown() {}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_relay_commands);
    RUN_TEST(test_analog_conversion);
    RUN_TEST(test_modbus_crc);
    RUN_TEST(test_line_framer);
    RUN_TEST(test_at_parser_and_mask);
    RUN_TEST(test_at_client_ok);
    RUN_TEST(test_modem_and_reconnect);
    RUN_TEST(test_registration_and_rssi);
    RUN_TEST(test_pdp_and_topics_json);
    RUN_TEST(test_backoff_and_app_fsm);
    return UNITY_END();
}
