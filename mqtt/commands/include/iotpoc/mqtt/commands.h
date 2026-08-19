#pragma once

#include "iotpoc/commands/relay_command.h"

namespace iotpoc {
namespace mqtt {

enum class ConfigKey {
    Unknown = 0,
    IntervalMs,
    DeviceId
};

ConfigKey parse_config_key(const char* payload);
commands::RelayCommand parse_command_payload(const char* payload);

}  // namespace mqtt
}  // namespace iotpoc
