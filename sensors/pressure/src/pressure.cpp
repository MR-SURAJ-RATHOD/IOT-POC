#include "iotpoc/sensors/pressure.h"

namespace iotpoc {
namespace sensors {

I2cPressureSensor::I2cPressureSensor(const char* id, comm::I2cRegisterDevice& device, uint8_t pressure_reg)
    : id_(id), device_(device), pressure_reg_(pressure_reg), ready_(false) {}

bool I2cPressureSensor::init() {
    ready_ = true;
    return true;
}

bool I2cPressureSensor::read(SensorReading& out) {
    out.sensor_id = id_;
    out.quantity = Quantity::Pressure;
    out.unit = "Pa";
    out.timestamp_ms = 0;
    uint16_t raw = 0;
    if (!ready_ || !device_.read_u16_be(pressure_reg_, raw)) {
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = ready_ ? SensorError::Bus : SensorError::NotInitialized;
        return false;
    }
    out.value = static_cast<float>(raw) * 10.0f;
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    return true;
}

SensorMetadata I2cPressureSensor::metadata() const {
    SensorMetadata meta;
    meta.sensor_id = id_;
    meta.category = "pressure";
    meta.bus = "i2c";
    return meta;
}

}  // namespace sensors
}  // namespace iotpoc
