#pragma once

#include <stddef.h>

#include "iotpoc/sensors/sensor_types.h"

namespace iotpoc {
namespace mqtt {

bool build_telemetry_json(const sensors::SensorReading& reading,
                          const char* device_id,
                          char* out,
                          size_t out_size);

}  // namespace mqtt
}  // namespace iotpoc
