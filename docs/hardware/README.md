# Hardware notes

Pin numbers in firmware are **examples**. Change them in `config.local.h` for your PCB.

## ESP32 controller

- DevKit-class ESP32 (WROOM / WROVER). First target for every example.
- USB-UART at 115200 8N1 for the console (`Serial`).
- Leave flash voltage and strapping pins (0, 2, 12, 15) alone unless you know the board.

## Relay / digital outputs

- Many modules are **active low**: GPIO LOW energises the coil.
- Default POC pins: GPIO 27 (relay 1), GPIO 14 (relay 2).
- Drive relays through a module or transistor; do not sink coil current into the ESP32 pin.

## UART to Quectel

- Example: ESP32 TX GPIO 17 → modem RX; ESP32 RX GPIO 16 → modem TX; common GND.
- Modem VBAT is typically ~3.8 V with a supply that can source 2 A peaks. Do not power the modem from the ESP32 3V3 pin.
- Optional RTS/CTS later; v1 examples are 8N1.

## I2C sensors

- GPIO 21 SDA / 22 SCL on many DevKits, with pull-ups on the bus.
- Addresses and register maps in drivers are **category examples**, not a guarantee of a specific vendor part.

## RS-485

- Use a 3.3 V transceiver (for example DE/RE on a GPIO). A/B polarity matters.
- Bias and termination belong on the cable, not in firmware.

## Analog

- ESP32 ADC1 pins are preferred while Wi-Fi is in use.
- Readings are illustrative; calibrate `vref` per board.

Manual desk checks: [tests/hardware/README.md](../../tests/hardware/README.md).
