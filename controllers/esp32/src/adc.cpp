#include "iotpoc/hal/adc.h"

#include <Arduino.h>

namespace iotpoc {
namespace hal {

int adc_read_raw(int pin) {
    return analogRead(pin);
}

float adc_raw_to_volts(int raw, float vref, int max_raw) {
    if (max_raw <= 0) {
        return 0.0f;
    }
    if (raw < 0) {
        raw = 0;
    }
    if (raw > max_raw) {
        raw = max_raw;
    }
    return (static_cast<float>(raw) / static_cast<float>(max_raw)) * vref;
}

}  // namespace hal
}  // namespace iotpoc
