/**
 * Signal quality: AT+CSQ -> RSSI. 99 usually means unknown / no signal.
 * Build: pio run -e example_signal_quality
 */

#include <Arduino.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/network.h"
#include "iotpoc/hal/arduino_uart.h"
#include "iotpoc/hal/board.h"
#include "iotpoc_config.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::parse_rssi;
using iotpoc::cellular::query_signal;
using iotpoc::hal::ArduinoUart;
using iotpoc::hal::board_init_serial;

static char line_buf[256];
static char resp[128];

void setup() {
    board_init_serial();
    ArduinoUart uart(Serial2, IOTPOC_MODEM_UART_RX_PIN, IOTPOC_MODEM_UART_TX_PIN, IOTPOC_MODEM_UART_BAUD);
    uart.begin();
    AtClient client(uart, line_buf, sizeof(line_buf));
    (void)query_signal(client, resp, sizeof(resp), 2000);
    Serial.print("[example] rssi=");
    Serial.println(parse_rssi(resp));
    Serial.println(resp);
}

void loop() {
    delay(5000);
}
