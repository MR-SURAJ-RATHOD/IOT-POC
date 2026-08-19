#include "iotpoc/mqtt/esp_client.h"

#include <Arduino.h>
#include <cstring>

namespace iotpoc {
namespace mqtt {

EspMqttClient::EspMqttClient() : mqtt_(wifi_) {}

bool EspMqttClient::connect_wifi(const char* ssid, const char* password, uint32_t timeout_ms) {
    /* Public tree uses YOUR_WIFI_SSID — skip so the sketch does not hang. */
    if (ssid == nullptr || std::strstr(ssid, "YOUR_") == ssid) {
        Serial.println("[mqtt] Wi-Fi SSID is still a placeholder; skip connect");
        Serial.println("[mqtt] Copy config.example.h -> config.local.h and set IOTPOC_WIFI_SSID");
        return false;
    }
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    const uint32_t start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < timeout_ms) {
        delay(200);
    }
    return WiFi.status() == WL_CONNECTED;
}

bool EspMqttClient::connect_broker(const char* host,
                                   uint16_t port,
                                   const char* client_id,
                                   const char* user,
                                   const char* password,
                                   const char* lwt_topic,
                                   const char* lwt_payload) {
    if (host == nullptr || std::strstr(host, "YOUR_") == host) {
        Serial.println("[mqtt] broker host is still a placeholder; skip connect");
        Serial.println("[mqtt] Set IOTPOC_MQTT_HOST in config.local.h");
        return false;
    }
    mqtt_.setServer(host, port);
    /* LWT is published by the broker if we disconnect uncleanly (power loss). */
    if (lwt_topic != nullptr && lwt_payload != nullptr) {
        return mqtt_.connect(client_id, user, password, lwt_topic, 1, true, lwt_payload);
    }
    return mqtt_.connect(client_id, user, password);
}

bool EspMqttClient::publish(const char* topic, const char* payload, bool retain, uint8_t qos) {
    (void)qos; /* PubSubClient has no QoS on publish; see header comment. */
    if (!mqtt_.connected()) {
        return false;
    }
    return mqtt_.publish(topic, payload, retain);
}

bool EspMqttClient::subscribe(const char* topic, uint8_t qos) {
    if (!mqtt_.connected()) {
        return false;
    }
    return mqtt_.subscribe(topic, qos);
}

void EspMqttClient::loop() {
    mqtt_.loop(); /* Required: keepalives and incoming publishes. */
}

bool EspMqttClient::connected() {
    return mqtt_.connected();
}

}  // namespace mqtt
}  // namespace iotpoc
