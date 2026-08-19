#include "iotpoc/cellular/at_parser.h"

#include <cstring>

namespace iotpoc {
namespace cellular {

AtParser::AtParser(char* buffer, size_t capacity)
    : buffer_(buffer), capacity_(capacity), length_(0) {}

void AtParser::reset() {
    length_ = 0;
    if (buffer_ != nullptr && capacity_ > 0) {
        buffer_[0] = '\0';
    }
}

bool AtParser::feed(uint8_t byte, char** line_out) {
    if (buffer_ == nullptr || capacity_ < 2 || line_out == nullptr) {
        return false;
    }
    *line_out = nullptr;
    if (byte == '\r') {
        return false;
    }
    if (byte == '\n') {
        buffer_[length_] = '\0';
        length_ = 0;
        if (buffer_[0] == '\0') {
            return false;
        }
        *line_out = buffer_;
        return true;
    }
    if (length_ < capacity_ - 1) {
        buffer_[length_++] = static_cast<char>(byte);
    } else {
        length_ = 0;
    }
    return false;
}

bool AtParser::is_ok(const char* line) {
    return line != nullptr && std::strcmp(line, "OK") == 0;
}

bool AtParser::is_error(const char* line) {
    return line != nullptr && std::strcmp(line, "ERROR") == 0;
}

bool AtParser::is_cme_error(const char* line) {
    return line != nullptr && std::strncmp(line, "+CME ERROR", 10) == 0;
}

bool AtParser::looks_like_urc(const char* line) {
    return line != nullptr && line[0] == '+' && std::strstr(line, ":") != nullptr;
}

void mask_secret(char* text) {
    if (text == nullptr) {
        return;
    }
    int digits = 0;
    for (char* p = text; *p != '\0'; ++p) {
        if (*p >= '0' && *p <= '9') {
            ++digits;
        }
    }
    if (digits < 8) {
        return;
    }
    int seen = 0;
    for (char* p = text; *p != '\0'; ++p) {
        if (*p >= '0' && *p <= '9') {
            ++seen;
            if (seen > 3 && seen + 2 < digits) {
                *p = '*';
            }
        }
    }
}

}  // namespace cellular
}  // namespace iotpoc
