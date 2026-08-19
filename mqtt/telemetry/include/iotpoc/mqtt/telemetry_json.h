#pragma once

#include <stddef.h>

#include "iotpoc/sensors/sensor_types.h"

namespace iotpoc {
namespace mqtt {

/**
 * Builds a small JSON object with "schema":1 so cloud parsers can version the payload.
 * CHANGE field names here if you must match an existing broker schema — keep schema bump.
 */
bool build_telemetry_json(const sensors::SensorReading& reading,
                          const char* device_id,
                          char* out,
                          size_t out_size);

}  // namespace mqtt
}  // namespace iotpoc
