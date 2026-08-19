#pragma once

#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

class TippingCountSensor : public ISensor {
public:
    TippingCountSensor(const char* id, float mm_per_tip);
    bool init() override;
    bool read(SensorReading& out) override;
    SensorMetadata metadata() const override;
    void add_tips(uint32_t tips);

private:
    const char* id_;
    float mm_per_tip_;
    uint32_t tips_;
    bool ready_;
};

}  // namespace sensors
}  // namespace iotpoc
