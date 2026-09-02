# Controllers (multi-platform HAL)

Hardware abstraction per **SoC / board**. Application and sensor code should depend on **`hal_contract`** interfaces, not on Arduino APIs directly.

| Platform | Folder | Firmware status | Typical role |
| --- | --- | --- | --- |
| **ESP32** | [`esp32/`](esp32/) | **Full** — all examples & POCs | Edge node, Wi-Fi/cellular gateway, Modbus |
| **STM32** | [`stm32/`](stm32/) | **Starter** — HAL + blink example | Industrial I/O, low-power field node, CAN/UART |
| **Raspberry Pi** | [`../edge/raspberry_pi/`](../edge/raspberry_pi/) | **Edge service** (Linux/Python) | Gateway, local MQTT bridge, dashboard host |

Shared contract headers: [`hal_contract/include/iotpoc/hal/`](hal_contract/include/iotpoc/hal/).

Platform comparison and industry mapping: [docs/REFERENCE_SCOPE.md](../docs/REFERENCE_SCOPE.md).

## Add a new MCU

1. Implement `iotpoc::hal::IUart`, GPIO helpers, etc. under `controllers/<mcu>/`.
2. Add `library.json` with the correct PlatformIO `platforms` filter.
3. Add `[env:example_<mcu>_…]` in `firmware/platformio.ini`.
4. Document pins in `docs/hardware/` and link from REFERENCE_SCOPE.
