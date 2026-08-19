/**
 * Migrated from the original root sketch relaycontrol.cpp
 * Author: Suraj Rathod (Electrical & IoT Engineer)
 *
 * WHAT IT DOES
 *   USB serial commands control two relays. Same text as MQTT commands (shared parser).
 *
 * HOW TO RUN
 *   cd firmware
 *   python -m platformio run -e poc_relay_control -t upload
 *   python -m platformio device monitor -e poc_relay_control
 *   Type: ON1  OFF1  ON2  OFF2   (115200 baud)
 *
 * WHERE TO CHANGE
 *   Pins: IOTPOC_RELAY1_PIN / IOTPOC_RELAY2_PIN in firmware/include/config.local.h
 *   Active-low: DigitalOutput(..., true). If your module is active-HIGH, pass false.
 *
 * HARDWARE
 *   Most relay modules are ACTIVE LOW: GPIO LOW = coil ON, HIGH = OFF.
 *   Drive a module/transistor, not the coil from the ESP32 pin.
 */

#include <Arduino.h>

#include "iotpoc/commands/relay_command.h"
#include "iotpoc/hal/board.h"
#include "iotpoc/sensors/digital.h"
#include "iotpoc_config.h"

using iotpoc::commands::RelayCommand;
using iotpoc::commands::parse_relay_command;
using iotpoc::commands::relay_command_channel;
using iotpoc::commands::relay_command_is_on;
using iotpoc::hal::board_init_serial;
using iotpoc::sensors::DigitalOutput;

static DigitalOutput relay1(IOTPOC_RELAY1_PIN, true); /* true = active-low module */
static DigitalOutput relay2(IOTPOC_RELAY2_PIN, true);

void setup() {
    board_init_serial(115200);
    relay1.init(true); /* start OFF so boot does not energise the coil */
    relay2.init(true);

    Serial.println("=== Relay Control POC ===");
    Serial.println("Available Commands:");
    Serial.println("  ON1  - Turn ON Relay 1");
    Serial.println("  OFF1 - Turn OFF Relay 1");
    Serial.println("  ON2  - Turn ON Relay 2");
    Serial.println("  OFF2 - Turn OFF Relay 2");
    Serial.println("--------------------------------");
}

void loop() {
    if (!Serial.available()) {
        return;
    }
    String command = Serial.readStringUntil('\n');
    command.trim();
    const RelayCommand parsed = parse_relay_command(command.c_str());
    if (parsed == RelayCommand::Invalid) {
        Serial.println("Invalid Command!");
        Serial.println("Use: ON1, OFF1, ON2, OFF2");
        return;
    }
    DigitalOutput& target = (relay_command_channel(parsed) == 1) ? relay1 : relay2;
    target.set(relay_command_is_on(parsed));
    Serial.print("Relay ");
    Serial.print(relay_command_channel(parsed));
    Serial.print(" -> ");
    Serial.println(relay_command_is_on(parsed) ? "ON" : "OFF");
}
