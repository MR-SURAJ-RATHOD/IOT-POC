#include "iotpoc/comm/i2c_register.h"

namespace iotpoc {
namespace comm {

I2cRegisterDevice::I2cRegisterDevice(hal::II2cBus& bus, uint8_t address)
    : bus_(bus), address_(address) {}

bool I2cRegisterDevice::write_u8(uint8_t reg, uint8_t value) {
    uint8_t buf[2] = {reg, value};
    return bus_.write(address_, buf, 2);
}

bool I2cRegisterDevice::read_u8(uint8_t reg, uint8_t& value) {
    return bus_.write_then_read(address_, &reg, 1, &value, 1);
}

bool I2cRegisterDevice::read_u16_be(uint8_t reg, uint16_t& value) {
    uint8_t raw[2] = {0, 0};
    if (!read_bytes(reg, raw, 2)) {
        return false;
    }
    value = static_cast<uint16_t>((static_cast<uint16_t>(raw[0]) << 8) | raw[1]);
    return true;
}

bool I2cRegisterDevice::read_bytes(uint8_t reg, uint8_t* data, size_t length) {
    return bus_.write_then_read(address_, &reg, 1, data, length);
}

}  // namespace comm
}  // namespace iotpoc
