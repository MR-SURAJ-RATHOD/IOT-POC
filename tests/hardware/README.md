# Hardware tests (manual)

CI does not require a board. Use this checklist on a desk setup.

## Relay POC (`poc_relay_control`)

- [ ] Active-low dual relay module on GPIO 27 and 14 (or pins from `config.local.h`)
- [ ] USB serial 115200
- [ ] `ON1` / `OFF1` / `ON2` / `OFF2` match coil state

## Analog / I2C / RS-485

- [ ] ADC pin within ESP32 ADC range
- [ ] I2C pull-ups present
- [ ] RS-485 A/B not swapped; DE/RE wired if using a transceiver

## Quectel

- [ ] UART TX/RX crossed (ESP TX → modem RX)
- [ ] Common ground, adequate 3.8 V / 4 V modem supply
- [ ] SIM inserted; APN only in `config.local.h`

## MQTT

- [ ] Broker reachable; LWT shows `offline` after unplug
