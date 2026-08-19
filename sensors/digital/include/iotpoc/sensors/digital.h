#pragma once

#include "iotpoc/hal/gpio.h"
#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

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
