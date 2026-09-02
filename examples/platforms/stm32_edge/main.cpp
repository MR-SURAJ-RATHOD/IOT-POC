/*
 * STM32 edge starter — proves PlatformIO + stm32_hal build.
 * Extend with sensors (ISensor), Modbus, or MQTT bridge as needed.
 *
 * Build: cd firmware && pio run -e example_stm32_edge
 */

#include <Arduino.h>
#include "iotpoc/hal/stm32_board.h"

void setup() {
    iotpoc::hal::Stm32Board::begin(115200);
    Serial.println("IOT-POC STM32 edge starter");
    Serial.println(iotpoc::hal::Stm32Board::platform_name());
}

void loop() {
    iotpoc::hal::Stm32Board::heartbeat();
    delay(500);
}
