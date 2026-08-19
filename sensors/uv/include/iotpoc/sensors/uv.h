#pragma once

#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

class UvIndexSensor : public ISensor {
public:
    explicit UvIndexSensor(const char* id);
    bool init() override;
    bool read(SensorReading& out) override;
    SensorMetadata metadata() const override;
    void inject_index(float index);

private:
    const char* id_;
    float index_;
    bool ready_;
};

}  // namespace sensors
}  // namespace iotpoc
