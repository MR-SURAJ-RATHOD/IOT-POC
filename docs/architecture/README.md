# Firmware architecture

Includes travel **downward only**:

```text
Application (examples/, poc/)
  → Services (MQTT, cellular feature modules, telemetry JSON, commands)
    → HAL / drivers (ESP32 HAL, ISensor drivers, AT core, bus helpers)
      → Hardware (ESP32, sensors/actuators, Quectel module)
```

Application code must not call `digitalWrite` or concatenate raw AT strings except in HAL-demo sketches. Drivers receive injected UART/I2C/GPIO handles.

## Configuration

`firmware/include/iotpoc_config.h` includes `config.local.h` when present, otherwise `config.example.h`. Local files are gitignored. Placeholders (`YOUR_WIFI_SSID`, `YOUR_APN`, `YOUR_MQTT_URI` style macros) are the only values allowed on `main`.

Device identity is `IOTPOC_DEVICE_ID`. Do not log IMSI, ICCID, or passwords; `mask_secret()` redacts long digit runs.

## Build

PlatformIO + Arduino-ESP32, board `esp32dev`. Each example is a `src_filter` environment in `firmware/platformio.ini`. ESP-IDF is a future controller option, not the v1 default.

## OTA concepts (not a production updater)

- Use a dual-OTA partition table when you move beyond USB flashing.
- Fetch firmware over **HTTPS** from a URL you control; verify a hash/signature before commit.
- Keep a recoverable factory/otadata slot so a bad image can roll back.
- Never embed private code-signing keys in this public tree.

See [hardware](../hardware/README.md), [sensors](../sensors/README.md), [cellular](../cellular/README.md), [MQTT](../mqtt/README.md), [RTOS](../rtos/README.md).
