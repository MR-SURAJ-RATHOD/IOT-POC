/**
 * Modem HTTP GET. URL: IOTPOC_HTTP_URL in config.local.h (public test host only).
 * Build: pio run -e example_http
 */

#include <Arduino.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/http.h"
#include "iotpoc/hal/arduino_uart.h"
#include "iotpoc/hal/board.h"
#include "iotpoc_config.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::http_get;
using iotpoc::cellular::http_set_url;
using iotpoc::hal::ArduinoUart;
using iotpoc::hal::board_init_serial;

static char line_buf[256];
static char resp[128];

void setup() {
    board_init_serial();
    ArduinoUart uart(Serial2, IOTPOC_MODEM_UART_RX_PIN, IOTPOC_MODEM_UART_TX_PIN, IOTPOC_MODEM_UART_BAUD);
    uart.begin();
    AtClient client(uart, line_buf, sizeof(line_buf));
    Serial.println("[example] HTTP GET via modem (URL is a placeholder)");
    (void)http_set_url(client, IOTPOC_HTTP_URL, resp, sizeof(resp), 3000);
    (void)http_get(client, resp, sizeof(resp), 8000);
}

void loop() {
    delay(10000);
}
