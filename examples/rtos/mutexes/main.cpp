/**
 * Mutex: two tasks bump a shared int. Take mutex before the shared write, give after.
 * Same pattern for I2C / AT UART (one owner at a time).
 * Build: pio run -e example_rtos_mutexes
 */

#include <Arduino.h>

static SemaphoreHandle_t mutex;
static int shared;

static void bump(void* arg) {
    const int step = static_cast<int>(reinterpret_cast<intptr_t>(arg));
    for (;;) {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            shared += step;
            Serial.println(shared);
            xSemaphoreGive(mutex);
        }
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

void setup() {
    Serial.begin(115200);
    delay(200);
    mutex = xSemaphoreCreateMutex();
    xTaskCreate(bump, "a", 2048, reinterpret_cast<void*>(1), 1, nullptr);
    xTaskCreate(bump, "b", 2048, reinterpret_cast<void*>(10), 1, nullptr);
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(10000));
}
