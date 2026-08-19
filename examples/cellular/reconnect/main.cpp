#include <Arduino.h>

#include "iotpoc/cellular/modem_state.h"
#include "iotpoc/cellular/reconnect.h"
#include "iotpoc/hal/board.h"

using iotpoc::cellular::ModemState;
using iotpoc::cellular::ReconnectPolicy;
using iotpoc::cellular::modem_state_name;
using iotpoc::hal::board_init_serial;

void setup() {
    board_init_serial();
    ReconnectPolicy policy;
    ModemState state = ModemState::Ready;
    const uint32_t d1 = policy.on_link_lost(state);
    const uint32_t d2 = policy.on_link_lost(state);
    Serial.print("[example] reconnect state=");
    Serial.print(modem_state_name(state));
    Serial.print(" delays=");
    Serial.print(d1);
    Serial.print(",");
    Serial.println(d2);
}

void loop() {
    delay(5000);
}
