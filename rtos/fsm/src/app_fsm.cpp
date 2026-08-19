#include "iotpoc/rtos/app_fsm.h"

namespace iotpoc {
namespace rtos {

AppState app_next_state(AppState current, AppEvent event) {
    if (event == AppEvent::Fatal) {
        return AppState::Fault;
    }
    switch (current) {
        case AppState::Idle:
            return (event == AppEvent::Start) ? AppState::Init : AppState::Idle;
        case AppState::Init:
            if (event == AppEvent::Ready) {
                return AppState::Run;
            }
            if (event == AppEvent::SensorFail) {
                return AppState::Degraded;
            }
            if (event == AppEvent::LinkLost) {
                return AppState::Reconnect;
            }
            break;
        case AppState::Run:
            if (event == AppEvent::SensorFail) {
                return AppState::Degraded;
            }
            if (event == AppEvent::LinkLost) {
                return AppState::Reconnect;
            }
            break;
        case AppState::Degraded:
            if (event == AppEvent::Ready) {
                return AppState::Run;
            }
            if (event == AppEvent::LinkLost) {
                return AppState::Reconnect;
            }
            break;
        case AppState::Reconnect:
            if (event == AppEvent::LinkUp || event == AppEvent::Ready) {
                return AppState::Run;
            }
            break;
        case AppState::Fault:
            return AppState::Fault;
        default:
            break;
    }
    return current;
}

const char* app_state_name(AppState state) {
    switch (state) {
        case AppState::Idle:
            return "idle";
        case AppState::Init:
            return "init";
        case AppState::Run:
            return "run";
        case AppState::Degraded:
            return "degraded";
        case AppState::Reconnect:
            return "reconnect";
        default:
            return "fault";
    }
}

}  // namespace rtos
}  // namespace iotpoc
