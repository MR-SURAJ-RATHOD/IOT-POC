#pragma once

#include <PubSubClient.h>
#include <WiFi.h>

namespace iotpoc {
namespace mqtt {

/**
 * ESP32-hosted MQTT over Wi-Fi (Backend A in docs/mqtt).
 *
 * Credentials: pass IOTPOC_WIFI_* and IOTPOC_MQTT_* from iotpoc_config.h.
 * If SSID or broker host still starts with "YOUR_", connect_* returns false
 * so public examples compile and run without secrets.
 *
 * After connect_broker(), call loop() frequently from loop() or an MQTT task.
 *
 * QoS note: PubSubClient publish() is QoS 0. The qos argument on publish()
 * is accepted for API stability but ignored. subscribe() can request QoS 0 or 1.
 *
 * CHANGE: Wi-Fi/broker values in config.local.h, not in this file.
 */
class EspMqttClient {
public:
    EspMqttClient();
    bool connect_wifi(const char* ssid, const char* password, uint32_t timeout_ms);
    bool connect_broker(const char* host,
                        uint16_t port,
                        const char* client_id,
                        const char* user,
                        const char* password,
                        const char* lwt_topic,
                        const char* lwt_payload);
    bool publish(const char* topic, const char* payload, bool retain, uint8_t qos);
    bool subscribe(const char* topic, uint8_t qos);
    void loop();
    bool connected();
    /** Use for setCallback() if you need incoming MQTT messages. */
    PubSubClient& raw() { return mqtt_; }

private:
    WiFiClient wifi_;
    PubSubClient mqtt_;
};

}  // namespace mqtt
}  // namespace iotpoc
