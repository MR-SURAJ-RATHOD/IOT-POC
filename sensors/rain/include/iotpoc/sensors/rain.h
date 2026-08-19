#pragma once

#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

/**
 * Tipping-bucket style counter (rain gauge or any pulse totaliser).
 * CHANGE mm_per_tip to your bucket volume. add_tips() from an ISR.
 */
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
