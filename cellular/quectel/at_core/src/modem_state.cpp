#include "iotpoc/cellular/modem_state.h"

namespace iotpoc {
namespace cellular {

ModemState modem_next_state(ModemState current, ModemEvent event) {
    if (event == ModemEvent::LinkLost) {
        return ModemState::Backoff;
    }
    switch (current) {
        case ModemState::Idle:
            return (event == ModemEvent::AtOk) ? ModemState::CheckAt : ModemState::Idle;
        case ModemState::CheckAt:
            if (event == ModemEvent::AtOk) {
                return ModemState::CheckSim;
            }
            if (event == ModemEvent::Timeout || event == ModemEvent::AtError) {
                return ModemState::Backoff;
            }
            break;
        case ModemState::CheckSim:
            if (event == ModemEvent::SimReady) {
                return ModemState::CheckRegistration;
            }
            if (event == ModemEvent::SimMissing || event == ModemEvent::Timeout) {
                return ModemState::Fault;
            }
            break;
        case ModemState::CheckRegistration:
            if (event == ModemEvent::Registered) {
                return ModemState::CheckSignal;
            }
            if (event == ModemEvent::NotRegistered || event == ModemEvent::Timeout) {
                return ModemState::Backoff;
            }
            break;
        case ModemState::CheckSignal:
            return ModemState::ConfigurePdp;
        case ModemState::ConfigurePdp:
            if (event == ModemEvent::PdpOk) {
                return ModemState::Ready;
            }
            if (event == ModemEvent::PdpFail || event == ModemEvent::Timeout) {
                return ModemState::Backoff;
            }
            break;
        case ModemState::Ready:
            if (event == ModemEvent::LinkLost) {
                return ModemState::Backoff;
            }
            return ModemState::Ready;
        case ModemState::Fault:
            return ModemState::Fault;
        case ModemState::Backoff:
            if (event == ModemEvent::AtOk) {
                return ModemState::CheckAt;
            }
            return ModemState::Backoff;
        default:
            break;
    }
    return current;
}

}  // namespace cellular
}  // namespace iotpoc
