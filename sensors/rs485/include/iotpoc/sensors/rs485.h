#pragma once

#include "iotpoc/comm/modbus_rtu.h"
#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

class ModbusHoldingSensor : public ISensor {
public:
    ModbusHoldingSensor(const char* id, uint8_t slave, uint16_t address);
    bool init() override;
    bool read(SensorReading& out) override;
    SensorMetadata metadata() const override;
    void inject_register(uint16_t value);
    bool build_request(uint8_t* out, size_t out_size, size_t* out_len) const;

private:
    const char* id_;
    uint8_t slave_;
    uint16_t address_;
    uint16_t value_;
    bool ready_;
};

}  // namespace sensors
}  // namespace iotpoc
