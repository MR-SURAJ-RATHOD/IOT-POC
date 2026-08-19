# Communication helpers

Protocol helpers sit above the HAL:

- `uart/` line assembler
- `i2c/` register access
- `spi/` transfer wrapper
- `rs485/` driver-enable around UART
- `modbus/` RTU CRC-16 and read-holding ADU builder
- `commands/` portable relay command parser (ON1/OFF1/ON2/OFF2)
