#include "iotpoc/cellular/mqtt_at.h"

#include <cstdio>

namespace iotpoc {
namespace cellular {

bool build_mqtt_open_command(const char* host, uint16_t port, char* out, size_t out_size) {
    if (host == nullptr || out == nullptr || out_size < 24) {
        return false;
    }
    const int n = std::snprintf(out, out_size, "AT+QMTOPEN=0,\"%s\",%u", host, static_cast<unsigned>(port));
    return n > 0 && static_cast<size_t>(n) < out_size;
}

AtStatus mqtt_at_open(AtClient& client, const char* host, uint16_t port, char* response, size_t response_size, uint32_t timeout_ms) {
    char cmd[160];
    if (!build_mqtt_open_command(host, port, cmd, sizeof(cmd))) {
        return AtStatus::Transport;
    }
    return client.send_command(cmd, response, response_size, timeout_ms);
}

}  // namespace cellular
}  // namespace iotpoc
