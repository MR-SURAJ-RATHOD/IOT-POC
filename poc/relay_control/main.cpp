/**
 * Migrated from the original root sketch relaycontrol.cpp
 * Author: Suraj Rathod (Electrical & IoT Engineer)
 *
 * Serial commands (unchanged):
 *   ON1 / OFF1 / ON2 / OFF2
 *
 * Most relay modules are ACTIVE LOW: LOW = ON, HIGH = OFF.
 * Example pins: GPIO 27 (relay 1), GPIO 14 (relay 2) — override in config.local.h.
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

static DigitalOutput relay1(IOTPOC_RELAY1_PIN, true);
static DigitalOutput relay2(IOTPOC_RELAY2_PIN, true);

void setup() {
    board_init_serial(115200);
    relay1.init(true);
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
