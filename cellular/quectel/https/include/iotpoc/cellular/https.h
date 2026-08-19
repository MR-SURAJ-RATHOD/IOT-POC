#pragma once

#include "iotpoc/cellular/at_client.h"

namespace iotpoc {
namespace cellular {

/** TLS context placeholder. Private certs stay in gitignored files, never in this tree. */
AtStatus https_configure_tls_placeholder(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms);

}  // namespace cellular
}  // namespace iotpoc
