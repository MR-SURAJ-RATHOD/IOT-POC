#pragma once

#include "iotpoc/sensors/sensor_types.h"

namespace iotpoc {
namespace sensors {

/**
 * Shared driver contract. Every sensor/actuator *input* in this repo implements this.
 *
 * How to add a new sensor:
 *   1. Create a class that inherits ISensor.
 *   2. Inject bus/pin handles in the constructor (do not hard-code Wire/GPIO inside).
 *   3. Fill SensorReading in read() — never throw; set error/quality instead.
 *
 * Application code should talk to ISensor*, not to a specific chip type.
 */
class ISensor {
public:
    virtual ~ISensor() {}
    /** Prepare the bus/pin. Return false if the device cannot start. */
    virtual bool init() = 0;
    /** Fill `out` with one sample. Return false on hard failure. */
    virtual bool read(SensorReading& out) = 0;
    virtual SensorMetadata metadata() const = 0;
    virtual bool reset() { return true; }
};

}  // namespace sensors
}  // namespace iotpoc
