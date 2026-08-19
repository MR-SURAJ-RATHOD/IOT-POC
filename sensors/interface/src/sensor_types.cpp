#include "iotpoc/sensors/sensor_types.h"

namespace iotpoc {
namespace sensors {

const char* quantity_name(Quantity quantity) {
    switch (quantity) {
        case Quantity::Temperature:
            return "temperature";
        case Quantity::Humidity:
            return "humidity";
        case Quantity::Pressure:
            return "pressure";
        case Quantity::Voltage:
            return "voltage";
        case Quantity::PulseHz:
            return "pulse_hz";
        case Quantity::AngleDeg:
            return "angle_deg";
        case Quantity::Count:
            return "count";
        case Quantity::UvIndex:
            return "uv_index";
        case Quantity::DigitalState:
            return "digital_state";
        case Quantity::Timestamp:
            return "timestamp";
        case Quantity::Raw:
            return "raw";
        default:
            return "unknown";
    }
}

const char* quality_name(Quality quality) {
    switch (quality) {
        case Quality::Ok:
            return "ok";
        case Quality::Stale:
            return "stale";
        case Quality::Degraded:
            return "degraded";
        default:
            return "invalid";
    }
}

}  // namespace sensors
}  // namespace iotpoc
