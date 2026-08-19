#pragma once

namespace iotpoc {
namespace commands {

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
int relay_command_channel(RelayCommand command);

}  // namespace commands
}  // namespace iotpoc
