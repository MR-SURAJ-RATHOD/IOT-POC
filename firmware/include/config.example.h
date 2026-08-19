#pragma once

/*
 * Placeholder configuration for public examples.
 * Copy this file to config.local.h (gitignored) and replace values locally.
 * Never commit real SSIDs, passwords, APNs, tokens, or private keys.
 */

#ifndef IOTPOC_DEVICE_ID
#define IOTPOC_DEVICE_ID "YOUR_DEVICE_ID"
#endif

#ifndef IOTPOC_WIFI_SSID
#define IOTPOC_WIFI_SSID "YOUR_WIFI_SSID"
#endif

#ifndef IOTPOC_WIFI_PASSWORD
#define IOTPOC_WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#endif

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

#ifndef IOTPOC_MODEM_UART_TX_PIN
#define IOTPOC_MODEM_UART_TX_PIN 17
#endif

#ifndef IOTPOC_MODEM_UART_RX_PIN
#define IOTPOC_MODEM_UART_RX_PIN 16
#endif

#ifndef IOTPOC_MODEM_UART_BAUD
#define IOTPOC_MODEM_UART_BAUD 115200
#endif

#ifndef IOTPOC_RELAY1_PIN
#define IOTPOC_RELAY1_PIN 27
#endif

#ifndef IOTPOC_RELAY2_PIN
#define IOTPOC_RELAY2_PIN 14
#endif
