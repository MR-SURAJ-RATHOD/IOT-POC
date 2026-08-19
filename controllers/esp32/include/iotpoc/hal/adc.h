#pragma once

#include <stdint.h>

namespace iotpoc {
namespace hal {

int adc_read_raw(int pin);
float adc_raw_to_volts(int raw, float vref = 3.3f, int max_raw = 4095);

}  // namespace hal
}  // namespace iotpoc
