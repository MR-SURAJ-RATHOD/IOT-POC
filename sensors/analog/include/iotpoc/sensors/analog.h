#pragma once

#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

float analog_raw_to_volts(int raw, float vref, int max_raw);

class AnalogVoltageSensor : public ISensor {
public:
    AnalogVoltageSensor(const char* id, int pin, float vref, int max_raw);
    bool init() override;
    bool read(SensorReading& out) override;
    SensorMetadata metadata() const override;

    void set_raw_reader(int (*reader)(int pin));
    void inject_raw(int raw);

private:
    const char* id_;
    int pin_;
    float vref_;
    int max_raw_;
    int (*reader_)(int);
    int injected_raw_;
    bool use_injected_;
    bool ready_;
};

}  // namespace sensors
}  // namespace iotpoc
