#pragma once

#include <stddef.h>
#include <stdint.h>

namespace iotpoc {
namespace comm {

/** Newline-terminated ASCII lines (same idea as AtParser, for generic UART). */
class LineFramer {
public:
    explicit LineFramer(char* buffer, size_t capacity);
    void reset();
    bool feed(uint8_t byte, char** line_out);

private:
    char* buffer_;
    size_t capacity_;
    size_t length_;
};

}  // namespace comm
}  // namespace iotpoc
