#include "iotpoc/cellular/pdp.h"

#include <cstdio>
#include <cstring>

namespace iotpoc {
namespace cellular {

bool build_pdp_command(const char* apn, char* out, size_t out_size) {
    if (apn == nullptr || out == nullptr || out_size < 16) {
        return false;
    }
    const int n = std::snprintf(out, out_size, "AT+CGDCONT=1,\"IP\",\"%s\"", apn);
    return n > 0 && static_cast<size_t>(n) < out_size;
}

AtStatus configure_pdp(AtClient& client, const char* apn, char* response, size_t response_size, uint32_t timeout_ms) {
    char cmd[128];
    if (!build_pdp_command(apn, cmd, sizeof(cmd))) {
        return AtStatus::Transport;
    }
    return client.send_command(cmd, response, response_size, timeout_ms);
}

}  // namespace cellular
}  // namespace iotpoc
