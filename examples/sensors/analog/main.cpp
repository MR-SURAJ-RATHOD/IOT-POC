#include <Arduino.h>

#include "iotpoc/hal/adc.h"
#include "iotpoc/hal/board.h"
#include "iotpoc/sensors/analog.h"

using iotpoc::hal::adc_read_raw;
using iotpoc::hal::board_init_serial;
using iotpoc::sensors::AnalogVoltageSensor;
using iotpoc::sensors::SensorReading;

static AnalogVoltageSensor sensor("adc34", 34, 3.3f, 4095);

void setup() {
    board_init_serial();
    sensor.init();
    sensor.set_raw_reader(adc_read_raw);
    Serial.println("[example] analog voltage on GPIO 34");
}

void loop() {
    SensorReading reading;
    if (sensor.read(reading)) {
        Serial.print("V=");
        Serial.println(reading.value, 3);
    }
    delay(1000);
}
