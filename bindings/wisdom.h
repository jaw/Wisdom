// GENERATED
#pragma once
#include "wisdom_exports.h"
#include <stdint.h>
#include <stdbool.h>

/** \mainpage Wisdom API Documentation

<b>Version 0.3.0</b>

Copyright (c) 2024 Ilya Doroshenko. All rights reserved.
License: MIT
See also: [repository on GitHub](https://github.com/Agrael1/Wisdom)
*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Shader stages that can be used in the pipeline.
 * Main use is Root signature and descriptor management.
 * Stages have no granularity, either all or one can be selected.
 *
 * Translates to D3D12_SHADER_VISIBILITY for dx implementation.
 * Translates to VkShaderStageFlagBits for vk implementation.
 * */
enum WisShaderStages {
    ShaderStagesAll = 0, ///< All shader stages.
    ShaderStagesVertex = 1, ///< Vertex shader stage.
    ShaderStagesHull = 2, ///< Hull/Tessellation control shader stage.
    ShaderStagesDomain = 3, ///< Domain/Tessellation evaluation shader stage.
    ShaderStagesGeometry = 4, ///< Geometry shader stage.
    ShaderStagesPixel = 5, ///< Pixel/Fragment shader stage.
    ShaderStagesAmplification = 6, ///< Amplification shader stage.
    ShaderStagesMesh = 7, ///< Mesh shader stage.
    ShaderStagesCount = 8, ///< Number of stages.
};

/**
 * @brief Represents main error communication source for the API.
 * Compare against StatusOk for success.
 *
 * */
enum WisStatus {
    StatusOk = 0, ///< Operation succeded.
    /**
     * @brief Operation timed out.
     * Counts as a success value in some cases.
     * */
    StatusTimeout = 1,
    /**
     * @brief Operation partially succeeded.
     * Some times it means that core value is initialized,
     * but some functionality may be missing and may require
     * you to check if demanded functionality is in place.
     * */
    StatusPartial = 2,
    StatusError = -1, ///< Operation failed. Check WisResult::error for more details.
    /**
     * @brief One or more arguments, or parts of arguments
     * passed to the function were incorrect. Check WisResult::error for more details.
     * */
    StatusInvalidArgument = -2,
    /**
     * @brief There is no more host memory available.
     * Allocation with malloc or similar call has failed.
     * */
    StatusOutOfMemory = -3,
    /**
     * @brief Device driver was forcefully stopped.
     * Most of the time happens on swapchain presentation.
     * */
    StatusDeviceLost = -4,
    /**
     * @brief Swapchain presentation was not visible to the user.
     * Rendering is too fast.
     * */
    StatusOccluded = -5,
};

/**
 * @brief Determines the behavior when wait for multiple fences is issued.
 *
 * */
enum WisMutiWaitFlags {
    MutiWaitFlagsAll = 0, ///< All the fences in the batch are triggered.
    MutiWaitFlagsAny = 1, ///< At least one of the fences from the batch is triggered.
};

/**
 * @brief Type of the descriptor in the descriptor table.
 *
 * Translates to D3D12_DESCRIPTOR_RANGE_TYPE for dx implementation.
 * Translates to VkDescriptorType for vk implementation.
 * */
enum WisDescriptorType {
    /**
     * @brief Descriptor is a shader resource view.
     * Used for textures.
     * */
    DescriptorTypeShaderResource = 0,
    DescriptorTypeConstantBuffer = 1, ///< Descriptor is a constant buffer view.
    /**
     * @brief Descriptor is an unordered access view.
     * Used for read/write operations in compute shaders.
     * */
    DescriptorTypeUnorderedAccess = 2,
    /**
     * @brief Descriptor is a sampler.
     * Sampler is used to sample textures in shaders.
     * Stored in separate descriptor table and
     * can't be mixed with other descriptor types
     * */
    DescriptorTypeSampler = 3,
};

/**
 * @brief Type of the queue to create.
 *
 * */
enum WisQueueType {
    QueueTypeGraphics = 0, ///< Queue is used for graphics operations.
    QueueTypeCompute = 2, ///< Queue is used for compute operations.
    QueueTypeCopy = 3, ///< Queue is used for copy operations.
    QueueTypeVideoDecode = 4, ///< Queue is used for video decoding operations.
};

/**
 * @brief Oreders the adapters according to preference
 * using builtin heuristics of underlying APIs.
 *
 * Translates to DXGI_GPU_PREFERENCE for dx implementation.
 * */
enum WisAdapterPreference {
    AdapterPreferenceNone = 0, ///< No particular preference, list adapters in system divised order.
    /**
     * @brief List the adapters from low power consumption to high.
     * Order is as follows: Integrated, Discrete, External, Software.
     * */
    AdapterPreferenceMinConsumption = 1,
    /**
     * @brief List the adapters from high performance to low.
     * Order is as follows: External, Discrete, Integrated, Software.
     * */
    AdapterPreferencePerformance = 2,
};

/**
 * @brief Log message severity.
 * Used with DebugCallback and internal library logging.
 *
 * */
enum WisSeverity {
    SeverityDebug = 0, ///< Message carries debug information.
    SeverityTrace = 1, ///< Message contains trace point (function call stack info).
    SeverityInfo = 2, ///< Message contains general information.
    /**
     * @brief Message contains warning.
     * There is something wrong and it may affect performance or stability of the application.
     * */
    SeverityWarning = 3,
    /**
     * @brief Message contains error.
     * Stability of the application is compromized.
     * */
    SeverityError = 4,
    /**
     * @brief Message contains critical error.
     * The application must be shut down, no further execution.
     * */
    SeverityCritical = 5,
};

/**
 * @brief Input classification for vertex buffer data.
 *
 * */
enum WisInputClass {
    InputClassPerVertex = 0, ///< Vertex buffer data is vertex data.
    InputClassPerInstance = 1, ///< Vertex buffer data is per instance data.
};

/**
 * @brief Cull mode for rasterizer.
 * Triangle culling depends on WisWindingOrder option.
 *
 * Translates to D3D12_CULL_MODE for dx implementation.
 * Translates to VkCullModeFlags for vk implementation.
 * */
enum WisCullMode {
    CullModeNone = 1, ///< No culling.
    CullModeFront = 2, ///< Cull front-facing triangles.
    CullModeBack = 3, ///< Cull back-facing triangles.
};

/**
 * @brief Data format for data.
 * Used as a template for data in several cases.
 * Can be used to describe:
 * - Vertex buffer data format
 * - Texture data format
 * - Render target data format
 * - Depth stencil data format
 *
 * Translates to DXGI_FORMAT for dx implementation.
 * Translates to VkFormat for vk implementation.
 * */
