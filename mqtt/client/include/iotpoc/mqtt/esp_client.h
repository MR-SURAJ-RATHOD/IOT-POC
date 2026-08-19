#pragma once

#include <PubSubClient.h>
#include <WiFi.h>

namespace iotpoc {
namespace mqtt {

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
    PubSubClient& raw() { return mqtt_; }

private:
    WiFiClient wifi_;
    PubSubClient mqtt_;
};

}  // namespace mqtt
}  // namespace iotpoc
