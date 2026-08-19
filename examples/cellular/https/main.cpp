#include <Arduino.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/https.h"
#include "iotpoc/hal/arduino_uart.h"
#include "iotpoc/hal/board.h"
#include "iotpoc_config.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::https_configure_tls_placeholder;
using iotpoc::hal::ArduinoUart;
using iotpoc::hal::board_init_serial;

static char line_buf[256];
static char resp[128];

void setup() {
    board_init_serial();
    ArduinoUart uart(Serial2, IOTPOC_MODEM_UART_RX_PIN, IOTPOC_MODEM_UART_TX_PIN, IOTPOC_MODEM_UART_BAUD);
    uart.begin();
    AtClient client(uart, line_buf, sizeof(line_buf));
    Serial.println("[example] HTTPS TLS context placeholder — do not commit private certificates");
    Serial.println(IOTPOC_HTTPS_URL);
    (void)https_configure_tls_placeholder(client, resp, sizeof(resp), 3000);
}

void loop() {
    delay(10000);
}
