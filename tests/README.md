# Tests

- `native/` — Unity tests compiled with PlatformIO `native` (no ESP32).
- `fixtures/` — sanitised AT snippets (no IMSI/ICCID).
- `hardware/` — optional on-desk checklist; not a CI gate.

```text
cd firmware
pio test -e native
```
