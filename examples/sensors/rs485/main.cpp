#include <Arduino.h>

#include "iotpoc/comm/modbus_rtu.h"
#include "iotpoc/hal/board.h"
#include "iotpoc/sensors/rs485.h"

using iotpoc::comm::modbus_crc_ok;
using iotpoc::hal::board_init_serial;
using iotpoc::sensors::ModbusHoldingSensor;

static ModbusHoldingSensor sensor("rs485_0", 1, 0x0001);
static uint8_t adu[8];

void setup() {
    board_init_serial();
    sensor.init();
    size_t len = 0;
    if (sensor.build_request(adu, sizeof(adu), &len)) {
        Serial.print("[example] Modbus RTU read-holding ADU, crc_ok=");
        Serial.println(modbus_crc_ok(adu, len) ? "yes" : "no");
    }
    sensor.inject_register(1234);
}

void loop() {
    iotpoc::sensors::SensorReading reading;
    sensor.read(reading);
    Serial.print("register=");
    Serial.println(reading.value);
    delay(2000);
}
