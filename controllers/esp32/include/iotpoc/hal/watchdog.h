#pragma once

#include <stdint.h>

namespace iotpoc {
namespace hal {

void watchdog_init(uint32_t timeout_ms);
void watchdog_feed();
void watchdog_add_current_task();

}  // namespace hal
}  // namespace iotpoc
