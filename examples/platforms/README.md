# Platform examples (non-ESP32)

| Environment | Platform | Folder |
| --- | --- | --- |
| `example_stm32_edge` | STM32 (Nucleo F103 default) | `stm32_edge/` |

Build from [`firmware/`](../firmware/):

```bash
cd firmware
pio run -e example_stm32_edge
```

**Raspberry Pi** edge service (Python, not PlatformIO): [`edge/raspberry_pi/`](../../edge/raspberry_pi/).

Docs: [docs/controllers/](../docs/controllers/README.md).
