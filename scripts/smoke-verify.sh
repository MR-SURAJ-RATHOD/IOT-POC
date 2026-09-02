#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

echo "=== IOT-POC smoke verify ==="

echo ""
echo "[1/5] ESP32 poc_relay_control"
cd firmware
python3 -m platformio run -e poc_relay_control

echo ""
echo "[2/5] STM32 example_stm32_edge"
python3 -m platformio run -e example_stm32_edge

echo ""
echo "[3/5] Native unit tests"
python3 -m platformio test -e native

cd "$ROOT"

echo ""
echo "[4/5] A7672 4G gateway"
cd "ESP32 4G LTE A7672 MODULE"
python3 -m platformio run

cd "$ROOT"

echo ""
echo "[5/5] Raspberry Pi dry-run"
cd edge/raspberry_pi
pip install -q -r requirements.txt
python3 telemetry_gateway.py --dry-run --once

cd "$ROOT"
echo ""
echo "=== ALL SMOKE CHECKS PASSED ==="
