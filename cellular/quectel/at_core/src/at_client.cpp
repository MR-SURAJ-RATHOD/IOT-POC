#include "iotpoc/cellular/at_client.h"

#include <cstring>

namespace iotpoc {
namespace cellular {

AtClient::AtClient(hal::IUart& uart, char* line_buffer, size_t line_capacity)
    : uart_(uart), parser_(line_buffer, line_capacity), line_buffer_(line_buffer) {}

AtStatus AtClient::wait_for_line(char* line, size_t line_size, uint32_t timeout_ms) {
    if (line == nullptr || line_size == 0) {
        return AtStatus::Transport;
    }
    line[0] = '\0';
    const uint32_t slice = 20;
    uint32_t waited = 0;
    parser_.reset();
    while (waited < timeout_ms) {
        const int b = uart_.read_byte(slice);
        waited += slice;
        if (b < 0) {
            continue;
        }
        char* assembled = nullptr;
        if (parser_.feed(static_cast<uint8_t>(b), &assembled) && assembled != nullptr) {
            std::strncpy(line, assembled, line_size - 1);
            line[line_size - 1] = '\0';
            return AtStatus::Ok;
        }
    }
    return AtStatus::Timeout;
}

AtStatus AtClient::send_command(const char* command,
                                char* response,
                                size_t response_size,
                                uint32_t timeout_ms) {
    if (command == nullptr) {
        return AtStatus::Transport;
    }
    if (response != nullptr && response_size > 0) {
        response[0] = '\0';
    }
    uart_.flush_input();
    parser_.reset();

    const size_t cmd_len = std::strlen(command);
    if (!uart_.write_bytes(reinterpret_cast<const uint8_t*>(command), cmd_len)) {
        return AtStatus::Transport;
    }
    const uint8_t crlf[2] = {'\r', '\n'};
    if (!uart_.write_bytes(crlf, 2)) {
        return AtStatus::Transport;
    }

    const uint32_t slice = 20;
    uint32_t waited = 0;
    size_t resp_len = 0;
    while (waited < timeout_ms) {
        const int b = uart_.read_byte(slice);
        waited += slice;
        if (b < 0) {
            continue;
        }
        char* assembled = nullptr;
        if (!parser_.feed(static_cast<uint8_t>(b), &assembled) || assembled == nullptr) {
            continue;
        }
        if (std::strcmp(assembled, command) == 0) {
            continue;
        }
        if (AtParser::is_ok(assembled)) {
            return AtStatus::Ok;
        }
        if (AtParser::is_cme_error(assembled)) {
            if (response != nullptr && response_size > 0) {
                std::strncpy(response, assembled, response_size - 1);
                response[response_size - 1] = '\0';
            }
            return AtStatus::CmeError;
        }
        if (AtParser::is_error(assembled)) {
            return AtStatus::Error;
        }
        if (response != nullptr && response_size > 1) {
            const size_t n = std::strlen(assembled);
            if (resp_len + n + 2 < response_size) {
                if (resp_len > 0) {
                    response[resp_len++] = '\n';
                }
                std::memcpy(response + resp_len, assembled, n);
                resp_len += n;
                response[resp_len] = '\0';
            }
        }
    }
    return AtStatus::Timeout;
}

}  // namespace cellular
}  // namespace iotpoc
