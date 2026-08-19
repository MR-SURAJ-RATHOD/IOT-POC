#include "iotpoc/comm/modbus_rtu.h"

namespace iotpoc {
namespace comm {

uint16_t modbus_crc16(const uint8_t* data, size_t length) {
    uint16_t crc = 0xFFFFu;
    if (data == nullptr) {
        return crc;
    }
    for (size_t i = 0; i < length; ++i) {
        crc ^= data[i];
        for (int bit = 0; bit < 8; ++bit) {
            if ((crc & 0x0001u) != 0) {
                crc = static_cast<uint16_t>((crc >> 1) ^ 0xA001u);
            } else {
                crc = static_cast<uint16_t>(crc >> 1);
            }
        }
    }
    return crc;
}

bool modbus_build_read_holding(uint8_t slave,
                               uint16_t start_address,
                               uint16_t quantity,
                               uint8_t* out,
                               size_t out_size,
                               size_t* out_len) {
    if (out == nullptr || out_len == nullptr || out_size < 8) {
        return false;
    }
    out[0] = slave;
    out[1] = 0x03;
    out[2] = static_cast<uint8_t>(start_address >> 8);
    out[3] = static_cast<uint8_t>(start_address & 0xFFu);
    out[4] = static_cast<uint8_t>(quantity >> 8);
    out[5] = static_cast<uint8_t>(quantity & 0xFFu);
    const uint16_t crc = modbus_crc16(out, 6);
    out[6] = static_cast<uint8_t>(crc & 0xFFu);
    out[7] = static_cast<uint8_t>(crc >> 8);
    *out_len = 8;
    return true;
}

bool modbus_crc_ok(const uint8_t* adu, size_t length) {
    if (adu == nullptr || length < 4) {
        return false;
    }
    const uint16_t crc = modbus_crc16(adu, length - 2);
    const uint16_t got = static_cast<uint16_t>(adu[length - 2] | (static_cast<uint16_t>(adu[length - 1]) << 8));
    return crc == got;
}

}  // namespace comm
}  // namespace iotpoc
