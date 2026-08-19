#pragma once

#include <stddef.h>
#include <stdint.h>

namespace iotpoc {
namespace hal {

enum class PinModeKind {
    Input = 0,
    Output,
    InputPullup
};

enum class PinLevel {
    Low = 0,
    High = 1
};

void gpio_set_mode(int pin, PinModeKind mode);
void gpio_write(int pin, PinLevel level);
PinLevel gpio_read(int pin);

}  // namespace hal
}  // namespace iotpoc
