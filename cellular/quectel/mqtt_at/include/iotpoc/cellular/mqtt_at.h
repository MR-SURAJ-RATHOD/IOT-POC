#pragma once

#include "iotpoc/cellular/at_client.h"

namespace iotpoc {
namespace cellular {

bool build_mqtt_open_command(const char* host, uint16_t port, char* out, size_t out_size);
AtStatus mqtt_at_open(AtClient& client, const char* host, uint16_t port, char* response, size_t response_size, uint32_t timeout_ms);

}  // namespace cellular
}  // namespace iotpoc
