# Raspberry Pi (edge gateway)

Linux **edge runtime** for gateway-class automation — not bare-metal firmware.

## Location

[`edge/raspberry_pi/`](../../edge/raspberry_pi/)

| File | Role |
| --- | --- |
| `telemetry_gateway.py` | MQTT publish loop — customize `read_payload()` / `build_json()` |
| `config.example.env` | Template (`YOUR_*` placeholders) |
| `config.local.env` | Your broker credentials (gitignored) |
| `requirements.txt` | Python dependencies |

## Quick start

```bash
cd edge/raspberry_pi
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
cp config.example.env config.local.env
# edit config.local.env
python telemetry_gateway.py
```

## When to use Pi vs ESP32 vs STM32

| Need | Prefer |
| --- | --- |
| Low cost, Wi-Fi/cellular, field I/O | ESP32 |
| Rugged 3.3 V I/O, industrial MCU, no Linux | STM32 |
| Local dashboard, multiple protocols, buffering | **Raspberry Pi** |
| Remote site 4G only | ESP32 A7672 gateway folder |

## Sensor / automation examples on Pi

| Input | Python approach |
| --- | --- |
| GPIO door / limit switch | `gpiozero` (optional in requirements) |
| I2C temp/humidity | `smbus2` or `adafruit-circuitpython-*` |
| Modbus meters | `pymodbus` |
| Aggregate ESP32 nodes | Subscribe or serial JSON from sub-devices |
| Camera / heavy ML | Pi only (out of scope for bare-metal) |

Customize the same JSON shape as ESP32 (`ID`, `DT`, `DATA`) so one MQTT consumer works for all platforms.

## systemd

Run at boot — see footer comment in `telemetry_gateway.py`.

See [REFERENCE_SCOPE.md](../REFERENCE_SCOPE.md).
