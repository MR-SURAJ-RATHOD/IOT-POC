#pragma once

namespace iotpoc {
namespace hal {

void board_init_serial(unsigned long baud = 115200);
const char* board_reset_reason();

}  // namespace hal
}  // namespace iotpoc
