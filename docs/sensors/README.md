# Sensors

The sensor layer is generic. Weather-related quantities are **one category** among analog, digital, RTC, and RS-485 devices.

## Contract

`iotpoc::sensors::ISensor`

- `init()`
- `read(SensorReading&)`
- `metadata()`
- optional `reset()`

`SensorReading` carries `sensor_id`, `quantity`, `value`, `unit`, `quality`, `timestamp_ms`, `error`.

Drivers **must** take injected bus/pin handles. They must not own a global `Wire` instance.

## Categories

| Folder | Pattern |
| --- | --- |
| `temperature_humidity` | I2C register-map example (scaled int16 / uint16) |
| `pressure` | I2C 16-bit pressure register example |
| `rtc` | I2C timestamp register example |
| `wind_speed` | Pulse frequency (anemometer-style, reusable for flow meters) |
| `wind_direction` | Analog fraction → degrees (vane-style, reusable for pots) |
| `rain` | Tipping count → engineering units (reusable for pulse totals) |
| `uv` | Index injection / analog mapping |
| `analog` | ADC voltage with injectable reader (native-testable) |
| `digital` | GPIO input sensor + active-low `DigitalOutput` |
| `rs485` | Modbus RTU holding-register request builder |

## Adding a driver

1. Implement `ISensor` in the matching folder.
2. Add a focused example under `examples/sensors/` or a new environment.
3. Add native tests for conversion/parsing.
4. Document the register map **you** validated; do not paste vendor PDFs.
