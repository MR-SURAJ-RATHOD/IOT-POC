#pragma once

#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

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
