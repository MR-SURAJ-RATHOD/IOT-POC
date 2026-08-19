#include "iotpoc/hal/gpio.h"

#include <Arduino.h>

namespace iotpoc {
namespace hal {

void gpio_set_mode(int pin, PinModeKind mode) {
    switch (mode) {
        case PinModeKind::Input:
            pinMode(pin, INPUT);
            break;
        case PinModeKind::Output:
            pinMode(pin, OUTPUT);
            break;
        case PinModeKind::InputPullup:
            pinMode(pin, INPUT_PULLUP);
            break;
    }
}

void gpio_write(int pin, PinLevel level) {
    digitalWrite(pin, level == PinLevel::High ? HIGH : LOW);
}

PinLevel gpio_read(int pin) {
    return digitalRead(pin) ? PinLevel::High : PinLevel::Low;
}

}  // namespace hal
}  // namespace iotpoc
