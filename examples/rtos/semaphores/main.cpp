#include <Arduino.h>

static SemaphoreHandle_t pulse;

static void isr_standin(void*) {
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(700));
        xSemaphoreGive(pulse);
    }
}

static void waiter(void*) {
    for (;;) {
        if (xSemaphoreTake(pulse, portMAX_DELAY) == pdTRUE) {
            Serial.println("[sem] pulse");
        }
    }
}

void setup() {
    Serial.begin(115200);
    delay(200);
    pulse = xSemaphoreCreateBinary();
    xTaskCreate(isr_standin, "isr", 2048, nullptr, 3, nullptr);
    xTaskCreate(waiter, "wait", 2048, nullptr, 2, nullptr);
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(10000));
}
