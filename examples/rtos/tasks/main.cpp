/**
 * FreeRTOS: two tasks printing on Serial. Change stack (2048) / priority (1) in xTaskCreate.
 * loop() is itself a FreeRTOS task — do not block it forever without vTaskDelay.
 * Build: pio run -e example_rtos_tasks
 */

#include <Arduino.h>

static void worker(void* arg) {
    const int id = static_cast<int>(reinterpret_cast<intptr_t>(arg));
    for (;;) {
        Serial.print("[task] ");
        Serial.println(id);
        vTaskDelay(pdMS_TO_TICKS(1000 + id * 200));
    }
}

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("[example] two FreeRTOS tasks");
    xTaskCreate(worker, "w1", 2048, reinterpret_cast<void*>(1), 1, nullptr);
    xTaskCreate(worker, "w2", 2048, reinterpret_cast<void*>(2), 1, nullptr);
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(10000));
}
