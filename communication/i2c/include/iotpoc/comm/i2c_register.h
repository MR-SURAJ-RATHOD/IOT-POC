#pragma once

#include <stddef.h>
#include <stdint.h>

#include "iotpoc/hal/i2c.h"

namespace iotpoc {
namespace comm {

class I2cRegisterDevice {
public:
    I2cRegisterDevice(hal::II2cBus& bus, uint8_t address);
    bool write_u8(uint8_t reg, uint8_t value);
    bool read_u8(uint8_t reg, uint8_t& value);
    bool read_u16_be(uint8_t reg, uint16_t& value);
    bool read_bytes(uint8_t reg, uint8_t* data, size_t length);

private:
    hal::II2cBus& bus_;
    uint8_t address_;
};

}  // namespace comm
}  // namespace iotpoc
