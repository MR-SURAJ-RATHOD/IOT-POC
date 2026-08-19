# Troubleshooting

## USB serial

- Select 115200 8N1 and the correct COM port.
- If upload fails, hold BOOT, tap EN, release BOOT (classic ESP32).
- `pio device monitor -e poc_relay_control`

## Relays

- No click: confirm **active-low** module and shared ground.
- Always on: pin floating at boot — `DigitalOutput::init(true)` forces OFF (HIGH for active-low).

## I2C / analog / RS-485

- I2C NACK: wrong address, missing pull-ups, 5 V device on a 3.3 V bus.
- ADC noisy: avoid ADC2 while Wi-Fi is running.
- Modbus CRC fail: byte order, 3.5-character silent interval, A/B swap.

## Cellular

- `AT` timeout: TX/RX swapped, baud mismatch, modem not powered.
- SIM not READY: insert SIM, disable PIN or handle `AT+CPIN` locally (do not commit the PIN).
- Not registered: antenna, operator, roaming. Query `AT+CEREG?` / `AT+CSQ`.
- PDP fail: APN placeholder still `YOUR_APN`, or username/password required by the operator (local config only).

## MQTT

- Connect skipped: host still `YOUR_BROKER_HOST`.
- Connect reset: TLS vs plain port, bad credentials (keep them out of git).
- LWT not firing: broker requires a persistent session and a non-clean disconnect.

## Watchdog resets

- `board_reset_reason()` prints `watchdog`.
- Feed in every long loop; do not block in `loop()` without `watchdog_feed()` after `watchdog_add_current_task()`.
