/**
 * MQTT publish one JSON hello to devices/{id}/telemetry.
 *
 * CHANGE: IOTPOC_WIFI_* and IOTPOC_MQTT_* in config.local.h
 * If they still start with YOUR_, connect is skipped (safe for public builds).
 * Build: pio run -e example_mqtt_publish
 */

#include <Arduino.h>

#include "iotpoc/hal/board.h"
#include "iotpoc/mqtt/esp_client.h"
#include "iotpoc/mqtt/topics.h"
#include "iotpoc_config.h"

using iotpoc::hal::board_init_serial;
using iotpoc::mqtt::EspMqttClient;
using iotpoc::mqtt::topic_telemetry;

static EspMqttClient mqtt;
static char topic[80];

void setup() {
    board_init_serial();
    topic_telemetry(IOTPOC_DEVICE_ID, topic, sizeof(topic));
    Serial.print("[example] publish topic=");
    Serial.println(topic);
    if (mqtt.connect_wifi(IOTPOC_WIFI_SSID, IOTPOC_WIFI_PASSWORD, 8000) &&
        mqtt.connect_broker(IOTPOC_MQTT_HOST, IOTPOC_MQTT_PORT, IOTPOC_MQTT_CLIENT_ID,
                            IOTPOC_MQTT_USER, IOTPOC_MQTT_PASSWORD, nullptr, nullptr)) {
        mqtt.publish(topic, "{\"hello\":1}", false, 0);
    }
}

void loop() {
    mqtt.loop();
    delay(10);
}
