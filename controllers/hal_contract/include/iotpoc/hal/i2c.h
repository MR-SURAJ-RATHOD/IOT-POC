#pragma once

#include <stddef.h>
#include <stdint.h>

namespace iotpoc {
namespace hal {

/**
 * Injected I2C bus. Sensor drivers take II2cBus& so they can be unit-tested
 * with a fake bus (see AnalogVoltageSensor::inject_raw for the same idea).
 */
class II2cBus {
public:
    virtual ~II2cBus() {}
    virtual bool write(uint8_t address, const uint8_t* data, size_t length) = 0;
    virtual bool read(uint8_t address, uint8_t* data, size_t length) = 0;
    virtual bool write_then_read(uint8_t address,
                                 const uint8_t* tx,
                                 size_t tx_len,
                                 uint8_t* rx,
                                 size_t rx_len) = 0;
};

}  // namespace hal
}  // namespace iotpoc
