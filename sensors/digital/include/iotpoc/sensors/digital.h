#pragma once

#include "iotpoc/hal/gpio.h"
#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

/**
 * GPIO output helper used by the relay POC.
 *
 * @param pin         ESP32 GPIO number (change IOTPOC_RELAY1_PIN in config.local.h).
 * @param active_low  true for typical relay modules: electrical LOW = coil ON.
 *
 * init(true) forces the OFF state at boot so a floating pin does not click the relay.
 */
class DigitalOutput {
public:
    DigitalOutput(int pin, bool active_low);
    void init(bool start_off = true);
    void set(bool on);
    bool is_on() const;
    int pin() const { return pin_; }

private:
    int pin_;
    bool active_low_;
    bool on_;
};

/** Digital input as ISensor (quantity DigitalState, value 0.0 or 1.0). */
class DigitalInputSensor : public ISensor {
public:
    DigitalInputSensor(const char* id, int pin, bool pullup);
    bool init() override;
    bool read(SensorReading& out) override;
    SensorMetadata metadata() const override;

private:
    const char* id_;
    int pin_;
    bool pullup_;
    bool ready_;
};

}  // namespace sensors
}  // namespace iotpoc
