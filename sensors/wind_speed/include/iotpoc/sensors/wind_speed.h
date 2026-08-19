#pragma once

#include "iotpoc/sensors/sensor_interface.h"

namespace iotpoc {
namespace sensors {

/**
 * Pulse-frequency sensor (anemometer-style, also usable for flow meters).
 * inject_pulses() from an ISR counter; hz_per_unit converts Hz to engineering units.
 */
class PulseFrequencySensor : public ISensor {
public:
    PulseFrequencySensor(const char* id, float hz_per_unit);
    bool init() override;
    bool read(SensorReading& out) override;
    SensorMetadata metadata() const override;
    void inject_pulses(uint32_t pulses, uint32_t window_ms);

private:
    const char* id_;
    float hz_per_unit_;
    uint32_t pulses_;
    uint32_t window_ms_;
    bool ready_;
};

}  // namespace sensors
}  // namespace iotpoc
