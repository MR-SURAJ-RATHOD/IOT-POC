#pragma once

#include "iotpoc/cellular/at_parser.h"
#include "iotpoc/cellular/types.h"
#include "iotpoc/hal/uart.h"

namespace iotpoc {
namespace cellular {

/**
 * Sends one AT command, waits until OK / ERROR / CME ERROR / timeout.
 *
 * Usage:
 *   char line[256], resp[192];
 *   AtClient client(uart, line, sizeof(line));
 *   AtStatus st = client.send_command("AT", resp, sizeof(resp), 1000);
 *
 * Do not send a second command until the first returns (single in-flight).
 * Feature modules (sim, network, pdp, …) wrap standard commands — prefer those
 * instead of concatenating AT strings in application code.
 */
class AtClient {
public:
    AtClient(hal::IUart& uart, char* line_buffer, size_t line_capacity);
    AtStatus send_command(const char* command,
                          char* response,
                          size_t response_size,
                          uint32_t timeout_ms);
    AtStatus wait_for_line(char* line, size_t line_size, uint32_t timeout_ms);

private:
    hal::IUart& uart_;
    AtParser parser_;
    char* line_buffer_;
};

}  // namespace cellular
}  // namespace iotpoc
