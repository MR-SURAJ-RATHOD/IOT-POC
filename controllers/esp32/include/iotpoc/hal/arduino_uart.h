#pragma once

#include <HardwareSerial.h>
#include "iotpoc/hal/uart.h"

namespace iotpoc {
namespace hal {

/**
 * Arduino HardwareSerial adapter for the Quectel AT stack.
 *
 * Constructor argument order: (port, rx_pin, tx_pin, baud)
 * Wiring: ESP32 TX pin -> modem RX, ESP32 RX pin -> modem TX, shared GND.
 * Default pins: IOTPOC_MODEM_UART_RX_PIN / TX_PIN in config (example 16 / 17).
 *
 * Typical call:
 *   ArduinoUart uart(Serial2, RX, TX, 115200);
 *   uart.begin();
 */
class ArduinoUart : public IUart {
public:
    ArduinoUart(HardwareSerial& port, int rx_pin, int tx_pin, uint32_t baud);
    bool begin();
    bool write_bytes(const uint8_t* data, size_t length) override;
    int read_byte(uint32_t timeout_ms) override;
    void flush_input() override;

private:
    HardwareSerial& port_;
    int rx_pin_;
    int tx_pin_;
    uint32_t baud_;
    bool started_;
};

}  // namespace hal
}  // namespace iotpoc
