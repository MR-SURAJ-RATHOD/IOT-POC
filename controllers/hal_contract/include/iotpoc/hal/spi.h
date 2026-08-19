#pragma once

#include <stddef.h>
#include <stdint.h>

namespace iotpoc {
namespace hal {

class ISpiBus {
public:
    virtual ~ISpiBus() {}
    virtual bool transfer(uint8_t* buffer, size_t length) = 0;
};

}  // namespace hal
}  // namespace iotpoc
