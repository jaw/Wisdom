#pragma once
// Select default API
// Override with WISDOM_FORCE_VULKAN
#include <wisdom/config.h>

#ifdef WISDOM_UWP
static_assert(WISDOM_UWP && _WIN32, "Platform error");
#endif // WISDOM_UWP

#ifdef WISDOM_WINDOWS
static_assert(WISDOM_WINDOWS && _WIN32, "Platform error");
#endif // WISDOM_WINDOWS

#ifdef WISDOM_LINUX
static_assert(WISDOM_LINUX && __linux__, "Platform error");
#endif // WISDOM_LINUX

#if defined(WISDOM_VULKAN) && defined(WISDOM_FORCE_VULKAN)
#define FORCEVK_SWITCH 1
#else
#define FORCEVK_SWITCH 0
#endif // WISDOM_VULKAN_FOUND

#if defined(WISDOM_DX12) && !FORCEVK_SWITCH
#include "wisdom_dx12.hpp"

namespace wis {

inline constexpr wis::ShaderIntermediate shader_intermediate = wis::ShaderIntermediate::DXIL;

using CommandQueue = DX12CommandQueue;
using Factory = DX12Factory;
using DeviceExtension = DX12DeviceExtension;
using PipelineState = DX12PipelineState;
using Adapter = DX12Adapter;
using Device = DX12Device;
using DescriptorBuffer = DX12DescriptorBuffer;
using FactoryExtension = DX12FactoryExtension;
using ResourceAllocator = DX12ResourceAllocator;
using Fence = DX12Fence;
using CommandList = DX12CommandList;
using Memory = DX12Memory;
using SwapChain = DX12SwapChain;
using Buffer = DX12Buffer;
using Texture = DX12Texture;
using RootSignature = DX12RootSignature;
using Shader = DX12Shader;
using DebugMessenger = DX12DebugMessenger;
using RenderTarget = DX12RenderTarget;
using Sampler = DX12Sampler;
using ShaderResource = DX12ShaderResource;

//-------------------------------------------------------------------------

/**
 * @brief Creates the wis::Factory with extensions, specified in extension array.
 * @param debug_layer Enable the debug layer for underlying API.
 * @param extensions The extensions to enable.
 * The extensions are initialized through this array.
 * @param extension_count The number of extensions to enable.
 * @return wis::Factory on success (wis::Status::Ok).
 * */
inline wis::ResultValue<wis::Factory> CreateFactory(bool debug_layer = false, wis::FactoryExtension** extensions = nullptr, uint32_t extension_count = 0)
{
    return DX12CreateFactory(debug_layer, extensions, extension_count);
}
/**
 * @brief Creates the wis::Device with extensions, specified in extension array.
 * @param adapter The adapter to create the logical device on. Must not be NULL.
 * @param extensions The extensions to enable.
 * The extensions are initialized through this array.
 * @param extension_count The number of extensions to enable.
 * @param force Create logical device even if some core functionality is absent.
 * The presence of core functionality is checked by the query function.
 * @return wis::Device on success (wis::Status::Ok).
 * */
inline wis::ResultValue<wis::Device> CreateDevice(wis::Adapter adapter, wis::DeviceExtension** extensions = nullptr, uint32_t extension_count = 0, bool force = false)
{
    return DX12CreateDevice(std::move(adapter), extensions, extension_count, force);
}

//-------------------------------------------------------------------------

using FenceView = DX12FenceView;
using BufferView = DX12BufferView;
using TextureView = DX12TextureView;
using RenderTargetView = DX12RenderTargetView;
using CommandListView = DX12CommandListView;
using ShaderView = DX12ShaderView;
using RootSignatureView = DX12RootSignatureView;
using DescriptorBufferView = DX12DescriptorBufferView;
using DescriptorBufferGPUView = DX12DescriptorBufferGPUView;
using RootSignatureView2 = DX12RootSignatureView2;
using MemoryView = DX12MemoryView;
using PipelineHandle = DX12PipelineHandle;
using SamplerView = DX12SamplerView;
using ShaderResourceView = DX12ShaderResourceView;
using BufferBarrier2 = DX12BufferBarrier2;
using TextureBarrier2 = DX12TextureBarrier2;
using GraphicsShaderStages = DX12GraphicsShaderStages;
using GraphicsPipelineDesc = DX12GraphicsPipelineDesc;
using RenderPassRenderTargetDesc = DX12RenderPassRenderTargetDesc;
using RenderPassDepthStencilDesc = DX12RenderPassDepthStencilDesc;
using RenderPassDesc = DX12RenderPassDesc;
using VertexBufferBinding = DX12VertexBufferBinding;
} // namespace wis

