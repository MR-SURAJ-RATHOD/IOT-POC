#pragma once

#include "iotpoc/comm/i2c_register.h"
#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

class I2cRtcSensor : public ISensor {
public:
    I2cRtcSensor(const char* id, comm::I2cRegisterDevice& device, uint8_t epoch_reg);
    bool init() override;
    bool read(SensorReading& out) override;
    SensorMetadata metadata() const override;

private:
    const char* id_;
    comm::I2cRegisterDevice& device_;
    uint8_t epoch_reg_;
    bool ready_;
};

}  // namespace sensors
}  // namespace iotpoc
