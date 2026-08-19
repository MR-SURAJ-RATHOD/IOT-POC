/**
 * I2C temperature/humidity CATEGORY driver (register map example, not a vendor SDK).
 * CHANGE: address 0x44, registers 0x00/0x02, and Wire pins (default SDA 21 / SCL 22).
 * Bus errors on Serial are expected if no device is attached.
 * Build: pio run -e example_sensor_temp_humidity
 */

#include <Arduino.h>

#include "iotpoc/comm/i2c_register.h"
#include "iotpoc/hal/arduino_i2c.h"
#include "iotpoc/hal/board.h"
#include "iotpoc/sensors/temperature_humidity.h"

using iotpoc::comm::I2cRegisterDevice;
using iotpoc::hal::ArduinoI2c;
using iotpoc::hal::board_init_serial;
using iotpoc::sensors::I2cTempHumiditySensor;
using iotpoc::sensors::SensorReading;

static ArduinoI2c i2c;
static I2cRegisterDevice device(i2c, 0x44);
static I2cTempHumiditySensor sensor("th0", device, 0x00, 0x02);

void setup() {
    board_init_serial();
    i2c.begin();
    sensor.init();
    Serial.println("[example] I2C temperature/humidity category driver (register map is an example)");
}

void loop() {
    SensorReading reading;
    if (sensor.read(reading)) {
        Serial.print("T=");
        Serial.println(reading.value, 2);
    } else {
        Serial.println("bus error (expected if no device is attached)");
    }
    delay(2000);
}
