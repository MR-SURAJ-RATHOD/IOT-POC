#pragma once

#include "iotpoc/comm/i2c_register.h"
#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

class I2cTempHumiditySensor : public ISensor {
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
