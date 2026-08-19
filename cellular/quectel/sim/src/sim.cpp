#include "iotpoc/cellular/sim.h"

#include <cstring>

namespace iotpoc {
namespace cellular {

AtStatus query_sim_ready(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms) {
    return client.send_command("AT+CPIN?", response, response_size, timeout_ms);
}

bool sim_response_ready(const char* response) {
    return response != nullptr && std::strstr(response, "READY") != nullptr;
}

}  // namespace cellular
}  // namespace iotpoc
