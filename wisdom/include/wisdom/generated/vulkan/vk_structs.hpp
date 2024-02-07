#pragma once
#include <wisdom/vulkan/xvk_views.h>
#include <wisdom/api/api.h>

namespace wis{
struct VKGraphicsShaderStages{
    wis::VKShaderView vertex;
    wis::VKShaderView hull;
    wis::VKShaderView domain;
    wis::VKShaderView geometry;
    wis::VKShaderView pixel;
};

struct VKGraphicsPipelineDesc{
    wis::VKRootSignatureView root_signature;
    wis::InputLayout input_layout;
    wis::VKGraphicsShaderStages shaders;
    wis::RenderAttachmentsDesc attachments;
    wis::RasterizerDesc* rasterizer;
    wis::SampleDesc* sample;
    wis::BlendStateDesc* blend;
    wis::DepthStencilDesc* depth_stencil;
};

inline constexpr VkShaderStageFlagBits convert_vk(ShaderStages value) noexcept{
    switch(value){
    default: return VK_SHADER_STAGE_ALL;
    case ShaderStages::All: return VK_SHADER_STAGE_ALL;
    case ShaderStages::Vertex: return VK_SHADER_STAGE_VERTEX_BIT;
    case ShaderStages::Hull: return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
    case ShaderStages::Domain: return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
    case ShaderStages::Geometry: return VK_SHADER_STAGE_GEOMETRY_BIT;
    case ShaderStages::Pixel: return VK_SHADER_STAGE_FRAGMENT_BIT;
    case ShaderStages::Amplification: return VK_SHADER_STAGE_TASK_BIT_NV;
    case ShaderStages::Mesh: return VK_SHADER_STAGE_MESH_BIT_NV;
    }
}
inline constexpr VkFormat convert_vk(DataFormat value) noexcept{
    switch(value){
    default: return {};
    case DataFormat::RGBA32Float: return VK_FORMAT_R32G32B32A32_SFLOAT;
    case DataFormat::RGBA32Uint: return VK_FORMAT_R32G32B32A32_UINT;
    case DataFormat::RGBA32Sint: return VK_FORMAT_R32G32B32A32_SINT;
    case DataFormat::RGB32Float: return VK_FORMAT_R32G32B32_SFLOAT;
    case DataFormat::RGB32Uint: return VK_FORMAT_R32G32B32_UINT;
    case DataFormat::RGB32Sint: return VK_FORMAT_R32G32B32_SINT;
    case DataFormat::RGBA16Float: return VK_FORMAT_R16G16B16A16_SFLOAT;
    case DataFormat::RGBA16Unorm: return VK_FORMAT_R16G16B16A16_UNORM;
    case DataFormat::RGBA16Uint: return VK_FORMAT_R16G16B16A16_UINT;
    case DataFormat::RGBA16Snorm: return VK_FORMAT_R16G16B16A16_SNORM;
    case DataFormat::RGBA16Sint: return VK_FORMAT_R16G16B16A16_SINT;
    case DataFormat::RG32Float: return VK_FORMAT_R32G32_SFLOAT;
    case DataFormat::RG32Uint: return VK_FORMAT_R32G32_UINT;
    case DataFormat::RG32Sint: return VK_FORMAT_R32G32_SINT;
    case DataFormat::D32FloatS8Uint: return VK_FORMAT_D32_SFLOAT_S8_UINT;
    case DataFormat::RGB10A2Unorm: return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
    case DataFormat::RGB10A2Uint: return VK_FORMAT_A2B10G10R10_UINT_PACK32;
    case DataFormat::RG11B10Float: return VK_FORMAT_B10G11R11_UFLOAT_PACK32;
    case DataFormat::RGBA8Unorm: return VK_FORMAT_R8G8B8A8_UNORM;
    case DataFormat::RGBA8UnormSrgb: return VK_FORMAT_R8G8B8A8_SRGB;
    case DataFormat::RGBA8Uint: return VK_FORMAT_R8G8B8A8_UINT;
    case DataFormat::RGBA8Snorm: return VK_FORMAT_R8G8B8A8_SNORM;
    case DataFormat::RGBA8Sint: return VK_FORMAT_R8G8B8A8_SINT;
    case DataFormat::RG16Float: return VK_FORMAT_R16G16_SFLOAT;
    case DataFormat::RG16Unorm: return VK_FORMAT_R16G16_UNORM;
    case DataFormat::RG16Uint: return VK_FORMAT_R16G16_UINT;
    case DataFormat::RG16Snorm: return VK_FORMAT_R16G16_SNORM;
    case DataFormat::RG16Sint: return VK_FORMAT_R16G16_SINT;
    case DataFormat::D32Float: return VK_FORMAT_D32_SFLOAT;
    case DataFormat::R32Float: return VK_FORMAT_R32_SFLOAT;
    case DataFormat::R32Uint: return VK_FORMAT_R32_UINT;
    case DataFormat::R32Sint: return VK_FORMAT_R32_SINT;
    case DataFormat::D24UnormS8Uint: return VK_FORMAT_D24_UNORM_S8_UINT;
    case DataFormat::RG8Unorm: return VK_FORMAT_R8G8_UNORM;
    case DataFormat::RG8Uint: return VK_FORMAT_R8G8_UINT;
    case DataFormat::RG8Snorm: return VK_FORMAT_R8G8_SNORM;
    case DataFormat::RG8Sint: return VK_FORMAT_R8G8_SINT;
    case DataFormat::R16Float: return VK_FORMAT_R16_SFLOAT;
    case DataFormat::D16Unorm: return VK_FORMAT_D16_UNORM;
    case DataFormat::R16Unorm: return VK_FORMAT_R16_UNORM;
    case DataFormat::R16Uint: return VK_FORMAT_R16_UINT;
    case DataFormat::R16Snorm: return VK_FORMAT_R16_SNORM;
    case DataFormat::R16Sint: return VK_FORMAT_R16_SINT;
    case DataFormat::R8Unorm: return VK_FORMAT_R8_UNORM;
    case DataFormat::R8Uint: return VK_FORMAT_R8_UINT;
    case DataFormat::R8Snorm: return VK_FORMAT_R8_SNORM;
    case DataFormat::R8Sint: return VK_FORMAT_R8_SINT;
    case DataFormat::RGB9E5UFloat: return VK_FORMAT_E5B9G9R9_UFLOAT_PACK32;
    case DataFormat::RG8BG8Unorm: return VK_FORMAT_B8G8R8G8_422_UNORM;
    case DataFormat::GR8GB8Unorm: return VK_FORMAT_G8B8G8R8_422_UNORM;
    case DataFormat::BC1RGBAUnorm: return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
    case DataFormat::BC1RGBAUnormSrgb: return VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
    case DataFormat::BC2RGBAUnorm: return VK_FORMAT_BC2_UNORM_BLOCK;
    case DataFormat::BC2RGBAUnormSrgb: return VK_FORMAT_BC2_SRGB_BLOCK;
    case DataFormat::BC3RGBAUnorm: return VK_FORMAT_BC3_UNORM_BLOCK;
    case DataFormat::BC3RGBAUnormSrgb: return VK_FORMAT_BC3_SRGB_BLOCK;
    case DataFormat::BC4RUnorm: return VK_FORMAT_BC4_UNORM_BLOCK;
    case DataFormat::BC4RSnorm: return VK_FORMAT_BC4_SNORM_BLOCK;
    case DataFormat::BC5RGUnorm: return VK_FORMAT_BC5_UNORM_BLOCK;
    case DataFormat::BC5RGSnorm: return VK_FORMAT_BC5_SNORM_BLOCK;
    case DataFormat::B5R6G5Unorm: return VK_FORMAT_B5G6R5_UNORM_PACK16;
    case DataFormat::B5G5R5A1Unorm: return VK_FORMAT_B5G5R5A1_UNORM_PACK16;
    case DataFormat::BGRA8Unorm: return VK_FORMAT_B8G8R8A8_UNORM;
    case DataFormat::BGRA8UnormSrgb: return VK_FORMAT_B8G8R8A8_SRGB;
    case DataFormat::BC6HUfloat16: return VK_FORMAT_BC6H_UFLOAT_BLOCK;
    case DataFormat::BC6HSfloat16: return VK_FORMAT_BC6H_SFLOAT_BLOCK;
    case DataFormat::BC7RGBAUnorm: return VK_FORMAT_BC7_UNORM_BLOCK;
    case DataFormat::BC7RGBAUnormSrgb: return VK_FORMAT_BC7_SRGB_BLOCK;
    }
}
inline constexpr VkPolygonMode convert_vk(FillMode value) noexcept{
    switch(value){
    default: return {};
    case FillMode::Lines: return VK_POLYGON_MODE_LINE;
    case FillMode::Solid: return VK_POLYGON_MODE_FILL;
    }
}
inline constexpr VkCullModeFlags convert_vk(CullMode value) noexcept{
    switch(value){
    default: return {};
    case CullMode::None: return VK_CULL_MODE_NONE;
    case CullMode::Front: return VK_CULL_MODE_FRONT_BIT;
    case CullMode::Back: return VK_CULL_MODE_BACK_BIT;
    }
}
inline constexpr VkFrontFace convert_vk(WindingOrder value) noexcept{
    switch(value){
    default: return {};
    case WindingOrder::Clockwise: return VK_FRONT_FACE_CLOCKWISE;
    case WindingOrder::CounterClockwise: return VK_FRONT_FACE_COUNTER_CLOCKWISE;
    }
}
inline constexpr VkSampleCountFlagBits convert_vk(SampleRate value) noexcept{
    switch(value){
    default: return {};
    case SampleRate::S1: return VK_SAMPLE_COUNT_1_BIT;
    case SampleRate::S2: return VK_SAMPLE_COUNT_2_BIT;
    case SampleRate::S4: return VK_SAMPLE_COUNT_4_BIT;
    case SampleRate::S8: return VK_SAMPLE_COUNT_8_BIT;
    case SampleRate::S16: return VK_SAMPLE_COUNT_16_BIT;
    }
}
inline constexpr VkCompareOp convert_vk(Compare value) noexcept{
    switch(value){
    default: return {};
    case Compare::Never: return VK_COMPARE_OP_NEVER;
    case Compare::Less: return VK_COMPARE_OP_LESS;
    case Compare::Equal: return VK_COMPARE_OP_EQUAL;
    case Compare::LessEqual: return VK_COMPARE_OP_LESS_OR_EQUAL;
    case Compare::Greater: return VK_COMPARE_OP_GREATER;
    case Compare::NotEqual: return VK_COMPARE_OP_NOT_EQUAL;
    case Compare::GreaterEqual: return VK_COMPARE_OP_GREATER_OR_EQUAL;
    case Compare::Always: return VK_COMPARE_OP_ALWAYS;
    }
}
inline constexpr VkStencilOp convert_vk(StencilOp value) noexcept{
    switch(value){
    default: return {};
    case StencilOp::Keep: return VK_STENCIL_OP_KEEP;
    case StencilOp::Zero: return VK_STENCIL_OP_ZERO;
    case StencilOp::Replace: return VK_STENCIL_OP_REPLACE;
    case StencilOp::IncClamp: return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
    case StencilOp::DecClamp: return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
    case StencilOp::Invert: return VK_STENCIL_OP_INVERT;
    case StencilOp::IncWrap: return VK_STENCIL_OP_INCREMENT_AND_WRAP;
    case StencilOp::DecWrap: return VK_STENCIL_OP_DECREMENT_AND_WRAP;
    }
}
inline constexpr VkBlendFactor convert_vk(BlendFactor value) noexcept{
    switch(value){
    default: return {};
    case BlendFactor::Zero: return VK_BLEND_FACTOR_ZERO;
    case BlendFactor::One: return VK_BLEND_FACTOR_ONE;
    case BlendFactor::SrcColor: return VK_BLEND_FACTOR_SRC_COLOR;
    case BlendFactor::InvSrcColor: return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
    case BlendFactor::SrcAlpha: return VK_BLEND_FACTOR_SRC_ALPHA;
    case BlendFactor::InvSrcAlpha: return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    case BlendFactor::DestAlpha: return VK_BLEND_FACTOR_DST_ALPHA;
    case BlendFactor::InvDestAlpha: return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
    case BlendFactor::DestColor: return VK_BLEND_FACTOR_DST_COLOR;
    case BlendFactor::InvDestColor: return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
    case BlendFactor::SrcAlphaSat: return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
    case BlendFactor::BlendFactor: return VK_BLEND_FACTOR_CONSTANT_COLOR;
    case BlendFactor::InvBlendFactor: return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
    case BlendFactor::Src1Color: return VK_BLEND_FACTOR_SRC1_COLOR;
    case BlendFactor::InvSrc1Color: return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
    case BlendFactor::Src1Alpha: return VK_BLEND_FACTOR_SRC1_ALPHA;
    case BlendFactor::InvSrc1Alpha: return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
    }
}
inline constexpr VkBlendOp convert_vk(BlendOp value) noexcept{
    switch(value){
    default: return {};
    case BlendOp::Add: return VK_BLEND_OP_ADD;
    case BlendOp::Subtract: return VK_BLEND_OP_SUBTRACT;
    case BlendOp::RevSubtract: return VK_BLEND_OP_REVERSE_SUBTRACT;
    case BlendOp::Min: return VK_BLEND_OP_MIN;
    case BlendOp::Max: return VK_BLEND_OP_MAX;
    }
}
inline constexpr VkLogicOp convert_vk(LogicOp value) noexcept{
    switch(value){
    default: return {};
    case LogicOp::Clear: return VK_LOGIC_OP_CLEAR;
    case LogicOp::Set: return VK_LOGIC_OP_SET;
    case LogicOp::Copy: return VK_LOGIC_OP_COPY;
    case LogicOp::CopyInverted: return VK_LOGIC_OP_COPY_INVERTED;
    case LogicOp::Noop: return VK_LOGIC_OP_NO_OP;
    case LogicOp::Invert: return VK_LOGIC_OP_INVERT;
    case LogicOp::And: return VK_LOGIC_OP_AND;
    case LogicOp::Nand: return VK_LOGIC_OP_NAND;
    case LogicOp::Or: return VK_LOGIC_OP_OR;
    case LogicOp::Nor: return VK_LOGIC_OP_NOR;
    case LogicOp::Xor: return VK_LOGIC_OP_XOR;
    case LogicOp::Equiv: return VK_LOGIC_OP_EQUIVALENT;
    case LogicOp::AndReverse: return VK_LOGIC_OP_AND_REVERSE;
    case LogicOp::AndInverted: return VK_LOGIC_OP_AND_INVERTED;
    case LogicOp::OrReverse: return VK_LOGIC_OP_OR_REVERSE;
    case LogicOp::OrInverted: return VK_LOGIC_OP_OR_INVERTED;
    }
}
}
