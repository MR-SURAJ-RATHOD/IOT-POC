#include "iotpoc/cellular/reconnect.h"

namespace iotpoc {
namespace cellular {

ReconnectPolicy::ReconnectPolicy() : backoff_(1000, 60000, 2) {}

uint32_t ReconnectPolicy::on_link_lost(ModemState& state) {
    state = modem_next_state(state, ModemEvent::LinkLost);
    return backoff_.next_delay_ms();
}

void ReconnectPolicy::on_ready() {
    backoff_.reset();
}

}  // namespace cellular
}  // namespace iotpoc
