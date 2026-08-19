#pragma once

#include "iotpoc/cellular/modem_state.h"
#include "iotpoc/rtos/backoff.h"

namespace iotpoc {
namespace cellular {

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
