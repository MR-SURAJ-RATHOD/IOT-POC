# FreeRTOS

Arduino-ESP32 already runs FreeRTOS. Examples under `examples/rtos/` isolate one primitive each. Composed POCs (`poc_cellular_data_path`) feed the task watchdog while stepping the modem state machine.

## Portable cores (native-tested)

- `rtos/backoff` — exponential cap
- `rtos/fsm` — application states: idle, init, run, degraded, reconnect, fault

## On-device examples

| Environment | Primitive |
| --- | --- |
| `example_rtos_tasks` | `xTaskCreate` |
| `example_rtos_priorities` | priority 1 vs 3 |
| `example_rtos_queues` | producer/consumer |
| `example_rtos_mutexes` | mutex around a counter |
| `example_rtos_semaphores` | binary semaphore (ISR stand-in) |
| `example_rtos_event_groups` | SIM + IP + MQTT bits |
| `example_rtos_timers` | software timer heartbeat |
| `example_rtos_watchdog` | ESP task WDT feed |
| `example_rtos_state_machines` | `app_next_state` |

Suggested production mapping: one task for sensors, one for communications, one for MQTT, a command task, and a high-priority watchdog/supervisor. Pass telemetry on queues; lock UART/AT and I2C with mutexes.
