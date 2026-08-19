#pragma once

#include "iotpoc/cellular/at_client.h"

namespace iotpoc {
namespace cellular {

bool build_pdp_command(const char* apn, char* out, size_t out_size);
AtStatus configure_pdp(AtClient& client, const char* apn, char* response, size_t response_size, uint32_t timeout_ms);

}  // namespace cellular
}  // namespace iotpoc
