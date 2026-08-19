#include <Arduino.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/at_parser.h"
#include "iotpoc/cellular/diagnostics.h"
#include "iotpoc/hal/arduino_uart.h"
#include "iotpoc/hal/board.h"
#include "iotpoc_config.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::mask_secret;
using iotpoc::cellular::query_firmware;
using iotpoc::cellular::query_manufacturer;
using iotpoc::hal::ArduinoUart;
using iotpoc::hal::board_init_serial;

static char line_buf[256];
static char resp[128];

void setup() {
    board_init_serial();
    ArduinoUart uart(Serial2, IOTPOC_MODEM_UART_RX_PIN, IOTPOC_MODEM_UART_TX_PIN, IOTPOC_MODEM_UART_BAUD);
    uart.begin();
    AtClient client(uart, line_buf, sizeof(line_buf));
    (void)query_manufacturer(client, resp, sizeof(resp), 2000);
    mask_secret(resp);
    Serial.print("[example] manufacturer=");
    Serial.println(resp);
    (void)query_firmware(client, resp, sizeof(resp), 2000);
    Serial.print("[example] firmware=");
    Serial.println(resp);
}

void loop() {
    delay(10000);
}
