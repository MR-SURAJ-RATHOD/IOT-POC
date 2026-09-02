# Contributing

Thank you for contributing to the Embedded & IoT Proof-of-Concept Reference.

This repository demonstrates **reusable embedded engineering patterns** on ESP32: sensors, buses, Quectel cellular, MQTT, FreeRTOS, diagnostics, and CI. It is not a single-product firmware tree and it is not a weather-station project. Environmental sensors are one driver category among several.

## Ways to contribute

- Bug reports and reproducible hardware notes
- New sensor or bus drivers that implement the shared interfaces
- Additional controller HALs (keep ESP32 working)
- Documentation, diagrams, and troubleshooting notes
- Native unit tests and CI improvements
- Focused examples that teach one pattern well

Please open an issue before large refactors or new third-party dependencies.

## Development setup

1. Install [PlatformIO Core](https://platformio.org/install/cli).
2. Clone this repository.
3. Read [docs/GETTING_STARTED.md](docs/GETTING_STARTED.md) for repo layout and which folder to use.
4. Copy `firmware/include/config.example.h` to `firmware/include/config.local.h` and fill **local** placeholders. Never commit `config.local.h`.
5. Build the first POC:

```text
cd firmware
pio run -e poc_relay_control
```

6. Run host tests (requires `gcc`/`g++` on PATH; GitHub Actions uses Ubuntu):

```text
cd firmware
python -m platformio test -e native
```

## Coding guidelines

- **Layering:** Application and examples depend on services; services depend on drivers/HAL; HAL depends on hardware. Do not call GPIO or raw AT strings from application code except in HAL-demo examples.
- **Original code:** Implement patterns yourself. Do not paste vendor SDK samples, proprietary firmware, or third-party documentation.
- **Portable cores:** Parsers, CRC, backoff, JSON builders, and state machines must compile in the `native` test environment (no `Arduino.h`).
- **Configuration:** Use placeholders (`YOUR_WIFI_SSID`, `YOUR_APN`, `YOUR_MQTT_URI`). No credentials, API keys, passwords, or private certificates.
- **Logging:** Mask IMSI, ICCID, APN passwords, broker passwords, and tokens.
- **Style:** C++11, 4-space indent, `iotpoc` namespace, file names `snake_case`.
- **License:** Contributions are accepted under the MIT License of this repository.

## Adding a sensor driver

1. Implement `iotpoc::sensors::ISensor` in the matching category folder under `sensors/`.
2. Inject bus/pin handles; do not hard-code global `Wire` or pin numbers inside the driver.
3. Add a focused example under `examples/`.
4. Document the driver in `docs/sensors/`.
5. Add native tests where logic is hardware-independent.

## Pull requests

- Keep PRs focused (one driver, one example family, or one docs change).
- Update `CHANGELOG.md` under **Unreleased**.
- Ensure CI is green: secret scan, native tests, and firmware builds.
- Do not add vendor binaries, credentials, or generated `.pio` artifacts.

## Issue templates

Use the GitHub issue templates for bugs, POC requests, and documentation.

## Security

Do not file public issues for vulnerabilities that could harm operators. See [SECURITY.md](SECURITY.md).
