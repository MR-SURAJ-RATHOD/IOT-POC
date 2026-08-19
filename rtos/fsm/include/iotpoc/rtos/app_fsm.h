#pragma once

namespace iotpoc {
namespace rtos {

/**
 * Application-level state table (not FreeRTOS itself).
 * Edit app_next_state() in rtos/fsm/src/app_fsm.cpp to add transitions.
 *
 * Typical path: Idle --Start--> Init --Ready--> Run
 *               Run --LinkLost--> Reconnect --LinkUp--> Run
 *               any --Fatal--> Fault (terminal)
 */
enum class AppState {
    Idle = 0,
    Init,
    Run,
    Degraded,
    Reconnect,
    Fault
};

enum class AppEvent {
    Start,
    Ready,
    SensorFail,
    LinkLost,
    LinkUp,
    Fatal
};

AppState app_next_state(AppState current, AppEvent event);
const char* app_state_name(AppState state);

}  // namespace rtos
}  // namespace iotpoc
