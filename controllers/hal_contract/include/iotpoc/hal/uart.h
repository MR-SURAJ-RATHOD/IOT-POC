#pragma once

#include <stddef.h>
#include <stdint.h>

namespace iotpoc {
namespace hal {

/**
 * Byte UART contract used by AtClient and RS-485.
 * Implement this on a new MCU instead of rewriting the AT parser.
 * read_byte() returns 0–255 or -1 on timeout.
 */
class IUart {
public:
    virtual ~IUart() {}
    virtual bool write_bytes(const uint8_t* data, size_t length) = 0;
    virtual int read_byte(uint32_t timeout_ms) = 0;
    virtual void flush_input() = 0;
};

}  // namespace hal
}  // namespace iotpoc
