# Raspberry Pi edge gateway (starter)

Linux **edge service** template — publish automation telemetry to MQTT (same idea as ESP32 `metrics_builder` + `telemetry_mqtt`, but in Python).

Use cases: local gateway, protocol bridge, dashboard host, aggregating sub-devices over Modbus/serial.

## Setup

```bash
cd edge/raspberry_pi
pip install -r requirements.txt
cp config.example.env config.local.env   # Windows: copy config.example.env config.local.env
```

Or from repo root: `scripts/setup-local-config.ps1` / `setup-local-config.sh`

## Run immediately (no MQTT broker)

```bash
python telemetry_gateway.py --dry-run --once
```

Prints sample JSON — works on PC or Pi without broker credentials.

## Run with MQTT

Edit `config.local.env`, then:

```bash
python telemetry_gateway.py
```

## Customize payload

Edit `telemetry_gateway.py`:

- `read_payload()` — sample GPIO (gpiozero), I2C (smbus2), Modbus, or read from serial
- `build_json()` — map fields to keys your cloud expects

## systemd (optional)

Run as a service on boot — see comments at bottom of `telemetry_gateway.py`.

Full doc: [docs/controllers/raspberry_pi.md](../../docs/controllers/raspberry_pi.md).
