#ifndef WIS_VK_SWAPCHAIN_CPP
#define WIS_VK_SWAPCHAIN_CPP
#include <wisdom/vulkan/vk_swapchain.h>
#include <wisdom/vulkan/vk_checks.h>
#include <wisdom/util/misc.h>
#include <wisdom/util/small_allocator.h>
#include <algorithm>
#include <limits>

wis::Result wis::detail::VKSwapChainCreateInfo::InitBackBuffers(VkExtent2D image_size) noexcept
{
    auto& table = device.table();
    if (!fence) {
        VkFenceCreateInfo fence_info{
            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
        };
        auto result = table.vkCreateFence(device.get(), &fence_info, nullptr, &fence);
        if (!wis::succeeded(result))
            return { wis::make_result<FUNC, "vkCreateFence failed">(result) };
    }

    uint32_t new_back_buffer_count = 0;
    auto result = table.vkGetSwapchainImagesKHR(device.get(), swapchain, &new_back_buffer_count, nullptr);

    if (new_back_buffer_count > back_buffer_count) {
        back_buffers = wis::detail::make_unique_for_overwrite<VKTexture[]>(new_back_buffer_count);
        if (!back_buffers)
            return { wis::make_result<FUNC, "failed to allocate back_buffers array">(result) };

        back_buffer_count = new_back_buffer_count;
    }

    wis::detail::limited_allocator<VkImage> allocator{ new_back_buffer_count, true };
    auto* image_data = allocator.data();
    result = table.vkGetSwapchainImagesKHR(device.get(), swapchain, &new_back_buffer_count, image_data);

    if (!wis::succeeded(result))
        return { wis::make_result<FUNC, "vkGetSwapchainImagesKHR failed">(result) };

    for (uint32_t i = 0; i < back_buffer_count; ++i) {
        back_buffers[i] = VKTexture{ format.format, image_data[i], { image_size.width, image_size.height } };
    }

    result = table.vkResetCommandBuffer(initialization, 0);
    if (!succeeded(result)) {
        return make_result<FUNC, "vkResetCommandBuffer failed">(result);
    }

    VkCommandBufferBeginInfo desc{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = nullptr,
        .flags = {},
        .pInheritanceInfo = nullptr,
    };
    result = table.vkBeginCommandBuffer(initialization, &desc);
    if (!succeeded(result)) {
        return make_result<FUNC, "vkBeginCommandBuffer failed">(result);
    }

    wis::detail::limited_allocator<VkImageMemoryBarrier2> barrier_allocator{ new_back_buffer_count, true };
    auto barrier_data = barrier_allocator.data();

    for (size_t i = 0; i < new_back_buffer_count; i++) {
        barrier_data[i] = VkImageMemoryBarrier2{
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .pNext = nullptr,
            .srcAccessMask = VK_ACCESS_2_NONE,
            .dstAccessMask = VK_ACCESS_2_NONE,
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = image_data[i],
            .subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 + uint32_t(stereo) },
        };
    }
    VkDependencyInfo dependency{
        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
        .pNext = nullptr,
        .dependencyFlags = 0,
        .imageMemoryBarrierCount = new_back_buffer_count,
        .pImageMemoryBarriers = barrier_data,
    };
    table.vkCmdPipelineBarrier2(initialization, &dependency);

    result = table.vkEndCommandBuffer(initialization);
    if (!succeeded(result)) {
        return make_result<FUNC, "vkEndCommandBuffer failed">(result);
    }

    VkSubmitInfo submit{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = nullptr,
        .waitSemaphoreCount = 0,
        .pWaitSemaphores = nullptr,
        .pWaitDstStageMask = nullptr,
        .commandBufferCount = 1,
        .pCommandBuffers = &initialization,
        .signalSemaphoreCount = 0,
        .pSignalSemaphores = nullptr,
    };
    table.vkQueueSubmit(present_queue, 1, &submit, fence);
    table.vkWaitForFences(device.get(), 1, &fence, VK_TRUE, std::numeric_limits<uint64_t>::max());
    table.vkResetFences(device.get(), 1, &fence);

    return wis::success;
}

