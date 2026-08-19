#pragma once

/*
 * PUBLIC PLACEHOLDERS — safe to commit.
 *
 * To run Wi-Fi, MQTT, or cellular on hardware:
 *   1. Copy this file to firmware/include/config.local.h
 *   2. Replace every YOUR_* value (SSID, passwords, APN, broker host)
 *   3. Adjust GPIO / UART pins to match YOUR wiring
 *   4. Never commit config.local.h (it is gitignored)
 *
 * Firmware includes iotpoc_config.h, which prefers config.local.h automatically.
 */

/* MQTT / telemetry identity. Appears in topic: devices/{id}/... */
#ifndef IOTPOC_DEVICE_ID
#define IOTPOC_DEVICE_ID "YOUR_DEVICE_ID"
#endif

/* Wi-Fi STA credentials. Leave YOUR_ prefix to skip connect in examples. */
#ifndef IOTPOC_WIFI_SSID
#define IOTPOC_WIFI_SSID "YOUR_WIFI_SSID"
#endif

#ifndef IOTPOC_WIFI_PASSWORD
#define IOTPOC_WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#endif

/* MQTT broker. Host still starting with YOUR_ means "do not connect". */
#ifndef IOTPOC_MQTT_HOST
#define IOTPOC_MQTT_HOST "YOUR_BROKER_HOST"
#endif

#ifndef IOTPOC_MQTT_PORT
#define IOTPOC_MQTT_PORT 1883
#endif

#ifndef IOTPOC_MQTT_USER
#define IOTPOC_MQTT_USER "YOUR_MQTT_USERNAME"
#endif

#ifndef IOTPOC_MQTT_PASSWORD
#define IOTPOC_MQTT_PASSWORD "YOUR_MQTT_PASSWORD"
#endif

#ifndef IOTPOC_MQTT_CLIENT_ID
#define IOTPOC_MQTT_CLIENT_ID "YOUR_MQTT_CLIENT_ID"
#endif

/* Cellular packet data. Operator APN only in config.local.h, never in git. */
#ifndef IOTPOC_APN
#define IOTPOC_APN "YOUR_APN"
#endif

#ifndef IOTPOC_APN_USER
#define IOTPOC_APN_USER "YOUR_APN_USERNAME"
#endif

#ifndef IOTPOC_APN_PASSWORD
#define IOTPOC_APN_PASSWORD "YOUR_APN_PASSWORD"
#endif

#ifndef IOTPOC_HTTP_URL
#define IOTPOC_HTTP_URL "http://YOUR_HTTP_HOST/path"
#endif

#ifndef IOTPOC_HTTPS_URL
#define IOTPOC_HTTPS_URL "https://YOUR_HTTPS_HOST/path"
#endif

/*
 * Quectel UART on ESP32 Serial2 (example pins — change for your PCB).
 * Cross TX/RX: ESP32 TX -> modem RX, ESP32 RX -> modem TX, common GND.
 */
#ifndef IOTPOC_MODEM_UART_TX_PIN
#define IOTPOC_MODEM_UART_TX_PIN 17
#endif

#ifndef IOTPOC_MODEM_UART_RX_PIN
#define IOTPOC_MODEM_UART_RX_PIN 16
#endif

#ifndef IOTPOC_MODEM_UART_BAUD
#define IOTPOC_MODEM_UART_BAUD 115200
#endif

/* Dual relay POC. Many modules are ACTIVE LOW (see poc/relay_control). */
#ifndef IOTPOC_RELAY1_PIN
#define IOTPOC_RELAY1_PIN 27
#endif

#ifndef IOTPOC_RELAY2_PIN
#define IOTPOC_RELAY2_PIN 14
#endif
