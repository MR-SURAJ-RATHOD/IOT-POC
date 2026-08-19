#include <Arduino.h>

#include "iotpoc/hal/board.h"
#include "iotpoc/mqtt/esp_client.h"
#include "iotpoc_config.h"

using iotpoc::hal::board_init_serial;
using iotpoc::mqtt::EspMqttClient;

static EspMqttClient mqtt;

void setup() {
    board_init_serial();
    Serial.println("[example] reconnect: loop() keeps the client alive; reconnect on drop");
    mqtt.connect_wifi(IOTPOC_WIFI_SSID, IOTPOC_WIFI_PASSWORD, 8000);
    mqtt.connect_broker(IOTPOC_MQTT_HOST, IOTPOC_MQTT_PORT, IOTPOC_MQTT_CLIENT_ID,
                        IOTPOC_MQTT_USER, IOTPOC_MQTT_PASSWORD, nullptr, nullptr);
}

void loop() {
    if (!mqtt.connected()) {
        mqtt.connect_broker(IOTPOC_MQTT_HOST, IOTPOC_MQTT_PORT, IOTPOC_MQTT_CLIENT_ID,
                            IOTPOC_MQTT_USER, IOTPOC_MQTT_PASSWORD, nullptr, nullptr);
        delay(500);
    }
    mqtt.loop();
    delay(10);
}
