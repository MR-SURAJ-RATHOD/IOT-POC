# STM32 controller HAL

**Starter target** for industrial STM32 boards (ST Nucleo, Blue Pill, custom PCB) using PlatformIO **Arduino-STM32** (`ststm32`).

ESP32 remains the primary fully documented platform. STM32 shares the same **`hal_contract`** idea: implement `IUart` / GPIO wrappers here, then reuse `sensors/` and `communication/` logic where portable.

## Build example

From [`firmware/`](../../firmware/):

```bash
pio run -e example_stm32_edge
pio run -e example_stm32_edge -t upload
pio device monitor -e example_stm32_edge
```

Default board: **NUCLEO-F103RB** (change in `firmware/platformio.ini`).

## Customize pins

Edit `IOTPOC_STM32_LED_PIN` in the environment `build_flags` or override before including `stm32_board.h`.

## Next steps on STM32

| Goal | Action |
| --- | --- |
| Modbus / RS-485 | Wire `IUart` to `HardwareSerial`, reuse `communication/modbus` |
| Sensors | Port `ISensor` drivers with injected I2C/UART |
| MQTT | Use Ethernet/Wi-Fi shield or publish via UART to a gateway |
| FreeRTOS | STM32duino supports RTOS — mirror patterns from `rtos/` |

See [docs/controllers/stm32.md](../../docs/controllers/stm32.md).