enum WisDataFormat {
    DataFormatUnknown = 0, ///< Unknown format.
    /**
     * @brief 32 bit per channel RGBA format.
     * A four-component, 128-bit signed floating-point format that has
     * a 32-bit R component in bytes 0..3,
     * a 32-bit G component in bytes 4..7,
     * a 32-bit B component in bytes 8..11,
     * a 32-bit A component in bytes 12..15.
     * */
    DataFormatRGBA32Float = 2,
    /**
     * @brief 32 bit per channel RGBA format.
     * A four-component, 128-bit unsigned integer format that has
     * a 32-bit R component in bytes 0..3,
     * a 32-bit G component in bytes 4..7,
     * a 32-bit B component in bytes 8..11,
     * a 32-bit A component in bytes 12..15.
     * */
    DataFormatRGBA32Uint = 3,
    /**
     * @brief 32 bit per channel RGBA format.
     * A four-component, 128-bit signed integer format that has
     * a 32-bit R component in bytes 0..3,
     * a 32-bit G component in bytes 4..7,
     * a 32-bit B component in bytes 8..11,
     * a 32-bit A component in bytes 12..15.
     * */
    DataFormatRGBA32Sint = 4,
    /**
     * @brief 32 bit per channel RGB format.
     * A three-component, 96-bit signed floating-point format that has
     * a 32-bit R component in bytes 0..3,
     * a 32-bit G component in bytes 4..7,
     * a 32-bit B component in bytes 8..11.
     * */
    DataFormatRGB32Float = 6,
    /**
     * @brief 32 bit per channel RGB format.
     * A three-component, 96-bit unsigned integer format that has
     * a 32-bit R component in bytes 0..3,
     * a 32-bit G component in bytes 4..7,
     * a 32-bit B component in bytes 8..11.
     * */
    DataFormatRGB32Uint = 7,
    /**
     * @brief 32 bit per channel RGB format.
     * A three-component, 96-bit signed integer format that has
     * a 32-bit R component in bytes 0..3,
     * a 32-bit G component in bytes 4..7,
     * a 32-bit B component in bytes 8..11.
     * */
    DataFormatRGB32Sint = 8,
    /**
     * @brief 16 bit per channel RGBA format.
     * A four-component, 64-bit signed floating-point format that has
     * a 16-bit R component in bytes 0..1,
     * a 16-bit G component in bytes 2..3,
     * a 16-bit B component in bytes 4..5,
     * a 16-bit A component in bytes 6..7.
     * */
    DataFormatRGBA16Float = 10,
    /**
     * @brief 16 bit per channel RGBA format.
     * A four-component, 64-bit unsigned normalized format that has
     * a 16-bit R component in bytes 0..1,
     * a 16-bit G component in bytes 2..3,
     * a 16-bit B component in bytes 4..5,
     * a 16-bit A component in bytes 6..7.
     * */
    DataFormatRGBA16Unorm = 11,
    /**
     * @brief 16 bit per channel RGBA format.
     * A four-component, 64-bit unsigned integer format that has
     * a 16-bit R component in bytes 0..1,
     * a 16-bit G component in bytes 2..3,
     * a 16-bit B component in bytes 4..5,
     * a 16-bit A component in bytes 6..7.
     * */
    DataFormatRGBA16Uint = 12,
    /**
     * @brief 16 bit per channel RGBA format.
     * A four-component, 64-bit signed normalized format that has
     * a 16-bit R component in bytes 0..1,
     * a 16-bit G component in bytes 2..3,
     * a 16-bit B component in bytes 4..5,
     * a 16-bit A component in bytes 6..7.
     * */
    DataFormatRGBA16Snorm = 13,
    /**
     * @brief 16 bit per channel RGBA format.
     * A four-component, 64-bit signed integer format that has
     * a 16-bit R component in bytes 0..1,
     * a 16-bit G component in bytes 2..3,
     * a 16-bit B component in bytes 4..5,
     * a 16-bit A component in bytes 6..7.
     * */
    DataFormatRGBA16Sint = 14,
    /**
     * @brief 32 bit per channel RG format.
     * A two-component, 64-bit signed floating-point format that has
     * a 32-bit R component in bytes 0..3,
     * a 32-bit G component in bytes 4..7.
     * */
    DataFormatRG32Float = 16,
    /**
     * @brief 32 bit per channel RG format.
     * A two-component, 64-bit unsigned integer format that has
     * a 32-bit R component in bytes 0..3,
     * a 32-bit G component in bytes 4..7.
     * */
    DataFormatRG32Uint = 17,
    /**
     * @brief 32 bit per channel RG format.
     * A two-component, 64-bit signed integer format that has
     * a 32-bit R component in bytes 0..3,
     * a 32-bit G component in bytes 4..7.
     * */
    DataFormatRG32Sint = 18,
    /**
     * @brief 32 bit depth, 8 bit stencil format.
     * A combined depth/stencil format with a 32-bit depth component in bytes 0..3
     * and an 8-bit stencil component in bytes 4..4.
     * */
    DataFormatD32FloatS8Uint = 20,
    /**
     * @brief 10 bit per channel RGB format with 2 bit alpha.
     * A four-component, 32-bit unsigned normalized format that has
     * a 10-bit R component in bits 0..9,
     * a 10-bit G component in bits 10..19,
     * a 10-bit B component in bits 20..29,
     * a 2-bit A component in bits 30..31.
     * */
    DataFormatRGB10A2Unorm = 24,
    /**
     * @brief 10 bit per channel RGB format with 2 bit alpha.
     * A four-component, 32-bit unsigned integer format that has
     * a 10-bit R component in bits 0..9,
     * a 10-bit G component in bits 10..19,
     * a 10-bit B component in bits 20..29,
     * a 2-bit A component in bits 30..31.
     * */
    DataFormatRGB10A2Uint = 25,
    /**
     * @brief 11 bit per channel RG format with 10 bit blue.
     * A three-component, 32-bit signed floating-point format that has
     * a 11-bit R component in bits 0..10,
     * a 11-bit G component in bits 11..21,
     * a 10-bit B component in bits 22..31.
     * */
    DataFormatRG11B10Float = 26,
    /**
     * @brief 8 bit per channel RGBA format.
     * A four-component, 32-bit unsigned normalized format that has
     * an 8-bit R component in bytes 0..0,
     * an 8-bit G component in bytes 1..1,
     * an 8-bit B component in bytes 2..2,
     * an 8-bit A component in bytes 3..3.
     * */
    DataFormatRGBA8Unorm = 28,
    /**
     * @brief 8 bit per channel RGBA format. SRGB non-linear color space.
     * A four-component, 32-bit unsigned normalized non-linear SRGB format that has
     * an 8-bit R component in bytes 0..0,
     * an 8-bit G component in bytes 1..1,
     * an 8-bit B component in bytes 2..2,
     * an 8-bit A component in bytes 3..3.
     * */
    DataFormatRGBA8UnormSrgb = 29,
    /**
     * @brief 8 bit per channel RGBA format.
     * A four-component, 32-bit unsigned integer format that has
     * an 8-bit R component in bytes 0..0,
     * an 8-bit G component in bytes 1..1,
     * an 8-bit B component in bytes 2..2,
     * an 8-bit A component in bytes 3..3.
     * */
    DataFormatRGBA8Uint = 30,
    /**
     * @brief 8 bit per channel RGBA format.
     * A four-component, 32-bit signed normalized format that has
     * an 8-bit R component in bytes 0..0,
     * an 8-bit G component in bytes 1..1,
     * an 8-bit B component in bytes 2..2,
     * an 8-bit A component in bytes 3..3.
     * */
    DataFormatRGBA8Snorm = 31,
    /**
     * @brief 8 bit per channel RGBA format.
     * A four-component, 32-bit signed integer format that has
     * an 8-bit R component in bytes 0..0,
     * an 8-bit G component in bytes 1..1,
     * an 8-bit B component in bytes 2..2,
     * an 8-bit A component in bytes 3..3.
     * */
    DataFormatRGBA8Sint = 32,
    /**
     * @brief 16 bit per channel RG format.
     * A two-component, 32-bit signed floating-point format that has
     * a 16-bit R component in bytes 0..1,
     * a 16-bit G component in bytes 2..3.
     * */
    DataFormatRG16Float = 34,
    /**
     * @brief 16 bit per channel RG format.
     * A two-component, 32-bit unsigned normalized format that has
     * a 16-bit R component in bytes 0..1,
     * a 16-bit G component in bytes 2..3.
     * */
    DataFormatRG16Unorm = 35,
    /**
     * @brief 16 bit per channel RG format.
     * A two-component, 32-bit unsigned integer format that has
     * a 16-bit R component in bytes 0..1,
     * a 16-bit G component in bytes 2..3.
     * */
    DataFormatRG16Uint = 36,
    /**
     * @brief 16 bit per channel RG format.
     * A two-component, 32-bit signed normalized format that has
     * a 16-bit R component in bytes 0..1,
     * a 16-bit G component in bytes 2..3.
     * */
    DataFormatRG16Snorm = 37,
    /**
     * @brief 16 bit per channel RG format.
     * A two-component, 32-bit signed integer format that has
     * a 16-bit R component in bytes 0..1,
     * a 16-bit G component in bytes 2..3.
     * */
    DataFormatRG16Sint = 38,
    /**
     * @brief 32 bit depth format.
     * A 32-bit depth format supporting 32-bit floating-point depth values.
     * */
    DataFormatD32Float = 40,
    /**
     * @brief 32 bit per channel R format.
     * A one-component, 32-bit signed floating-point format that has
     * a 32-bit R component in bytes 0..3.
     * */
    DataFormatR32Float = 41,
    /**
     * @brief 32 bit per channel R format.
     * A one-component, 32-bit unsigned integer format that has
     * a 32-bit R component in bytes 0..3.
     * */
    DataFormatR32Uint = 42,
    /**
     * @brief 32 bit per channel R format.
     * A one-component, 32-bit signed integer format that has
     * a 32-bit R component in bytes 0..3.
     * */
    DataFormatR32Sint = 43,
    /**
     * @brief 24 bit depth, 8 bit stencil format.
     * A combined depth/stencil format with a 24-bit depth component in bytes 0..2
     * and an 8-bit stencil component in bytes 3..3.
     * */
    DataFormatD24UnormS8Uint = 45,
    /**
     * @brief 8 bit per channel RG format.
     * A two-component, 16-bit unsigned normalized format that has
     * an 8-bit R component in bytes 0..0,
     * an 8-bit G component in bytes 1..1.
     * */
    DataFormatRG8Unorm = 49,
    /**
     * @brief 8 bit per channel RG format.
     * A two-component, 16-bit unsigned integer format that has
     * an 8-bit R component in bytes 0..0,
     * an 8-bit G component in bytes 1..1.
     * */
    DataFormatRG8Uint = 50,
    /**
     * @brief 8 bit per channel RG format.
     * A two-component, 16-bit signed normalized format that has
     * an 8-bit R component in bytes 0..0,
     * an 8-bit G component in bytes 1..1.
     * */
    DataFormatRG8Snorm = 51,
    /**
     * @brief 8 bit per channel RG format.
     * A two-component, 16-bit signed integer format that has
     * an 8-bit R component in bytes 0..0,
     * an 8-bit G component in bytes 1..1.
     * */
    DataFormatRG8Sint = 52,
    /**
     * @brief 16 bit per channel R format.
     * A one-component, 16-bit signed floating-point format that has
     * a 16-bit R component in bytes 0..1.
     * */
    DataFormatR16Float = 54,
    /**
     * @brief 16 bit depth format.
     * A 16-bit depth format supporting 16-bit unsigned normalized depth values.
     * */
    DataFormatD16Unorm = 55,
    /**
     * @brief 16 bit per channel R format.
     * A one-component, 16-bit unsigned normalized format that has
     * a 16-bit R component in bytes 0..1.
     * */
    DataFormatR16Unorm = 56,
    /**
     * @brief 16 bit per channel R format.
     * A one-component, 16-bit unsigned integer format that has
     * a 16-bit R component in bytes 0..1.
     * */
    DataFormatR16Uint = 57,
    /**
     * @brief 16 bit per channel R format.
     * A one-component, 16-bit signed normalized format that has
     * a 16-bit R component in bytes 0..1.
     * */
    DataFormatR16Snorm = 58,
    /**
     * @brief 16 bit per channel R format.
     * A one-component, 16-bit signed integer format that has
     * a 16-bit R component in bytes 0..1.
     * */
    DataFormatR16Sint = 59,
    /**
     * @brief 8 bit per channel R format.
     * A one-component, 8-bit unsigned normalized format that has
     * an 8-bit R component in bytes 0..0.
     * */
    DataFormatR8Unorm = 61,
    /**
     * @brief 8 bit per channel R format.
     * A one-component, 8-bit unsigned integer format that has
     * an 8-bit R component in bytes 0..0.
     * */
    DataFormatR8Uint = 62,
    /**
     * @brief 8 bit per channel R format.
     * A one-component, 8-bit signed normalized format that has
     * an 8-bit R component in bytes 0..0.
     * */
    DataFormatR8Snorm = 63,
    /**
     * @brief 8 bit per channel R format.
     * A one-component, 8-bit signed integer format that has
     * an 8-bit R component in bytes 0..0.
     * */
    DataFormatR8Sint = 64,
    /**
     * @brief 9 bit per channel RGB format with shared exponent.
     * A three-component, 32-bit unsigned floating-point format that has
     * a 9-bit R component in bits 0..8,
     * a 9-bit G component in bits 9..17,
     * a 9-bit B component in bits 18..26,
     * a shared 5-bit exponent in bits 27..31.
     * */
    DataFormatRGB9E5UFloat = 67,
    /**
     * @brief BC1/DXT1 compressed format.
     * A four-component, block-compressed format where each 64-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned normalized RGB texel data, and provides 1 bit of alpha.
     * */
    DataFormatBC1RGBAUnorm = 71,
    /**
     * @brief BC1/DXT1 compressed format.
     * A four-component, block-compressed format where each 64-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned normalized RGB texel data with sRGB nonlinear encoding, and provides 1 bit of alpha.
     * */
    DataFormatBC1RGBAUnormSrgb = 72,
    /**
     * @brief BC2/DXT3 compressed format.
     * A four-component, block-compressed format where each 128-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned normalized RGBA texel data
     * with the first 64 bits encoding alpha values followed by 64 bits encoding RGB values
     * */
    DataFormatBC2RGBAUnorm = 74,
    /**
     * @brief BC2/DXT3 compressed format.
     * A four-component, block-compressed format where each 128-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned normalized RGBA texel data with sRGB nonlinear encoding
     * with the first 64 bits encoding alpha values followed by 64 bits encoding RGB values
     * */
    DataFormatBC2RGBAUnormSrgb = 75,
    /**
     * @brief BC3/DXT5 compressed format.
     * A four-component, block-compressed format where each 128-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned normalized RGBA texel data with the first 64 bits encoding alpha values
     * followed by 64 bits encoding RGB values
     * */
    DataFormatBC3RGBAUnorm = 77,
    /**
     * @brief BC3/DXT5 compressed format.
     * A four-component, block-compressed format where each 128-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned normalized RGBA texel data with sRGB nonlinear encoding
     * with the first 64 bits encoding alpha values followed by 64 bits encoding RGB values
     * */
    DataFormatBC3RGBAUnormSrgb = 78,
    /**
     * @brief BC4 compressed format.
     * A single-component, block-compressed format where each 64-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned normalized red texel data
     * */
    DataFormatBC4RUnorm = 80,
    /**
     * @brief BC4 compressed format.
     * A single-component, block-compressed format where each 64-bit
     * compressed texel block encodes a 4×4 rectangle
     * of signed normalized red texel data
     * */
    DataFormatBC4RSnorm = 81,
    /**
     * @brief BC5 compressed format.
     * A two-component, block-compressed format where each 128-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned normalized red and green texel data
     * */
    DataFormatBC5RGUnorm = 83,
    /**
     * @brief BC5 compressed format.
     * A two-component, block-compressed format where each 128-bit
     * compressed texel block encodes a 4×4 rectangle
     * of signed normalized red and green texel data
     * */
    DataFormatBC5RGSnorm = 84,
    /**
     * @brief 16 bit per channel RGB format.
     * A three-component, 16-bit unsigned normalized format that has
     * a 5-bit B component in bits 0..4,
     * a 6-bit G component in bits 5..10,
     * a 5-bit R component in bits 11..15.
     * */
    DataFormatB5G6R5Unorm = 85,
    /**
     * @brief 16 bit per channel RGBA format.
     * A four-component, 16-bit unsigned normalized format that has
     * a 5-bit B component in bits 0..4,
     * a 5-bit G component in bits 5..9,
     * a 5-bit R component in bits 10..14,
     * a 1-bit A component in bits 15..15.
     * */
    DataFormatB5G5R5A1Unorm = 86,
    /**
     * @brief 8 bit per channel RGBA format.
     * A four-component, 32-bit unsigned normalized format that has
     * an 8-bit B component in bytes 0..0,
     * an 8-bit G component in bytes 1..1,
     * an 8-bit R component in bytes 2..2,
     * an 8-bit A component in bytes 3..3.
     * */
    DataFormatBGRA8Unorm = 87,
    /**
     * @brief 8 bit per channel RGBA format. SRGB non-linear color space.
     * A four-component, 32-bit unsigned normalized non-linear SRGB format that has
     * an 8-bit B component in bytes 0..0,
     * an 8-bit G component in bytes 1..1,
     * an 8-bit R component in bytes 2..2,
     * an 8-bit A component in bytes 3..3.
     * */
    DataFormatBGRA8UnormSrgb = 91,
    /**
     * @brief BC6H compressed format.
     * A three-component, block-compressed format where each 128-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned floating-point RGB texel data
     * */
    DataFormatBC6HUfloat16 = 95,
    /**
     * @brief BC6H compressed format.
     * A three-component, block-compressed format where each 128-bit
     * compressed texel block encodes a 4×4 rectangle
     * of signed floating-point RGB texel data
     * */
    DataFormatBC6HSfloat16 = 96,
    /**
     * @brief BC7 compressed format.
     * A four-component, block-compressed format where each 128-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned normalized RGBA texel data
     * */
    DataFormatBC7RGBAUnorm = 98,
    /**
     * @brief BC7 compressed format.
     * A four-component, block-compressed format where each 128-bit
     * compressed texel block encodes a 4×4 rectangle
     * of unsigned normalized RGBA texel data with sRGB nonlinear encoding
     * */
    DataFormatBC7RGBAUnormSrgb = 99,
    /**
     * @brief 4 bit per channel RGB format.
     * A four-component, 16-bit unsigned normalized format that has
     * a 4-bit B component in bits 0..3,
     * a 4-bit G component in bits 4..7,
     * a 4-bit R component in bits 8..11,
     * a 4-bit A component in bits 12..15.
     * */
    DataFormatBGRA4Unorm = 115,
};

/**
 * @brief Fill mode for rasterizer.
 *
 * Translates to D3D12_FILL_MODE for dx implementation.
 * Translates to VkPolygonMode for vk implementation.
 * */
enum WisFillMode {
    FillModeLines = 2, ///< Draw lines between vertices. Wireframe rendering.
    FillModeSolid = 3, ///< Fill the area between vertices forming polygons.
};

/**
 * @brief Descriptor memory type.
 * Decides if descriptors are visible and can be bound to GPU.
 *
 * Translates to D3D12_DESCRIPTOR_HEAP_FLAGS for dx implementation.
 * */
enum WisDescriptorMemory {
    /**
     * @brief Descriptors are only visible to CPU.
     * May be used for copying descriptors to the GPU visible pool.
     * */
    DescriptorMemoryCpuOnly = 0,
    /**
     * @brief Descriptors are visible to GPU.
     * Descriptors can be bound to the GPU pipeline directly.
     * */
    DescriptorMemoryShaderVisible = 1,
};

