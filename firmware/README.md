# PlatformIO workspace

All **main repository** firmware builds run from this folder:

```bash
cd firmware
pio run -e poc_relay_control
pio run -e example_mqtt_publish
pio test -e native
```

## Why `src_dir = ..`?

`platformio.ini` sets `src_dir` to the **repository root** (parent of `firmware/`). Each `[env:...]` uses `build_src_filter` to compile exactly one application folder:

| Environment prefix | Source folder |
| --- | --- |
| `poc_*` | `poc/<name>/` |
| `example_sensor_*` | `examples/sensors/<name>/` |
| `example_cellular_*` / `example_at_*` / … | `examples/cellular/<name>/` |
| `example_mqtt_*` | `examples/mqtt/<name>/` |
| `example_rtos_*` | `examples/rtos/<name>/` |
| `example_stm32_edge` | `examples/platforms/stm32_edge/` (STM32, not ESP32) |

**Raspberry Pi** uses Python in [`edge/raspberry_pi/`](../edge/raspberry_pi/) — not built from this folder.

Shared code is **not** copied into `firmware/src/`. Libraries are pulled from domain folders via `lib_extra_dirs`:

```text
../controllers
../sensors
../communication
../cellular/quectel
../mqtt
../rtos
```

## Configuration

| File | Role |
| --- | --- |
| `include/config.example.h` | Committed template (`YOUR_*` placeholders) |
| `include/config.local.h` | Your secrets (gitignored — create locally) |
| `include/iotpoc_config.h` | Includes local if present, else example |

```bash
# Windows
copy include\config.example.h include\config.local.h

# Linux / macOS
cp include/config.example.h include/config.local.h
```

## Standalone 4G gateway

The [`ESP32 4G LTE A7672 MODULE`](../ESP32%204G%20LTE%20A7672%20MODULE/) project has its **own** `platformio.ini` and config (`data/config.local.env`). Build from that folder, not from `firmware/`.

## Full guide

See [docs/GETTING_STARTED.md](../docs/GETTING_STARTED.md) for path selection, folder map, and learning order.
