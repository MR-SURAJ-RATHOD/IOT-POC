#include "iotpoc/mqtt/commands.h"

#include <cstdlib>
#include <cstring>

namespace iotpoc {
namespace mqtt {

ConfigKey parse_config_key(const char* payload) {
    if (payload == nullptr) {
        return ConfigKey::Unknown;
    }
    if (std::strstr(payload, "interval_ms") != nullptr) {
        return ConfigKey::IntervalMs;
    }
    if (std::strstr(payload, "device_id") != nullptr) {
        return ConfigKey::DeviceId;
    }
    return ConfigKey::Unknown;
}

commands::RelayCommand parse_command_payload(const char* payload) {
    return commands::parse_relay_command(payload);
}

}  // namespace mqtt
}  // namespace iotpoc
