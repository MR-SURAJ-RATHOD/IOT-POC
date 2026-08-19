#pragma once

#include "iotpoc/cellular/at_client.h"

namespace iotpoc {
namespace cellular {

AtStatus query_sim_ready(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms);
bool sim_response_ready(const char* response);

}  // namespace cellular
}  // namespace iotpoc
