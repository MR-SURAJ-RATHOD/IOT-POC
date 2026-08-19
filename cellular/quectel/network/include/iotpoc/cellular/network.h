#pragma once

#include "iotpoc/cellular/at_client.h"

namespace iotpoc {
namespace cellular {

AtStatus query_registration(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms);
AtStatus query_signal(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms);
bool registration_attached(const char* response);
int parse_rssi(const char* response);

}  // namespace cellular
}  // namespace iotpoc
