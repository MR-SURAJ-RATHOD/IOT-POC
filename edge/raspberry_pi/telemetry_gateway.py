#!/usr/bin/env python3
"""
Raspberry Pi MQTT telemetry gateway (starter template).

CUSTOMIZE:
  - read_payload()  : your sensors / Modbus / GPIO / I2C
  - build_json()    : JSON keys for your MQTT consumer

Config: config.local.env (copy from config.example.env)
"""

from __future__ import annotations

import json
import os
import time
from dataclasses import dataclass, field
from pathlib import Path

try:
    import paho.mqtt.client as mqtt
except ImportError:
    raise SystemExit("Install: pip install -r requirements.txt")


@dataclass
class Payload:
    """CUSTOMIZE: add fields for your automation project."""

    field_a: float = 0.0
    field_b: float = 0.0
    # temperature_c: float = 0.0
    # tank_level_pct: float = 0.0
    # door_open: bool = False


@dataclass
class Config:
    device_id: str = "YOUR_DEVICE_ID"
    tenant_id: str = "YOUR_TENANT_ID"
    asset_id: str = "YOUR_ASSET_ID"
    mqtt_broker: str = "YOUR_MQTT_BROKER_HOST"
    mqtt_port: int = 1883
    mqtt_user: str = "YOUR_MQTT_USERNAME"
    mqtt_pass: str = "YOUR_MQTT_PASSWORD"
    mqtt_topic: str = "YOUR_MQTT_PUBLISH_TOPIC"
    publish_interval_sec: int = 60
    use_gpio: bool = False
    gpio_input_pin: int = 17


def load_config() -> Config:
    cfg = Config()
    base = Path(__file__).parent
    env_path = base / "config.local.env"
    if not env_path.exists():
        env_path = base / "config.example.env"
        if env_path.exists():
            print(f"Using {env_path.name} (copy to config.local.env for your secrets)")
        else:
            print("Warning: no config file — using YOUR_* placeholders")
            return cfg

    for line in env_path.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        key, value = key.strip(), value.strip()
        if key == "DEVICE_ID":
            cfg.device_id = value
        elif key == "TENANT_ID":
            cfg.tenant_id = value
        elif key == "ASSET_ID":
            cfg.asset_id = value
        elif key == "MQTT_BROKER":
            cfg.mqtt_broker = value
        elif key == "MQTT_PORT":
            cfg.mqtt_port = int(value)
        elif key == "MQTT_USER":
            cfg.mqtt_user = value
        elif key == "MQTT_PASS":
            cfg.mqtt_pass = value
        elif key == "MQTT_TOPIC":
            cfg.mqtt_topic = value
        elif key == "PUBLISH_INTERVAL_SEC":
            cfg.publish_interval_sec = int(value)
        elif key == "USE_GPIO":
            cfg.use_gpio = value in ("1", "true", "True", "yes")
        elif key == "GPIO_INPUT_PIN":
            cfg.gpio_input_pin = int(value)
    return cfg


def read_payload(cfg: Config) -> Payload:
    """
    CUSTOMIZE: read real sensors here.

    Examples:
      - GPIO door contact (gpiozero): DigitalInputDevice(cfg.gpio_input_pin).value
      - I2C temp/humidity (smbus2)
      - Modbus RTU via pymodbus
      - Parse serial from ESP32 sub-node
    """
    p = Payload()

    if cfg.use_gpio:
        try:
            from gpiozero import DigitalInputDevice

            pin = DigitalInputDevice(cfg.gpio_input_pin, pull_up=True)
            p.field_a = 1.0 if pin.value else 0.0
        except Exception as exc:
            print(f"GPIO read skipped: {exc}")

    return p


def build_json(cfg: Config, payload: Payload) -> dict:
    """
    CUSTOMIZE: MQTT JSON envelope (same idea as ESP32 telemetry_mqtt.cpp).
    """
    data = {
        "field_a": f"{payload.field_a:.4f}",
        "field_b": f"{payload.field_b:.4f}",
    }
    return {
        "ID": cfg.device_id,
        "DT": str(int(time.time())),
        # "tenant_id": cfg.tenant_id,
        # "asset_id": cfg.asset_id,
        "DATA": data,
    }


def config_ready(cfg: Config) -> bool:
    return (
        cfg.mqtt_broker
        and not cfg.mqtt_broker.startswith("YOUR_")
        and cfg.mqtt_topic
        and not cfg.mqtt_topic.startswith("YOUR_")
    )


def run_once(cfg: Config, *, dry_run: bool) -> None:
    payload = read_payload(cfg)
    body = build_json(cfg, payload)
    msg = json.dumps(body, indent=2)

    if dry_run or not config_ready(cfg):
        print("--- dry-run (no MQTT) ---")
        print(msg)
        if not config_ready(cfg):
            print("\nTip: copy config.example.env to config.local.env and set MQTT_BROKER / MQTT_TOPIC")
        return

    client = mqtt.Client(client_id=cfg.device_id)
    if cfg.mqtt_user and not cfg.mqtt_user.startswith("YOUR_"):
        client.username_pw_set(cfg.mqtt_user, cfg.mqtt_pass)

    print(f"Connecting to {cfg.mqtt_broker}:{cfg.mqtt_port} topic={cfg.mqtt_topic}")
    client.connect(cfg.mqtt_broker, cfg.mqtt_port, 60)
    client.loop_start()
    try:
        client.publish(cfg.mqtt_topic, json.dumps(body), qos=0)
        print(f"Published {len(msg)} bytes ID={body['ID']}")
    finally:
        client.loop_stop()
        client.disconnect()


def main() -> None:
    import argparse

    parser = argparse.ArgumentParser(description="Raspberry Pi MQTT telemetry gateway")
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Print JSON only; do not connect to MQTT (default if config has YOUR_* placeholders)",
    )
    parser.add_argument(
        "--once",
        action="store_true",
        help="Single publish (or one dry-run print) then exit",
    )
    args = parser.parse_args()

    cfg = load_config()
    dry = args.dry_run or not config_ready(cfg)

    if args.once:
        run_once(cfg, dry_run=dry)
        return

    if dry:
        print("Running in dry-run loop (Ctrl+C to stop). Use --once for a single sample.")
        try:
            while True:
                run_once(cfg, dry_run=True)
                time.sleep(cfg.publish_interval_sec)
        except KeyboardInterrupt:
            print("Stopping.")
        return

    client = mqtt.Client(client_id=cfg.device_id)
    if cfg.mqtt_user and not cfg.mqtt_user.startswith("YOUR_"):
        client.username_pw_set(cfg.mqtt_user, cfg.mqtt_pass)

    print(f"Connecting to {cfg.mqtt_broker}:{cfg.mqtt_port} topic={cfg.mqtt_topic}")
    client.connect(cfg.mqtt_broker, cfg.mqtt_port, 60)
    client.loop_start()

    try:
        while True:
            payload = read_payload(cfg)
            body = build_json(cfg, payload)
            msg = json.dumps(body)
            client.publish(cfg.mqtt_topic, msg, qos=0)
            print(f"Published {len(msg)} bytes ID={body['ID']}")
            time.sleep(cfg.publish_interval_sec)
    except KeyboardInterrupt:
        print("Stopping.")
    finally:
        client.loop_stop()
        client.disconnect()


if __name__ == "__main__":
    main()

# systemd example (optional):
#   ExecStart=/path/to/.venv/bin/python /path/to/telemetry_gateway.py
#   WorkingDirectory=/path/to/edge/raspberry_pi
