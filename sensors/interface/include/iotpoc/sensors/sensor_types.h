#pragma once

#include <stdint.h>

namespace iotpoc {
namespace sensors {

/** Physical quantity. Weather-related values are one category among several. */
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

/** Sample health — telemetry JSON uses quality_name(). */
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

/**
 * One reading from any driver. `sensor_id` and `unit` are string literals
 * owned by the driver (do not free). timestamp_ms is 0 when the HAL has no clock.
 */
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
    const char* category; /* folder name, e.g. "analog" */
    const char* bus;      /* "gpio", "i2c", "adc", "modbus_rtu", "pulse" */
};

const char* quantity_name(Quantity quantity);
const char* quality_name(Quality quality);

}  // namespace sensors
}  // namespace iotpoc
