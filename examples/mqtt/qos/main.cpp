/**
 * QoS demo: publish is QoS 0 (PubSubClient limit); subscribe requests QoS 1.
 * Build: pio run -e example_mqtt_qos
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
    Serial.println("[example] QoS: PubSubClient publish is QoS 0; subscribe requests QoS 1");
    if (mqtt.connect_wifi(IOTPOC_WIFI_SSID, IOTPOC_WIFI_PASSWORD, 8000) &&
        mqtt.connect_broker(IOTPOC_MQTT_HOST, IOTPOC_MQTT_PORT, IOTPOC_MQTT_CLIENT_ID,
                            IOTPOC_MQTT_USER, IOTPOC_MQTT_PASSWORD, nullptr, nullptr)) {
        mqtt.publish(topic, "{\"qos_demo\":0}", false, 0);
        mqtt.subscribe(topic, 1);
    }
}

void loop() {
    mqtt.loop();
    delay(10);
}
