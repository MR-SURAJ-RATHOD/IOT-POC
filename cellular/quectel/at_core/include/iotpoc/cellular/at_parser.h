#pragma once

#include <stddef.h>
#include <stdint.h>

namespace iotpoc {
namespace cellular {

class AtParser {
public:
    AtParser(char* buffer, size_t capacity);
    void reset();
    bool feed(uint8_t byte, char** line_out);
    static bool is_ok(const char* line);
    static bool is_error(const char* line);
    static bool is_cme_error(const char* line);
    static bool looks_like_urc(const char* line);

private:
    char* buffer_;
    size_t capacity_;
    size_t length_;
};

void mask_secret(char* text);

}  // namespace cellular
}  // namespace iotpoc
