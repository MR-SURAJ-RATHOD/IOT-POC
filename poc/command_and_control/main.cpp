/**
 * POC: same command parser for USB serial and MQTT cmd topic.
 * Type ON1/OFF1 on serial. MQTT topic printed is devices/{id}/cmd.
 *
 * CHANGE: IOTPOC_DEVICE_ID and relay pin in config.local.h
 * Build: pio run -e poc_command_and_control
 */

#include <Arduino.h>

#include "iotpoc/commands/relay_command.h"
#include "iotpoc/hal/board.h"
#include "iotpoc/mqtt/commands.h"
#include "iotpoc/mqtt/topics.h"
#include "iotpoc/sensors/digital.h"
#include "iotpoc_config.h"

using iotpoc::commands::RelayCommand;
using iotpoc::hal::board_init_serial;
using iotpoc::mqtt::parse_command_payload;
using iotpoc::mqtt::topic_cmd;
using iotpoc::sensors::DigitalOutput;

static DigitalOutput relay1(IOTPOC_RELAY1_PIN, true);
static char topic[80];

void setup() {
    board_init_serial();
    relay1.init(true);
    topic_cmd(IOTPOC_DEVICE_ID, topic, sizeof(topic));
    Serial.print("[poc] command_and_control subscribe placeholder topic=");
    Serial.println(topic);
    Serial.println("[poc] type ON1/OFF1 on USB serial to exercise the same parser used for MQTT payloads");
}

void loop() {
    if (!Serial.available()) {
        delay(50);
        return;
    }
    String line = Serial.readStringUntil('\n');
    line.trim();
    const RelayCommand cmd = parse_command_payload(line.c_str());
    if (cmd == RelayCommand::On1 || cmd == RelayCommand::Off1) {
        relay1.set(cmd == RelayCommand::On1);
        Serial.println(relay1.is_on() ? "Relay 1 ON" : "Relay 1 OFF");
    } else {
        Serial.println("Use ON1 or OFF1 (MQTT command payloads use the same parser)");
    }
}
