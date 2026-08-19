#include "iotpoc/hal/arduino_uart.h"

#include <Arduino.h>

namespace iotpoc {
namespace hal {

ArduinoUart::ArduinoUart(HardwareSerial& port, int rx_pin, int tx_pin, uint32_t baud)
    : port_(port), rx_pin_(rx_pin), tx_pin_(tx_pin), baud_(baud), started_(false) {}

bool ArduinoUart::begin() {
    port_.begin(baud_, SERIAL_8N1, rx_pin_, tx_pin_);
    started_ = true;
    return true;
}

bool ArduinoUart::write_bytes(const uint8_t* data, size_t length) {
    if (!started_ || data == nullptr) {
        return false;
    }
    return port_.write(data, length) == length;
}

int ArduinoUart::read_byte(uint32_t timeout_ms) {
    if (!started_) {
        return -1;
    }
    const uint32_t start = millis();
    while (millis() - start < timeout_ms) {
        if (port_.available() > 0) {
            return port_.read();
        }
        delay(1);
    }
    return -1;
}

void ArduinoUart::flush_input() {
    if (!started_) {
        return;
    }
    while (port_.available() > 0) {
        (void)port_.read();
    }
}

}  // namespace hal
}  // namespace iotpoc