/**
 * @brief Winding order for front-facing triangles.
 *
 * Translates to BOOL for dx implementation.
 * Translates to VkFrontFace for vk implementation.
 * */
enum WisWindingOrder {
    WindingOrderClockwise = 0, ///< Front-facing triangles have clockwise winding order.
    WindingOrderCounterClockwise = 1, ///< Front-facing triangles have counter-clockwise winding order.
};

/**
 * @brief Sample rate for multisampling.
 *
 * Translates to uint32_t for dx implementation.
 * Translates to VkSampleCountFlagBits for vk implementation.
 * */
enum WisSampleRate {
    SampleRateS1 = 1, ///< 1 sample per pixel.
    SampleRateS2 = 2, ///< 2 samples per pixel.
    SampleRateS4 = 4, ///< 4 samples per pixel.
    SampleRateS8 = 8, ///< 8 samples per pixel.
    SampleRateS16 = 16, ///< 16 samples per pixel.
};

/**
 * @brief Comparison function for depth and stencil operations.
 *
 * Translates to D3D12_COMPARISON_FUNC for dx implementation.
 * Translates to VkCompareOp for vk implementation.
 * */
enum WisCompare {
    CompareNone = 0, ///< No comparison.
    CompareNever = 1, ///< Always fail the comparison.
    CompareLess = 2, ///< Pass the comparison if the source value is less than the destination value.
    CompareEqual = 3, ///< Pass the comparison if the source value is equal to the destination value.
    CompareLessEqual = 4, ///< Pass the comparison if the source value is less than or equal to the destination value.
    CompareGreater = 5, ///< Pass the comparison if the source value is greater than the destination value.
    CompareNotEqual = 6, ///< Pass the comparison if the source value is not equal to the destination value.
    CompareGreaterEqual = 7, ///< Pass the comparison if the source value is greater than or equal to the destination value.
    CompareAlways = 8, ///< Always pass the comparison.
};

/**
 * @brief Stencil operation for depth and stencil operations.
 *
 * Translates to D3D12_STENCIL_OP for dx implementation.
 * Translates to VkStencilOp for vk implementation.
 * */
enum WisStencilOp {
    StencilOpKeep = 1, ///< Keep the current value.
    StencilOpZero = 2, ///< Set the value to zero.
    StencilOpReplace = 3, ///< Replace the value with the reference value.
    StencilOpIncClamp = 4, ///< Increment the value and clamp to the maximum value.
    StencilOpDecClamp = 5, ///< Decrement the value and clamp to the minimum value.
    StencilOpInvert = 6, ///< Invert the value.
    StencilOpIncWrap = 7, ///< Increment the value and wrap to zero when the maximum value is exceeded.
    StencilOpDecWrap = 8, ///< Decrement the value and wrap to the maximum value when the minimum value is exceeded.
};

/**
 * @brief Blend factor for color blending operations.
 *
 * Translates to D3D12_BLEND for dx implementation.
 * Translates to VkBlendFactor for vk implementation.
 * */
enum WisBlendFactor {
    BlendFactorZero = 1, ///< Use zero for blending.
    BlendFactorOne = 2, ///< Use one for blending.
    BlendFactorSrcColor = 3, ///< Use the source color for blending.
    BlendFactorInvSrcColor = 4, ///< Use the inverse source color for blending.
    BlendFactorSrcAlpha = 5, ///< Use the source alpha for blending.
    BlendFactorInvSrcAlpha = 6, ///< Use the inverse source alpha for blending.
    BlendFactorDestAlpha = 7, ///< Use the destination alpha for blending.
    BlendFactorInvDestAlpha = 8, ///< Use the inverse destination alpha for blending.
    BlendFactorDestColor = 9, ///< Use the destination color for blending.
    BlendFactorInvDestColor = 10, ///< Use the inverse destination color for blending.
    BlendFactorSrcAlphaSat = 11, ///< Use the source alpha saturated for blending.
    BlendFactorBlendFactor = 14, ///< Use a constant blend factor for blending.
    BlendFactorInvBlendFactor = 15, ///< Use the inverse constant blend factor for blending.
    BlendFactorSrc1Color = 16, ///< Use the source color for blending. Dual source blending mode.
    BlendFactorInvSrc1Color = 17, ///< Use the inverse source color for blending. Dual source blending mode.
    BlendFactorSrc1Alpha = 18, ///< Use the source alpha for blending. Dual source blending mode.
    BlendFactorInvSrc1Alpha = 19, ///< Use the inverse source alpha for blending. Dual source blending mode.
};

/**
 * @brief Blend operation for color blending operations.
 *
 * Translates to D3D12_BLEND_OP for dx implementation.
 * Translates to VkBlendOp for vk implementation.
 * */
enum WisBlendOp {
    BlendOpAdd = 1, ///< Add the source and destination colors.
    BlendOpSubtract = 2, ///< Subtract the source color from the destination color.
    BlendOpRevSubtract = 3, ///< Subtract the destination color from the source color.
    BlendOpMin = 4, ///< Use the minimum of the source and destination colors.
    BlendOpMax = 5, ///< Use the maximum of the source and destination colors.
};

/**
 * @brief Logic operation for color blending operations.
 *
 * Translates to D3D12_LOGIC_OP for dx implementation.
 * Translates to VkLogicOp for vk implementation.
 * */
enum WisLogicOp {
    LogicOpClear = 0, ///< Clear the destination value.
    LogicOpSet = 1, ///< Set the destination value.
    LogicOpCopy = 2, ///< Copy the source value to the destination.
    LogicOpCopyInverted = 3, ///< Copy the inverted source value to the destination.
    LogicOpNoop = 4, ///< Do not modify the destination value.
    LogicOpInvert = 5, ///< Invert the destination value.
    LogicOpAnd = 6, ///< Perform a bitwise AND operation on the source and destination values.
    LogicOpNand = 7, ///< Perform a bitwise NAND operation on the source and destination values.
    LogicOpOr = 8, ///< Perform a bitwise OR operation on the source and destination values.
    LogicOpNor = 9, ///< Perform a bitwise NOR operation on the source and destination values.
    LogicOpXor = 10, ///< Perform a bitwise XOR operation on the source and destination values.
    LogicOpEquiv = 11, ///< Perform a bitwise equivalent operation on the source and destination values.
    LogicOpAndReverse = 12, ///< Perform a bitwise AND operation on the source and inverted destination values.
    LogicOpAndInverted = 13, ///< Perform a bitwise AND operation on the inverted source and destination values.
    LogicOpOrReverse = 14, ///< Perform a bitwise OR operation on the source and inverted destination values.
    LogicOpOrInverted = 15, ///< Perform a bitwise OR operation on the inverted source and destination values.
};

/**
 * @brief Memory type for resource allocation.
 *
 * Translates to D3D12_HEAP_TYPE for dx implementation.
 * Translates to VkMemoryPropertyFlags for vk implementation.
 * */
enum WisMemoryType {
    /**
     * @brief Default memory type.
     * Local device memory, most efficient for rendering.
     * */
    MemoryTypeDefault = 0,
    /**
     * @brief Upload memory type.
     * Used for data that is uploaded to the GPU Local memory using copy operations.
     * */
    MemoryTypeUpload = 1,
    /**
     * @brief Readback memory type.
     * Used for data that is read back from the GPU Local memory using copy operations.
     * */
    MemoryTypeReadback = 2,
    /**
     * @brief GPU upload memory type.
     * Used for data that is directly uploaded to the GPU Local memory using copy operations.
     * Can be used only with Extended Allocation extension enabled and supported.
     * Usage outside of the Extended Allocation is undefined behavior.
     * Usage with buffers requires allocating memory on GPUUpload heap and mapping the memory.
     * */
    MemoryTypeGPUUpload = 3,
};

/**
 * @brief Intermediate shader representation.
 *
 * */
enum WisShaderIntermediate {
    ShaderIntermediateDXIL = 0, ///< DirectX Intermediate Language.
    ShaderIntermediateSPIRV = 1, ///< Standard Portable Intermediate Representation for Vulkan.
};

/**
 * @brief Texture state for resource transitions.
 *
 * Translates to D3D12_BARRIER_LAYOUT for dx implementation.
 * Translates to VkImageLayout for vk implementation.
 * */
enum WisTextureState {
    TextureStateUndefined = 4294967295, ///< Undefined state.
    TextureStateCommon = 0, ///< Common state.
    TextureStateRead = 1, ///< General Read state.
    TextureStateRenderTarget = 2, ///< Render Target state.
    TextureStateUnorderedAccess = 3, ///< Unordered Access state.
    TextureStateDepthStencilWrite = 4, ///< Depth Stencil Write state.
    TextureStateDepthStencilRead = 5, ///< Depth Stencil Read state.
    TextureStateShaderResource = 6, ///< Shader Resource state.
    TextureStateCopySource = 7, ///< Copy Source state.
    TextureStateCopyDest = 8, ///< Copy Destination state.
    TextureStatePresent = 9, ///< Present swapchain state.
    TextureStateShadingRate = 10, ///< Shading Rate state. Used for Variable Shading Rate.
    TextureStateVideoDecodeRead = 11, ///< Video Decode Read state.
    TextureStateVideoDecodeWrite = 12, ///< Video Decode Write state.
};

/**
 * @brief Attachment load operation for render pass.
 *
 * Translates to VkAttachmentLoadOp for vk implementation.
 * Translates to D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE for dx implementation.
 * */
enum WisLoadOperation {
    LoadOperationLoad = 0, ///< Load the attachment contents.
    LoadOperationClear = 1, ///< Clear the attachment contents.
    LoadOperationDontCare = 2, ///< Do not care about the attachment contents.
};

/**
 * @brief Texture layout. Determines how texture will be accessed.
 *
 * */
enum WisTextureLayout {
    TextureLayoutTexture1D = 2, ///< Texture is 1D array of data. Behaves similarly to Buffer.
    TextureLayoutTexture1DArray = 3, ///< Texture is an array of 1D data.
    TextureLayoutTexture2D = 4, ///< Texture is 2D image, default texture type.
    TextureLayoutTexture2DArray = 5, ///< Texture is an array of 2D images. Can also be used for Cube maps.
    TextureLayoutTexture2DMS = 6, ///< Texture is 2D multisampled image.
    TextureLayoutTexture2DMSArray = 7, ///< Texture is an array of 2D multisampled images.
    TextureLayoutTexture3D = 8, ///< Texture is 3D volume.
};

/**
 * @brief Descriptor heap type.
 *
 * Translates to D3D12_DESCRIPTOR_HEAP_TYPE for dx implementation.
 * */
enum WisDescriptorHeapType {
    /**
     * @brief Descriptor heap type.
     * Used for all descriptor types, except for samplers.
     * */
    DescriptorHeapTypeDescriptor = 0,
    /**
     * @brief Sampler heap type.
     * Used for sampler descriptors.
     * */
    DescriptorHeapTypeSampler = 1,
};

/**
 * @brief Attachment store operation for render pass.
 *
 * Translates to VkAttachmentStoreOp for vk implementation.
 * Translates to D3D12_RENDER_PASS_ENDING_ACCESS_TYPE for dx implementation.
 * */
enum WisStoreOperation {
    StoreOperationStore = 0, ///< Store the attachment contents.
    StoreOperationDontCare = 1, ///< Do not care about the attachment contents.
    StoreOperationResolve = 2, ///< Resolve the attachment contents. Used for multisampling attachments.
};

/**
 * @brief Primitive topology for rendering.
 * More info could be found [here](https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-primitive-topologies).
 *
 * Translates to D3D_PRIMITIVE_TOPOLOGY for dx implementation.
 * Translates to VkPrimitiveTopology for vk implementation.
 * */
enum WisPrimitiveTopology {
    PrimitiveTopologyPointList = 1, ///< Render points for each vertex.
    PrimitiveTopologyLineList = 2, ///< Render lines between vertices.
    PrimitiveTopologyLineStrip = 3, ///< Render lines between vertices in a strip.
    PrimitiveTopologyTriangleList = 4, ///< Render triangles between vertices.
    PrimitiveTopologyTriangleStrip = 5, ///< Render triangles between vertices in a strip.
    PrimitiveTopologyTriangleFan = 6, ///< Interpret vertex data to form a fan of triangles.
    PrimitiveTopologyLineListAdj = 10, ///< Render lines between vertices with adjacency.
    PrimitiveTopologyLineStripAdj = 11, ///< Render lines between vertices in a strip with adjacency.
    PrimitiveTopologyTriangleListAdj = 12, ///< Render triangles between vertices with adjacency.
    PrimitiveTopologyTriangleStripAdj = 13, ///< Render triangles between vertices in a strip with adjacency.
};

/**
 * @brief Primitive topology type for rendering.
 *
 * Translates to D3D12_PRIMITIVE_TOPOLOGY_TYPE for dx implementation.
 * Translates to VkPrimitiveTopology for vk implementation.
 * */
