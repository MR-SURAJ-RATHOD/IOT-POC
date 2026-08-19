#include "iotpoc/sensors/digital.h"

namespace iotpoc {
namespace sensors {

DigitalOutput::DigitalOutput(int pin, bool active_low)
    : pin_(pin), active_low_(active_low), on_(false) {}

void DigitalOutput::init(bool start_off) {
    hal::gpio_set_mode(pin_, hal::PinModeKind::Output);
    set(!start_off);
}

void DigitalOutput::set(bool on) {
    on_ = on;
    /* Active-low module: coil ON means drive the pin LOW. */
    const bool high = active_low_ ? !on : on;
    hal::gpio_write(pin_, high ? hal::PinLevel::High : hal::PinLevel::Low);
}

bool DigitalOutput::is_on() const {
    return on_;
}

DigitalInputSensor::DigitalInputSensor(const char* id, int pin, bool pullup)
    : id_(id), pin_(pin), pullup_(pullup), ready_(false) {}

bool DigitalInputSensor::init() {
    hal::gpio_set_mode(pin_, pullup_ ? hal::PinModeKind::InputPullup : hal::PinModeKind::Input);
    ready_ = true;
    return true;
}

bool DigitalInputSensor::read(SensorReading& out) {
    out.sensor_id = id_;
    out.quantity = Quantity::DigitalState;
    out.unit = "bool";
    out.timestamp_ms = 0;
    if (!ready_) {
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = SensorError::NotInitialized;
        return false;
    }
    const bool high = hal::gpio_read(pin_) == hal::PinLevel::High;
    out.value = high ? 1.0f : 0.0f;
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    return true;
}

SensorMetadata DigitalInputSensor::metadata() const {
    SensorMetadata meta;
    meta.sensor_id = id_;
    meta.category = "digital";
    meta.bus = "gpio";
    return meta;
}

}  // namespace sensors
}  // namespace iotpoc
