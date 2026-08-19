/**
 * Remote config stand-in: type interval_ms=2000 on USB.
 * MQTT topic is devices/{id}/cfg. Add NVS persistence later — RAM only here.
 * Build: pio run -e example_mqtt_configuration
 */

#include <Arduino.h>

#include "iotpoc/hal/board.h"
#include "iotpoc/mqtt/commands.h"
#include "iotpoc/mqtt/topics.h"
#include "iotpoc_config.h"

using iotpoc::hal::board_init_serial;
using iotpoc::mqtt::ConfigKey;
using iotpoc::mqtt::parse_config_key;
using iotpoc::mqtt::topic_cfg;

static char topic[80];
static uint32_t interval_ms = 1000;

void setup() {
    board_init_serial();
    topic_cfg(IOTPOC_DEVICE_ID, topic, sizeof(topic));
    Serial.print("[example] configuration topic=");
    Serial.println(topic);
    Serial.println("[example] type interval_ms=2000 on USB serial");
}

void loop() {
    if (!Serial.available()) {
        delay(50);
        return;
    }
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (parse_config_key(line.c_str()) == ConfigKey::IntervalMs) {
        const int v = line.substring(line.indexOf('=') + 1).toInt();
        if (v > 0) {
            interval_ms = static_cast<uint32_t>(v);
        }
        Serial.print("interval_ms=");
        Serial.println(interval_ms);
    }
}
