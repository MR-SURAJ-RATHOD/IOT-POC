#pragma once

#include "iotpoc/sensors/sensor_types.h"

namespace iotpoc {
namespace sensors {

class ISensor {
public:
    virtual ~ISensor() {}
    virtual bool init() = 0;
    virtual bool read(SensorReading& out) = 0;
    virtual SensorMetadata metadata() const = 0;
    virtual bool reset() { return true; }
};

}  // namespace sensors
}  // namespace iotpoc