#elif defined(WISDOM_VULKAN)
#include "wisdom_vk.hpp"

namespace wis {

inline constexpr wis::ShaderIntermediate shader_intermediate = wis::ShaderIntermediate::SPIRV;

using CommandQueue = VKCommandQueue;
using Factory = VKFactory;
using DeviceExtension = VKDeviceExtension;
using PipelineState = VKPipelineState;
using Adapter = VKAdapter;
using Device = VKDevice;
using DescriptorBuffer = VKDescriptorBuffer;
using FactoryExtension = VKFactoryExtension;
using ResourceAllocator = VKResourceAllocator;
using Fence = VKFence;
using CommandList = VKCommandList;
using Memory = VKMemory;
using SwapChain = VKSwapChain;
using Buffer = VKBuffer;
using Texture = VKTexture;
using RootSignature = VKRootSignature;
using Shader = VKShader;
using DebugMessenger = VKDebugMessenger;
using RenderTarget = VKRenderTarget;
using Sampler = VKSampler;
using ShaderResource = VKShaderResource;

//-------------------------------------------------------------------------

/**
 * @brief Creates the wis::Factory with extensions, specified in extension array.
 * @param debug_layer Enable the debug layer for underlying API.
 * @param extensions The extensions to enable.
 * The extensions are initialized through this array.
 * @param extension_count The number of extensions to enable.
 * @return wis::Factory on success (wis::Status::Ok).
 * */
inline wis::ResultValue<wis::Factory> CreateFactory(bool debug_layer = false, wis::FactoryExtension** extensions = nullptr, uint32_t extension_count = 0)
{
    return VKCreateFactory(debug_layer, extensions, extension_count);
}
/**
 * @brief Creates the wis::Device with extensions, specified in extension array.
 * @param adapter The adapter to create the logical device on. Must not be NULL.
 * @param extensions The extensions to enable.
 * The extensions are initialized through this array.
 * @param extension_count The number of extensions to enable.
 * @param force Create logical device even if some core functionality is absent.
 * The presence of core functionality is checked by the query function.
 * @return wis::Device on success (wis::Status::Ok).
 * */
inline wis::ResultValue<wis::Device> CreateDevice(wis::Adapter adapter, wis::DeviceExtension** extensions = nullptr, uint32_t extension_count = 0, bool force = false)
{
    return VKCreateDevice(std::move(adapter), extensions, extension_count, force);
}

//-------------------------------------------------------------------------

using FenceView = VKFenceView;
using BufferView = VKBufferView;
using TextureView = VKTextureView;
using RenderTargetView = VKRenderTargetView;
using CommandListView = VKCommandListView;
using ShaderView = VKShaderView;
using RootSignatureView = VKRootSignatureView;
using DescriptorBufferView = VKDescriptorBufferView;
using DescriptorBufferGPUView = VKDescriptorBufferGPUView;
using RootSignatureView2 = VKRootSignatureView2;
using MemoryView = VKMemoryView;
using PipelineHandle = VKPipelineHandle;
using SamplerView = VKSamplerView;
using ShaderResourceView = VKShaderResourceView;
using BufferBarrier2 = VKBufferBarrier2;
using TextureBarrier2 = VKTextureBarrier2;
using GraphicsShaderStages = VKGraphicsShaderStages;
using GraphicsPipelineDesc = VKGraphicsPipelineDesc;
using RenderPassRenderTargetDesc = VKRenderPassRenderTargetDesc;
using RenderPassDepthStencilDesc = VKRenderPassDepthStencilDesc;
using RenderPassDesc = VKRenderPassDesc;
using VertexBufferBinding = VKVertexBufferBinding;
} // namespace wis

#else
#error "No API selected"
#endif
