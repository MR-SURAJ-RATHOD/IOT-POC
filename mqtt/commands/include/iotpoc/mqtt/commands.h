#pragma once

#include "iotpoc/commands/relay_command.h"

namespace iotpoc {
namespace mqtt {

/**
 * Configuration keys in MQTT / USB payloads (example: interval_ms=2000).
 * Add new keys here and in parse_config_key() — keep payloads out of git.
 */
enum class ConfigKey {
    Unknown = 0,
    IntervalMs,
    DeviceId
};

ConfigKey parse_config_key(const char* payload);
/** Same ON1/OFF1 parser as the serial relay POC. */
commands::RelayCommand parse_command_payload(const char* payload);

}  // namespace mqtt
}  // namespace iotpoc
