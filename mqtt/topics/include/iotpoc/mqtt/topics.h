#pragma once

#include <stddef.h>

namespace iotpoc {
namespace mqtt {

bool topic_telemetry(const char* device_id, char* out, size_t out_size);
bool topic_status(const char* device_id, char* out, size_t out_size);
bool topic_heartbeat(const char* device_id, char* out, size_t out_size);
bool topic_cmd(const char* device_id, char* out, size_t out_size);
bool topic_cmd_ack(const char* device_id, char* out, size_t out_size);
bool topic_cfg(const char* device_id, char* out, size_t out_size);

}  // namespace mqtt
}  // namespace iotpoc
