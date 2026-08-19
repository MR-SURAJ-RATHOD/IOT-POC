#include "iotpoc/cellular/http.h"

#include <cstdio>
#include <cstring>

namespace iotpoc {
namespace cellular {

bool build_http_url_command(const char* url, char* out, size_t out_size) {
    if (url == nullptr || out == nullptr || out_size < 20) {
        return false;
    }
    const int n = std::snprintf(out, out_size, "AT+QHTTPURL=%u,80", static_cast<unsigned>(std::strlen(url)));
    return n > 0 && static_cast<size_t>(n) < out_size;
}

AtStatus http_set_url(AtClient& client, const char* url, char* response, size_t response_size, uint32_t timeout_ms) {
    char cmd[64];
    if (!build_http_url_command(url, cmd, sizeof(cmd))) {
        return AtStatus::Transport;
    }
    return client.send_command(cmd, response, response_size, timeout_ms);
}

AtStatus http_get(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms) {
    return client.send_command("AT+QHTTPGET=80", response, response_size, timeout_ms);
}

}  // namespace cellular
}  // namespace iotpoc
