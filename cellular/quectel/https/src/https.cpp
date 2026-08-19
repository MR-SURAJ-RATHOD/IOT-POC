#include "iotpoc/cellular/https.h"

namespace iotpoc {
namespace cellular {

AtStatus https_configure_tls_placeholder(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms) {
    /* Context 1, SSL version placeholder — certificates must stay out of git. */
    return client.send_command("AT+QSSLCFG=\"sslversion\",1,4", response, response_size, timeout_ms);
}

}  // namespace cellular
}  // namespace iotpoc
