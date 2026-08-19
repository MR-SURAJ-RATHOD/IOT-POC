#include "iotpoc/hal/board.h"

#include <Arduino.h>
#include <esp_system.h>

namespace iotpoc {
namespace hal {

void board_init_serial(unsigned long baud) {
    Serial.begin(baud);
    delay(100);
}

const char* board_reset_reason() {
    switch (esp_reset_reason()) {
        case ESP_RST_POWERON:
            return "power_on";
        case ESP_RST_SW:
            return "software";
        case ESP_RST_PANIC:
            return "panic";
        case ESP_RST_INT_WDT:
        case ESP_RST_TASK_WDT:
        case ESP_RST_WDT:
            return "watchdog";
        case ESP_RST_BROWNOUT:
            return "brownout";
        default:
            return "other";
    }
}

}  // namespace hal
}  // namespace iotpoc
