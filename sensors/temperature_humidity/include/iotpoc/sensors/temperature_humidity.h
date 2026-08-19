#pragma once

#include "iotpoc/comm/i2c_register.h"
#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

/**
 * Category example: I2C 16-bit temperature (int16/100 °C) and humidity (uint16/100 %RH).
 * This is a REGISTER MAP PATTERN, not a copy of a vendor SHT/BME driver.
 *
 * CHANGE: I2C address (example 0x44), temp_reg, humidity_reg to match YOUR chip datasheet.
 */
public:
    I2cTempHumiditySensor(const char* id,
                          comm::I2cRegisterDevice& device,
                          uint8_t temp_reg,
                          uint8_t humidity_reg);
    bool init() override;
    bool read(SensorReading& out) override;
    SensorMetadata metadata() const override;
    bool read_humidity(SensorReading& out);

private:
    const char* id_;
    comm::I2cRegisterDevice& device_;
    uint8_t temp_reg_;
    uint8_t humidity_reg_;
    bool ready_;
    bool last_was_humidity_;
};

}  // namespace sensors
}  // namespace iotpoc
