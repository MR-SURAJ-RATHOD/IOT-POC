#pragma once

#include <stddef.h>
#include <stdint.h>

namespace iotpoc {
namespace comm {

/**
 * Modbus RTU CRC-16 (polynomial 0xA001). Used by RS-485 holding-register POC.
 * CHANGE slave id / start address in the sensor constructor, not in this CRC.
 */
uint16_t modbus_crc16(const uint8_t* data, size_t length);

bool modbus_build_read_holding(uint8_t slave,
                               uint16_t start_address,
                               uint16_t quantity,
                               uint8_t* out,
                               size_t out_size,
                               size_t* out_len);

bool modbus_crc_ok(const uint8_t* adu, size_t length);

}  // namespace comm
}  // namespace iotpoc
