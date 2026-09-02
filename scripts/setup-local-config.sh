#!/usr/bin/env bash
# Copy config templates to local gitignored files. Run from repo root.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

echo "IOT-POC local config setup (repo: $ROOT)"

copy_if_missing() {
  local src="$1" dst="$2"
  if [[ ! -f "$src" ]]; then
    echo "Skip (missing): $src"
    return
  fi
  if [[ -f "$dst" ]]; then
    echo "Exists: $dst"
  else
    cp "$src" "$dst"
    echo "Created: $dst"
  fi
}

copy_if_missing firmware/include/config.example.h firmware/include/config.local.h
copy_if_missing edge/raspberry_pi/config.example.env edge/raspberry_pi/config.local.env
copy_if_missing "ESP32 4G LTE A7672 MODULE/data/config.local.env.example" "ESP32 4G LTE A7672 MODULE/data/config.local.env"

echo ""
echo "Next steps:"
echo "  cd firmware && pio run -e poc_relay_control"
echo "  cd firmware && pio test -e native"
echo "  cd edge/raspberry_pi && python3 telemetry_gateway.py --dry-run --once"
