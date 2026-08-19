#include "iotpoc/comm/rs485.h"

namespace iotpoc {
namespace comm {

Rs485Port::Rs485Port(hal::IUart& uart, IDirectionPin& direction)
    : uart_(uart), direction_(direction) {}

bool Rs485Port::write_frame(const uint8_t* data, size_t length) {
    direction_.set_transmit(true);
    const bool ok = uart_.write_bytes(data, length);
    direction_.set_transmit(false);
    return ok;
}

int Rs485Port::read_byte(uint32_t timeout_ms) {
    return uart_.read_byte(timeout_ms);
}

}  // namespace comm
}  // namespace iotpoc
