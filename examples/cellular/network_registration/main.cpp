#include <Arduino.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/network.h"
#include "iotpoc/hal/arduino_uart.h"
#include "iotpoc/hal/board.h"
#include "iotpoc_config.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::query_registration;
using iotpoc::cellular::registration_attached;
using iotpoc::hal::ArduinoUart;
using iotpoc::hal::board_init_serial;

static char line_buf[256];
static char resp[128];

void setup() {
    board_init_serial();
    ArduinoUart uart(Serial2, IOTPOC_MODEM_UART_RX_PIN, IOTPOC_MODEM_UART_TX_PIN, IOTPOC_MODEM_UART_BAUD);
    uart.begin();
    AtClient client(uart, line_buf, sizeof(line_buf));
    (void)query_registration(client, resp, sizeof(resp), 3000);
    Serial.print("[example] registered=");
    Serial.println(registration_attached(resp) ? "yes" : "no");
    Serial.println(resp);
}

void loop() {
    delay(5000);
}
