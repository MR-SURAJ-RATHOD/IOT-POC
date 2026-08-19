#include "iotpoc/comm/line_framer.h"

namespace iotpoc {
namespace comm {

LineFramer::LineFramer(char* buffer, size_t capacity)
    : buffer_(buffer), capacity_(capacity), length_(0) {}

void LineFramer::reset() {
    length_ = 0;
    if (buffer_ != nullptr && capacity_ > 0) {
        buffer_[0] = '\0';
    }
}

bool LineFramer::feed(uint8_t byte, char** line_out) {
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

}  // namespace comm
}  // namespace iotpoc