enum WisTopologyType {
    TopologyTypePoint = 1, ///< Render points for each vertex.
    TopologyTypeLine = 2, ///< Render lines between vertices.
    TopologyTypeTriangle = 3, ///< Render triangles between vertices.
    TopologyTypePatch = 4, ///< Vertices are interpret as patch list. Used in tesselation process.
};

/**
 * @brief Features that device may support.
 * Query by calling with Device::QueryFeatureSupport. Contains core features with optional ones.
 *
 * */
enum WisDeviceFeature {
    /**
     * @brief Core Functionality. Descriptor buffer support for VK, always true for DX12.
     * Vulkan provides DescriptorPool and DescriptorSet functionalities, that have to be used manually through library internals.
     * */
    DeviceFeatureDescriptorBuffer = 0,
    /**
     * @brief Core Functionality. Supports enhanced barriers. Support for VK and DX12.
     * Used in all barriers to provide more control over synchronization. Without the feature behavior is undefined.
     * To run without this feature for DX12 there are legacy barriers, which can be manually submitted through CommandList internals.
     * Vulkan will not work, as half of current functionality depends on VK_KHR_synchronization2.
     * */
    DeviceFeatureEnchancedBarriers = 1,
    /**
     * @brief Supports waiting for present to finish. Support for VK, always true for DX12.
     * Unlocks Swapchain::WaitForPresent.
     * */
    DeviceFeatureWaitForPresent = 2,
    /**
     * @brief Descriptor size for SRV UAV and CBV are equal in size, support for VK, always true for DX12.
     * Unlocks DescriptorBuffer::WriteShaderResource2, DescriptorBuffer::WriteConstantBuffer2 functions. Without the feature their behavior is undefined.
     * */
    DeviceFeatureDescriptorEqualSize = 3,
    /**
     * @brief Supports advanced index buffer features. Support for VK, always true for DX12.
     * Unlocks CommandList::IASetIndexBuffer2 function. Without the extension behavior is undefined.
     * */
    DeviceFeatureAdvancedIndexBuffer = 4,
    /**
     * @brief Supports dynamic VSync. Support for VK, always true for DX12.
     * Unlocks Swapchain::Present2 function. Without the extension behavior is the same as Swapchain::Present.
     * */
    DeviceFeatureDynamicVSync = 5,
};

/**
 * @brief Filtering mode for texture sampling.
 *
 * Translates to VkFilter for vk implementation.
 * Translates to D3D12_FILTER_TYPE for dx implementation.
 * */
enum WisFilter {
    FilterPoint = 0, ///< Nearest neighbor filtering.
    FilterLinear = 1, ///< Linear filtering.
};

/**
 * @brief Address mode for texture sampling.
 *
 * Translates to VkSamplerAddressMode for vk implementation.
 * Translates to D3D12_TEXTURE_ADDRESS_MODE for dx implementation.
 * */
enum WisAddressMode {
    AddressModeRepeat = 0, ///< Repeat the texture.
    AddressModeMirroredRepeat = 1, ///< Repeat the texture with mirroring.
    AddressModeClampToEdge = 2, ///< Clamp the texture to the edge.
    AddressModeClampToBorder = 3, ///< Clamp the texture to the border.
    AddressModeMirrorClampToEdge = 4, ///< Mirror and clamp the texture to the edge.
};

/**
 * @brief Texture view type.
 *
 * Translates to VkImageViewType for vk implementation.
 * Translates to D3D12_SRV_DIMENSION for dx implementation.
 * */
enum WisTextureViewType {
    TextureViewTypeTexture1D = 0, ///< Texture is 1D array of data. Behaves similarly to Buffer.
    TextureViewTypeTexture1DArray = 1, ///< Texture is an array of 1D data.
    TextureViewTypeTexture2D = 2, ///< Texture is 2D image, default texture type.
    TextureViewTypeTexture2DArray = 3, ///< Texture is an array of 2D images.
    TextureViewTypeTexture2DMS = 4, ///< Texture is 2D multisampled image.
    TextureViewTypeTexture2DMSArray = 5, ///< Texture is an array of 2D multisampled images.
    TextureViewTypeTexture3D = 6, ///< Texture is 3D volume.
    TextureViewTypeTextureCube = 7, ///< Texture is a cube map.
    TextureViewTypeTextureCubeArray = 8, ///< Texture is an array of cube maps.
};

/**
 * @brief Component swizzle for texture sampling.
 *
 * Translates to D3D12_SHADER_COMPONENT_MAPPING for dx implementation.
 * Translates to VkComponentSwizzle for vk implementation.
 * */
enum WisComponentSwizzle {
    ComponentSwizzleRed = 0, ///< Use the red component for sampling.
    ComponentSwizzleGreen = 1, ///< Use the green component for sampling.
    ComponentSwizzleBlue = 2, ///< Use the blue component for sampling.
    ComponentSwizzleAlpha = 3, ///< Use the alpha component for sampling.
    ComponentSwizzleZero = 4, ///< Use zero for sampling.
    ComponentSwizzleOne = 5, ///< Use one for sampling.
};

/**
 * @brief Index type for index buffer.
 * Enum values resemble the byte stride of the format.
 *
 * Translates to DXGI_FORMAT for dx implementation.
 * Translates to VkIndexType for vk implementation.
 * */
enum WisIndexType {
    IndexTypeUInt16 = 2, ///< 16-bit unsigned integer index type.
    IndexTypeUInt32 = 4, ///< 32-bit unsigned integer index type.
};

/**
 * @brief Factory extension ID.
 * Platform extension values start from 2049
 * 0 is reserved as invalid/custom extension.
 *
 * */
enum WisFactoryExtID {
    FactoryExtIDCustom = 0, ///< Custom provided extension. Default initialization of the extension is done by user.
    FactoryExtIDDebugExtension = 1,
};

/**
 * @brief Device extension ID.
 * Platform extension values start from 2049
 * 0 is reserved as invalid/custom extension.
 *
 * */
enum WisDeviceExtID {
    DeviceExtIDCustom = 0, ///< Custom provided extension. Default initialization of the extension is done by user.
};

//-------------------------------------------------------------------------

/**
 * @brief Flags that describe adapter.
 *
 * */
enum WisAdapterFlagsBits {
    AdapterFlagsNone = 0x0, ///< No flags set. Adapter may be descrete or embedded.
    AdapterFlagsRemote = 1 << 0, ///< Adapter is remote. Used for remote rendering.
    AdapterFlagsSoftware = 1 << 1, ///< Adapter is software. Used for software rendering.
};

/**
 * @brief Depth stencil select flags.
 * Affect which part of the depth stencil buffer is used.
 *
 * */
enum WisDSSelectBits {
    DSSelectNone = 0x0, ///< No flags set. Depth stencil buffer is not used.
    DSSelectDepth = 1 << 0, ///< Use depth part of the depth stencil buffer.
    DSSelectStencil = 1 << 1, ///< Use stencil part of the depth stencil buffer.
    DSSelectDepthStencil = 0x3, ///< Use both depth and stencil parts of the depth stencil buffer.
};

/**
 * @brief Color component flags.
 * Used for color blending operations.
 *
 * */
enum WisColorComponentsBits {
    ColorComponentsNone = 0x0, ///< No flags set. Color blending is not used.
    ColorComponentsR = 1 << 0, ///< Use red component for blending.
    ColorComponentsG = 1 << 1, ///< Use green component for blending.
    ColorComponentsB = 1 << 2, ///< Use blue component for blending.
    ColorComponentsA = 1 << 3, ///< Use alpha component for blending.
    ColorComponentsAll = 0xF, ///< Use all color components for blending.
};

/**
 * @brief Buffer usage flags.
 * Determine how the buffer can be used throughout its lifetime.
 *
 * */
enum WisBufferUsageBits {
    BufferUsageNone = 0x0, ///< No flags set. Buffer is not used.
    BufferUsageCopySrc = 1 << 0, ///< Buffer is used as a source for copy operations.
    BufferUsageCopyDst = 1 << 1, ///< Buffer is used as a destination for copy operations.
    BufferUsageConstantBuffer = 1 << 4, ///< Buffer is used as a constant buffer.
    BufferUsageIndexBuffer = 1 << 6, ///< Buffer is used as an index buffer.
    BufferUsageVertexBuffer = 1 << 7, ///< Buffer is used as a vertex buffer or an instance buffer.
};

/**
 * @brief Memory flags.
 * Determine optional properties of the memory allocation.
 *
 * Translates to VmaAllocationCreateFlags for vk implementation.
 * Translates to D3D12MA::ALLOCATION_FLAGS for dx implementation.
 * */
enum WisMemoryFlagsBits {
    MemoryFlagsNone = 0x0, ///< No flags set. Memory is regular.
    /**
     * @brief Memory is dedicated.
     * Used for resources that require dedicated memory.
     * Useful for big resources that are not shared with other resources.
     * E.g. fullscreen textures, big buffers, etc.
     * */
    MemoryFlagsDedicatedAllocation = 1 << 0,
    /**
     * @brief Memory is mapped.
     * Used in combination with MemoryTypeUpload or MemoryTypeReadback to map memory for CPU access.
     * */
    MemoryFlagsMapped = 1 << 1,
    /**
     * @brief Memory is exportable.
     * If set, memory can be exported to other processes or APIs.
     * Works only with Device Local memory (MemoryTypeDefault) and only on AllocateXMemory calls.
     * Outside of AllocateXMemory the flag is ignored.
     * */
    MemoryFlagsExportable = 1 << 2,
};

/**
 * @brief Render pass flags.
 * Set of flags that affect render pass behavior.
 * More on render pass flags [here](https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-render-passes).
 *
 * Translates to VkRenderingFlags for vk implementation.
 * Translates to D3D12_RENDER_PASS_FLAGS for dx implementation.
 * */
enum WisRenderPassFlagsBits {
    RenderPassFlagsNone = 0x0, ///< No flags set. Render pass is regular.
    RenderPassFlagsSuspending = 1 << 1, ///< Render pass is suspending.
    RenderPassFlagsResuming = 1 << 2, ///< Render pass is resuming.
};

/**
 * @brief Barrier synchronization flags.
 * Used to synchronize resources between different stages of the pipeline.
 *
 * Translates to D3D12_BARRIER_SYNC for dx implementation.
 * Translates to VkPipelineStageFlags2 for vk implementation.
 * */
enum WisBarrierSyncBits {
    BarrierSyncNone = 0x0, ///< No flags set. No synchronization is performed.
    BarrierSyncAll = 1 << 0, ///< Synchronize all commands.
    BarrierSyncDraw = 1 << 1, ///< Synchronize draw commands.
    BarrierSyncIndexInput = 1 << 2, ///< Synchronize index input commands.
    BarrierSyncVertexShading = 1 << 3, ///< Synchronize vertex shading commands.
    BarrierSyncPixelShading = 1 << 4, ///< Synchronize pixel shading commands.
    BarrierSyncDepthStencil = 1 << 5, ///< Synchronize depth stencil commands.
    BarrierSyncRenderTarget = 1 << 6, ///< Synchronize render target commands.
    BarrierSyncCompute = 1 << 7, ///< Synchronize compute commands.
    BarrierSyncRaytracing = 1 << 8, ///< Synchronize raytracing commands.
    BarrierSyncCopy = 1 << 9, ///< Synchronize copy commands.
    BarrierSyncResolve = 1 << 10, ///< Synchronize resolve commands.
    BarrierSyncExecuteIndirect = 1 << 11, ///< Synchronize execute indirect commands.
    BarrierSyncAllShading = 1 << 12, ///< Synchronize all shading commands.
    BarrierSyncNonPixelShading = 1 << 13, ///< Synchronize non-pixel shading commands.
    BarrierSyncClearUAV = 1 << 14, ///< Synchronize clear UAV commands.
    BarrierSyncVideoDecode = 1 << 15, ///< Synchronize video decode commands.
    BarrierSyncVideoEncode = 1 << 16, ///< Synchronize video encode commands.
    BarrierSyncBuildRTAS = 1 << 17, ///< Synchronize build raytracing acceleration structure commands.
    BarrierSyncCopyRTAS = 1 << 18, ///< Synchronize copy raytracing acceleration structure commands.
};

/**
 * @brief Resource access flags.
 * Determine how resource will be accessed. Used in Barriers.
 *
 * Translates to D3D12_BARRIER_ACCESS for dx implementation.
 * Translates to VkAccessFlags2 for vk implementation.
 * */
