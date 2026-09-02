# Run guide — make it work on your machine

Step-by-step commands so **clone → build → run** succeeds. No secrets required for compile-only paths.

---

## 0. One-time setup (all platforms)

### Install

- [PlatformIO](https://platformio.org/install/cli) (or VS Code + PlatformIO extension)
- Python 3.10+ (for Pi edge script and native tests helper)
- USB driver for your board

### Copy config templates

**Windows (repo root):**

```powershell
powershell -ExecutionPolicy Bypass -File scripts/setup-local-config.ps1
```

**Linux / macOS:**

```bash
chmod +x scripts/setup-local-config.sh
./scripts/setup-local-config.sh
```

This creates gitignored `config.local.*` files. Edit them when you have real Wi-Fi / MQTT / APN values.

---

## 1. ESP32 — compile (no board needed)

```bash
cd firmware
python -m platformio run -e poc_relay_control
```

**Expected:** `SUCCESS` — builds relay POC firmware.

### Flash to hardware

1. Connect ESP32 DevKit via USB.
2. Wire relays active-low to GPIO **27** and **14** (or change pins in config).
3. Upload and monitor:

```bash
python -m platformio run -e poc_relay_control -t upload
python -m platformio device monitor -e poc_relay_control
```

4. Serial 115200 — send: `ON1` `OFF1` `ON2` `OFF2`

### Other ESP32 examples (compile)

```bash
python -m platformio run -e example_sensor_analog
python -m platformio run -e example_mqtt_publish
python -m platformio run -e example_rtos_tasks
```

Wi-Fi/MQTT examples **skip broker connect** while config still has `YOUR_*` placeholders.

---

## 2. STM32 — compile (no board needed)

Default board: **NUCLEO-F103RB** (change in `firmware/platformio.ini` if needed).

```bash
cd firmware
python -m platformio run -e example_stm32_edge
```

**Expected:** `SUCCESS` (~first run downloads STM32 toolchain).

### Flash to hardware

```bash
python -m platformio run -e example_stm32_edge -t upload
python -m platformio device monitor -e example_stm32_edge
```

**Expected:** Serial prints `IOT-POC STM32 edge starter`; onboard LED blinks.

---

## 3. Raspberry Pi — run without MQTT broker

Works on **any PC** for demo (dry-run prints JSON):

```bash
cd edge/raspberry_pi
pip install -r requirements.txt
python telemetry_gateway.py --dry-run --once
```

**Expected output:**

```json
{
  "ID": "RPi-GW-EXAMPLE-01",
  "DT": "...",
  "DATA": { "field_a": "0.0000", "field_b": "0.0000" }
}
```

### On real Raspberry Pi with MQTT

1. Edit `config.local.env` — set `MQTT_BROKER`, `MQTT_TOPIC`, credentials.
2. Run:

```bash
python telemetry_gateway.py
```

Optional GPIO: set `USE_GPIO=1` and install `gpiozero`.

---

## 4. ESP32 + A7672 4G gateway — compile

```bash
cd "ESP32 4G LTE A7672 MODULE"
copy data\config.local.env.example data\config.local.env
python -m platformio run
```

### Flash to hardware

```bash
# Edit data/config.local.env first (MQTT, DEVICE_ID, APN)
python -m platformio run -t uploadfs
python -m platformio run -t upload
python -m platformio device monitor
```

Customize payload: `src/metrics/metrics_builder.*`

---

## 5. Native unit tests (no hardware)

```bash
cd firmware
python -m platformio test -e native
```

**Expected:** `10 test cases: 10 succeeded`

Requires `gcc`/`g++` on PATH (Ubuntu CI has this; Windows: install MinGW or use WSL).

---

## 6. Verify everything (smoke script)

**Windows:**

```powershell
powershell -ExecutionPolicy Bypass -File scripts/smoke-verify.ps1
```

**Linux / macOS:**

```bash
./scripts/smoke-verify.sh
```

Builds ESP32 default, STM32 example, A7672 project, runs native tests, and Pi dry-run.

---

## Troubleshooting

| Problem | Fix |
| --- | --- |
| `pio` not found | Use `python -m platformio` instead |
| ESP32 upload fail | Check COM port, hold BOOT if needed |
| STM32 first build slow | Normal — toolchain download once |
| Pi script MQTT error | Use `--dry-run --once` or fill `config.local.env` |
| Native test no gcc | Install compiler or use GitHub Actions CI |
| A7672 shows `YOUR_*` | Run `pio run -t uploadfs` after editing config |

More: [troubleshooting/README.md](troubleshooting/README.md)

---

## Full map

- Folder structure: [GETTING_STARTED.md](GETTING_STARTED.md)
- Controllers & industries: [REFERENCE_SCOPE.md](REFERENCE_SCOPE.md)
