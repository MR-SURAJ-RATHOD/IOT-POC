#pragma once

#include <stdint.h>

namespace iotpoc {
namespace cellular {

/** Result of one AT exchange. Timeout is common if TX/RX are swapped. */
enum class AtStatus {
    Ok = 0,
    Error,
    CmeError,
    Timeout,
    Transport
};

/**
 * Bring-up states. Walk: Idle -> CheckAt -> CheckSim -> CheckRegistration
 * -> CheckSignal -> ConfigurePdp -> Ready. Failures go to Backoff or Fault.
 * Table: modem_next_state() in modem_state.cpp — edit there, not in examples.
 */
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

/** Timeouts for the first documented module class (EC2xx-style). Add BG9x as another profile, do not fork the parser. */
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
