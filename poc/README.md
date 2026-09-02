# Composed POCs

**Mini-systems** that combine multiple layers (HAL, sensors, MQTT, cellular, commands). Use these after single-topic [`examples/`](../examples/) demos.

Build from [`firmware/`](../firmware/):

```bash
cd firmware
pio run -e poc_<name> -t upload
pio device monitor
```

Overview: [docs/GETTING_STARTED.md](../docs/GETTING_STARTED.md).

---

## Available POCs

| Environment | Folder | Description |
| --- | --- | --- |
| `poc_relay_control` | [`relay_control/`](relay_control/) | Serial relay commands (`ON1`/`OFF1`/`ON2`/`OFF2`). Migrated from root `relaycontrol.cpp`. Active-low GPIO 27 / 14. **Default build env.** |
| `poc_sensor_telemetry` | [`sensor_telemetry/`](sensor_telemetry/) | Sample analog sensor → JSON telemetry pattern |
| `poc_cellular_data_path` | [`cellular_data_path/`](cellular_data_path/) | Quectel bring-up state machine + watchdog |
| `poc_command_and_control` | [`command_and_control/`](command_and_control/) | Shared command parser for serial and MQTT |

---

## When to use POC vs example

| Use | Folder |
| --- | --- |
| Learn one API (MQTT publish, one AT command, one sensor) | `examples/` |
| See how layers fit together for a small product-like flow | `poc/` |
| Ship-ready 4G MQTT gateway with your own payload | [`ESP32 4G LTE A7672 MODULE/`](../ESP32%204G%20LTE%20A7672%20MODULE/) |

---

## Configuration

Same as main repo: copy `firmware/include/config.example.h` → `config.local.h` before using Wi-Fi, MQTT, or cellular features.
