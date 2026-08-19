#pragma once

#include "iotpoc/cellular/at_client.h"

namespace iotpoc {
namespace cellular {

AtStatus gnss_power_on(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms);
AtStatus gnss_query_position(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms);

}  // namespace cellular
}  // namespace iotpoc
