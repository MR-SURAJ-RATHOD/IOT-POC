#pragma once

namespace iotpoc {
namespace hal {

/** USB console. Match pio device monitor / Serial Monitor: 115200 8N1. */
void board_init_serial(unsigned long baud = 115200);
/** Why we booted: power_on, watchdog, brownout, … — useful after WDT demos. */
const char* board_reset_reason();

}  // namespace hal
}  // namespace iotpoc
