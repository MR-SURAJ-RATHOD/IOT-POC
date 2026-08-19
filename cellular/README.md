# Quectel cellular

Original AT stack for Quectel LTE modules (first documented class: Cat.1 / EC2xx-style). Folders:

- `at_core/` parser, client, module profile, bring-up state machine
- `sim/` `network/` `pdp/` registration and packet data
- `http/` `https/` `mqtt_at/` application protocols on the modem
- `gnss/` `ntp/`
- `reconnect/` exponential backoff around the state machine
- `diagnostics/` manufacturer/firmware queries

Examples live under `examples/cellular/`. Credentials and APNs stay in `config.local.h`.
