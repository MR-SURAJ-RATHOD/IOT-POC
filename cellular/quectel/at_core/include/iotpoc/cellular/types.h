#pragma once

#include <stdint.h>

namespace iotpoc {
namespace cellular {

enum class AtStatus {
    Ok = 0,
    Error,
    CmeError,
    Timeout,
    Transport
};

enum class ModemState {
    Idle = 0,
    CheckAt,
    CheckSim,
    CheckRegistration,
    CheckSignal,
    ConfigurePdp,
    Ready,
    Fault,
    Backoff
};

enum class ModemEvent {
    AtOk,
    AtError,
    SimReady,
    SimMissing,
    Registered,
    NotRegistered,
    PdpOk,
    PdpFail,
    Timeout,
    LinkLost
};

struct ModuleProfile {
    const char* name;
    uint32_t at_timeout_ms;
    uint32_t sim_timeout_ms;
    uint32_t net_timeout_ms;
    uint32_t pdp_timeout_ms;
};

const ModuleProfile& default_ec2xx_profile();

const char* modem_state_name(ModemState state);
const char* at_status_name(AtStatus status);

}  // namespace cellular
}  // namespace iotpoc
