# Sensors

The sensor layer is generic. Weather-related quantities are **one category** among analog, digital, RTC, and RS-485 devices.

**Full checklist:** sensor types, what you can add, and industry mapping (agri, water, industrial) → [REFERENCE_SCOPE.md](../REFERENCE_SCOPE.md).

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

## Using sensors with the 4G LTE gateway

The [`ESP32 4G LTE A7672 MODULE`](../../ESP32%204G%20LTE%20A7672%20MODULE/) project publishes MQTT telemetry over cellular. It does **not** ship a fixed sensor list — you add fields in `metrics_builder.*` for your automation site.

Typical integrations:

| Automation need | Start from repo pattern |
| --- | --- |
| Room / duct temperature | `temperature_humidity` (I2C) |
| Tank or sump level | `analog` (ADC) or Modbus level transmitter |
| Door, gate, limit switch | `digital` (GPIO input) |
| Flow meter pulse | `wind_speed` pulse pattern or GPIO ISR |
| Plant Modbus devices | `rs485` + `communication/modbus` |

Real-time loop: sample in `readPayload()` → JSON in `fillJsonPayload()` → MQTT every `PUBLISH_INTERVAL_MS`.

Details: [cellular/esp32-a7672-gateway.md](../cellular/esp32-a7672-gateway.md).
