#include <Arduino.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/pdp.h"
#include "iotpoc/hal/arduino_uart.h"
#include "iotpoc/hal/board.h"
#include "iotpoc_config.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::AtStatus;
using iotpoc::cellular::at_status_name;
using iotpoc::cellular::build_pdp_command;
using iotpoc::cellular::configure_pdp;
using iotpoc::hal::ArduinoUart;
using iotpoc::hal::board_init_serial;

static char line_buf[256];
static char resp[128];
static char cmd[128];

void setup() {
    board_init_serial();
    build_pdp_command(IOTPOC_APN, cmd, sizeof(cmd));
    Serial.print("[example] PDP command=");
    Serial.println(cmd);
    ArduinoUart uart(Serial2, IOTPOC_MODEM_UART_RX_PIN, IOTPOC_MODEM_UART_TX_PIN, IOTPOC_MODEM_UART_BAUD);
    uart.begin();
    AtClient client(uart, line_buf, sizeof(line_buf));
    const AtStatus st = configure_pdp(client, IOTPOC_APN, resp, sizeof(resp), 4000);
    Serial.println(at_status_name(st));
}

void loop() {
    delay(5000);
}
