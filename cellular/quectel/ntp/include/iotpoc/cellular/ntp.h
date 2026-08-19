#pragma once

#include "iotpoc/cellular/at_client.h"

namespace iotpoc {
namespace cellular {

bool build_ntp_command(const char* server, char* out, size_t out_size);
AtStatus ntp_sync(AtClient& client, const char* server, char* response, size_t response_size, uint32_t timeout_ms);

}  // namespace cellular
}  // namespace iotpoc