enum WisResourceAccessBits {
    /**
     * @brief Common access.
     * Subresource data must be available for any layout-compatible access after a barrier.
     * */
    ResourceAccessCommon = 0x0,
    ResourceAccessVertexBuffer = 1 << 0, ///< Vertex buffer access. Applies only to buffers.
    ResourceAccessConstantBuffer = 1 << 1, ///< Constant buffer access. Applies only to buffers.
    ResourceAccessIndexBuffer = 1 << 2, ///< Index buffer access. Applies only to buffers.
    ResourceAccessRenderTarget = 1 << 3, ///< Render target access. Applies only to textures.
    ResourceAccessUnorderedAccess = 1 << 4, ///< Unordered access access.
    ResourceAccessDepthWrite = 1 << 5, ///< Depth write access. Applies only to DS textures.
    ResourceAccessDepthRead = 1 << 6, ///< Depth read access. Applies only to DS textures.
    ResourceAccessShaderResource = 1 << 7, ///< Shader resource access. Applies only to textures.
    ResourceAccessStreamOutput = 1 << 8, ///< Stream output access. Applies only to buffers. Reserved for extension.
    ResourceAccessIndirectArgument = 1 << 9, ///< Indirect argument access.
    ResourceAccessCopyDest = 1 << 10, ///< Copy destination access.
    ResourceAccessCopySource = 1 << 11, ///< Copy source access.
    ResourceAccessConditionalRendering = 1 << 12, ///< Conditional rendering access.
    ResourceAccessAccelerationStrucureRead = 1 << 13, ///< Acceleration structure read access.
    ResourceAccessAccelerationStrucureWrite = 1 << 14, ///< Acceleration structure write access.
    ResourceAccessShadingRate = 1 << 15, ///< Shading rate access. Used in variable shading rate.
    ResourceAccessVideoDecodeRead = 1 << 16, ///< Video decode read access.
    ResourceAccessVideoDecodeWrite = 1 << 17, ///< Video decode write access.
    ResourceAccessPresent = 1 << 18, ///< Present access. Used fpr swapchain presentation.
    ResourceAccessResolveDest = 1 << 19, ///< Resolve destination access. Used in multisampling.
    ResourceAccessResolveSource = 1 << 20, ///< Resolve source access. Used in multisampling.
    ResourceAccessNoAccess = 1 << 31, ///< No access. Used to indicate no access throughout pipeline.
};

/**
 * @brief Texture usage flags.
 * Determine how the texture can be used throughout its lifetime.
 *
 * Translates to D3D12_RESOURCE_FLAGS for dx implementation.
 * Translates to VkImageUsageFlags for vk implementation.
 * */
enum WisTextureUsageBits {
    TextureUsageNone = 0x0, ///< No flags set. Texture is not used.
    TextureUsageRenderTarget = 1 << 0, ///< Texture is used as a render target.
    TextureUsageDepthStencil = 1 << 1, ///< Texture is used as a depth stencil buffer.
    TextureUsageCopySrc = 1 << 2, ///< Texture is used as a source for copy operations.
    TextureUsageCopyDst = 1 << 3, ///< Texture is used as a destination for copy operations.
    TextureUsageShaderResource = 1 << 4, ///< Texture is used as a shader resource.
    TextureUsageUnorderedAccess = 1 << 5, ///< Texture is used as an unordered access resource.
    TextureUsageHostCopy = 1 << 7, ///< Texture is used for host copy operations. Works with ExtendedAllocation extension.
};

/**
 * @brief Fence flags for additional fence features
 *
 * Translates to D3D12_FENCE_FLAGS for dx implementation.
 * */
enum WisFenceFlagsBits {
    FenceFlagsNone = 0x0, ///< No flags set. Fence is regular.
    FenceFlagsShared = 1 << 0, ///< Fence is shared. Used for sharing fences for single physical device.
};

//-------------------------------------------------------------------------

typedef struct WisResult WisResult;
typedef struct WisSize2D WisSize2D;
typedef struct WisSize3D WisSize3D;
typedef struct WisBufferRegion WisBufferRegion;
typedef struct WisAdapterDesc WisAdapterDesc;
typedef struct WisInputSlotDesc WisInputSlotDesc;
typedef struct WisInputAttribute WisInputAttribute;
typedef struct WisInputLayout WisInputLayout;
typedef struct WisRasterizerDesc WisRasterizerDesc;
typedef struct WisSampleDesc WisSampleDesc;
typedef struct WisStencilDesc WisStencilDesc;
typedef struct WisDepthStencilDesc WisDepthStencilDesc;
typedef struct WisBlendAttachmentDesc WisBlendAttachmentDesc;
typedef struct WisBlendStateDesc WisBlendStateDesc;
typedef struct WisRenderAttachmentsDesc WisRenderAttachmentsDesc;
typedef struct WisRootConstant WisRootConstant;
typedef struct WisSwapchainDesc WisSwapchainDesc;
typedef struct WisTextureDesc WisTextureDesc;
typedef struct WisAllocationInfo WisAllocationInfo;
typedef struct WisTextureRegion WisTextureRegion;
typedef struct WisBufferTextureCopyRegion WisBufferTextureCopyRegion;
typedef struct WisPushDescriptor WisPushDescriptor;
typedef struct WisSubresourceRange WisSubresourceRange;
typedef struct WisRenderTargetDesc WisRenderTargetDesc;
typedef struct WisViewport WisViewport;
typedef struct WisScissor WisScissor;
typedef struct WisBufferBarrier WisBufferBarrier;
typedef struct WisTextureBarrier WisTextureBarrier;
typedef struct WisDescriptorTableEntry WisDescriptorTableEntry;
typedef struct WisDescriptorTable WisDescriptorTable;
typedef struct WisSamplerDesc WisSamplerDesc;
typedef struct WisComponentMapping WisComponentMapping;
typedef struct WisShaderResourceDesc WisShaderResourceDesc;
typedef struct WisFactoryExtQuery WisFactoryExtQuery;
typedef struct WisDeviceExtQuery WisDeviceExtQuery;
typedef enum WisShaderStages WisShaderStages;
typedef enum WisStatus WisStatus;
typedef enum WisMutiWaitFlags WisMutiWaitFlags;
typedef enum WisDescriptorType WisDescriptorType;
typedef enum WisQueueType WisQueueType;
typedef enum WisAdapterPreference WisAdapterPreference;
typedef enum WisSeverity WisSeverity;
typedef enum WisInputClass WisInputClass;
typedef enum WisCullMode WisCullMode;
typedef enum WisDataFormat WisDataFormat;
typedef enum WisFillMode WisFillMode;
typedef enum WisDescriptorMemory WisDescriptorMemory;
typedef enum WisWindingOrder WisWindingOrder;
typedef enum WisSampleRate WisSampleRate;
typedef enum WisCompare WisCompare;
typedef enum WisStencilOp WisStencilOp;
typedef enum WisBlendFactor WisBlendFactor;
typedef enum WisBlendOp WisBlendOp;
typedef enum WisLogicOp WisLogicOp;
typedef enum WisMemoryType WisMemoryType;
typedef enum WisShaderIntermediate WisShaderIntermediate;
typedef enum WisTextureState WisTextureState;
typedef enum WisLoadOperation WisLoadOperation;
typedef enum WisTextureLayout WisTextureLayout;
typedef enum WisDescriptorHeapType WisDescriptorHeapType;
typedef enum WisStoreOperation WisStoreOperation;
typedef enum WisPrimitiveTopology WisPrimitiveTopology;
typedef enum WisTopologyType WisTopologyType;
typedef enum WisDeviceFeature WisDeviceFeature;
typedef enum WisFilter WisFilter;
typedef enum WisAddressMode WisAddressMode;
typedef enum WisTextureViewType WisTextureViewType;
typedef enum WisComponentSwizzle WisComponentSwizzle;
typedef enum WisIndexType WisIndexType;
typedef enum WisFactoryExtID WisFactoryExtID;
typedef enum WisDeviceExtID WisDeviceExtID;
typedef enum WisAdapterFlagsBits WisAdapterFlagsBits;
typedef uint32_t WisAdapterFlags;
typedef enum WisDSSelectBits WisDSSelectBits;
typedef uint32_t WisDSSelect;
typedef enum WisColorComponentsBits WisColorComponentsBits;
typedef uint32_t WisColorComponents;
typedef enum WisBufferUsageBits WisBufferUsageBits;
typedef uint32_t WisBufferUsage;
typedef enum WisMemoryFlagsBits WisMemoryFlagsBits;
typedef uint32_t WisMemoryFlags;
typedef enum WisRenderPassFlagsBits WisRenderPassFlagsBits;
typedef uint32_t WisRenderPassFlags;
typedef enum WisBarrierSyncBits WisBarrierSyncBits;
typedef uint32_t WisBarrierSync;
typedef enum WisResourceAccessBits WisResourceAccessBits;
typedef uint32_t WisResourceAccess;
typedef enum WisTextureUsageBits WisTextureUsageBits;
typedef uint32_t WisTextureUsage;
typedef enum WisFenceFlagsBits WisFenceFlagsBits;
typedef uint32_t WisFenceFlags;

//-------------------------------------------------------------------------

/**
 * @brief Main source of communication of operation success.
 * To check for success compare WisResult::status with StatusOk.
 * If there is any error there is  string which is compile-time.
 * It communicates the source of problems even in Release mode.
 * The string contains function name and error message.
 * */
struct WisResult {
    WisStatus status; ///< Operation status. Compare with StatusOk
    const char* error; ///< Error message. nullptr or 'Operation Succeeded.' if no error.
};

/**
 * @brief 2D unsigned size.
 * */
struct WisSize2D {
    uint32_t width;
    uint32_t height;
};

/**
 * @brief 3D unsigned size.
 * */
struct WisSize3D {
    uint32_t width;
    uint32_t height;
    uint32_t depth_or_layers; ///< Depth for 3D textures, layers for 2D arrays
};

/**
 * @brief Buffer region for copy operations.
 * */
struct WisBufferRegion {
    uint64_t src_offset; ///< Source offset in bytes. Default is 0.
    uint64_t dst_offset; ///< Destination offset in bytes. Default is 0.
    uint64_t size_bytes; ///< Size of portion of source buffer to take copy from in bytes.
};

/**
 * @brief Adapter description.
 * Describes hardware driver identificators as well as memory limits.
 * */
struct WisAdapterDesc {
    const char description[256]; ///< Adapter description. Contains name of the graphics adapter.
    uint32_t vendor_id; ///< Vendor ID. Can be used to find the correct adapter.
    uint32_t device_id; ///< Device ID. Together with WisAdapterDesc::vendor_id uniquely identifies the device.
    uint32_t subsys_id; ///< Unused
    uint32_t revision; ///< Driver revision. Unused.
    uint64_t dedicated_video_memory; ///< Dedicated video memory in bytes. Used for Default Memory type.
    uint64_t dedicated_system_memory; ///< Dedicated system memory in bytes. Used for Upload and Readback Memory types.
    uint64_t shared_system_memory; ///< Shared system memory in bytes. Used for GPUUpload Memory type.
    uint64_t adapter_id; ///< Adapter unique ID. Can be used to find the correct adapter.
    WisAdapterFlags flags; ///< Adapter flags. Describe the adapter kind.
};

/**
 * @brief Input slot description for WisInputLayout.
 * */
struct WisInputSlotDesc {
    uint32_t slot; ///< Input slot number. Must be unique.
    uint32_t stride_bytes; ///< Stride in bytes. Size of one vertex in the slot.
    WisInputClass input_class; ///< Input class. Defines how the data is read (Per vertex or Per instance).
};

/**
 * @brief Input attribute description for WisInputLayout.
 * */
struct WisInputAttribute {
    uint32_t input_slot; ///< Input slot number. Must be unique.
    const char* semantic_name; ///< Semantic name of the attribute in HLSL. Must be unique.
    uint32_t semantic_index; ///< Semantic index of the attribute in HLSL. Must be unique.
    uint32_t location; ///< Location of the attribute in HLSL. Must be unique.
    WisDataFormat format; ///< Data format of the attribute.
    uint32_t offset_bytes; ///< Offset in bytes from the beginning of the vertex.
};

/**
 * @brief Input layout description for .
 * */
struct WisInputLayout {
    WisInputSlotDesc* slots; ///< Input slots array. Made to pick up data from several arrays of vertex data.
    uint32_t slot_count; ///< Input slots count. Max number is 16.
    WisInputAttribute* attributes; ///< Input attributes array. Describes how the vertex data is read by the HLSL shader.
    uint32_t attribute_count; ///< Input attributes count.
};

/**
 * @brief Rasterizer description for .
 * */
struct WisRasterizerDesc {
    WisFillMode fill_mode; ///< Fill mode. Solid or Wireframe. Default is FillModeSolid.
    WisCullMode cull_mode; ///< Cull mode. None, Front, Back. Default is CullModeBack.
    WisWindingOrder front_face; ///< Front face winding order. Clockwise or CounterClockwise. Default is WindingOrderClockwise.
    bool depth_bias_enable; ///< Depth bias enable. Default is false.
    float depth_bias; ///< Depth bias. Default is 0.0f.
    float depth_bias_clamp; ///< Depth bias clamp. Default is 0.0f.
    float depth_bias_slope_factor; ///< Depth bias slope factor e.g. for shadows. Default is 0.0f.
    bool depth_clip_enable; ///< Depth clip enable. Default is true.
};

/**
 * @brief Sample description of Multisampling for .
 * */
struct WisSampleDesc {
    WisSampleRate rate; ///< Sample rate. Default is SampleRateS1.
    float quality; ///< Sample quality. Default is 0.0f.
    uint32_t sample_mask; ///< Sample mask. Default is 0xffffffff.
};

/**
 * @brief Stencil description for WisDepthStencilDesc.
 * */
struct WisStencilDesc {
    WisStencilOp fail_op; ///< Stencil operation if the stencil test fails. Default is StencilOpKeep.
    WisStencilOp depth_fail_op; ///< Stencil operation if the stencil test passes and the depth test fails. Default is StencilOpKeep.
    WisStencilOp pass_op; ///< Stencil operation if the stencil test passes. Default is StencilOpKeep.
    WisCompare comparison; ///< Stencil comparison function. Default is CompareAlways.
    uint8_t read_mask; ///< Stencil read mask. Default is 0xff.
    uint8_t write_mask; ///< Stencil write mask. Default is 0xff.
};

