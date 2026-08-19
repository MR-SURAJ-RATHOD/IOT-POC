#include "iotpoc/rtos/backoff.h"

namespace iotpoc {
namespace rtos {

ExponentialBackoff::ExponentialBackoff(uint32_t initial_ms, uint32_t max_ms, uint32_t multiplier)
    : initial_ms_(initial_ms == 0 ? 1 : initial_ms),
      max_ms_(max_ms < initial_ms_ ? initial_ms_ : max_ms),
      multiplier_(multiplier < 2 ? 2 : multiplier),
      current_ms_(initial_ms_),
      attempt_(0) {}

uint32_t ExponentialBackoff::next_delay_ms() {
    const uint32_t delay = current_ms_;
    ++attempt_;
    const uint32_t next = current_ms_ * multiplier_;
    current_ms_ = (next > max_ms_ || next < current_ms_) ? max_ms_ : next;
    return delay;
}

void ExponentialBackoff::reset() {
    current_ms_ = initial_ms_;
    attempt_ = 0;
}

}  // namespace rtos
}  // namespace iotpoc
