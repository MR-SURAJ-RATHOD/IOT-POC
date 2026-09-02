# STM32 (PlatformIO / Arduino-STM32)

Starter firmware target for **industrial STM32** boards. ESP32 is still the primary reference; STM32 reuses the same layering via `hal_contract`.

## Supported boards (examples)

| Board | PlatformIO `board` | Notes |
| --- | --- | --- |
| NUCLEO-F103RB | `nucleo_f103rb` | Default in `platformio.ini` |
| Blue Pill F103C8 | `bluepill_f103c8` | Change board id; 3.3 V I/O |
| NUCLEO-F401RE | `nucleo_f401re` | More RAM/Flash |

Change board in `[env:example_stm32_edge]` in [`firmware/platformio.ini`](../../firmware/platformio.ini).

## Build

```bash
cd firmware
pio run -e example_stm32_edge
pio run -e example_stm32_edge -t upload
pio device monitor -e example_stm32_edge
```

## HAL location

- [`controllers/stm32/`](../../controllers/stm32/) — `Stm32Board` bring-up
- [`controllers/hal_contract/`](../../controllers/hal_contract/) — `IUart`, I2C contracts for porting AT/Modbus

## Typical industrial uses

| Use | How |
| --- | --- |
| Digital I/O node | GPIO + `sensors/digital` pattern |
| Modbus RTU master | Implement `IUart` on `HardwareSerial` + `communication/modbus` |
| CAN / RS-485 gateway | UART/CAN HAL + upstream MQTT via Wi-Fi module or RPi |
| Low-power remote I/O | STM32 sleep modes (extend `stm32_board` ) |

## Sensors

Same [`sensors/`](../../sensors/) drivers when you inject bus handles. Native tests (`pio test -e native`) still run parser logic on PC without STM32 hardware.

See [REFERENCE_SCOPE.md](../REFERENCE_SCOPE.md).
