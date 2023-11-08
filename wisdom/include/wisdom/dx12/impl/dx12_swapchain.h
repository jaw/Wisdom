#pragma once
#ifndef WISDOM_HEADER_ONLY
#include <wisdom/dx12/xdx12_swapchain.h>
#endif // !WISDOM_HEADER_ONLY
#include <wisdom/dx12/xdx12_device.h>
#include <d3d11.h>

namespace wis::detail {
inline void DX12ToSwapchainDesc(DXGI_SWAP_CHAIN_DESC1& swap_desc, const wis::SwapchainDesc* desc)
{
    swap_desc.Width = desc->size.width;
    swap_desc.Height = desc->size.height;
    swap_desc.Format = convert_dx(desc->format);
    swap_desc.Stereo = desc->stereo;
    swap_desc.SampleDesc.Count = 1u;
    swap_desc.SampleDesc.Quality = 0u;
    swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_desc.BufferCount = desc->buffer_count;
    swap_desc.Scaling = DXGI_SCALING_STRETCH;
    swap_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swap_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    swap_desc.Flags = 0;
}
inline wis::com_ptr<ID3D11Device> CreateD3D11Device() noexcept
{
    constexpr D3D_FEATURE_LEVEL featureLevels[]{
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1
    };

    wis::com_ptr<ID3D11Device> device11;
    D3D11CreateDevice(nullptr,
                      D3D_DRIVER_TYPE_HARDWARE,
                      nullptr, 0,
                      featureLevels, 3, D3D11_SDK_VERSION, device11.put(), nullptr, nullptr);
    return device11;
}
} // namespace wis::detail

std::pair<wis::Result, wis::DX12SwapChain>
wis::DX12CreateSwapchainWin32(const DX12Device& device, DX12QueueView main_queue, const wis::SwapchainDesc* desc, void* hwnd) noexcept
{
    DXGI_SWAP_CHAIN_DESC1 swap_desc;
    detail::DX12ToSwapchainDesc(swap_desc, desc);
    HWND hwnd_ = static_cast<HWND>(hwnd);
    auto& devicei = device.GetInternal();

    HRESULT hr;

    wis::com_ptr<IDXGISwapChain1> swap;

    // until microsoft fixes this
    if (desc->stereo && !wis::succeeded(hr = devicei.factory->CreateSwapChainForHwnd(detail::CreateD3D11Device().get(), hwnd_, &swap_desc, nullptr, nullptr, swap.put()))) {
        return std::pair{
            wis::make_result<FUNC, "Failed to create D3D11 device for stereo mode">(hr), DX12SwapChain{}
        };
    }

    hr = devicei.factory->CreateSwapChainForHwnd(
            std::get<0>(main_queue), // Swap chain needs the queue so that it can force a flush on it.
            hwnd_,
            &swap_desc,
            nullptr,
            nullptr,
            swap.put());

    if (!wis::succeeded(hr)) {
        return std::pair{
            wis::make_result<FUNC, "Failed to create swapchain for hwnd">(hr), DX12SwapChain{}
        };
    }
    auto [hrx, swap4] = swap.as<IDXGISwapChain4>();
    return wis::succeeded(hrx)
            ? std::pair{ wis::success, DX12SwapChain{ std::move(swap4) } }
            : std::pair{ wis::make_result<FUNC, "Failed to create swapchain">(hr), DX12SwapChain{} };
}