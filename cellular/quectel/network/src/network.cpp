#include "iotpoc/cellular/network.h"

#include <cstdlib>
#include <cstring>

namespace iotpoc {
namespace cellular {

AtStatus query_registration(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms) {
    return client.send_command("AT+CEREG?", response, response_size, timeout_ms);
}

AtStatus query_signal(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms) {
    return client.send_command("AT+CSQ", response, response_size, timeout_ms);
}

bool registration_attached(const char* response) {
    if (response == nullptr) {
        return false;
    }
    const char* comma = std::strchr(response, ',');
    if (comma == nullptr || comma[1] == '\0') {
        return false;
    }
    const int stat = std::atoi(comma + 1);
    return stat == 1 || stat == 5;
}

int parse_rssi(const char* response) {
    if (response == nullptr) {
        return -1;
    }
    const char* p = std::strstr(response, "+CSQ:");
    if (p == nullptr) {
        p = std::strstr(response, "CSQ:");
    }
    if (p == nullptr) {
        return -1;
    }
    while (*p != '\0' && (*p < '0' || *p > '9')) {
        ++p;
    }
    if (*p == '\0') {
        return -1;
    }
    return std::atoi(p);
}

}  // namespace cellular
}  // namespace iotpoc
