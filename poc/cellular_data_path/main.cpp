/**
 * POC: Quectel bring-up (AT -> SIM -> registration -> PDP) + task watchdog.
 *
 * WHERE TO CHANGE
 *   UART pins / baud: IOTPOC_MODEM_UART_* in config.local.h
 *   APN: IOTPOC_APN (placeholder YOUR_APN will still send CGDCONT — use a real APN on hardware)
 *
 * WIRING: ESP32 TX -> modem RX, ESP32 RX -> modem TX, strong modem supply (not ESP 3V3).
 * Build: pio run -e poc_cellular_data_path
 */

#include <Arduino.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/modem_state.h"
#include "iotpoc/cellular/network.h"
#include "iotpoc/cellular/pdp.h"
#include "iotpoc/cellular/reconnect.h"
#include "iotpoc/cellular/sim.h"
#include "iotpoc/cellular/types.h"
#include "iotpoc/hal/arduino_uart.h"
#include "iotpoc/hal/board.h"
#include "iotpoc/hal/watchdog.h"
#include "iotpoc_config.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::AtStatus;
using iotpoc::cellular::ModemEvent;
using iotpoc::cellular::ModemState;
using iotpoc::cellular::ReconnectPolicy;
using iotpoc::cellular::configure_pdp;
using iotpoc::cellular::default_ec2xx_profile;
using iotpoc::cellular::modem_next_state;
using iotpoc::cellular::modem_state_name;
using iotpoc::cellular::query_registration;
using iotpoc::cellular::query_sim_ready;
using iotpoc::cellular::registration_attached;
using iotpoc::cellular::sim_response_ready;
using iotpoc::hal::ArduinoUart;
using iotpoc::hal::board_init_serial;
using iotpoc::hal::watchdog_add_current_task;
using iotpoc::hal::watchdog_feed;
using iotpoc::hal::watchdog_init;

static char line_buf[256];
static char resp[192];

void setup() {
    board_init_serial();
    watchdog_init(15000);
    watchdog_add_current_task();

    ArduinoUart uart(Serial2, IOTPOC_MODEM_UART_RX_PIN, IOTPOC_MODEM_UART_TX_PIN, IOTPOC_MODEM_UART_BAUD);
    uart.begin();
    AtClient client(uart, line_buf, sizeof(line_buf));
    const auto& profile = default_ec2xx_profile();
    ReconnectPolicy reconnect;
    ModemState state = ModemState::CheckAt;

    Serial.print("[poc] cellular_data_path profile=");
    Serial.println(profile.name);

    AtStatus st = client.send_command("AT", resp, sizeof(resp), profile.at_timeout_ms);
    state = modem_next_state(state, st == AtStatus::Ok ? ModemEvent::AtOk : ModemEvent::AtError);
    watchdog_feed();

    st = query_sim_ready(client, resp, sizeof(resp), profile.sim_timeout_ms);
    state = modem_next_state(state, sim_response_ready(resp) ? ModemEvent::SimReady : ModemEvent::SimMissing);
    watchdog_feed();

    st = query_registration(client, resp, sizeof(resp), profile.net_timeout_ms);
    state = modem_next_state(state, registration_attached(resp) ? ModemEvent::Registered : ModemEvent::NotRegistered);
    watchdog_feed();

    st = configure_pdp(client, IOTPOC_APN, resp, sizeof(resp), profile.pdp_timeout_ms);
    state = modem_next_state(state, st == AtStatus::Ok ? ModemEvent::PdpOk : ModemEvent::PdpFail);

    Serial.print("[poc] state=");
    Serial.println(modem_state_name(state));
    if (state != ModemState::Ready) {
        const uint32_t delay_ms = reconnect.on_link_lost(state);
        Serial.print("[poc] backoff_ms=");
        Serial.println(delay_ms);
    }
}

void loop() {
    watchdog_feed();
    delay(1000);
}
