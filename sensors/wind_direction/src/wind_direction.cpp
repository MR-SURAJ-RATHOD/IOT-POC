#include "iotpoc/sensors/wind_direction.h"

namespace iotpoc {
namespace sensors {

AnalogAngleSensor::AnalogAngleSensor(const char* id, float degrees_at_full_scale)
    : id_(id), degrees_at_full_scale_(degrees_at_full_scale), fraction_(0), ready_(false) {}

bool AnalogAngleSensor::init() {
    ready_ = true;
    return true;
}

void AnalogAngleSensor::inject_fraction(float fraction) {
    if (fraction < 0.0f) {
        fraction = 0.0f;
    }
    if (fraction > 1.0f) {
        fraction = 1.0f;
    }
    fraction_ = fraction;
}

bool AnalogAngleSensor::read(SensorReading& out) {
    out.sensor_id = id_;
    out.quantity = Quantity::AngleDeg;
    out.unit = "deg";
    out.timestamp_ms = 0;
    if (!ready_) {
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = SensorError::NotInitialized;
        return false;
    }
    out.value = fraction_ * degrees_at_full_scale_;
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    return true;
}

SensorMetadata AnalogAngleSensor::metadata() const {
    SensorMetadata meta;
    meta.sensor_id = id_;
    meta.category = "wind_direction";
    meta.bus = "analog";
    return meta;
}

}  // namespace sensors
}  // namespace iotpoc
