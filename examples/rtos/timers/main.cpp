#include <Arduino.h>

static TimerHandle_t timer;

static void on_timer(TimerHandle_t) {
    Serial.println("[timer] tick");
}

void setup() {
    Serial.begin(115200);
    delay(200);
    timer = xTimerCreate("hb", pdMS_TO_TICKS(1000), pdTRUE, nullptr, on_timer);
    xTimerStart(timer, 0);
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(10000));
}
