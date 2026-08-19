# Sensors

Generic, reusable drivers. Environmental quantities (temperature, wind, rain, UV) are **category examples**, not the identity of this repository.

All drivers implement `iotpoc::sensors::ISensor` and return `SensorReading`. Buses and pins are injected; drivers do not own global `Wire` objects.

See [docs/sensors](../docs/sensors/README.md).
