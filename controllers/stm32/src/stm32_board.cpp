#include "iotpoc/hal/stm32_board.h"

#ifndef IOTPOC_STM32_LED_PIN
#define IOTPOC_STM32_LED_PIN LED_BUILTIN
#endif

namespace iotpoc {
namespace hal {

void Stm32Board::begin(uint32_t serial_baud) {
    Serial.begin(serial_baud);
    pinMode(IOTPOC_STM32_LED_PIN, OUTPUT);
}

void Stm32Board::heartbeat() {
    static bool on = false;
    on = !on;
    digitalWrite(IOTPOC_STM32_LED_PIN, on ? HIGH : LOW);
}

const char* Stm32Board::platform_name() {
    return "STM32 (Arduino-STM32)";
}

}  // namespace hal
}  // namespace iotpoc
