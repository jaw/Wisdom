#pragma once
#include <wisdom/xvulkan/vk_fence.h>
#include <wisdom/xvulkan/vk_adapter.h>
#include <wisdom/xvulkan/vk_queue_residency.h>
#include <wisdom/xvulkan/vk_command_queue.h>
#include <wisdom/xvulkan/vk_command_list.h>
#include <wisdom/xvulkan/vk_pipeline_state.h>
#include <wisdom/xvulkan/vk_root_signature.h>
#include <wisdom/xvulkan/vk_shader.h>
#include <wisdom/xvulkan/vk_allocator.h>
#include <wisdom/xvulkan/vk_swapchain.h>
#include <wisdom/generated/vulkan/vk_structs.hpp>

namespace wis {
struct InternalFeatures {
    bool has_descriptor_buffer : 1 = false;
    bool push_descriptor_bufferless : 1 = false;
    bool dynamic_rendering : 1 = false;
    uint32_t max_ia_attributes = 0;
};

class VKDevice;

template<>
struct Internal<VKDevice> {
    wis::VKAdapter adapter;
    wis::SharedDevice device;
    InternalFeatures ifeatures;

    std::shared_ptr<VmaVulkanFunctions> allocator_functions;

    detail::QueueResidency queues;

public:
    auto& GetInstanceTable() const noexcept
    {
        return adapter.GetInternal().instance.table();
    }
};

class VKDevice : public QueryInternal<VKDevice>
{
    friend wis::ResultValue<wis::VKDevice>
    VKCreateDevice(wis::VKAdapter in_adapter) noexcept;

public:
    VKDevice() noexcept = default;
    WIS_INLINE explicit VKDevice(wis::SharedDevice device,
                                 wis::VKAdapter adapter,
                                 wis::DeviceFeatures features = wis::DeviceFeatures::None,
                                 InternalFeatures ifeatures = {}) noexcept;

    operator bool() const noexcept { return bool(device); }
    operator VKDeviceHandle() const noexcept { return device; }

public:
    [[nodicard]] WIS_INLINE wis::Result
    WaitForMultipleFences(const VKFenceView* fences,
                          const uint64_t* values,
                          uint32_t count,
                          MutiWaitFlags wait_all = MutiWaitFlags::All,
                          uint64_t timeout = std::numeric_limits<uint64_t>::max()) const noexcept;

    [[nodiscard]] WIS_INLINE wis::ResultValue<wis::VKFence>
    CreateFence(uint64_t initial_value = 0ull) const noexcept;

    [[nodiscard]] WIS_INLINE wis::ResultValue<wis::VKCommandQueue>
    CreateCommandQueue(wis::QueueType type, wis::QueuePriority priority = wis::QueuePriority::Common) const noexcept;

    [[nodiscard]] WIS_INLINE wis::ResultValue<wis::VKCommandList>
    CreateCommandList(wis::QueueType type) const noexcept;

    [[nodiscard]] WIS_INLINE wis::ResultValue<wis::VKPipelineState>
    CreateGraphicsPipeline(const wis::VKGraphicsPipelineDesc* desc) const noexcept;

    [[nodiscard]] WIS_INLINE wis::ResultValue<wis::VKRootSignature>
    CreateRootSignature(RootConstant* constants = nullptr, uint32_t constants_size = 0) const noexcept;

    [[nodiscard]] WIS_INLINE wis::ResultValue<wis::VKShader>
    CreateShader(void* bytecode, uint32_t size) const noexcept;

    [[nodiscard]] WIS_INLINE wis::ResultValue<wis::VKResourceAllocator>
    CreateAllocator() const noexcept;

public:
    [[nodiscard]] WIS_INLINE wis::ResultValue<wis::VKSwapChain>
    VKCreateSwapChain(wis::SharedSurface surface, const SwapchainDesc* desc, VkQueue graphics_queue) const noexcept;

private:
    [[nodiscard]] WIS_INLINE wis::ResultValue<VkDescriptorSetLayout>
    CreatePushDescriptorLayout(wis::PushDescriptor desc) const noexcept;

    [[nodiscard]] WIS_INLINE wis::ResultValue<VmaAllocator>
    CreateAllocatorI() const noexcept;

private:
    wis::DeviceFeatures features;
};

[[nodiscard]] WIS_INLINE wis::ResultValue<wis::VKDevice>
VKCreateDevice(wis::VKAdapter in_adapter) noexcept;

} // namespace wis

#ifdef WISDOM_HEADER_ONLY
#include "impl/vk_device.cpp"
#endif // !WISDOM_HEADER_ONLY