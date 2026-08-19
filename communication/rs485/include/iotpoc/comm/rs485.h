#pragma once

#include <stddef.h>
#include <stdint.h>

#include "iotpoc/hal/uart.h"

namespace iotpoc {
namespace comm {

class IDirectionPin {
public:
    virtual ~IDirectionPin() {}
    virtual void set_transmit(bool enable) = 0;
};

class Rs485Port {
public:
    Rs485Port(hal::IUart& uart, IDirectionPin& direction);
    bool write_frame(const uint8_t* data, size_t length);
    int read_byte(uint32_t timeout_ms);

private:
    hal::IUart& uart_;
    IDirectionPin& direction_;
};

}  // namespace comm
}  // namespace iotpoc
