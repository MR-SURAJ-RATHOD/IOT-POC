#include <Arduino.h>

#include "iotpoc/hal/adc.h"
#include "iotpoc/hal/board.h"
#include "iotpoc/mqtt/telemetry_json.h"
#include "iotpoc/sensors/analog.h"
#include "iotpoc_config.h"

using iotpoc::hal::adc_read_raw;
using iotpoc::hal::board_init_serial;
using iotpoc::mqtt::build_telemetry_json;
using iotpoc::sensors::AnalogVoltageSensor;
using iotpoc::sensors::SensorReading;

static AnalogVoltageSensor analog("adc0", 34, 3.3f, 4095);
static char json[192];

void setup() {
    board_init_serial();
    analog.init();
    analog.set_raw_reader(adc_read_raw);
    Serial.println("[poc] sensor_telemetry: analog reading -> JSON (MQTT publish is optional)");
}

void loop() {
    SensorReading reading;
    if (analog.read(reading)) {
        if (build_telemetry_json(reading, IOTPOC_DEVICE_ID, json, sizeof(json))) {
            Serial.println(json);
        }
    }
    delay(2000);
}
