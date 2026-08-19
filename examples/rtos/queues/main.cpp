#include <Arduino.h>

static QueueHandle_t queue;

static void producer(void*) {
    uint32_t n = 0;
    for (;;) {
        n++;
        xQueueSend(queue, &n, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void consumer(void*) {
    uint32_t n = 0;
    for (;;) {
        if (xQueueReceive(queue, &n, portMAX_DELAY) == pdTRUE) {
            Serial.print("[queue] ");
            Serial.println(n);
        }
    }
}

void setup() {
    Serial.begin(115200);
    delay(200);
    queue = xQueueCreate(8, sizeof(uint32_t));
    xTaskCreate(producer, "prod", 2048, nullptr, 2, nullptr);
    xTaskCreate(consumer, "cons", 2048, nullptr, 2, nullptr);
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(10000));
}
