#include "iotpoc/hal/watchdog.h"

#include <Arduino.h>
#include <esp_idf_version.h>
#include <esp_task_wdt.h>

namespace iotpoc {
namespace hal {

void watchdog_init(uint32_t timeout_ms) {
    uint32_t timeout_s = timeout_ms / 1000u;
    if (timeout_s < 1u) {
        timeout_s = 1u;
    }

#if ESP_IDF_VERSION_MAJOR >= 5
    (void)esp_task_wdt_deinit();
    const esp_task_wdt_config_t config = {
        .timeout_ms = timeout_s * 1000u,
        .idle_core_mask = 0,
        .trigger_panic = true,
    };
    (void)esp_task_wdt_init(&config);
#else
    (void)esp_task_wdt_init(timeout_s, true);
#endif
}

void watchdog_feed() {
    (void)esp_task_wdt_reset();
}

void watchdog_add_current_task() {
    (void)esp_task_wdt_add(NULL);
}

}  // namespace hal
}  // namespace iotpoc
