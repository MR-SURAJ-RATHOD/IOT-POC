#include "iotpoc/sensors/uv.h"

namespace iotpoc {
namespace sensors {

UvIndexSensor::UvIndexSensor(const char* id) : id_(id), index_(0), ready_(false) {}

bool UvIndexSensor::init() {
    ready_ = true;
    return true;
}

void UvIndexSensor::inject_index(float index) {
    index_ = index;
}

bool UvIndexSensor::read(SensorReading& out) {
    out.sensor_id = id_;
    out.quantity = Quantity::UvIndex;
    out.unit = "UVI";
    out.timestamp_ms = 0;
    if (!ready_) {
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = SensorError::NotInitialized;
        return false;
    }
    out.value = index_;
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    return true;
}

SensorMetadata UvIndexSensor::metadata() const {
    SensorMetadata meta;
    meta.sensor_id = id_;
    meta.category = "uv";
    meta.bus = "analog";
    return meta;
}

}  // namespace sensors
}  // namespace iotpoc
