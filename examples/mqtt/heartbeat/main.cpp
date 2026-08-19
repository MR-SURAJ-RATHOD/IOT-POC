/**
 * Heartbeat every 5 s on devices/{id}/heartbeat. Change 5000 in loop() for period.
 * Build: pio run -e example_mqtt_heartbeat
 */

#include <Arduino.h>

#include "iotpoc/hal/board.h"
#include "iotpoc/mqtt/esp_client.h"
#include "iotpoc/mqtt/topics.h"
#include "iotpoc_config.h"

using iotpoc::hal::board_init_serial;
using iotpoc::mqtt::EspMqttClient;
using iotpoc::mqtt::topic_heartbeat;

static EspMqttClient mqtt;
static char topic[80];
static uint32_t last_ms = 0;

void setup() {
    board_init_serial();
    topic_heartbeat(IOTPOC_DEVICE_ID, topic, sizeof(topic));
    mqtt.connect_wifi(IOTPOC_WIFI_SSID, IOTPOC_WIFI_PASSWORD, 8000);
    mqtt.connect_broker(IOTPOC_MQTT_HOST, IOTPOC_MQTT_PORT, IOTPOC_MQTT_CLIENT_ID,
                        IOTPOC_MQTT_USER, IOTPOC_MQTT_PASSWORD, nullptr, nullptr);
}

void loop() {
    mqtt.loop();
    if (millis() - last_ms > 5000) {
        last_ms = millis();
        mqtt.publish(topic, "{\"hb\":1}", false, 0);
        Serial.println("[example] heartbeat");
    }
}
