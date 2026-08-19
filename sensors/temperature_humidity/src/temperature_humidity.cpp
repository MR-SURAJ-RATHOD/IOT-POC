#include "iotpoc/sensors/temperature_humidity.h"

namespace iotpoc {
namespace sensors {

I2cTempHumiditySensor::I2cTempHumiditySensor(const char* id,
                                             comm::I2cRegisterDevice& device,
                                             uint8_t temp_reg,
                                             uint8_t humidity_reg)
    : id_(id),
      device_(device),
      temp_reg_(temp_reg),
      humidity_reg_(humidity_reg),
      ready_(false),
      last_was_humidity_(false) {}

bool I2cTempHumiditySensor::init() {
    ready_ = true;
    return true;
}

bool I2cTempHumiditySensor::read(SensorReading& out) {
    out.sensor_id = id_;
    out.timestamp_ms = 0;
    if (!ready_) {
        out.quantity = Quantity::Temperature;
        out.unit = "C";
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = SensorError::NotInitialized;
        return false;
    }
    uint16_t raw = 0;
    if (!device_.read_u16_be(temp_reg_, raw)) {
        out.quantity = Quantity::Temperature;
        out.unit = "C";
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = SensorError::Bus;
        return false;
    }
    out.quantity = Quantity::Temperature;
    out.unit = "C";
    out.value = static_cast<float>(static_cast<int16_t>(raw)) / 100.0f;
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    last_was_humidity_ = false;
    return true;
}

bool I2cTempHumiditySensor::read_humidity(SensorReading& out) {
    out.sensor_id = id_;
    out.quantity = Quantity::Humidity;
    out.unit = "%RH";
    out.timestamp_ms = 0;
    uint16_t raw = 0;
    if (!ready_ || !device_.read_u16_be(humidity_reg_, raw)) {
        out.value = 0;
        out.quality = Quality::Invalid;
        out.error = ready_ ? SensorError::Bus : SensorError::NotInitialized;
        return false;
    }
    out.value = static_cast<float>(raw) / 100.0f;
    out.quality = Quality::Ok;
    out.error = SensorError::None;
    last_was_humidity_ = true;
    return true;
}

SensorMetadata I2cTempHumiditySensor::metadata() const {
    SensorMetadata meta;
    meta.sensor_id = id_;
    meta.category = "temperature_humidity";
    meta.bus = "i2c";
    return meta;
}

}  // namespace sensors
}  // namespace iotpoc
