/**
 * Digital input on GPIO 0 with pull-up (often the BOOT button on DevKit).
 * CHANGE the pin if GPIO 0 is awkward on your board.
 * Build: pio run -e example_sensor_digital
 */

#include <Arduino.h>

#include "iotpoc/hal/board.h"
#include "iotpoc/sensors/digital.h"

using iotpoc::hal::board_init_serial;
using iotpoc::sensors::DigitalInputSensor;
using iotpoc::sensors::SensorReading;

static DigitalInputSensor button("din0", 0, true);

void setup() {
    board_init_serial();
    button.init();
    Serial.println("[example] digital input GPIO 0 (pull-up)");
}

void loop() {
    SensorReading reading;
    if (button.read(reading)) {
        Serial.println(reading.value > 0.5f ? "HIGH" : "LOW");
    }
    delay(500);
}
