#include "iotpoc/commands/relay_command.h"

#include <cctype>
#include <cstring>

namespace iotpoc {
namespace commands {
namespace {

void trim_copy(const char* in, char* out, int out_size) {
    if (in == nullptr || out == nullptr || out_size <= 0) {
        return;
    }
    while (*in != '\0' && std::isspace(static_cast<unsigned char>(*in))) {
        ++in;
    }
    int n = 0;
    while (in[n] != '\0' && n < out_size - 1) {
        ++n;
    }
    while (n > 0 && std::isspace(static_cast<unsigned char>(in[n - 1]))) {
        --n;
    }
    for (int i = 0; i < n; ++i) {
        out[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(in[i])));
    }
    out[n] = '\0';
}

}  // namespace

RelayCommand parse_relay_command(const char* line) {
    char buf[16];
    trim_copy(line, buf, static_cast<int>(sizeof(buf)));
    if (std::strcmp(buf, "ON1") == 0) {
        return RelayCommand::On1;
    }
    if (std::strcmp(buf, "OFF1") == 0) {
        return RelayCommand::Off1;
    }
    if (std::strcmp(buf, "ON2") == 0) {
        return RelayCommand::On2;
    }
    if (std::strcmp(buf, "OFF2") == 0) {
        return RelayCommand::Off2;
    }
    return RelayCommand::Invalid;
}

const char* relay_command_name(RelayCommand command) {
    switch (command) {
        case RelayCommand::On1:
            return "ON1";
        case RelayCommand::Off1:
            return "OFF1";
        case RelayCommand::On2:
            return "ON2";
        case RelayCommand::Off2:
            return "OFF2";
        default:
            return "INVALID";
    }
}

bool relay_command_is_on(RelayCommand command) {
    return command == RelayCommand::On1 || command == RelayCommand::On2;
}

int relay_command_channel(RelayCommand command) {
    switch (command) {
        case RelayCommand::On1:
        case RelayCommand::Off1:
            return 1;
        case RelayCommand::On2:
        case RelayCommand::Off2:
            return 2;
        default:
            return 0;
    }
}

}  // namespace commands
}  // namespace iotpoc
