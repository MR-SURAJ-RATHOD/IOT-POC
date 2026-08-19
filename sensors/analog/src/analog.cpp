#include "iotpoc/sensors/analog.h"

namespace iotpoc {
namespace sensors {

float analog_raw_to_volts(int raw, float vref, int max_raw) {
    if (max_raw <= 0) {
        return 0.0f;
    }
    if (raw < 0) {
        raw = 0;
    }
    if (raw > max_raw) {
        raw = max_raw;
    }
    return (static_cast<float>(raw) / static_cast<float>(max_raw)) * vref;
}

AnalogVoltageSensor::AnalogVoltageSensor(const char* id, int pin, float vref, int max_raw)
    : id_(id),
      pin_(pin),
      vref_(vref),
      max_raw_(max_raw),
      reader_(nullptr),
      injected_raw_(0),
      use_injected_(false),
      ready_(false) {}

bool AnalogVoltageSensor::init() {
    ready_ = true;
    return true;
}

void AnalogVoltageSensor::set_raw_reader(int (*reader)(int pin)) {
    reader_ = reader;
    use_injected_ = false;
}

void AnalogVoltageSensor::inject_raw(int raw) {
    injected_raw_ = raw;
    use_injected_ = true;
}

bool AnalogVoltageSensor::read(SensorReading& out) {
    out.sensor_id = id_;
    out.quantity = Quantity::Voltage;
    out.unit = "V";
    out.timestamp_ms = 0;
    if (!ready_) {
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = SensorError::NotInitialized;
        return false;
    }
    int raw = injected_raw_;
    if (!use_injected_) {
        if (reader_ == nullptr) {
            out.value = 0;
            out.quality = Quality::Invalid;
            out.error = SensorError::Unsupported;
            return false;
        }
        raw = reader_(pin_);
    }
    out.value = analog_raw_to_volts(raw, vref_, max_raw_);
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    return true;
}

SensorMetadata AnalogVoltageSensor::metadata() const {
    SensorMetadata meta;
    meta.sensor_id = id_;
    meta.category = "analog";
    meta.bus = "adc";
    return meta;
}

}  // namespace sensors
}  // namespace iotpoc
