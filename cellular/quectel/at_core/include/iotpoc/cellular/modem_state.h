#pragma once

#include "iotpoc/cellular/types.h"

namespace iotpoc {
namespace cellular {

ModemState modem_next_state(ModemState current, ModemEvent event);

}  // namespace cellular
}  // namespace iotpoc
