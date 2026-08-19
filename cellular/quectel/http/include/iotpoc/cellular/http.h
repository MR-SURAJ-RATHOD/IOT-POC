#pragma once

#include "iotpoc/cellular/at_client.h"

namespace iotpoc {
namespace cellular {

/** HTTP over the modem. URL from IOTPOC_HTTP_URL — public test hosts only. */
bool build_http_url_command(const char* url, char* out, size_t out_size);
AtStatus http_set_url(AtClient& client, const char* url, char* response, size_t response_size, uint32_t timeout_ms);
AtStatus http_get(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms);

}  // namespace cellular
}  // namespace iotpoc
