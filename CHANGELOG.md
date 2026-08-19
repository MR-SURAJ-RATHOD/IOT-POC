# Changelog

All notable changes to this project are documented in this file.

The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project uses [Semantic Versioning](https://semver.org/spec/v2.0.0.html)
starting with the first tagged release.

## [Unreleased]

### Added

- Repository identity as an Embedded & IoT Proof-of-Concept Reference (not a single-product or weather-only tree).
- Open-source governance: `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`, `SECURITY.md`, GitHub issue and pull-request templates.
- PlatformIO workspace targeting ESP32 (Arduino framework) with layered libraries: controller HAL, sensors, buses, Quectel AT core, MQTT, FreeRTOS helpers.
- Migrated serial relay POC into `poc/relay_control` using the digital-output driver and a portable command parser. Root `relaycontrol.cpp` is retained until this environment is the documented entry point.
- Sensor interface (`ISensor` / `SensorReading`) and category drivers: analog, digital, temperature/humidity, pressure, RTC, wind speed/direction, rain, UV, RS-485.
- Communication helpers: UART line framing, I2C register access, SPI stub, RS-485 direction control, Modbus RTU CRC and ADU builder.
- Quectel modular AT stack: parser, client, module profile, bring-up state machine, SIM/network/PDP/HTTP/HTTPS/MQTT-AT/GNSS/NTP/reconnect/diagnostics.
- MQTT service examples: publish, subscribe, JSON telemetry, QoS, retained messages, LWT, reconnect, backoff, heartbeat, device status, commands, configuration.
- FreeRTOS examples: tasks, priorities, queues, mutexes, semaphores, event groups, timers, watchdog, state machines.
- Native Unity tests and GitHub Actions CI (firmware matrix, native tests, secret scan).
- Teaching comments on HAL, sensors, Quectel, MQTT, RTOS, examples, and config explaining how to use each piece and where to change pins/credentials.

### Security

- Configuration examples use placeholders only; `config.local.h` is gitignored.

## [0.0.1] - 2025-08-19

### Added

- Initial public files: MIT license, stub README, Arduino serial relay sketch (`relaycontrol.cpp`).
