#pragma once
#include <wisdom/vulkan/vk_views.h>
#include <wisdom/generated/api/api.h>
#include <wisdom/util/flags.h>

namespace wis{
struct VKBufferBarrier2{
    wis::BufferBarrier barrier;
    wis::VKBufferView buffer;
};

struct VKTextureBarrier2{
    wis::TextureBarrier barrier;
    wis::VKTextureView texture;
};

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
    wis::RasterizerDesc* rasterizer = nullptr;
    wis::SampleDesc* sample = nullptr;
    wis::BlendStateDesc* blend = nullptr;
    wis::DepthStencilDesc* depth_stencil = nullptr;
    wis::TopologyType topology_type = wis::TopologyType::Triangle;
};

struct VKRenderPassRenderTargetDesc{
    wis::VKRenderTargetView target;
    wis::LoadOperation load_op = wis::LoadOperation::Load;
    wis::StoreOperation store_op = wis::StoreOperation::Store;
    std::array<float, 4> clear_value {};
};

struct VKRenderPassDesc{
    wis::VKRenderPassRenderTargetDesc* targets;
    uint32_t target_count;
    wis::RenderPassFlags flags;
};

struct VKVertexBufferBinding{
    wis::VKBufferView buffer;
    uint32_t size;
    uint32_t stride;
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
inline constexpr VkDescriptorType convert_vk(DescriptorType value) noexcept{
    switch(value){
    default: return {};
    case DescriptorType::ShaderResource: return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
    case DescriptorType::ConstantBuffer: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    case DescriptorType::UnorderedAccess: return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    case DescriptorType::Sampler: return VK_DESCRIPTOR_TYPE_SAMPLER;
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
    case Compare::None: return VK_COMPARE_OP_NEVER;
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
inline constexpr VkPipelineStageFlags2 convert_vk(BarrierSync value) noexcept{
    VkPipelineStageFlags2 output = {};
    if(value & BarrierSync::All) output |= VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    if(value & BarrierSync::Draw) output |= VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT;
    return output;
}
inline constexpr VkAccessFlags2 convert_vk(ResourceAccess value) noexcept{
    VkAccessFlags2 output = {};
    if(value & ResourceAccess::VertexBuffer) output |= VK_ACCESS_2_VERTEX_ATTRIBUTE_READ_BIT;
    if(value & ResourceAccess::ConstantBuffer) output |= VK_ACCESS_2_UNIFORM_READ_BIT;
    if(value & ResourceAccess::IndexBuffer) output |= VK_ACCESS_2_INDEX_READ_BIT;
    if(value & ResourceAccess::RenderTarget) output |= VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
    if(value & ResourceAccess::UnorderedAccess) output |= VK_ACCESS_2_SHADER_WRITE_BIT | VK_ACCESS_2_SHADER_READ_BIT;
    if(value & ResourceAccess::DepthWrite) output |= VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    if(value & ResourceAccess::DepthRead) output |= VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
    if(value & ResourceAccess::ShaderResource) output |= VK_ACCESS_2_SHADER_READ_BIT;
    if(value & ResourceAccess::StreamOutput) output |= VK_ACCESS_2_TRANSFORM_FEEDBACK_WRITE_BIT_EXT;
    if(value & ResourceAccess::IndirectArgument) output |= VK_ACCESS_2_INDIRECT_COMMAND_READ_BIT;
    if(value & ResourceAccess::CopyDest) output |= VK_ACCESS_2_TRANSFER_WRITE_BIT;
    if(value & ResourceAccess::CopySource) output |= VK_ACCESS_2_TRANSFER_READ_BIT;
    if(value & ResourceAccess::ConditionalRendering) output |= VK_ACCESS_2_CONDITIONAL_RENDERING_READ_BIT_EXT;
    if(value & ResourceAccess::AccelerationStrucureRead) output |= VK_ACCESS_2_ACCELERATION_STRUCTURE_READ_BIT_KHR;
    if(value & ResourceAccess::AccelerationStrucureWrite) output |= VK_ACCESS_2_ACCELERATION_STRUCTURE_WRITE_BIT_KHR;
    if(value & ResourceAccess::ShadingRate) output |= VK_ACCESS_2_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR;
    if(value & ResourceAccess::VideoDecodeRead) output |= VK_ACCESS_2_VIDEO_DECODE_READ_BIT_KHR;
    if(value & ResourceAccess::VideoDecodeWrite) output |= VK_ACCESS_2_VIDEO_DECODE_WRITE_BIT_KHR;
    if(value & ResourceAccess::Present) output |= VK_ACCESS_2_VIDEO_DECODE_WRITE_BIT_KHR;
    if(value & ResourceAccess::NoAccess) output |= VK_ACCESS_2_NONE;
    return output;
}
inline constexpr VkImageLayout convert_vk(TextureState value) noexcept{
    switch(value){
    default: return {};
    case TextureState::Undefined: return VK_IMAGE_LAYOUT_UNDEFINED;
    case TextureState::Common: return VK_IMAGE_LAYOUT_GENERAL;
    case TextureState::Read: return VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL;
    case TextureState::RenderTarget: return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    case TextureState::UnorderedAccess: return VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL;
    case TextureState::DepthStencilWrite: return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    case TextureState::DepthStencilRead: return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
    case TextureState::ShaderResource: return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    case TextureState::CopySource: return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    case TextureState::CopyDest: return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    case TextureState::Present: return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    case TextureState::ShadingRate: return VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR;
    case TextureState::VideoDecodeRead: return VK_IMAGE_LAYOUT_VIDEO_DECODE_SRC_KHR;
    case TextureState::VideoDecodeWrite: return VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR;
    }
}
inline constexpr VkRenderingFlags convert_vk(RenderPassFlags value) noexcept{
    VkRenderingFlags output = {};
    if(value & RenderPassFlags::Suspending) output |= VK_RENDERING_SUSPENDING_BIT;
    if(value & RenderPassFlags::Resuming) output |= VK_RENDERING_RESUMING_BIT;
    return output;
}
inline constexpr VkAttachmentLoadOp convert_vk(LoadOperation value) noexcept{
    switch(value){
    default: return {};
    case LoadOperation::Load: return VK_ATTACHMENT_LOAD_OP_LOAD;
    case LoadOperation::Clear: return VK_ATTACHMENT_LOAD_OP_CLEAR;
    case LoadOperation::DontCare: return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    }
}
inline constexpr VkAttachmentStoreOp convert_vk(StoreOperation value) noexcept{
    switch(value){
    default: return {};
    case StoreOperation::Store: return VK_ATTACHMENT_STORE_OP_STORE;
    case StoreOperation::DontCare: return VK_ATTACHMENT_STORE_OP_DONT_CARE;
    case StoreOperation::Resolve: return VK_ATTACHMENT_STORE_OP_STORE;
    }
}
inline constexpr VkPrimitiveTopology convert_vk(PrimitiveTopology value) noexcept{
    switch(value){
    default: return {};
    case PrimitiveTopology::PointList: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case PrimitiveTopology::LineList: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case PrimitiveTopology::LineStrip: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case PrimitiveTopology::TriangleList: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case PrimitiveTopology::TriangleStrip: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    case PrimitiveTopology::TriangleFan: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
    case PrimitiveTopology::LineListAdj: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
    case PrimitiveTopology::LineStripAdj: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
    case PrimitiveTopology::TriangleListAdj: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
    case PrimitiveTopology::TriangleStripAdj: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
    }
}
inline constexpr VkPrimitiveTopology convert_vk(TopologyType value) noexcept{
    switch(value){
    default: return {};
    case TopologyType::Point: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case TopologyType::Line: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case TopologyType::Triangle: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case TopologyType::Patch: return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
    }
}
inline constexpr VkSampleCountFlagBits convert_vk(SampleCount value) noexcept{
    switch(value){
    default: return {};
    case SampleCount::S1: return VK_SAMPLE_COUNT_1_BIT;
    case SampleCount::S2: return VK_SAMPLE_COUNT_2_BIT;
    case SampleCount::S4: return VK_SAMPLE_COUNT_4_BIT;
    case SampleCount::S8: return VK_SAMPLE_COUNT_8_BIT;
    case SampleCount::S16: return VK_SAMPLE_COUNT_16_BIT;
    case SampleCount::S32: return VK_SAMPLE_COUNT_32_BIT;
    case SampleCount::S64: return VK_SAMPLE_COUNT_64_BIT;
    }
}
inline constexpr VkImageUsageFlags convert_vk(TextureUsage value) noexcept{
    VkImageUsageFlags output = {};
    if(value & TextureUsage::RenderTarget) output |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if(value & TextureUsage::DepthStencil) output |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    if(value & TextureUsage::CopySrc) output |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    if(value & TextureUsage::CopyDst) output |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    if(value & TextureUsage::ShaderResource) output |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
    if(value & TextureUsage::UnorderedAccess) output |= VK_IMAGE_USAGE_STORAGE_BIT;
    return output;
}
inline constexpr VkFilter convert_vk(Filter value) noexcept{
    switch(value){
    default: return {};
    case Filter::Point: return VK_FILTER_NEAREST;
    case Filter::Linear: return VK_FILTER_LINEAR;
    }
}
inline constexpr VkSamplerAddressMode convert_vk(AddressMode value) noexcept{
    switch(value){
    default: return {};
    case AddressMode::Repeat: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    case AddressMode::MirroredRepeat: return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    case AddressMode::ClampToEdge: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    case AddressMode::ClampToBorder: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
    case AddressMode::MirrorClampToEdge: return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
    }
}
inline constexpr VkImageViewType convert_vk(TextureViewType value) noexcept{
    switch(value){
    default: return {};
    case TextureViewType::Texture1D: return VK_IMAGE_VIEW_TYPE_1D;
    case TextureViewType::Texture1DArray: return VK_IMAGE_VIEW_TYPE_1D_ARRAY;
    case TextureViewType::Texture2D: return VK_IMAGE_VIEW_TYPE_2D;
    case TextureViewType::Texture2DArray: return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
    case TextureViewType::Texture2DMS: return VK_IMAGE_VIEW_TYPE_2D;
    case TextureViewType::Texture2DMSArray: return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
    case TextureViewType::Texture3D: return VK_IMAGE_VIEW_TYPE_3D;
    case TextureViewType::TextureCube: return VK_IMAGE_VIEW_TYPE_CUBE;
    case TextureViewType::TextureCubeArray: return VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
    }
}
inline constexpr VkComponentSwizzle convert_vk(ComponentSwizzle value) noexcept{
    switch(value){
    default: return {};
    case ComponentSwizzle::Red: return VK_COMPONENT_SWIZZLE_R;
    case ComponentSwizzle::Green: return VK_COMPONENT_SWIZZLE_G;
    case ComponentSwizzle::Blue: return VK_COMPONENT_SWIZZLE_B;
    case ComponentSwizzle::Alpha: return VK_COMPONENT_SWIZZLE_A;
    case ComponentSwizzle::Zero: return VK_COMPONENT_SWIZZLE_ZERO;
    case ComponentSwizzle::One: return VK_COMPONENT_SWIZZLE_ONE;
    }
}
}
