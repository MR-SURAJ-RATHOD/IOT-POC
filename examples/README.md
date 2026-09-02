# Examples

**Single-concern** firmware demos — each folder teaches one topic. Build from [`firmware/`](../firmware/) (not from this folder directly).

```bash
cd firmware
pio run -e example_<category>_<name> -t upload
pio device monitor
```

New to the repo? Start with [docs/GETTING_STARTED.md](../docs/GETTING_STARTED.md).

---

## Sensors (`examples/sensors/`)

| Environment | Folder | What it demonstrates |
| --- | --- | --- |
| `example_sensor_analog` | `analog/` | ADC voltage via injectable reader |
| `example_sensor_digital` | `digital/` | GPIO digital input |
| `example_sensor_temp_humidity` | `temperature_humidity/` | I2C register-map temp/humidity pattern |
| `example_sensor_rs485` | `rs485/` | Modbus RTU holding-register read |

Driver code lives in [`sensors/`](../sensors/). Examples show how to wire `ISensor` in an application.

---

## MQTT over Wi-Fi (`examples/mqtt/`)

Requires Wi-Fi and broker settings in `firmware/include/config.local.h`. Examples skip connect while placeholders remain `YOUR_*`.

| Environment | Focus |
| --- | --- |
| `example_mqtt_publish` | Basic publish |
| `example_mqtt_subscribe` | Subscribe + callback |
| `example_mqtt_json_telemetry` | JSON payload shape |
| `example_mqtt_qos` | QoS levels |
| `example_mqtt_retained` | Retained messages |
| `example_mqtt_lwt` | Last will and testament |
| `example_mqtt_reconnect` | Reconnect loop |
| `example_mqtt_backoff` | Exponential backoff |
| `example_mqtt_heartbeat` | Periodic keepalive publish |
| `example_mqtt_device_status` | Status topic pattern |
| `example_mqtt_commands` | Incoming command handling |
| `example_mqtt_configuration` | Remote config concept |

Helpers: [`mqtt/`](../mqtt/).

---

## Cellular — Quectel (`examples/cellular/`)

Uses the **Quectel AT stack** in [`cellular/quectel/`](../cellular/quectel/). Expects a Quectel LTE module on UART (pins in `config.example.h`).

| Environment | Focus |
| --- | --- |
| `example_at_handling` | AT send / parse |
| `example_sim_status` | SIM PIN state |
| `example_network_registration` | `CEREG` |
| `example_signal_quality` | `CSQ` |
| `example_apn_pdp` | APN / PDP context |
| `example_http` / `example_https` | Modem HTTP / TLS |
| `example_mqtt_at` | Modem-hosted MQTT |
| `example_gnss` | GNSS |
| `example_ntp` | Network time |
| `example_reconnect` | Backoff + reconnect |
| `example_diagnostics` | Module identity |

> **Not** the A7672 integrated board — that is a separate project: [`ESP32 4G LTE A7672 MODULE/`](../ESP32%204G%20LTE%20A7672%20MODULE/).

---

## FreeRTOS (`examples/rtos/`)

| Environment | Focus |
| --- | --- |
| `example_rtos_tasks` | Basic tasks |
| `example_rtos_priorities` | Priority scheduling |
| `example_rtos_queues` | Queue IPC |
| `example_rtos_mutexes` | Mutex |
| `example_rtos_semaphores` | Semaphore |
| `example_rtos_event_groups` | Event groups |
| `example_rtos_timers` | Software timers |
| `example_rtos_watchdog` | Task WDT |
| `example_rtos_state_machines` | App FSM |

Helpers: [`rtos/`](../rtos/).

---

## Platforms (`examples/platforms/`)

| Environment | Platform |
| --- | --- |
| `example_stm32_edge` | STM32 Nucleo F103 (change board in `platformio.ini`) |

**Raspberry Pi** (Python, not PlatformIO): [`edge/raspberry_pi/`](../../edge/raspberry_pi/).

---

## Add a new example

1. Create `examples/<category>/<name>/main.cpp`.
2. Add `[env:example_<category>_<name>]` in [`firmware/platformio.ini`](../firmware/platformio.ini) with `build_src_filter = -<*> +<examples/<category>/<name>/>`.
3. Document the environment in this README.
4. Add a CI build entry in [`.github/workflows/ci.yml`](../.github/workflows/ci.yml) if it should compile on every push.