wis::Result wis::detail::VKSwapChainCreateInfo::AquireNextIndex() const noexcept
{
    auto& dtable = device.table();
    auto result = dtable.vkAcquireNextImageKHR(device.get(), swapchain, std::numeric_limits<uint64_t>::max(), image_ready_semaphores[acquire_index], nullptr, &present_index);
    if (!wis::succeeded(result))
        return wis::make_result<FUNC, "vkAcquireNextImageKHR failed">(result);

    constexpr static VkPipelineStageFlags wait_stages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSemaphoreSubmitInfo submit_info{
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = image_ready_semaphores[acquire_index],
        .stageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
    };

    VkSubmitInfo2 desc2{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .pNext = nullptr,
        .waitSemaphoreInfoCount = 1,
        .pWaitSemaphoreInfos = &submit_info,
    };
    result = dtable.vkQueueSubmit2(graphics_queue, 1, &desc2, nullptr);
    return wis::succeeded(result) ? wis::success : wis::make_result<FUNC, "vkQueueSubmit failed">(result);
}
wis::detail::VKSwapChainCreateInfo& wis::detail::VKSwapChainCreateInfo::operator=(VKSwapChainCreateInfo&& o) noexcept
{
    if (this == &o)
        return *this;

    Destroy();
    surface = std::move(o.surface);
    device = std::move(o.device);
    adapter = o.adapter;
    swapchain = std::move(o.swapchain);
    initialization = std::move(o.initialization);

    command_pool = std::move(o.command_pool);
    present_queue = std::move(o.present_queue);
    graphics_queue = std::move(o.graphics_queue);

    render_completed_semaphore = std::move(o.render_completed_semaphore);
    image_ready_semaphores = std::move(o.image_ready_semaphores);
    back_buffers = std::move(o.back_buffers);
    fence = std::move(o.fence);

    format = o.format;
    back_buffer_count = o.back_buffer_count;
    present_mode = o.present_mode;
    stereo = o.stereo;
    stereo_requested = o.stereo_requested;
    acquire_index = o.acquire_index;
    present_index = o.present_index;
    supported_presentations = o.supported_presentations;

    return *this;
}
void wis::detail::VKSwapChainCreateInfo::Destroy() noexcept
{
    if (!swapchain)
        return;

    auto& table = device.table();
    auto hdevice = device.get();

    ReleaseSemaphores();

    for (uint32_t n = 0; n < back_buffer_count; n++) {
        table.vkDestroySemaphore(hdevice, render_completed_semaphore[n], nullptr);
        table.vkDestroySemaphore(hdevice, image_ready_semaphores[n], nullptr);
    }
    table.vkDestroyCommandPool(hdevice, command_pool, nullptr);
    table.vkDestroySwapchainKHR(hdevice, swapchain, nullptr);
}
wis::Result wis::detail::VKSwapChainCreateInfo::InitSemaphores() noexcept
{
    render_completed_semaphore = wis::detail::make_unique_for_overwrite<VkSemaphore[]>(back_buffer_count);
    if (!render_completed_semaphore)
        return { wis::make_result<FUNC, "failed to allocate render_completed_semaphore array">(VK_ERROR_OUT_OF_HOST_MEMORY) };

    image_ready_semaphores = wis::detail::make_unique_for_overwrite<VkSemaphore[]>(back_buffer_count);
    if (!image_ready_semaphores)
        return { wis::make_result<FUNC, "failed to allocate image_ready_semaphores array">(VK_ERROR_OUT_OF_HOST_MEMORY) };

    auto& table = device.table();
    VkSemaphoreCreateInfo semaphore_info{
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
    };

    for (uint32_t n = 0; n < back_buffer_count; n++) {
        auto result = table.vkCreateSemaphore(device.get(), &semaphore_info, nullptr, &render_completed_semaphore[n]);
        if (!wis::succeeded(result))
            return { wis::make_result<FUNC, "vkCreateSemaphore failed for present_semaphore">(result) };

        auto result2 = table.vkCreateSemaphore(device.get(), &semaphore_info, nullptr, &image_ready_semaphores[n]);
        if (!wis::succeeded(result2))
            return { wis::make_result<FUNC, "vkCreateSemaphore failed for image_ready_semaphore">(result) };
    }
    return wis::success;
}

void wis::detail::VKSwapChainCreateInfo::ReleaseSemaphores() noexcept
{
    auto& dtable = device.table();
    dtable.vkQueueSubmit(graphics_queue, 0, nullptr, fence);
    dtable.vkWaitForFences(device.get(), 1, &fence, VK_TRUE, std::numeric_limits<uint64_t>::max());
    dtable.vkResetFences(device.get(), 1, &fence);

    dtable.vkQueueSubmit(present_queue, 0, nullptr, fence);
    dtable.vkWaitForFences(device.get(), 1, &fence, VK_TRUE, std::numeric_limits<uint64_t>::max());
    dtable.vkResetFences(device.get(), 1, &fence);

    dtable.vkDestroyFence(device.get(), fence, nullptr);
    fence = nullptr;
}

wis::Result wis::ImplVKSwapChain::Resize(uint32_t width, uint32_t height) noexcept
{
    return VKRecreateSwapchain(width, height, nullptr);
}

