# Cellular (Quectel)

Original AT stack. First documented module class: LTE Cat.1 / **EC2xx-style**. Other families should add a `ModuleProfile` (timeouts, command variants), not a fork of the parser.

## Layers

1. `AtParser` — line assembly, OK/ERROR/CME, URC heuristic, digit masking
2. `AtClient` — one command in flight, timeout slices, echo skip
3. `modem_next_state` — Idle → AT → SIM → registration → signal → PDP → Ready; faults go to Backoff
4. Feature modules: SIM, network, PDP, HTTP, HTTPS, MQTT-AT, GNSS, NTP, reconnect, diagnostics

Transport is `iotpoc::hal::IUart`. On ESP32, `ArduinoUart` wraps `Serial2`.

## Examples

| Environment | Focus |
| --- | --- |
| `example_at_handling` | `AT` / parser tokens |
| `example_sim_status` | `AT+CPIN?` |
| `example_network_registration` | `AT+CEREG?` |
| `example_signal_quality` | `AT+CSQ` |
| `example_apn_pdp` | `AT+CGDCONT` (APN placeholder) |
| `example_http` / `example_https` | Modem HTTP and TLS context placeholder |
| `example_mqtt_at` | Modem-hosted MQTT open |
| `example_gnss` / `example_ntp` | GNSS and time |
| `example_reconnect` | Exponential backoff |
| `example_diagnostics` | `AT+CGMI` / `AT+CGMR` |
| `poc_cellular_data_path` | Full bring-up + watchdog |

## TLS

Prefer **public test** endpoints. Private certificates stay in gitignored files. Modem TLS (`AT+QSSLCFG`) and ESP32 TLS (after PPP, future) are different trust stores — document which path you use.

Do not log IMSI/ICCID. `mask_secret()` redacts long numeric strings.
