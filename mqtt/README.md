# MQTT

ESP32-hosted MQTT helpers (Wi-Fi first). Cellular AT-MQTT lives under `cellular/quectel/mqtt_at/`.

- `topics/` device topic layout
- `telemetry/` JSON builder for `SensorReading`
- `commands/` text command and configuration key parsing
- `client/` Arduino PubSubClient wrapper (skips connect when placeholders remain)
