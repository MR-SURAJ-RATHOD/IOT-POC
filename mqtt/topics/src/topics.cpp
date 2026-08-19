#include "iotpoc/mqtt/topics.h"

#include <cstdio>
#include <cstring>

namespace iotpoc {
namespace mqtt {
namespace {

/* Single formatter so all topics stay devices/{id}/{suffix}. Change the pattern here. */
bool format_topic(char* out, size_t out_size, const char* device_id, const char* suffix) {
    if (out == nullptr || device_id == nullptr || suffix == nullptr || out_size < 8) {
        return false;
    }
    const int n = std::snprintf(out, out_size, "devices/%s/%s", device_id, suffix);
    return n > 0 && static_cast<size_t>(n) < out_size;
}

}  // namespace

bool topic_telemetry(const char* device_id, char* out, size_t out_size) {
    return format_topic(out, out_size, device_id, "telemetry");
}
bool topic_status(const char* device_id, char* out, size_t out_size) {
    return format_topic(out, out_size, device_id, "status");
}
bool topic_heartbeat(const char* device_id, char* out, size_t out_size) {
    return format_topic(out, out_size, device_id, "heartbeat");
}
bool topic_cmd(const char* device_id, char* out, size_t out_size) {
    return format_topic(out, out_size, device_id, "cmd");
}
bool topic_cmd_ack(const char* device_id, char* out, size_t out_size) {
    return format_topic(out, out_size, device_id, "cmd/ack");
}
bool topic_cfg(const char* device_id, char* out, size_t out_size) {
    return format_topic(out, out_size, device_id, "cfg");
}

}  // namespace mqtt
}  // namespace iotpoc
