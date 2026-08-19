#pragma once

#include "iotpoc/hal/spi.h"

namespace iotpoc {
namespace comm {

inline bool spi_transfer(hal::ISpiBus& bus, uint8_t* buffer, size_t length) {
    if (buffer == nullptr && length > 0) {
        return false;
    }
    return bus.transfer(buffer, length);
}

}  // namespace comm
}  // namespace iotpoc
