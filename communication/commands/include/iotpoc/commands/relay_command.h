#pragma once

namespace iotpoc {
namespace commands {

/**
 * Text commands shared by USB serial AND MQTT payloads.
 * Keep this parser the single source of truth so ON1 on serial matches ON1 on MQTT.
 *
 * Accepted (case-insensitive, surrounding spaces ignored): ON1 OFF1 ON2 OFF2
 */
enum class RelayCommand {
    On1,
    Off1,
    On2,
    Off2,
    Invalid
};

RelayCommand parse_relay_command(const char* line);
const char* relay_command_name(RelayCommand command);
bool relay_command_is_on(RelayCommand command);
/** 1 or 2 for valid commands, 0 for Invalid. */
int relay_command_channel(RelayCommand command);

}  // namespace commands
}  // namespace iotpoc
