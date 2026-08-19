#pragma once

#include <stdint.h>

namespace iotpoc {
namespace hal {

/**
 * ESP32 task watchdog. After watchdog_init(), call watchdog_add_current_task()
 * in each task you want watched, then watchdog_feed() often enough.
 *
 * If you block longer than timeout_ms without feeding, the chip resets
 * (board_reset_reason() prints "watchdog").
 *
 * See examples/rtos/watchdog and poc/cellular_data_path.
 */
void watchdog_init(uint32_t timeout_ms);
void watchdog_feed();
void watchdog_add_current_task();

}  // namespace hal
}  // namespace iotpoc
