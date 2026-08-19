/**
 * GNSS power-on + position query (outdoor antenna usually required).
 * Build: pio run -e example_gnss
 */

#include <Arduino.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/gnss.h"
#include "iotpoc/hal/arduino_uart.h"
#include "iotpoc/hal/board.h"
#include "iotpoc_config.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::gnss_power_on;
using iotpoc::cellular::gnss_query_position;
using iotpoc::hal::ArduinoUart;
using iotpoc::hal::board_init_serial;

static char line_buf[256];
static char resp[192];

void setup() {
    board_init_serial();
    ArduinoUart uart(Serial2, IOTPOC_MODEM_UART_RX_PIN, IOTPOC_MODEM_UART_TX_PIN, IOTPOC_MODEM_UART_BAUD);
    uart.begin();
    AtClient client(uart, line_buf, sizeof(line_buf));
    Serial.println("[example] GNSS power-on + position query");
    (void)gnss_power_on(client, resp, sizeof(resp), 3000);
    (void)gnss_query_position(client, resp, sizeof(resp), 5000);
}

void loop() {
    delay(10000);
}
