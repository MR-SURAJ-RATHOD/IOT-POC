#pragma once

#include "iotpoc/cellular/at_client.h"

namespace iotpoc {
namespace cellular {

/** Modem MQTT open (AT+QMTOPEN). Host/port from IOTPOC_MQTT_* — not the ESP32 Wi-Fi client. */
bool build_mqtt_open_command(const char* host, uint16_t port, char* out, size_t out_size);
AtStatus mqtt_at_open(AtClient& client, const char* host, uint16_t port, char* response, size_t response_size, uint32_t timeout_ms);

}  // namespace cellular
}  // namespace iotpoc
