#pragma once

#include <Arduino.h>

namespace iotpoc {
namespace hal {

/**
 * STM32 board bring-up (Arduino-STM32 / PlatformIO ststm32).
 * CHANGE: LED pin for your Nucleo / Blue Pill / custom PCB.
 */
class Stm32Board {
public:
    static void begin(uint32_t serial_baud = 115200);
    static void heartbeat();
    static const char* platform_name();
};

}  // namespace hal
}  // namespace iotpoc
