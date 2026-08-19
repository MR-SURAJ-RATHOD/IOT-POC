#pragma once

#include <stdint.h>

namespace iotpoc {
namespace rtos {

class ExponentialBackoff {
public:
    ExponentialBackoff(uint32_t initial_ms, uint32_t max_ms, uint32_t multiplier);
    uint32_t next_delay_ms();
    void reset();
    uint32_t attempt() const { return attempt_; }

private:
    uint32_t initial_ms_;
    uint32_t max_ms_;
    uint32_t multiplier_;
    uint32_t current_ms_;
    uint32_t attempt_;
};

}  // namespace rtos
}  // namespace iotpoc
