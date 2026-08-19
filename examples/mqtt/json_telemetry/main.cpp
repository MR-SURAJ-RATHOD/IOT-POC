#include <Arduino.h>

#include "iotpoc/hal/board.h"
#include "iotpoc/mqtt/telemetry_json.h"
#include "iotpoc/sensors/sensor_types.h"
#include "iotpoc_config.h"

using iotpoc::hal::board_init_serial;
using iotpoc::mqtt::build_telemetry_json;
using iotpoc::sensors::Quality;
using iotpoc::sensors::Quantity;
using iotpoc::sensors::SensorError;
using iotpoc::sensors::SensorReading;

static char json[192];

void setup() {
    board_init_serial();
    SensorReading reading;
    reading.sensor_id = "demo";
    reading.quantity = Quantity::Voltage;
    reading.value = 3.141f;
    reading.unit = "V";
    reading.quality = Quality::Ok;
    reading.timestamp_ms = 0;
    reading.error = SensorError::None;
    build_telemetry_json(reading, IOTPOC_DEVICE_ID, json, sizeof(json));
    Serial.println(json);
}

void loop() {
    delay(5000);
}
