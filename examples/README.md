Single-concern firmware demos. Build from `firmware/`:

```text
pio run -e example_at_handling
pio run -e example_mqtt_publish
pio run -e example_rtos_tasks
```

Cellular examples expect a Quectel module on UART (see `config.example.h` pins). MQTT Wi-Fi examples skip broker connect while placeholders remain.
