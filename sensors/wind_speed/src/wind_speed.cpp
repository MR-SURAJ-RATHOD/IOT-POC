#include "iotpoc/sensors/wind_speed.h"

namespace iotpoc {
namespace sensors {

PulseFrequencySensor::PulseFrequencySensor(const char* id, float hz_per_unit)
    : id_(id), hz_per_unit_(hz_per_unit), pulses_(0), window_ms_(1000), ready_(false) {}

bool PulseFrequencySensor::init() {
    ready_ = true;
    return true;
}

void PulseFrequencySensor::inject_pulses(uint32_t pulses, uint32_t window_ms) {
    pulses_ = pulses;
    window_ms_ = window_ms == 0 ? 1 : window_ms;
}

bool PulseFrequencySensor::read(SensorReading& out) {
    out.sensor_id = id_;
    out.quantity = Quantity::PulseHz;
    out.unit = "Hz";
    out.timestamp_ms = 0;
    if (!ready_) {
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = SensorError::NotInitialized;
        return false;
    }
    const float hz = (static_cast<float>(pulses_) * 1000.0f) / static_cast<float>(window_ms_);
    out.value = (hz_per_unit_ > 0.0f) ? (hz / hz_per_unit_) : hz;
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    return true;
}

SensorMetadata PulseFrequencySensor::metadata() const {
    SensorMetadata meta;
    meta.sensor_id = id_;
    meta.category = "wind_speed";
    meta.bus = "pulse";
    return meta;
}

}  // namespace sensors
}  // namespace iotpoc
