#pragma once
#include <array>

namespace wis {
struct Result;
struct AdapterDesc;

enum class Status : int32_t {
    Ok = 0,
    Timeout = 1,
    Error = -1,
    InvalidArgument = -2,
    OutOfMemory = -3,
    DeviceLost = -4,
};

enum class QueueType : uint32_t {
    Graphics = 0,
    DX12Bundle = 1,
    Compute = 2,
    Copy = 3,
    VideoDecode = 4,
    DX12VideoProcess = 5,
    DX12VideoEncode = 6,
};

enum class MutiWaitFlags : uint32_t {
    All = 0,
    Any = 1,
};

enum class AdapterPreference : int32_t {
    None = 0,
    MinConsumption = 1,
    Performance = 2,
};

enum class Severity {
    Debug = 0,
    Trace = 1,
    Info = 2,
    Warning = 3,
    Error = 4,
    Critical = 5,
};

enum class AdapterFlags {
    None = 0x0,
    Remote = 1 << 0,
    Software = 1 << 1,
    DX12ACGCompatible = 1 << 2,
    DX12SupportsMonitoredFences = 1 << 3,
    DX12SupportsNonMonitoredFences = 1 << 4,
    DX12KeyedMutexConformance = 1 << 5,
};

struct Result{
    wis::Status status = wis::Status::Ok;
    const char* error = nullptr;
};

struct AdapterDesc{
    std::array<const char, 256> description {};
    uint32_t vendor_id;
    uint32_t device_id;
    uint32_t subsys_id;
    uint32_t revision;
    uint64_t dedicated_video_memory;
    uint64_t dedicated_system_memory;
    uint64_t shared_system_memory;
    uint64_t adapter_id;
    wis::AdapterFlags flags;
};

//=================================DELEGATES=================================

typedef void (*DebugCallback)(wis::Severity severity, const char *message, void *user_data);
//==============================TYPE TRAITS==============================

template <typename T> struct is_flag_enum : public std::false_type {};
template <> struct is_flag_enum<wis::AdapterFlags>:public std::true_type {};
}
