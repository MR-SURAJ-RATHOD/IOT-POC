#include <Arduino.h>

#include "iotpoc/rtos/app_fsm.h"

using iotpoc::rtos::AppEvent;
using iotpoc::rtos::AppState;
using iotpoc::rtos::app_next_state;
using iotpoc::rtos::app_state_name;

void setup() {
    Serial.begin(115200);
    delay(200);
    AppState s = AppState::Idle;
    s = app_next_state(s, AppEvent::Start);
    s = app_next_state(s, AppEvent::Ready);
    Serial.print("[fsm] ");
    Serial.println(app_state_name(s));
    s = app_next_state(s, AppEvent::LinkLost);
    Serial.print("[fsm] ");
    Serial.println(app_state_name(s));
    s = app_next_state(s, AppEvent::LinkUp);
    Serial.print("[fsm] ");
    Serial.println(app_state_name(s));
}

void loop() {
    delay(5000);
}
