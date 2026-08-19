#include "iotpoc/cellular/diagnostics.h"

namespace iotpoc {
namespace cellular {

AtStatus query_manufacturer(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms) {
    return client.send_command("AT+CGMI", response, response_size, timeout_ms);
}

AtStatus query_firmware(AtClient& client, char* response, size_t response_size, uint32_t timeout_ms) {
    return client.send_command("AT+CGMR", response, response_size, timeout_ms);
}

}  // namespace cellular
}  // namespace iotpoc
