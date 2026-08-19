#include "iotpoc/sensors/rain.h"

namespace iotpoc {
namespace sensors {

TippingCountSensor::TippingCountSensor(const char* id, float mm_per_tip)
    : id_(id), mm_per_tip_(mm_per_tip), tips_(0), ready_(false) {}

bool TippingCountSensor::init() {
    ready_ = true;
    return true;
}

void TippingCountSensor::add_tips(uint32_t tips) {
    tips_ += tips;
}

bool TippingCountSensor::read(SensorReading& out) {
    out.sensor_id = id_;
    out.quantity = Quantity::Count;
    out.unit = "mm";
    out.timestamp_ms = 0;
    if (!ready_) {
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = SensorError::NotInitialized;
        return false;
    }
    out.value = static_cast<float>(tips_) * mm_per_tip_;
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    return true;
}

SensorMetadata TippingCountSensor::metadata() const {
    SensorMetadata meta;
    meta.sensor_id = id_;
    meta.category = "rain";
    meta.bus = "pulse";
    return meta;
}

}  // namespace sensors
}  // namespace iotpoc
