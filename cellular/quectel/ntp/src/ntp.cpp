#include "iotpoc/cellular/ntp.h"

#include <cstdio>

namespace iotpoc {
namespace cellular {

bool build_ntp_command(const char* server, char* out, size_t out_size) {
    if (server == nullptr || out == nullptr) {
        return false;
    }
    const int n = std::snprintf(out, out_size, "AT+QNTP=1,\"%s\"", server);
    return n > 0 && static_cast<size_t>(n) < out_size;
}

AtStatus ntp_sync(AtClient& client, const char* server, char* response, size_t response_size, uint32_t timeout_ms) {
    char cmd[96];
    if (!build_ntp_command(server, cmd, sizeof(cmd))) {
        return AtStatus::Transport;
    }
    return client.send_command(cmd, response, response_size, timeout_ms);
}

}  // namespace cellular
}  // namespace iotpoc
