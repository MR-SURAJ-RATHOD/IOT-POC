#include "iotpoc/mqtt/telemetry_json.h"

#include <cstdio>

namespace iotpoc {
namespace mqtt {

bool build_telemetry_json(const sensors::SensorReading& reading,
                          const char* device_id,
                          char* out,
                          size_t out_size) {
    if (out == nullptr || device_id == nullptr || out_size < 32) {
        return false;
    }
    const char* sid = reading.sensor_id != nullptr ? reading.sensor_id : "unknown";
    const char* unit = reading.unit != nullptr ? reading.unit : "";
    const int n = std::snprintf(
        out,
        out_size,
        "{\"schema\":1,\"device\":\"%s\",\"sensor\":\"%s\",\"q\":\"%s\",\"value\":%.3f,\"unit\":\"%s\",\"quality\":\"%s\"}",
        device_id,
        sid,
        sensors::quantity_name(reading.quantity),
        static_cast<double>(reading.value),
        unit,
        sensors::quality_name(reading.quality));
    return n > 0 && static_cast<size_t>(n) < out_size;
}

}  // namespace mqtt
}  // namespace iotpoc
