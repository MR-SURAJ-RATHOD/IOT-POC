#pragma once

#include "iotpoc/cellular/modem_state.h"
#include "iotpoc/rtos/backoff.h"

namespace iotpoc {
namespace cellular {

/**
 * On link loss: move the modem FSM to Backoff and return the next wait (ms).
 * Call on_ready() after PDP/MQTT is healthy so the delay sequence restarts.
 */
class ReconnectPolicy {
public:
    ReconnectPolicy();
    uint32_t on_link_lost(ModemState& state);
    void on_ready();

private:
    rtos::ExponentialBackoff backoff_;
};

}  // namespace cellular
}  // namespace iotpoc
