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
