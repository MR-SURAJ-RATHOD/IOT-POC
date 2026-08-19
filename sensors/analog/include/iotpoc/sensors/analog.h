#pragma once

#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

/**
 * Convert ADC counts to volts. ESP32 default is often 12-bit (0..4095) and ~3.3 V.
 * Calibrate vref on your board; this is not factory-accurate.
 */
float analog_raw_to_volts(int raw, float vref, int max_raw);

/**
 * Analog voltage as ISensor.
 *
 * On device: analog.set_raw_reader(iotpoc::hal::adc_read_raw);
 * In native tests: analog.inject_raw(2048);  // no hardware
 *
 * CHANGE the GPIO pin in the constructor (example uses ADC1 GPIO 34).
 * Avoid ADC2 pins while Wi-Fi is on.
 */
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
