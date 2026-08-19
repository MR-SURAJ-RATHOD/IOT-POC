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
