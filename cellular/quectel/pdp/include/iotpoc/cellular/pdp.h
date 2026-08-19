#pragma once

#include "iotpoc/cellular/at_client.h"

namespace iotpoc {
namespace cellular {

/**
 * PDP / APN: builds AT+CGDCONT=1,"IP","<apn>".
 * Pass IOTPOC_APN from config.local.h — never commit a real operator APN.
 */
bool build_pdp_command(const char* apn, char* out, size_t out_size);
AtStatus configure_pdp(AtClient& client, const char* apn, char* response, size_t response_size, uint32_t timeout_ms);

}  // namespace cellular
}  // namespace iotpoc
