// Generated by wisdom generator on 2023-11-08 23:54:58.3008943 GMT+1
#pragma once
#include <wisdom/dx12/xdx12_views.h>
#include <wisdom/api/api.h>

namespace wis{
struct DX12GraphicsShaderStages{
    wis::DX12ShaderView vertex;
    wis::DX12ShaderView hull;
    wis::DX12ShaderView domain;
    wis::DX12ShaderView geometry;
    wis::DX12ShaderView pixel;
};

struct DX12GraphicsPipelineDesc{
    wis::DX12RootSignatureView root_signature;
    wis::InputLayout input_layout;
    wis::DX12GraphicsShaderStages shaders;
    wis::RenderAttachmentsDesc attachments;
    wis::RasterizerDesc* rasterizer;
    wis::SampleDesc* sample;
    wis::BlendStateDesc* blend;
    wis::DepthStencilDesc* depth_stencil;
};

inline constexpr DXGI_GPU_PREFERENCE convert_dx(AdapterPreference value) noexcept {
    return static_cast<DXGI_GPU_PREFERENCE>(value);
}
inline constexpr D3D12_SHADER_VISIBILITY convert_dx(ShaderStages value) noexcept {
    return static_cast<D3D12_SHADER_VISIBILITY>(value);
}
inline constexpr DXGI_FORMAT convert_dx(DataFormat value) noexcept {
    return static_cast<DXGI_FORMAT>(value);
}
inline constexpr D3D12_FILL_MODE convert_dx(FillMode value) noexcept {
    return static_cast<D3D12_FILL_MODE>(value);
}
inline constexpr D3D12_CULL_MODE convert_dx(CullMode value) noexcept {
    return static_cast<D3D12_CULL_MODE>(value);
}
inline constexpr BOOL convert_dx(WindingOrder value) noexcept {
    return static_cast<BOOL>(value);
}
inline constexpr uint32_t convert_dx(SampleRate value) noexcept {
    return static_cast<uint32_t>(value);
}
inline constexpr D3D12_COMPARISON_FUNC convert_dx(Compare value) noexcept {
    return static_cast<D3D12_COMPARISON_FUNC>(value);
}
inline constexpr D3D12_STENCIL_OP convert_dx(StencilOp value) noexcept {
    return static_cast<D3D12_STENCIL_OP>(value);
}
inline constexpr D3D12_BLEND convert_dx(BlendFactor value) noexcept {
    return static_cast<D3D12_BLEND>(value);
}
inline constexpr D3D12_BLEND_OP convert_dx(BlendOp value) noexcept {
    return static_cast<D3D12_BLEND_OP>(value);
}
inline constexpr D3D12_LOGIC_OP convert_dx(LogicOp value) noexcept {
    return static_cast<D3D12_LOGIC_OP>(value);
}
}
