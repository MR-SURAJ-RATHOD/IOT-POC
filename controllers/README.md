# ESP32 controller HAL

First SoC target for this reference repository. The HAL hides Arduino-ESP32 calls behind small interfaces so services and examples do not scatter `pinMode` / `Serial` usage.

| Header | Role |
| --- | --- |
| `iotpoc/hal/gpio.h` | Pin mode and level |
| `iotpoc/hal/uart.h` | Byte-oriented UART contract used by the Quectel AT transport |
| `iotpoc/hal/i2c.h` | Injected I2C bus for sensor drivers |
| `iotpoc/hal/spi.h` | SPI transfer contract (stub adapter can be added per board) |
| `iotpoc/hal/adc.h` | Analog samples |
| `iotpoc/hal/watchdog.h` | Task watchdog helper |
| `iotpoc/hal/board.h` | Serial console and reset-reason string |

Arduino implementations (`ArduinoUart`, `ArduinoI2c`) live in this library and are not compiled in the `native` test environment.

Pin numbers in examples are **illustrative**. Copy `config.example.h` and change them for your PCB.
