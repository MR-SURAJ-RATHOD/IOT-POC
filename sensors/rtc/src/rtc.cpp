#include "iotpoc/sensors/rtc.h"

namespace iotpoc {
namespace sensors {

I2cRtcSensor::I2cRtcSensor(const char* id, comm::I2cRegisterDevice& device, uint8_t epoch_reg)
    : id_(id), device_(device), epoch_reg_(epoch_reg), ready_(false) {}

bool I2cRtcSensor::init() {
    ready_ = true;
    return true;
}

bool I2cRtcSensor::read(SensorReading& out) {
    out.sensor_id = id_;
    out.quantity = Quantity::Timestamp;
    out.unit = "s";
    out.timestamp_ms = 0;
    uint16_t raw = 0;
    if (!ready_ || !device_.read_u16_be(epoch_reg_, raw)) {
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = ready_ ? SensorError::Bus : SensorError::NotInitialized;
        return false;
    }
    out.value = static_cast<float>(raw);
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    return true;
}

SensorMetadata I2cRtcSensor::metadata() const {
    SensorMetadata meta;
    meta.sensor_id = id_;
    meta.category = "rtc";
    meta.bus = "i2c";
    return meta;
}

}  // namespace sensors
}  // namespace iotpoc
