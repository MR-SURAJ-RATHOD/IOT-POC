#include "iotpoc/cellular/types.h"

namespace iotpoc {
namespace cellular {

namespace {
const ModuleProfile kEc2xx = {
    "EC2xx-class",
    1000,
    3000,
    8000,
    8000,
};
}  // namespace

const ModuleProfile& default_ec2xx_profile() {
    return kEc2xx;
}

const char* modem_state_name(ModemState state) {
    switch (state) {
        case ModemState::Idle:
            return "idle";
        case ModemState::CheckAt:
            return "check_at";
        case ModemState::CheckSim:
            return "check_sim";
        case ModemState::CheckRegistration:
            return "check_registration";
        case ModemState::CheckSignal:
            return "check_signal";
        case ModemState::ConfigurePdp:
            return "configure_pdp";
        case ModemState::Ready:
            return "ready";
        case ModemState::Fault:
            return "fault";
        case ModemState::Backoff:
            return "backoff";
        default:
            return "unknown";
    }
}

const char* at_status_name(AtStatus status) {
    switch (status) {
        case AtStatus::Ok:
            return "ok";
        case AtStatus::Error:
            return "error";
        case AtStatus::CmeError:
            return "cme_error";
        case AtStatus::Timeout:
            return "timeout";
        default:
            return "transport";
    }
}

}  // namespace cellular
}  // namespace iotpoc
