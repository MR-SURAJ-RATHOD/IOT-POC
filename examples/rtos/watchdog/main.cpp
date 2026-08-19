/**
 * Task watchdog: init 8 s, add this task, feed every 1 s.
 * Comment out watchdog_feed() once to see a reset (reset reason = watchdog).
 * Build: pio run -e example_rtos_watchdog
 */

#include <Arduino.h>

#include "iotpoc/hal/watchdog.h"

using iotpoc::hal::watchdog_add_current_task;
using iotpoc::hal::watchdog_feed;
using iotpoc::hal::watchdog_init;

void setup() {
    Serial.begin(115200);
    delay(200);
    watchdog_init(8000);
    watchdog_add_current_task();
    Serial.println("[example] feeding task watchdog");
}

void loop() {
    watchdog_feed();
    Serial.println("[wdt] feed");
    delay(1000);
}
