#include <Arduino.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/at_parser.h"
#include "iotpoc/hal/arduino_uart.h"
#include "iotpoc/hal/board.h"
#include "iotpoc_config.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::AtParser;
using iotpoc::cellular::AtStatus;
using iotpoc::cellular::at_status_name;
using iotpoc::hal::ArduinoUart;
using iotpoc::hal::board_init_serial;

static char line_buf[256];
static char resp[128];

void setup() {
    board_init_serial();
    ArduinoUart uart(Serial2, IOTPOC_MODEM_UART_RX_PIN, IOTPOC_MODEM_UART_TX_PIN, IOTPOC_MODEM_UART_BAUD);
    uart.begin();
    AtClient client(uart, line_buf, sizeof(line_buf));
    const AtStatus st = client.send_command("AT", resp, sizeof(resp), 1000);
    Serial.print("[example] AT -> ");
    Serial.println(at_status_name(st));
    Serial.print("parser OK token is_ok=");
    Serial.println(AtParser::is_ok("OK") ? "true" : "false");
}

void loop() {
    delay(5000);
}
