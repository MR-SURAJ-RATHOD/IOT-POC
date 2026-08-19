# MQTT

Two complementary paths:

- **ESP32-hosted** (`mqtt/`): Wi-Fi + PubSubClient wrapper (`EspMqttClient`)
- **Modem-hosted** (`cellular/quectel/mqtt_at/`): AT MQTT on the Quectel module
- **PPP + ESP32 MQTT** is a later backend behind the same topic/JSON helpers

## Topics

```text
devices/{device_id}/telemetry    JSON, typically not retained
devices/{device_id}/status       retained online/offline
devices/{device_id}/heartbeat
devices/{device_id}/cmd          subscribe
devices/{device_id}/cmd/ack
devices/{device_id}/cfg          subscribe
```

JSON telemetry includes `"schema":1` plus sensor quantity, value, unit, and quality.

## Behaviours demonstrated

Publish, subscribe, JSON, QoS notes (PubSubClient publish is QoS 0; subscribe can request QoS 1), retained status, LWT `offline`, reconnect loop, exponential backoff, heartbeat, device status, text commands (`ON1`/`OFF1` shared with the relay POC), configuration keys (`interval_ms`).

Broker host/user/password remain placeholders unless you copy `config.local.h`. The client **skips** connect when the host still starts with `YOUR_`.
