/**
 * Exponential backoff delays printed on Serial (500, 1000, 2000, ... cap 8000 ms).
 * No broker required. Tune initial/max/multiplier in ExponentialBackoff(...).
 * Build: pio run -e example_mqtt_backoff
 */

#include <Arduino.h>

#include "iotpoc/hal/board.h"
#include "iotpoc/rtos/backoff.h"

using iotpoc::hal::board_init_serial;
using iotpoc::rtos::ExponentialBackoff;

void setup() {
    board_init_serial();
    ExponentialBackoff backoff(500, 8000, 2);
    for (int i = 0; i < 6; ++i) {
        Serial.print("[example] backoff_ms=");
        Serial.println(backoff.next_delay_ms());
    }
}

void loop() {
    delay(5000);
}
