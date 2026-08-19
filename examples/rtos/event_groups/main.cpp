#include <Arduino.h>

#define BIT_SIM (1 << 0)
#define BIT_IP (1 << 1)
#define BIT_MQTT (1 << 2)

static EventGroupHandle_t flags;

static void bring_up(void*) {
    vTaskDelay(pdMS_TO_TICKS(200));
    xEventGroupSetBits(flags, BIT_SIM);
    vTaskDelay(pdMS_TO_TICKS(200));
    xEventGroupSetBits(flags, BIT_IP);
    vTaskDelay(pdMS_TO_TICKS(200));
    xEventGroupSetBits(flags, BIT_MQTT);
    vTaskDelete(nullptr);
}

static void wait_ready(void*) {
    const EventBits_t all = BIT_SIM | BIT_IP | BIT_MQTT;
    xEventGroupWaitBits(flags, all, pdFALSE, pdTRUE, portMAX_DELAY);
    Serial.println("[event] SIM+IP+MQTT ready");
    vTaskDelete(nullptr);
}

void setup() {
    Serial.begin(115200);
    delay(200);
    flags = xEventGroupCreate();
    xTaskCreate(bring_up, "up", 2048, nullptr, 2, nullptr);
    xTaskCreate(wait_ready, "wait", 2048, nullptr, 2, nullptr);
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(10000));
}
