#pragma once

namespace iotpoc {
namespace rtos {

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
