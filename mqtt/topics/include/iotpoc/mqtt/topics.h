#pragma once

#include <stddef.h>

namespace iotpoc {
namespace mqtt {

/**
 * Canonical topic layout (change the prefix here if your broker uses another tree).
 *
 *   devices/{device_id}/telemetry   JSON samples, usually not retained
 *   devices/{device_id}/status      retained "online" / LWT "offline"
 *   devices/{device_id}/heartbeat
 *   devices/{device_id}/cmd         subscribe — same parser as USB serial
 *   devices/{device_id}/cmd/ack
 *   devices/{device_id}/cfg         subscribe — interval_ms=... payloads
 *
 * device_id comes from IOTPOC_DEVICE_ID (config.local.h).
 */

bool topic_telemetry(const char* device_id, char* out, size_t out_size);
bool topic_status(const char* device_id, char* out, size_t out_size);
bool topic_heartbeat(const char* device_id, char* out, size_t out_size);
bool topic_cmd(const char* device_id, char* out, size_t out_size);
bool topic_cmd_ack(const char* device_id, char* out, size_t out_size);
bool topic_cfg(const char* device_id, char* out, size_t out_size);

}  // namespace mqtt
}  // namespace iotpoc
