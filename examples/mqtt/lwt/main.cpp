/**
 * Last Will (LWT): broker publishes retained "offline" if we vanish without DISCONNECT.
 * Unplug USB after connect to test. Build: pio run -e example_mqtt_lwt
 */

#include <Arduino.h>

#include "iotpoc/hal/board.h"
#include "iotpoc/mqtt/esp_client.h"
#include "iotpoc/mqtt/topics.h"
#include "iotpoc_config.h"

using iotpoc::hal::board_init_serial;
using iotpoc::mqtt::EspMqttClient;
using iotpoc::mqtt::topic_status;

static EspMqttClient mqtt;
static char topic[80];

void setup() {
    board_init_serial();
    topic_status(IOTPOC_DEVICE_ID, topic, sizeof(topic));
    if (mqtt.connect_wifi(IOTPOC_WIFI_SSID, IOTPOC_WIFI_PASSWORD, 8000)) {
        mqtt.connect_broker(IOTPOC_MQTT_HOST, IOTPOC_MQTT_PORT, IOTPOC_MQTT_CLIENT_ID,
                            IOTPOC_MQTT_USER, IOTPOC_MQTT_PASSWORD, topic, "offline");
        Serial.println("[example] LWT payload=offline on status topic");
    }
}

void loop() {
    mqtt.loop();
    delay(10);
}
