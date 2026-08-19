#pragma once

#include <Wire.h>
#include "iotpoc/hal/i2c.h"

namespace iotpoc {
namespace hal {

/**
 * Arduino Wire adapter. Default Wire is SDA=21 SCL=22 on many ESP32 DevKits.
 * Pass another TwoWire if you use a second I2C bus.
 */
class ArduinoI2c : public II2cBus {
public:
    explicit ArduinoI2c(TwoWire& wire = Wire);
    bool begin();
    bool write(uint8_t address, const uint8_t* data, size_t length) override;
    bool read(uint8_t address, uint8_t* data, size_t length) override;
    bool write_then_read(uint8_t address,
                         const uint8_t* tx,
                         size_t tx_len,
                         uint8_t* rx,
                         size_t rx_len) override;

private:
    TwoWire& wire_;
};

}  // namespace hal
}  // namespace iotpoc
