#include "iotpoc/sensors/rs485.h"

namespace iotpoc {
namespace sensors {

ModbusHoldingSensor::ModbusHoldingSensor(const char* id, uint8_t slave, uint16_t address)
    : id_(id), slave_(slave), address_(address), value_(0), ready_(false) {}

bool ModbusHoldingSensor::init() {
    ready_ = true;
    return true;
}

void ModbusHoldingSensor::inject_register(uint16_t value) {
    value_ = value;
}

bool ModbusHoldingSensor::build_request(uint8_t* out, size_t out_size, size_t* out_len) const {
    return comm::modbus_build_read_holding(slave_, address_, 1, out, out_size, out_len);
}

bool ModbusHoldingSensor::read(SensorReading& out) {
    out.sensor_id = id_;
    out.quantity = Quantity::Raw;
    out.unit = "reg";
    out.timestamp_ms = 0;
    if (!ready_) {
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = SensorError::NotInitialized;
        return false;
    }
    out.value = static_cast<float>(value_);
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    return true;
}

SensorMetadata ModbusHoldingSensor::metadata() const {
    SensorMetadata meta;
    meta.sensor_id = id_;
    meta.category = "rs485";
    meta.bus = "modbus_rtu";
    return meta;
}

}  // namespace sensors
}  // namespace iotpoc
