/**
 * MQTT command stand-in: type ON1/OFF1 on USB (same parser as broker payloads).
 * Topic name printed is devices/{id}/cmd. Relay pin: IOTPOC_RELAY1_PIN.
 * Build: pio run -e example_mqtt_commands
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
    Serial.print("[example] commands on ");
    Serial.println(topic);
    Serial.println("[example] USB stand-in: type ON1 or OFF1");
}

void loop() {
    if (Serial.available()) {
        String line = Serial.readStringUntil('\n');
        line.trim();
        const RelayCommand cmd = parse_command_payload(line.c_str());
        if (cmd == RelayCommand::On1 || cmd == RelayCommand::Off1) {
            relay1.set(cmd == RelayCommand::On1);
            Serial.println(relay1.is_on() ? "ON" : "OFF");
        }
    }
    delay(20);
}
