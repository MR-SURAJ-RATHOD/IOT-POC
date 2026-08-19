/**
 * Modem-hosted MQTT (AT+QMTOPEN). Host/port: IOTPOC_MQTT_HOST / IOTPOC_MQTT_PORT.
 * This is Backend B (AT-MQTT), not the ESP32 Wi-Fi PubSubClient path.
 * Build: pio run -e example_mqtt_at
 */

#include <Arduino.h>

#include "iotpoc/cellular/at_client.h"
#include "iotpoc/cellular/mqtt_at.h"
#include "iotpoc/hal/arduino_uart.h"
#include "iotpoc/hal/board.h"
#include "iotpoc_config.h"

using iotpoc::cellular::AtClient;
using iotpoc::cellular::build_mqtt_open_command;
using iotpoc::cellular::mqtt_at_open;
using iotpoc::hal::ArduinoUart;
using iotpoc::hal::board_init_serial;

static char line_buf[256];
static char resp[128];
static char cmd[160];

void setup() {
    board_init_serial();
    build_mqtt_open_command(IOTPOC_MQTT_HOST, IOTPOC_MQTT_PORT, cmd, sizeof(cmd));
    Serial.println(cmd);
    ArduinoUart uart(Serial2, IOTPOC_MODEM_UART_RX_PIN, IOTPOC_MODEM_UART_TX_PIN, IOTPOC_MODEM_UART_BAUD);
    uart.begin();
    AtClient client(uart, line_buf, sizeof(line_buf));
    (void)mqtt_at_open(client, IOTPOC_MQTT_HOST, IOTPOC_MQTT_PORT, resp, sizeof(resp), 8000);
}

void loop() {
    delay(10000);
}