wis::Result wis::ImplVKSwapChain::Present() const noexcept
{
    return VKPresent(nullptr);
}

wis::Result wis::ImplVKSwapChain::Present2(bool in_vsync) const noexcept
{
    // Dynamic VSync results in performance degradation, hence it was removed
    return Present();
}

wis::Result
wis::ImplVKSwapChain::WaitForPresent(uint64_t timeout_ns) const noexcept
{
    auto& dtable = device.table();
    if (!dtable.vkWaitForPresentKHR)
        return wis::make_result<FUNC, "vkWaitForPresentKHR not available">(VK_ERROR_UNKNOWN);

    auto res = dtable.vkWaitForPresentKHR(device.get(), swapchain, present_id, timeout_ns);
    return wis::succeeded(res) ? wis::success : wis::make_result<FUNC, "vkWaitForPresentKHR failed">(res);
}

wis::Result
wis::ImplVKSwapChain::VKRecreateSwapchain(uint32_t width, uint32_t height, void* pNext) noexcept
{
    auto& dtable = device.table();
    auto& itable = surface.header().parent.table();

    dtable.vkQueueSubmit(present_queue, 0, nullptr, fence);
    dtable.vkWaitForFences(device.get(), 1, &fence, VK_TRUE, std::numeric_limits<uint64_t>::max());
    dtable.vkResetFences(device.get(), 1, &fence);

    dtable.vkQueueSubmit(graphics_queue, 0, nullptr, fence);
    dtable.vkWaitForFences(device.get(), 1, &fence, VK_TRUE, std::numeric_limits<uint64_t>::max());
    dtable.vkResetFences(device.get(), 1, &fence);

    VkSurfaceCapabilitiesKHR caps{};
    itable.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(adapter, surface.get(), &caps);

    width = std::clamp(width, caps.minImageExtent.width, caps.maxImageExtent.width);
    height = std::clamp(height, caps.minImageExtent.height, caps.maxImageExtent.height);
    stereo = stereo_requested && caps.maxImageArrayLayers > 1;

    VkSwapchainKHR old_swapchain = swapchain;
    VkSwapchainCreateInfoKHR desc{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = pNext,
        .flags = 0,
        .surface = surface.get(),
        .minImageCount = back_buffer_count,
        .imageFormat = format.format,
        .imageColorSpace = format.colorSpace,
        .imageExtent = { width, height },
        .imageArrayLayers = stereo ? 2u : 1u,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr,
        .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = present_mode,
        .clipped = VK_TRUE,
        .oldSwapchain = old_swapchain,
    };

    auto result = dtable.vkCreateSwapchainKHR(device.get(), &desc, nullptr, &swapchain);
    if (!succeeded(result)) {
        return wis::make_result<FUNC, "vkCreateSwapchainKHR failed">(result);
    }

    dtable.vkDestroySwapchainKHR(device.get(), old_swapchain, nullptr);

    auto rres = InitBackBuffers(desc.imageExtent);
    if (rres.status != wis::Status::Ok)
        return rres;

    return AquireNextIndex();
}

wis::Result
wis::ImplVKSwapChain::VKPresent(void* pNext) const noexcept
{
    auto& dtable = device.table();

    VkSemaphoreSubmitInfo present_submit_info{
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .pNext = nullptr,
        .semaphore = render_completed_semaphore[present_index],
        .stageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
    };

    VkSubmitInfo2 desc{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .pNext = nullptr,
        .signalSemaphoreInfoCount = 1,
        .pSignalSemaphoreInfos = &present_submit_info,
    };
    dtable.vkQueueSubmit2(graphics_queue, 1, &desc, nullptr);

    VkPresentIdKHR present_id{
        .sType = VK_STRUCTURE_TYPE_PRESENT_ID_KHR,
        .pNext = pNext,
        .swapchainCount = 1,
        .pPresentIds = &this->present_id,
    };

    VkPresentInfoKHR present_info{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .pNext = dtable.vkWaitForPresentKHR ? &present_id : pNext,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &render_completed_semaphore[present_index],
        .swapchainCount = 1,
        .pSwapchains = &swapchain.handle,
        .pImageIndices = &present_index,
        .pResults = nullptr,
    };

    auto result = dtable.vkQueuePresentKHR(present_queue, &present_info);
    if (!wis::succeeded(result)) {
        return wis::make_result<FUNC, "vkQueuePresentKHR failed">(result);
    }

    acquire_index = (acquire_index + 1) % back_buffer_count;
    return AquireNextIndex();
}

#endif // VK_SWAPCHAIN_H