/**
 * @brief Depth stencil description for .
 * */
struct WisDepthStencilDesc {
    bool depth_enable; ///< Depth test enable. Default is false.
    bool depth_write_enable; ///< Depth write enable. Default is false.
    WisCompare depth_comp; ///< Depth comparison function. Default is CompareLess.
    bool stencil_enable; ///< Stencil test enable. Default is false.
    WisStencilDesc stencil_front; ///< Stencil description for front faces.
    WisStencilDesc stencil_back; ///< Stencil description for back faces.
    bool depth_bound_test; ///< Depth bound test enable. Default is false.
};

/**
 * @brief Blend attachment description for WisBlendStateDesc.
 * */
struct WisBlendAttachmentDesc {
    bool blend_enable; ///< Blend enable. Default is false.
    WisBlendFactor src_color_blend; ///< Source color blend factor. Default is BlendFactorOne.
    WisBlendFactor dst_color_blend; ///< Destination color blend factor. Default is BlendFactorZero.
    WisBlendOp color_blend_op; ///< Color blend operation. Default is BlendOpAdd.
    WisBlendFactor src_alpha_blend; ///< Source alpha blend factor. Default is BlendFactorOne.
    WisBlendFactor dst_alpha_blend; ///< Destination alpha blend factor. Default is BlendFactorZero.
    WisBlendOp alpha_blend_op; ///< Alpha blend operation. Default is BlendOpAdd.
    WisColorComponents color_write_mask; ///< Color write mask. Default is ColorComponentsAll.
};

/**
 * @brief Blend state description for .
 * */
struct WisBlendStateDesc {
    bool logic_op_enable; ///< Logic operation enable. Default is false.
    WisLogicOp logic_op; ///< Logic operation. Default is LogicOpNoop.
    WisBlendAttachmentDesc attachments[8]; ///< Blend attachment descriptions. Max Array size is 8.
    uint32_t attachment_count; ///< Blend attachment count.
};

/**
 * @brief Render attachments description for .
 * */
struct WisRenderAttachmentsDesc {
    WisDataFormat* attachment_formats; ///< Attachment formats array. Describes the format of the render target.
    uint32_t attachments_count; ///< Attachment formats count.
    WisDataFormat depth_attachment; ///< Depth attachment format. Describes the format of the depth buffer.
};

/**
 * @brief Root constant description for .
 * */
struct WisRootConstant {
    WisShaderStages stage; ///< Shader stage. Defines the stage where the constant is used.
    uint32_t size_bytes; ///< Size of the constant in bytes.
};

/**
 * @brief Swapchain description for SwapChain creation.
 * */
struct WisSwapchainDesc {
    WisSize2D size; ///< Swapchain texture size.
    WisDataFormat format; ///< Swapchain texture format.
    uint32_t buffer_count; ///< Swapchain buffer count.
    bool stereo; ///< Stereo mode enable. If there is no stereo in the system will be ignored.
    bool vsync; ///< VSync enable. Specifies Initial VSync. This value may be changed on per-present bases with DeviceFeatureDynamicVSync.
    bool tearing; ///< Tearing enable. If VSync is disabled, Tearing may be enabled. If System does not allow tearing the flag is ignored.
};

/**
 * @brief Texture description for Texture creation.
 * */
struct WisTextureDesc {
    WisDataFormat format; ///< Texture pixel/block format.
    WisSize3D size; ///< Texture size. Third dimension may be used for array layers or depth layers, depending on WisTextureDesc::layout.
    uint32_t mip_levels; ///< Mip levels count. Default is 1.
    WisTextureLayout layout; ///< Texture layout. Default is TextureLayoutTexture2D.
    WisSampleRate sample_count; ///< Sample count. Default is SampleRateS1.
    WisTextureUsage usage; ///< Texture usage flags.
};

/**
 * @brief Allocation info for Resource Allocation.
 * */
struct WisAllocationInfo {
    uint64_t size_bytes; ///< Size of the allocation in bytes.
    uint64_t alignment_bytes; ///< Alignment of the allocation in bytes.
};

/**
 * @brief Texture region for copy operations.
 * */
struct WisTextureRegion {
    /**
     * @brief Offset in the texture in pixels.
     * In BufferToTexture determines offset of destination texture.
     * In TextureToBuffer - offset of source image.
     * */
    WisSize3D offset;
    WisSize3D size; ///< Size of the region in pixels.
    uint32_t mip; ///< Mip level of the texture.
    uint32_t array_layer; ///< Array layer of the texture.
    WisDataFormat format; ///< Format of the texture.
};

/**
 * @brief Buffer to texture copy region.
 * */
struct WisBufferTextureCopyRegion {
    uint64_t buffer_offset; ///< Buffer offset in bytes.
    WisTextureRegion texture; ///< Texture region.
};

/**
 * @brief Push descriptor. Unused for now.
 * */
struct WisPushDescriptor {
    WisShaderStages stage;
    uint32_t bind_register;
    WisDescriptorType type;
    uint32_t reserved;
};

/**
 * @brief Subresource range for WisTextureBarrier.
 * */
struct WisSubresourceRange {
    uint32_t base_mip_level; ///< Base mip level.
    uint32_t level_count; ///< Mip levels count.
    uint32_t base_array_layer; ///< Base array layer.
    uint32_t layer_count; ///< Array layers count.
};

/**
 * @brief Render target description for RenderTarget creation.
 * */
struct WisRenderTargetDesc {
    WisDataFormat format; ///< Render target format.
    WisTextureLayout layout; ///< Render target layout. Default is TextureLayoutTexture2D.
    uint32_t mip; ///< Mip level of the render target. Default is 0.
    uint32_t base_array_layer; ///< Base array layer of the render target. Default is 0.
    uint32_t layer_count; ///< Array layers count of the render target. Default is 1.
};

/**
 * @brief Viewport description for CommandList.
 * Viewport is considered from Top Left corner.
 * */
struct WisViewport {
    float top_leftx; ///< Top left corner x coordinate.
    float top_lefty; ///< Top left corner y coordinate.
    float width; ///< Viewport width.
    float height; ///< Viewport height.
    float min_depth; ///< Minimum depth of the viewport.
    float max_depth; ///< Maximum depth of the viewport.
};

/**
 * @brief Scissor description for CommandList.
 * */
struct WisScissor {
    int32_t left; ///< Left corner x coordinate.
    int32_t top; ///< Top corner y coordinate.
    int32_t right; ///< Right corner x coordinate.
    int32_t bottom; ///< Bottom corner y coordinate.
};

/**
 * @brief Buffer barrier for CommandList.
 * */
struct WisBufferBarrier {
    WisBarrierSync sync_before; ///< Synchronization before the barrier.
    WisBarrierSync sync_after; ///< Synchronization after the barrier.
    WisResourceAccess access_before; ///< Resource access before the barrier.
    WisResourceAccess access_after; ///< Resource access after the barrier.
    uint64_t offset; ///< Offset in the buffer in bytes. Default is 0.
    uint64_t size; ///< Size of the buffer in bytes. Default is UINT64_MAX, which means entire buffer.
};

/**
 * @brief Texture barrier for CommandList.
 * */
struct WisTextureBarrier {
    WisBarrierSync sync_before; ///< Synchronization before the barrier.
    WisBarrierSync sync_after; ///< Synchronization after the barrier.
    WisResourceAccess access_before; ///< Resource access before the barrier.
    WisResourceAccess access_after; ///< Resource access after the barrier.
    WisTextureState state_before; ///< Texture state before the barrier.
    WisTextureState state_after; ///< Texture state after the barrier.
    WisSubresourceRange subresource_range; ///< Subresource range of the texture.
};

/**
 * @brief Descriptor table entry for WisDescriptorTable.
 * */
struct WisDescriptorTableEntry {
    WisDescriptorType type; ///< Descriptor type.
    uint32_t bind_register; ///< Bind register number in HLSL.
    uint32_t binding; ///< Binding number in HLSL.
    uint32_t count; ///< Descriptor count for Array descriptors.
};

/**
 * @brief Descriptor table for .
 * */
struct WisDescriptorTable {
    WisDescriptorHeapType type; ///< Descriptor heap type. Either Descriptor or Sampler.
    WisDescriptorTableEntry* entries; ///< Descriptor table entries array.
    uint32_t entry_count; ///< Descriptor table entries count.
    WisShaderStages stage; ///< Shader stage. Defines the stage where the table is used.
};

/**
 * @brief Sampler description for Sampler creation.
 * */
struct WisSamplerDesc {
    WisFilter min_filter; ///< Minification filter.
    WisFilter mag_filter; ///< Magnification filter.
    WisFilter mip_filter; ///< Mip level filter.
    bool anisotropic; ///< Anisotropic filtering enable.
    uint32_t max_anisotropy; ///< Max anisotropy level. Max is 16.
    WisAddressMode address_u; ///< Address mode for U coordinate.
    WisAddressMode address_v; ///< Address mode for V coordinate.
    WisAddressMode address_w; ///< Address mode for W coordinate.
    float min_lod; ///< Min LOD value.
    float max_lod; ///< Max LOD value.
    float mip_lod_bias; ///< Mip LOD bias value.
    WisCompare comparison_op; ///< Comparison operation for comparison samplers.
    float border_color[4]; ///< Border color.
};

/**
 * @brief Component mapping for WisShaderResourceDesc.
 * */
struct WisComponentMapping {
    WisComponentSwizzle r; ///< Component mapping for Red channel. Default is ComponentSwizzleRed.
    WisComponentSwizzle g; ///< Component mapping for Green channel. Default is ComponentSwizzleGreen.
    WisComponentSwizzle b; ///< Component mapping for Blue channel. Default is ComponentSwizzleBlue.
    WisComponentSwizzle a; ///< Component mapping for Alpha channel. Default is ComponentSwizzleAlpha.
};

/**
 * @brief Shader resource description for .
 * */
struct WisShaderResourceDesc {
    WisDataFormat format; ///< Resource format.
    WisTextureViewType view_type; ///< Resource view type.
    WisComponentMapping component_mapping; ///< Component mapping.
    WisSubresourceRange subresource_range; ///< Subresource range of the resource.
};

/**
 * @brief Struct used to query the extensions for C code.
 * Queried results should not be freed, their lifetime ends with the Factory they were created with.
 * If WisFactoryExtQuery::extension_id is 0, WisFactoryExtQuery::result must be populated with already created extension.
 * Otherwise extension is ignored.
 * */
struct WisFactoryExtQuery {
    WisFactoryExtID extension_id; ///< Extension ID.
    /**
     * @brief Result of the query.
     * Pointer is populated with the extension with queried ID.
     * If the extension is not supported/failed to initialize the result is NULL.
     * */
    void* result;
};

/**
 * @brief Struct used to query the extensions for C code.
 * Queried results should not be freed, their lifetime ends with the Factory they were created with.
 * If WisDeviceExtQuery::extension_id is 0, WisDeviceExtQuery::result must be populated with already created extension.
 * Otherwise extension is ignored.
 * */
