/**
 * Priorities: high=3 preempts low=1 when both are runnable.
 * Higher number = higher priority on FreeRTOS.
 * Build: pio run -e example_rtos_priorities
 */

#include <Arduino.h>

static void low_task(void*) {
    for (;;) {
        Serial.println("[prio] low");
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}

static void high_task(void*) {
    for (;;) {
        Serial.println("[prio] high");
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("[example] priorities: high=3, low=1");
    xTaskCreate(low_task, "low", 2048, nullptr, 1, nullptr);
    xTaskCreate(high_task, "high", 2048, nullptr, 3, nullptr);
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(10000));
}
