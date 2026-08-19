#pragma once

#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

/**
 * Analog fraction 0..1 mapped to degrees (wind vane or potentiometer).
 * inject_fraction() from ADC/full-scale. CHANGE degrees_at_full_scale (often 360).
 */
class AnalogAngleSensor : public ISensor {
public:
    AnalogAngleSensor(const char* id, float degrees_at_full_scale);
    bool init() override;
    bool read(SensorReading& out) override;
    SensorMetadata metadata() const override;
    void inject_fraction(float fraction);

private:
    const char* id_;
    float degrees_at_full_scale_;
    float fraction_;
    bool ready_;
};

}  // namespace sensors
}  // namespace iotpoc