struct WisDeviceExtQuery {
    WisDeviceExtID extension_id; ///< Extension ID.
    /**
     * @brief Result of the query.
     * Pointer is populated with the extension with queried ID.
     * If the extension is not supported/failed to initialize the result is NULL.
     * */
    void* result;
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

//=================================DELEGATES=================================

/**
 * @brief Debug callback delegate. Used for Library internal log messages.
 * @param severity Severity of the message. Depend on WISDOM_LOG_LEVEL option.
 * @param message Message string.
 * @param user_data User data pointer.
 * */
typedef void (*DebugCallback)(WisSeverity severity, const char* message, void* user_data);

//-------------------------------------------------------------------------

#ifdef WISDOM_VULKAN
typedef struct VKCommandListView VKCommandListView;
typedef struct VKGraphicsPipelineDesc VKGraphicsPipelineDesc;
typedef struct VKFenceView VKFenceView;
typedef struct VKRenderPassDepthStencilDesc VKRenderPassDepthStencilDesc;
typedef struct VKBufferView VKBufferView;
typedef struct VKTextureView VKTextureView;
typedef struct VKShaderView VKShaderView;
typedef struct VKRenderTargetView VKRenderTargetView;
typedef struct VKRootSignatureView VKRootSignatureView;
typedef struct VKDescriptorBufferView VKDescriptorBufferView;
typedef struct VKBufferBarrier2 VKBufferBarrier2;
typedef struct VKTextureBarrier2 VKTextureBarrier2;
typedef struct VKGraphicsShaderStages VKGraphicsShaderStages;
typedef struct VKRenderPassRenderTargetDesc VKRenderPassRenderTargetDesc;
typedef struct VKRenderPassDesc VKRenderPassDesc;
typedef struct VKVertexBufferBinding VKVertexBufferBinding;

//-------------------------------------------------------------------------

struct VKFenceView {
    void* value;
};

struct VKBufferView {
    void* value;
};

struct VKTextureView {
    void* value;
    uint32_t value2;
    WisSize2D value3;
};

struct VKRenderTargetView {
    void* value;
};

struct VKCommandListView {
    void* value;
};

struct VKShaderView {
    void* value;
};

struct VKRootSignatureView {
    void* value;
};

struct VKDescriptorBufferView {
    uint64_t value1;
    uint32_t value2;
};

/**
 * @brief Variant of BufferBarrier with BufferView.
 * */
struct VKBufferBarrier2 {
    WisBufferBarrier barrier; ///< Buffer barrier.
    VKBufferView buffer; ///< Buffer view.
};

/**
 * @brief Variant of TextureBarrier with TextureView.
 * */
struct VKTextureBarrier2 {
    WisTextureBarrier barrier; ///< Texture barrier.
    VKTextureView texture; ///< Texture view.
};

/**
 * @brief Variant of ShaderView for all graphics stages.
 * */
struct VKGraphicsShaderStages {
    VKShaderView vertex; ///< Vertex shader.
    VKShaderView hull; ///< Hull shader.
    VKShaderView domain; ///< Domain shader.
    VKShaderView geometry; ///< Geometry shader.
    VKShaderView pixel; ///< Pixel shader.
};

/**
 * @brief Variant of PipelineStateDesc for graphics pipeline.
 * */
struct VKGraphicsPipelineDesc {
    VKRootSignatureView root_signature; ///< Root signature.
    WisInputLayout input_layout; ///< Input layout.
    VKGraphicsShaderStages shaders; ///< Shader stages.
    WisRenderAttachmentsDesc attachments; ///< Render attachments.
    WisRasterizerDesc* rasterizer; ///< Rasterizer description.
    WisSampleDesc* sample; ///< Sample description.
    WisBlendStateDesc* blend; ///< Blend state description.
    WisDepthStencilDesc* depth_stencil; ///< Depth stencil description.
    WisTopologyType topology_type; ///< Topology type. Default is TopologyTypeTriangle.
};

/**
 * @brief Variant of RenderPassDesc for render target.
 * */
struct VKRenderPassRenderTargetDesc {
    VKRenderTargetView target; ///< Render target view.
    WisLoadOperation load_op; ///< Load operation on beginning of render pass. Default is LoadOperationLoad.
    WisStoreOperation store_op; ///< Store operation on end of render pass. Default is StoreOperationStore.
    float clear_value[4]; ///< Clear value for LoadOperationClear.
};

/**
 * @brief Variant of RenderPassDesc for depth stencil.
 * */
struct VKRenderPassDepthStencilDesc {
    VKRenderTargetView target; ///< Depth stencil view.
    WisLoadOperation load_op_depth; ///< Load operation on beginning of render pass for depth. Default is LoadOperationLoad.
    WisLoadOperation load_op_stencil; ///< Load operation on beginning of render pass for stencil. Default is LoadOperationLoad.
    WisStoreOperation store_op_depth; ///< Store operation on end of render pass for depth. Default is StoreOperationStore.
    WisStoreOperation store_op_stencil; ///< Store operation on end of render pass for stencil. Default is StoreOperationStore.
    WisDSSelect depth_stencil_select; ///< Depth stencil select. Default is DSSelectNone.
    float clear_depth; ///< Clear depth value for LoadOperationClear. Default is 1.0f.
    uint8_t clear_stencil; ///< Clear stencil value for LoadOperationClear. Default is 0.
};

/**
 * @brief Variant of PipelineStateDesc for render pass.
 * */
struct VKRenderPassDesc {
    WisRenderPassFlags flags; ///< Render pass flags.
    uint32_t target_count; ///< Render target count.
    VKRenderPassRenderTargetDesc* targets; ///< Render target descriptions.
    VKRenderPassDepthStencilDesc* depth_stencil; ///< Depth stencil description.
};

/**
 * @brief Variant of BufferView for vertex buffer binding.
 * */
struct VKVertexBufferBinding {
    VKBufferView buffer; ///< Buffer view.
    uint32_t size; ///< Size of the buffer in bytes.
    uint32_t stride; ///< Stride of the buffer in bytes.
};

//-------------------------------------------------------------------------

typedef struct VKCommandQueue_t* VKCommandQueue;
typedef struct VKRootSignature_t* VKRootSignature;
typedef struct VKFactory_t* VKFactory;
typedef struct VKDeviceExtension_t* VKDeviceExtension;
typedef struct VKPipelineState_t* VKPipelineState;
typedef struct VKAdapter_t* VKAdapter;
typedef struct VKDevice_t* VKDevice;
typedef struct VKFence_t* VKFence;
typedef struct VKFactoryExtension_t* VKFactoryExtension;
typedef struct VKResourceAllocator_t* VKResourceAllocator;
typedef struct VKShader_t* VKShader;
typedef struct VKCommandList_t* VKCommandList;
typedef struct VKSwapChain_t* VKSwapChain;
typedef struct VKBuffer_t* VKBuffer;
typedef struct VKTexture_t* VKTexture;
typedef struct VKDebugMessenger_t* VKDebugMessenger;
typedef struct VKRenderTarget_t* VKRenderTarget;
typedef struct VKDescriptorBuffer_t* VKDescriptorBuffer;
typedef struct VKSampler_t* VKSampler;
typedef struct VKMemory_t* VKMemory;
typedef struct VKShaderResource_t* VKShaderResource;

//-------------------------------------------------------------------------

// VKFactory methods --
/**
 * @brief Destroys the VKFactory and all the extensions created by it.
 * Order of destruction is Extensions in which they were created, then factory.
 * @param self valid handle to the Factory
 * */
WISDOM_API void VKFactoryDestroy(VKFactory self);

/**
 * @brief Creates the VKAdapter for the factory with provided index.
 * @param self valid handle to the Factory
 * @param index The index of the adapter to get.
 * @param preference The preference of the adapter to get.
 * Default is AdapterPreferencePerformance.
 * @param adapter VKAdapter on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
WISDOM_API WisResult VKFactoryGetAdapter(VKFactory self, uint32_t index, WisAdapterPreference preference, VKAdapter* adapter);

// VKAdapter methods --
/**
 * @brief Destroys the VKAdapter.
 * @param self valid handle to the Adapter
 * */
WISDOM_API void VKAdapterDestroy(VKAdapter self);

/**
 * @brief Fills WisAdapterDesc with physical adapter's data.
 * @param self valid handle to the Adapter
 * @param inout_desc The WisAdapterDesc to fill.
 * Must not be NULL.
 * */
WISDOM_API void VKAdapterGetDesc(VKAdapter self, WisAdapterDesc* inout_desc);

//-------------------------------------------------------------------------

/**
 * @brief Creates the VKFactory with extensions, specified in extension array.
 * @param debug_layer Enable the debug layer for underlying API.
 * @param extensions Query the extensions that need to be present.
 * The extension pointers are initialized if the extension is found and initialized.
 * Otherwise returns NULL.
 * @param extension_count The number of extensions to enable.
 * @param factory VKFactory on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
WISDOM_API WisResult VKCreateFactory(bool debug_layer, WisFactoryExtQuery* extensions, uint32_t extension_count, VKFactory* factory);
/**
 * @brief Creates the VKDevice with extensions, specified in extension array.
 * @param adapter The adapter to create the logical device on.
 * @param extensions Query the extensions that need to be present.
 * The extension pointers are initialized if the extension is found and initialized.
 * Otherwise returns NULL.
 * @param extension_count The number of extensions to enable.
 * @param force Create logical device even if some core functionality is absent.
 * The presence of core functionality is checked by the query function.
 * @param device VKDevice on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
WISDOM_API WisResult VKCreateDevice(VKAdapter adapter, WisDeviceExtQuery* extensions, uint32_t extension_count, bool force, VKDevice* device);

//-------------------------------------------------------------------------

WISDOM_API VKFenceView AsVKFenceView(VKFence self);
WISDOM_API VKBufferView AsVKBufferView(VKBuffer self);
WISDOM_API VKTextureView AsVKTextureView(VKTexture self);
WISDOM_API VKRenderTargetView AsVKRenderTargetView(VKRenderTarget self);
WISDOM_API VKCommandListView AsVKCommandListView(VKCommandList self);
WISDOM_API VKShaderView AsVKShaderView(VKShader self);
WISDOM_API VKRootSignatureView AsVKRootSignatureView(VKRootSignature self);
WISDOM_API VKDescriptorBufferView AsVKDescriptorBufferView(VKDescriptorBuffer self);
#endif

#ifdef WISDOM_DX12
typedef struct DX12CommandListView DX12CommandListView;
typedef struct DX12GraphicsPipelineDesc DX12GraphicsPipelineDesc;
typedef struct DX12FenceView DX12FenceView;
typedef struct DX12RenderPassDepthStencilDesc DX12RenderPassDepthStencilDesc;
typedef struct DX12BufferView DX12BufferView;
typedef struct DX12TextureView DX12TextureView;
typedef struct DX12ShaderView DX12ShaderView;
typedef struct DX12RenderTargetView DX12RenderTargetView;
typedef struct DX12RootSignatureView DX12RootSignatureView;
typedef struct DX12DescriptorBufferView DX12DescriptorBufferView;
typedef struct DX12BufferBarrier2 DX12BufferBarrier2;
typedef struct DX12TextureBarrier2 DX12TextureBarrier2;
typedef struct DX12GraphicsShaderStages DX12GraphicsShaderStages;
typedef struct DX12RenderPassRenderTargetDesc DX12RenderPassRenderTargetDesc;
typedef struct DX12RenderPassDesc DX12RenderPassDesc;
typedef struct DX12VertexBufferBinding DX12VertexBufferBinding;

//-------------------------------------------------------------------------

struct DX12FenceView {
    void* value;
};

struct DX12BufferView {
    void* value;
};

struct DX12TextureView {
    void* value;
};

struct DX12RenderTargetView {
    void* value;
};

struct DX12CommandListView {
    void* value;
};

struct DX12ShaderView {
    void* bytecode;
    uint32_t size_bytes;
};

struct DX12RootSignatureView {
    void* value;
};

struct DX12DescriptorBufferView {
    void* value;
};

/**
 * @brief Variant of BufferBarrier with BufferView.
 * */
struct DX12BufferBarrier2 {
    WisBufferBarrier barrier; ///< Buffer barrier.
    DX12BufferView buffer; ///< Buffer view.
};

/**
 * @brief Variant of TextureBarrier with TextureView.
 * */
struct DX12TextureBarrier2 {
    WisTextureBarrier barrier; ///< Texture barrier.
    DX12TextureView texture; ///< Texture view.
};

/**
 * @brief Variant of ShaderView for all graphics stages.
 * */
struct DX12GraphicsShaderStages {
    DX12ShaderView vertex; ///< Vertex shader.
    DX12ShaderView hull; ///< Hull shader.
    DX12ShaderView domain; ///< Domain shader.
    DX12ShaderView geometry; ///< Geometry shader.
    DX12ShaderView pixel; ///< Pixel shader.
};

/**
 * @brief Variant of PipelineStateDesc for graphics pipeline.
 * */
struct DX12GraphicsPipelineDesc {
    DX12RootSignatureView root_signature; ///< Root signature.
    WisInputLayout input_layout; ///< Input layout.
    DX12GraphicsShaderStages shaders; ///< Shader stages.
    WisRenderAttachmentsDesc attachments; ///< Render attachments.
    WisRasterizerDesc* rasterizer; ///< Rasterizer description.
    WisSampleDesc* sample; ///< Sample description.
    WisBlendStateDesc* blend; ///< Blend state description.
    WisDepthStencilDesc* depth_stencil; ///< Depth stencil description.
    WisTopologyType topology_type; ///< Topology type. Default is TopologyTypeTriangle.
};

/**
 * @brief Variant of RenderPassDesc for render target.
 * */
struct DX12RenderPassRenderTargetDesc {
    DX12RenderTargetView target; ///< Render target view.
    WisLoadOperation load_op; ///< Load operation on beginning of render pass. Default is LoadOperationLoad.
    WisStoreOperation store_op; ///< Store operation on end of render pass. Default is StoreOperationStore.
    float clear_value[4]; ///< Clear value for LoadOperationClear.
};

/**
 * @brief Variant of RenderPassDesc for depth stencil.
 * */
struct DX12RenderPassDepthStencilDesc {
    DX12RenderTargetView target; ///< Depth stencil view.
    WisLoadOperation load_op_depth; ///< Load operation on beginning of render pass for depth. Default is LoadOperationLoad.
    WisLoadOperation load_op_stencil; ///< Load operation on beginning of render pass for stencil. Default is LoadOperationLoad.
    WisStoreOperation store_op_depth; ///< Store operation on end of render pass for depth. Default is StoreOperationStore.
    WisStoreOperation store_op_stencil; ///< Store operation on end of render pass for stencil. Default is StoreOperationStore.
    WisDSSelect depth_stencil_select; ///< Depth stencil select. Default is DSSelectNone.
    float clear_depth; ///< Clear depth value for LoadOperationClear. Default is 1.0f.
    uint8_t clear_stencil; ///< Clear stencil value for LoadOperationClear. Default is 0.
};

/**
 * @brief Variant of PipelineStateDesc for render pass.
 * */
struct DX12RenderPassDesc {
    WisRenderPassFlags flags; ///< Render pass flags.
    uint32_t target_count; ///< Render target count.
    DX12RenderPassRenderTargetDesc* targets; ///< Render target descriptions.
    DX12RenderPassDepthStencilDesc* depth_stencil; ///< Depth stencil description.
};

/**
 * @brief Variant of BufferView for vertex buffer binding.
 * */
struct DX12VertexBufferBinding {
    DX12BufferView buffer; ///< Buffer view.
    uint32_t size; ///< Size of the buffer in bytes.
    uint32_t stride; ///< Stride of the buffer in bytes.
};

//-------------------------------------------------------------------------

typedef struct DX12CommandQueue_t* DX12CommandQueue;
typedef struct DX12RootSignature_t* DX12RootSignature;
typedef struct DX12Factory_t* DX12Factory;
typedef struct DX12DeviceExtension_t* DX12DeviceExtension;
typedef struct DX12PipelineState_t* DX12PipelineState;
typedef struct DX12Adapter_t* DX12Adapter;
typedef struct DX12Device_t* DX12Device;
typedef struct DX12Fence_t* DX12Fence;
typedef struct DX12FactoryExtension_t* DX12FactoryExtension;
typedef struct DX12ResourceAllocator_t* DX12ResourceAllocator;
typedef struct DX12Shader_t* DX12Shader;
typedef struct DX12CommandList_t* DX12CommandList;
typedef struct DX12SwapChain_t* DX12SwapChain;
typedef struct DX12Buffer_t* DX12Buffer;
typedef struct DX12Texture_t* DX12Texture;
typedef struct DX12DebugMessenger_t* DX12DebugMessenger;
typedef struct DX12RenderTarget_t* DX12RenderTarget;
typedef struct DX12DescriptorBuffer_t* DX12DescriptorBuffer;
typedef struct DX12Sampler_t* DX12Sampler;
typedef struct DX12Memory_t* DX12Memory;
typedef struct DX12ShaderResource_t* DX12ShaderResource;

//-------------------------------------------------------------------------

// DX12Factory methods --
/**
 * @brief Destroys the DX12Factory and all the extensions created by it.
 * Order of destruction is Extensions in which they were created, then factory.
 * @param self valid handle to the Factory
 * */
WISDOM_API void DX12FactoryDestroy(DX12Factory self);

/**
 * @brief Creates the DX12Adapter for the factory with provided index.
 * @param self valid handle to the Factory
 * @param index The index of the adapter to get.
 * @param preference The preference of the adapter to get.
 * Default is AdapterPreferencePerformance.
 * @param adapter DX12Adapter on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
WISDOM_API WisResult DX12FactoryGetAdapter(DX12Factory self, uint32_t index, WisAdapterPreference preference, DX12Adapter* adapter);

// DX12Adapter methods --
/**
 * @brief Destroys the DX12Adapter.
 * @param self valid handle to the Adapter
 * */
WISDOM_API void DX12AdapterDestroy(DX12Adapter self);

/**
 * @brief Fills WisAdapterDesc with physical adapter's data.
 * @param self valid handle to the Adapter
 * @param inout_desc The WisAdapterDesc to fill.
 * Must not be NULL.
 * */
WISDOM_API void DX12AdapterGetDesc(DX12Adapter self, WisAdapterDesc* inout_desc);

//-------------------------------------------------------------------------

/**
 * @brief Creates the DX12Factory with extensions, specified in extension array.
 * @param debug_layer Enable the debug layer for underlying API.
 * @param extensions Query the extensions that need to be present.
 * The extension pointers are initialized if the extension is found and initialized.
 * Otherwise returns NULL.
 * @param extension_count The number of extensions to enable.
 * @param factory DX12Factory on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
WISDOM_API WisResult DX12CreateFactory(bool debug_layer, WisFactoryExtQuery* extensions, uint32_t extension_count, DX12Factory* factory);
/**
 * @brief Creates the DX12Device with extensions, specified in extension array.
 * @param adapter The adapter to create the logical device on.
 * @param extensions Query the extensions that need to be present.
 * The extension pointers are initialized if the extension is found and initialized.
 * Otherwise returns NULL.
 * @param extension_count The number of extensions to enable.
 * @param force Create logical device even if some core functionality is absent.
 * The presence of core functionality is checked by the query function.
 * @param device DX12Device on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
WISDOM_API WisResult DX12CreateDevice(DX12Adapter adapter, WisDeviceExtQuery* extensions, uint32_t extension_count, bool force, DX12Device* device);

//-------------------------------------------------------------------------

WISDOM_API DX12FenceView AsDX12FenceView(DX12Fence self);
WISDOM_API DX12BufferView AsDX12BufferView(DX12Buffer self);
WISDOM_API DX12TextureView AsDX12TextureView(DX12Texture self);
WISDOM_API DX12RenderTargetView AsDX12RenderTargetView(DX12RenderTarget self);
WISDOM_API DX12CommandListView AsDX12CommandListView(DX12CommandList self);
WISDOM_API DX12ShaderView AsDX12ShaderView(DX12Shader self);
WISDOM_API DX12RootSignatureView AsDX12RootSignatureView(DX12RootSignature self);
WISDOM_API DX12DescriptorBufferView AsDX12DescriptorBufferView(DX12DescriptorBuffer self);
#endif

#if defined(WISDOM_VULKAN) && defined(WISDOM_FORCE_VULKAN)
#define FORCEVK_SWITCH 1
#else
#define FORCEVK_SWITCH 0
#endif

#if defined(WISDOM_DX12) && !FORCEVK_SWITCH
typedef DX12CommandQueue WisCommandQueue;
typedef DX12RootSignature WisRootSignature;
typedef DX12Factory WisFactory;
typedef DX12DeviceExtension WisDeviceExtension;
typedef DX12PipelineState WisPipelineState;
typedef DX12Adapter WisAdapter;
typedef DX12Device WisDevice;
typedef DX12Fence WisFence;
typedef DX12FactoryExtension WisFactoryExtension;
typedef DX12ResourceAllocator WisResourceAllocator;
typedef DX12Shader WisShader;
typedef DX12CommandList WisCommandList;
typedef DX12SwapChain WisSwapChain;
typedef DX12Buffer WisBuffer;
typedef DX12Texture WisTexture;
typedef DX12DebugMessenger WisDebugMessenger;
typedef DX12RenderTarget WisRenderTarget;
typedef DX12DescriptorBuffer WisDescriptorBuffer;
typedef DX12Sampler WisSampler;
typedef DX12Memory WisMemory;
typedef DX12ShaderResource WisShaderResource;

//-------------------------------------------------------------------------

// WisFactory methods --
/**
 * @brief Destroys the WisFactory and all the extensions created by it.
 * Order of destruction is Extensions in which they were created, then factory.
 * @param self valid handle to the Factory
 * */
inline void WisFactoryDestroy(WisFactory self)
{
    return DX12FactoryDestroy(self);
}

/**
 * @brief Creates the WisAdapter for the factory with provided index.
 * @param self valid handle to the Factory
 * @param index The index of the adapter to get.
 * @param preference The preference of the adapter to get.
 * Default is AdapterPreferencePerformance.
 * @param adapter WisAdapter on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
inline WisResult WisFactoryGetAdapter(WisFactory self, uint32_t index, WisAdapterPreference preference, WisAdapter* adapter)
{
    return DX12FactoryGetAdapter(self, index, preference, adapter);
}

// WisAdapter methods --
/**
 * @brief Destroys the WisAdapter.
 * @param self valid handle to the Adapter
 * */
inline void WisAdapterDestroy(WisAdapter self)
{
    return DX12AdapterDestroy(self);
}

/**
 * @brief Fills WisAdapterDesc with physical adapter's data.
 * @param self valid handle to the Adapter
 * @param inout_desc The WisAdapterDesc to fill.
 * Must not be NULL.
 * */
inline void WisAdapterGetDesc(WisAdapter self, WisAdapterDesc* inout_desc)
{
    return DX12AdapterGetDesc(self, inout_desc);
}

//-------------------------------------------------------------------------

/**
 * @brief Creates the WisFactory with extensions, specified in extension array.
 * @param debug_layer Enable the debug layer for underlying API.
 * @param extensions Query the extensions that need to be present.
 * The extension pointers are initialized if the extension is found and initialized.
 * Otherwise returns NULL.
 * @param extension_count The number of extensions to enable.
 * @param factory WisFactory on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
inline WisResult WisCreateFactory(bool debug_layer, WisFactoryExtQuery* extensions, uint32_t extension_count, WisFactory* factory)
{
    return DX12CreateFactory(debug_layer, extensions, extension_count, factory);
}

/**
 * @brief Creates the WisDevice with extensions, specified in extension array.
 * @param adapter The adapter to create the logical device on.
 * @param extensions Query the extensions that need to be present.
 * The extension pointers are initialized if the extension is found and initialized.
 * Otherwise returns NULL.
 * @param extension_count The number of extensions to enable.
 * @param force Create logical device even if some core functionality is absent.
 * The presence of core functionality is checked by the query function.
 * @param device WisDevice on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
inline WisResult WisCreateDevice(WisAdapter adapter, WisDeviceExtQuery* extensions, uint32_t extension_count, bool force, WisDevice* device)
{
    return DX12CreateDevice(adapter, extensions, extension_count, force, device);
}

#elif defined(WISDOM_VULKAN)

typedef VKCommandQueue WisCommandQueue;
typedef VKRootSignature WisRootSignature;
typedef VKFactory WisFactory;
typedef VKDeviceExtension WisDeviceExtension;
typedef VKPipelineState WisPipelineState;
typedef VKAdapter WisAdapter;
typedef VKDevice WisDevice;
typedef VKFence WisFence;
typedef VKFactoryExtension WisFactoryExtension;
typedef VKResourceAllocator WisResourceAllocator;
typedef VKShader WisShader;
typedef VKCommandList WisCommandList;
typedef VKSwapChain WisSwapChain;
typedef VKBuffer WisBuffer;
typedef VKTexture WisTexture;
typedef VKDebugMessenger WisDebugMessenger;
typedef VKRenderTarget WisRenderTarget;
typedef VKDescriptorBuffer WisDescriptorBuffer;
typedef VKSampler WisSampler;
typedef VKMemory WisMemory;
typedef VKShaderResource WisShaderResource;

//-------------------------------------------------------------------------

// WisFactory methods --
/**
 * @brief Destroys the WisFactory and all the extensions created by it.
 * Order of destruction is Extensions in which they were created, then factory.
 * @param self valid handle to the Factory
 * */
inline void WisFactoryDestroy(WisFactory self)
{
    return VKFactoryDestroy(self);
}

/**
 * @brief Creates the WisAdapter for the factory with provided index.
 * @param self valid handle to the Factory
 * @param index The index of the adapter to get.
 * @param preference The preference of the adapter to get.
 * Default is AdapterPreferencePerformance.
 * @param adapter WisAdapter on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
inline WisResult WisFactoryGetAdapter(WisFactory self, uint32_t index, WisAdapterPreference preference, WisAdapter* adapter)
{
    return VKFactoryGetAdapter(self, index, preference, adapter);
}

// WisAdapter methods --
/**
 * @brief Destroys the WisAdapter.
 * @param self valid handle to the Adapter
 * */
inline void WisAdapterDestroy(WisAdapter self)
{
    return VKAdapterDestroy(self);
}

/**
 * @brief Fills WisAdapterDesc with physical adapter's data.
 * @param self valid handle to the Adapter
 * @param inout_desc The WisAdapterDesc to fill.
 * Must not be NULL.
 * */
inline void WisAdapterGetDesc(WisAdapter self, WisAdapterDesc* inout_desc)
{
    return VKAdapterGetDesc(self, inout_desc);
}

//-------------------------------------------------------------------------

/**
 * @brief Creates the WisFactory with extensions, specified in extension array.
 * @param debug_layer Enable the debug layer for underlying API.
 * @param extensions Query the extensions that need to be present.
 * The extension pointers are initialized if the extension is found and initialized.
 * Otherwise returns NULL.
 * @param extension_count The number of extensions to enable.
 * @param factory WisFactory on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
inline WisResult WisCreateFactory(bool debug_layer, WisFactoryExtQuery* extensions, uint32_t extension_count, WisFactory* factory)
{
    return VKCreateFactory(debug_layer, extensions, extension_count, factory);
}

/**
 * @brief Creates the WisDevice with extensions, specified in extension array.
 * @param adapter The adapter to create the logical device on.
 * @param extensions Query the extensions that need to be present.
 * The extension pointers are initialized if the extension is found and initialized.
 * Otherwise returns NULL.
 * @param extension_count The number of extensions to enable.
 * @param force Create logical device even if some core functionality is absent.
 * The presence of core functionality is checked by the query function.
 * @param device WisDevice on success (StatusOk).
 * @return Result with StatusOk on success.
 * Error in WisResult::error otherwise.
 * */
inline WisResult WisCreateDevice(WisAdapter adapter, WisDeviceExtQuery* extensions, uint32_t extension_count, bool force, WisDevice* device)
{
    return VKCreateDevice(adapter, extensions, extension_count, force, device);
}

#endif

#ifdef __cplusplus
}
#endif

//-------------------------------------------------------------------------
