#pragma once

#include "iotpoc/cellular/types.h"

namespace iotpoc {
namespace cellular {

/** Pure table: current state + event -> next state. Edit the .cpp, not examples. */
ModemState modem_next_state(ModemState current, ModemEvent event);

}  // namespace cellular
}  // namespace iotpoc
