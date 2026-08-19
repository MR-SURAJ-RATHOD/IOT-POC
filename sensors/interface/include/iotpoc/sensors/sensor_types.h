#pragma once

#include <stdint.h>

namespace iotpoc {
namespace sensors {

enum class Quantity {
    Unknown = 0,
    Temperature,
    Humidity,
    Pressure,
    Voltage,
    PulseHz,
    AngleDeg,
    Count,
    UvIndex,
    DigitalState,
    Timestamp,
    Raw
};

enum class Quality {
    Ok = 0,
    Stale,
    Degraded,
    Invalid
};

enum class SensorError {
    None = 0,
    NotInitialized,
    Bus,
    Timeout,
    OutOfRange,
    Unsupported
};

struct SensorReading {
    const char* sensor_id;
    Quantity quantity;
    float value;
    const char* unit;
    Quality quality;
    uint32_t timestamp_ms;
    SensorError error;
};

struct SensorMetadata {
    const char* sensor_id;
    const char* category;
    const char* bus;
};

const char* quantity_name(Quantity quantity);
const char* quality_name(Quality quality);

}  // namespace sensors
}  // namespace iotpoc
