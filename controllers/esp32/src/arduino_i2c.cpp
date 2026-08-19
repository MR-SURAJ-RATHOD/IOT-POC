#include "iotpoc/hal/arduino_i2c.h"

namespace iotpoc {
namespace hal {

ArduinoI2c::ArduinoI2c(TwoWire& wire) : wire_(wire) {}

bool ArduinoI2c::begin() {
    wire_.begin();
    return true;
}

bool ArduinoI2c::write(uint8_t address, const uint8_t* data, size_t length) {
    if (data == nullptr && length > 0) {
        return false;
    }
    wire_.beginTransmission(address);
    if (length > 0) {
        wire_.write(data, length);
    }
    return wire_.endTransmission() == 0;
}

bool ArduinoI2c::read(uint8_t address, uint8_t* data, size_t length) {
    if (data == nullptr && length > 0) {
        return false;
    }
    const size_t got = wire_.requestFrom(static_cast<int>(address), static_cast<int>(length));
    if (got != length) {
        return false;
    }
    for (size_t i = 0; i < length; ++i) {
        data[i] = static_cast<uint8_t>(wire_.read());
    }
    return true;
}

bool ArduinoI2c::write_then_read(uint8_t address,
                                 const uint8_t* tx,
                                 size_t tx_len,
                                 uint8_t* rx,
                                 size_t rx_len) {
    if (!write(address, tx, tx_len)) {
        return false;
    }
    return read(address, rx, rx_len);
}

}  // namespace hal
}  // namespace iotpoc
