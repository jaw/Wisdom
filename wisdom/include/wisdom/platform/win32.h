#pragma once
#ifdef WISDOM_WINDOWS
#if WISDOM_DX12
#include <wisdom/dx12/dx12_swapchain.h>

namespace wis {
[[nodiscard]] WIS_INLINE wis::ResultValue<wis::DX12SwapChain>
DX12CreateSwapchainWin32(const DX12Device& device, DX12QueueView main_queue, const wis::SwapchainDesc* desc, HWND hwnd) noexcept;
[[nodiscard]] WIS_INLINE wis::ResultValue<wis::DX12SwapChain>
DX12CreateSwapchainUWP(const DX12Device& device, DX12QueueView main_queue, const wis::SwapchainDesc* desc, IUnknown* window) noexcept;
} // namespace wis

#endif // WISDOM_DX12
#if WISDOM_VULKAN
#include <wisdom/vulkan/vk_swapchain.h>

namespace wis {
[[nodiscard]] WIS_INLINE wis::ResultValue<wis::VKSwapChain>
VKCreateSwapchainWin32(const VKDevice& device, VKQueueView main_queue, const wis::SwapchainDesc* desc, HWND hwnd) noexcept;
}
#endif // WISDOM_VULKAN

namespace wis {
#if WISDOM_DX12 && !defined(WISDOM_FORCE_VULKAN)
constexpr auto CreateSwapchainWin32 = DX12CreateSwapchainWin32;
constexpr auto CreateSwapchainUWP = DX12CreateSwapchainUWP;
#elif WISDOM_VULKAN
constexpr auto CreateSwapchainWin32 = VKCreateSwapchainWin32;
#endif // WISDOM_DX12
} // namespace wis

#ifdef WISDOM_PLATFORM_HEADER_ONLY
#include "impl/win32.cpp"
#endif // !WISDOM_PLATFORM_HEADER_ONLY

#endif // WISDOM_WINDOWS
