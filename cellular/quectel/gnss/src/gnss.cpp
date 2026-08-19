#include "iotpoc/cellular/gnss.h"

namespace iotpoc {
namespace cellular {

AtStatus gnss_power_on(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms) {
    return client.send_command("AT+QGPS=1", response, response_size, timeout_ms);
}

AtStatus gnss_query_position(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms) {
    return client.send_command("AT+QGPSLOC=2", response, response_size, timeout_ms);
}

}  // namespace cellular
}  // namespace iotpoc
