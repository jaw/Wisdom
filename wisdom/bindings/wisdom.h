// Generated by wisdom generator on 2024-02-17 15:06:38.9745564 GMT+1
#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct WisResult WisResult;
typedef struct WisSize2D WisSize2D;
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
typedef struct WisPushDescriptor WisPushDescriptor;
typedef enum WisShaderStages WisShaderStages;
typedef enum WisStatus WisStatus;
typedef enum WisQueuePriority WisQueuePriority;
typedef enum WisMutiWaitFlags WisMutiWaitFlags;
typedef enum WisDescriptorType WisDescriptorType;
typedef enum WisQueueType WisQueueType;
typedef enum WisAdapterPreference WisAdapterPreference;
typedef enum WisSeverity WisSeverity;
typedef enum WisInputClass WisInputClass;
typedef enum WisCullMode WisCullMode;
typedef enum WisDataFormat WisDataFormat;
typedef enum WisFillMode WisFillMode;
typedef enum WisWindingOrder WisWindingOrder;
typedef enum WisSampleRate WisSampleRate;
typedef enum WisCompare WisCompare;
typedef enum WisStencilOp WisStencilOp;
typedef enum WisBlendFactor WisBlendFactor;
typedef enum WisBlendOp WisBlendOp;
typedef enum WisLogicOp WisLogicOp;
typedef enum WisAdapterFlagsBits WisAdapterFlagsBits;
typedef uint32_t WisAdapterFlags;
typedef enum WisColorComponentsBits WisColorComponentsBits;
typedef uint32_t WisColorComponents;
typedef enum WisDeviceFeaturesBits WisDeviceFeaturesBits;
typedef uint32_t WisDeviceFeatures;
typedef struct DX12GraphicsPipelineDesc DX12GraphicsPipelineDesc;
typedef struct VKGraphicsPipelineDesc VKGraphicsPipelineDesc;
typedef struct DX12CommandListView DX12CommandListView;
typedef struct VKCommandListView VKCommandListView;
typedef struct DX12FenceView DX12FenceView;
typedef struct VKFenceView VKFenceView;
typedef struct DX12ShaderView DX12ShaderView;
typedef struct VKShaderView VKShaderView;
typedef struct DX12RootSignatureView DX12RootSignatureView;
typedef struct VKRootSignatureView VKRootSignatureView;
typedef struct DX12GraphicsShaderStages DX12GraphicsShaderStages;
typedef struct VKGraphicsShaderStages VKGraphicsShaderStages;

enum WisShaderStages {
    ShaderStagesAll = 0,
    ShaderStagesVertex = 1,
    ShaderStagesHull = 2,
    ShaderStagesDomain = 3,
    ShaderStagesGeometry = 4,
    ShaderStagesPixel = 5,
    ShaderStagesAmplification = 6,
    ShaderStagesMesh = 7,
};

enum WisStatus {
    StatusOk = 0,
    StatusTimeout = 1,
    StatusError = -1,
    StatusInvalidArgument = -2,
    StatusOutOfMemory = -3,
    StatusDeviceLost = -4,
};

enum WisQueuePriority {
    QueuePriorityCommon = 0,
    QueuePriorityHigh = 100,
    QueuePriorityRealtime = 10000,
};

enum WisMutiWaitFlags {
    MutiWaitFlagsAll = 0,
    MutiWaitFlagsAny = 1,
};

enum WisDescriptorType {
    DescriptorTypeNone = 0,
    DescriptorTypeConstantBuffer = 2,
    DescriptorTypeShaderResource = 3,
    DescriptorTypeUnorderedAccess = 4,
};

enum WisQueueType {
    QueueTypeGraphics = 0,
    QueueTypeDX12Bundle = 1,
    QueueTypeCompute = 2,
    QueueTypeCopy = 3,
    QueueTypeVideoDecode = 4,
    QueueTypeDX12VideoProcess = 5,
    QueueTypeDX12VideoEncode = 6,
};

enum WisAdapterPreference {
    AdapterPreferenceNone = 0,
    AdapterPreferenceMinConsumption = 1,
    AdapterPreferencePerformance = 2,
};

enum WisSeverity {
    SeverityDebug = 0,
    SeverityTrace = 1,
    SeverityInfo = 2,
    SeverityWarning = 3,
    SeverityError = 4,
    SeverityCritical = 5,
};

enum WisInputClass {
    InputClassPerVertex = 0,
    InputClassPerInstance = 1,
};

enum WisCullMode {
    CullModeNone = 1,
    CullModeFront = 2,
    CullModeBack = 3,
};

enum WisDataFormat {
    DataFormatUnknown = 0,
    DataFormatRGBA32Float = 2,
    DataFormatRGBA32Uint = 3,
    DataFormatRGBA32Sint = 4,
    DataFormatRGB32Float = 6,
    DataFormatRGB32Uint = 7,
    DataFormatRGB32Sint = 8,
    DataFormatRGBA16Float = 10,
    DataFormatRGBA16Unorm = 11,
    DataFormatRGBA16Uint = 12,
    DataFormatRGBA16Snorm = 13,
    DataFormatRGBA16Sint = 14,
    DataFormatRG32Float = 16,
    DataFormatRG32Uint = 17,
    DataFormatRG32Sint = 18,
    DataFormatD32FloatS8Uint = 20,
    DataFormatRGB10A2Unorm = 24,
    DataFormatRGB10A2Uint = 25,
    DataFormatRG11B10Float = 26,
    DataFormatRGBA8Unorm = 28,
    DataFormatRGBA8UnormSrgb = 29,
    DataFormatRGBA8Uint = 30,
    DataFormatRGBA8Snorm = 31,
    DataFormatRGBA8Sint = 32,
    DataFormatRG16Float = 34,
    DataFormatRG16Unorm = 35,
    DataFormatRG16Uint = 36,
    DataFormatRG16Snorm = 37,
    DataFormatRG16Sint = 38,
    DataFormatD32Float = 40,
    DataFormatR32Float = 41,
    DataFormatR32Uint = 42,
    DataFormatR32Sint = 43,
    DataFormatD24UnormS8Uint = 45,
    DataFormatRG8Unorm = 49,
    DataFormatRG8Uint = 50,
    DataFormatRG8Snorm = 51,
    DataFormatRG8Sint = 52,
    DataFormatR16Float = 54,
    DataFormatD16Unorm = 55,
    DataFormatR16Unorm = 56,
    DataFormatR16Uint = 57,
    DataFormatR16Snorm = 58,
    DataFormatR16Sint = 59,
    DataFormatR8Unorm = 61,
    DataFormatR8Uint = 62,
    DataFormatR8Snorm = 63,
    DataFormatR8Sint = 64,
    DataFormatRGB9E5UFloat = 67,
    DataFormatRG8BG8Unorm = 68,
    DataFormatGR8GB8Unorm = 69,
    DataFormatBC1RGBAUnorm = 71,
    DataFormatBC1RGBAUnormSrgb = 72,
    DataFormatBC2RGBAUnorm = 74,
    DataFormatBC2RGBAUnormSrgb = 75,
    DataFormatBC3RGBAUnorm = 77,
    DataFormatBC3RGBAUnormSrgb = 78,
    DataFormatBC4RUnorm = 80,
    DataFormatBC4RSnorm = 81,
    DataFormatBC5RGUnorm = 83,
    DataFormatBC5RGSnorm = 84,
    DataFormatB5R6G5Unorm = 85,
    DataFormatB5G5R5A1Unorm = 86,
    DataFormatBGRA8Unorm = 87,
    DataFormatBGRA8UnormSrgb = 91,
    DataFormatBC6HUfloat16 = 95,
    DataFormatBC6HSfloat16 = 96,
    DataFormatBC7RGBAUnorm = 98,
    DataFormatBC7RGBAUnormSrgb = 99,
};

enum WisFillMode {
    FillModeLines = 2,
    FillModeSolid = 3,
};

enum WisWindingOrder {
    WindingOrderClockwise = 0,
    WindingOrderCounterClockwise = 1,
};

enum WisSampleRate {
    SampleRateS1 = 1,
    SampleRateS2 = 2,
    SampleRateS4 = 4,
    SampleRateS8 = 8,
    SampleRateS16 = 16,
};

enum WisCompare {
    CompareNever = 1,
    CompareLess = 2,
    CompareEqual = 3,
    CompareLessEqual = 4,
    CompareGreater = 5,
    CompareNotEqual = 6,
    CompareGreaterEqual = 7,
    CompareAlways = 8,
};

enum WisStencilOp {
    StencilOpKeep = 1,
    StencilOpZero = 2,
    StencilOpReplace = 3,
    StencilOpIncClamp = 4,
    StencilOpDecClamp = 5,
    StencilOpInvert = 6,
    StencilOpIncWrap = 7,
    StencilOpDecWrap = 8,
};

enum WisBlendFactor {
    BlendFactorZero = 1,
    BlendFactorOne = 2,
    BlendFactorSrcColor = 3,
    BlendFactorInvSrcColor = 4,
    BlendFactorSrcAlpha = 5,
    BlendFactorInvSrcAlpha = 6,
    BlendFactorDestAlpha = 7,
    BlendFactorInvDestAlpha = 8,
    BlendFactorDestColor = 9,
    BlendFactorInvDestColor = 10,
    BlendFactorSrcAlphaSat = 11,
    BlendFactorBlendFactor = 14,
    BlendFactorInvBlendFactor = 15,
    BlendFactorSrc1Color = 16,
    BlendFactorInvSrc1Color = 17,
    BlendFactorSrc1Alpha = 18,
    BlendFactorInvSrc1Alpha = 19,
};

enum WisBlendOp {
    BlendOpAdd = 1,
    BlendOpSubtract = 2,
    BlendOpRevSubtract = 3,
    BlendOpMin = 4,
    BlendOpMax = 5,
};

enum WisLogicOp {
    LogicOpClear = 0,
    LogicOpSet = 1,
    LogicOpCopy = 2,
    LogicOpCopyInverted = 3,
    LogicOpNoop = 4,
    LogicOpInvert = 5,
    LogicOpAnd = 6,
    LogicOpNand = 7,
    LogicOpOr = 8,
    LogicOpNor = 9,
    LogicOpXor = 10,
    LogicOpEquiv = 11,
    LogicOpAndReverse = 12,
    LogicOpAndInverted = 13,
    LogicOpOrReverse = 14,
    LogicOpOrInverted = 15,
};

enum WisAdapterFlagsBits {
    AdapterFlagsNone = 0x0,
    AdapterFlagsRemote = 1 << 0,
    AdapterFlagsSoftware = 1 << 1,
    AdapterFlagsDX12ACGCompatible = 1 << 2,
    AdapterFlagsDX12SupportsMonitoredFences = 1 << 3,
    AdapterFlagsDX12SupportsNonMonitoredFences = 1 << 4,
    AdapterFlagsDX12KeyedMutexConformance = 1 << 5,
};

enum WisColorComponentsBits {
    ColorComponentsNone = 0x0,
    ColorComponentsR = 1 << 0,
    ColorComponentsG = 1 << 1,
    ColorComponentsB = 1 << 2,
    ColorComponentsA = 1 << 3,
    ColorComponentsAll = 0xF,
};

enum WisDeviceFeaturesBits {
    DeviceFeaturesNone = 0x0,
    DeviceFeaturesPushDescriptors = 1 << 0,
};

struct WisResult{
    WisStatus status;
    const char* error;
};

struct WisSize2D{
    uint32_t width;
    uint32_t height;
};

struct WisAdapterDesc{
    const char description[256];
    uint32_t vendor_id;
    uint32_t device_id;
    uint32_t subsys_id;
    uint32_t revision;
    uint64_t dedicated_video_memory;
    uint64_t dedicated_system_memory;
    uint64_t shared_system_memory;
    uint64_t adapter_id;
    WisAdapterFlags flags;
};

struct WisInputSlotDesc{
    uint32_t slot;
    uint32_t stride_bytes;
    WisInputClass input_class;
};

struct WisInputAttribute{
    uint32_t input_slot;
    const char* semantic_name;
    uint32_t semantic_index;
    uint32_t location;
    WisDataFormat format;
    uint32_t offset_bytes;
};

struct WisInputLayout{
    WisInputSlotDesc* slots;
    uint32_t slot_count;
    WisInputAttribute* attributes;
    uint32_t attribute_count;
};

struct WisRasterizerDesc{
    WisFillMode fill_mode;
    WisCullMode cull_mode;
    WisWindingOrder front_face;
    bool depth_bias_enable;
    float depth_bias;
    float depth_bias_clamp;
    float depth_bias_slope_factor;
    bool depth_clip_enable;
};

struct WisSampleDesc{
    WisSampleRate rate;
    float quality;
    uint32_t sample_mask;
};

struct WisStencilDesc{
    WisStencilOp fail_op;
    WisStencilOp depth_fail_op;
    WisStencilOp pass_op;
    WisCompare comparison;
    uint8_t read_mask;
    uint8_t write_mask;
};

struct WisDepthStencilDesc{
    bool depth_enable;
    bool depth_write_enable;
    WisCompare depth_comp;
    bool stencil_enable;
    WisStencilDesc stencil_front;
    WisStencilDesc stencil_back;
    bool depth_bound_test;
};

struct WisBlendAttachmentDesc{
    bool blend_enable;
    WisBlendFactor src_color_blend;
    WisBlendFactor dst_color_blend;
    WisBlendOp color_blend_op;
    WisBlendFactor src_alpha_blend;
    WisBlendFactor dst_alpha_blend;
    WisBlendOp alpha_blend_op;
    WisColorComponents color_write_mask;
};

struct WisBlendStateDesc{
    bool logic_op_enable;
    WisLogicOp logic_op;
    WisBlendAttachmentDesc attachments[8];
    uint32_t attachment_count;
};

struct WisRenderAttachmentsDesc{
    WisDataFormat* attachment_formats;
    uint32_t attachments_count;
    WisDataFormat depth_attachment;
};

struct WisRootConstant{
    WisShaderStages stage;
    uint32_t size_bytes;
};

struct WisSwapchainDesc{
    WisSize2D size;
    WisDataFormat format;
    uint32_t buffer_count;
    bool stereo;
    bool vsync;
};

struct WisPushDescriptor{
    WisShaderStages stage;
    uint32_t bind_register;
    WisDescriptorType type;
    uint32_t reserved;
};

struct DX12GraphicsPipelineDesc{
    DX12RootSignatureView root_signature;
    WisInputLayout input_layout;
    DX12GraphicsShaderStages shaders;
    WisRenderAttachmentsDesc attachments;
    WisRasterizerDesc* rasterizer;
    WisSampleDesc* sample;
    WisBlendStateDesc* blend;
    WisDepthStencilDesc* depth_stencil;
};

struct VKGraphicsPipelineDesc{
    VKRootSignatureView root_signature;
    WisInputLayout input_layout;
    VKGraphicsShaderStages shaders;
    WisRenderAttachmentsDesc attachments;
    WisRasterizerDesc* rasterizer;
    WisSampleDesc* sample;
    WisBlendStateDesc* blend;
    WisDepthStencilDesc* depth_stencil;
};

struct DX12CommandListView{
    void* value;
};

struct VKCommandListView{
    void* value;
};

struct DX12FenceView{
    void* value;
};

struct VKFenceView{
    void* value;
};

struct DX12ShaderView{
    void* bytecode;
    uint32_t size_bytes;
};

struct VKShaderView{
    void* value;
};

struct DX12RootSignatureView{
    void* value;
};

struct VKRootSignatureView{
    void* value;
};

struct DX12GraphicsShaderStages{
    DX12ShaderView vertex;
    DX12ShaderView hull;
    DX12ShaderView domain;
    DX12ShaderView geometry;
    DX12ShaderView pixel;
};

struct VKGraphicsShaderStages{
    VKShaderView vertex;
    VKShaderView hull;
    VKShaderView domain;
    VKShaderView geometry;
    VKShaderView pixel;
};

//=================================DELEGATES=================================

typedef void (*DebugCallback)( WisSeverity severity,  const char* message,  void* user_data);
//==================================HANDLES==================================

typedef struct DX12CommandQueue_t* DX12CommandQueue;
typedef struct VKCommandQueue_t* VKCommandQueue;

typedef struct DX12RootSignature_t* DX12RootSignature;
typedef struct VKRootSignature_t* VKRootSignature;

typedef struct DX12Factory_t* DX12Factory;
typedef struct VKFactory_t* VKFactory;

typedef struct DX12PipelineState_t* DX12PipelineState;
typedef struct VKPipelineState_t* VKPipelineState;

typedef struct DX12Adapter_t* DX12Adapter;
typedef struct VKAdapter_t* VKAdapter;

typedef struct DX12Device_t* DX12Device;
typedef struct VKDevice_t* VKDevice;

typedef struct DX12Fence_t* DX12Fence;
typedef struct VKFence_t* VKFence;

typedef struct DX12ResourceAllocator_t* DX12ResourceAllocator;
typedef struct VKResourceAllocator_t* VKResourceAllocator;

typedef struct DX12Shader_t* DX12Shader;
typedef struct VKShader_t* VKShader;

typedef struct DX12CommandList_t* DX12CommandList;
typedef struct VKCommandList_t* VKCommandList;

typedef struct DX12SwapChain_t* DX12SwapChain;
typedef struct VKSwapChain_t* VKSwapChain;

typedef struct DX12Buffer_t* DX12Buffer;
typedef struct VKBuffer_t* VKBuffer;

//=================================FUNCTIONS=================================

WisResult DX12CreateFactory( bool debug_layer,  DebugCallback callback,  void* user_data, DX12Factory* out_factory);
WisResult VKCreateFactory( bool debug_layer,  DebugCallback callback,  void* user_data, VKFactory* out_factory);
WisResult DX12CreateDevice( DX12Factory factory,  DX12Adapter adapter, DX12Device* out_device);
WisResult VKCreateDevice( VKFactory factory,  VKAdapter adapter, VKDevice* out_device);
WisResult DX12GetAdapter(DX12Factory self,  uint32_t index,  WisAdapterPreference preference, DX12Adapter* out_adapter);
WisResult VKGetAdapter(VKFactory self,  uint32_t index,  WisAdapterPreference preference, VKAdapter* out_adapter);
void DX12FactoryDestroy(DX12Factory self);
void VKFactoryDestroy(VKFactory self);
WisResult DX12GetDesc(DX12Adapter self,  WisAdapterDesc* desc);
WisResult VKGetDesc(VKAdapter self,  WisAdapterDesc* desc);
void DX12DeviceDestroy(DX12Device self);
void VKDeviceDestroy(VKDevice self);
WisResult DX12CreateFence(DX12Device self,  uint64_t initial_value, DX12Fence* out_fence);
WisResult VKCreateFence(VKDevice self,  uint64_t initial_value, VKFence* out_fence);
WisResult DX12CreateRootSignature(DX12Device self,  WisRootConstant* constants,  uint32_t constants_size, DX12RootSignature* out_root_signature);
WisResult VKCreateRootSignature(VKDevice self,  WisRootConstant* constants,  uint32_t constants_size, VKRootSignature* out_root_signature);
WisResult DX12CreateAllocator(DX12Device self, DX12ResourceAllocator* out_allocator);
WisResult VKCreateAllocator(VKDevice self, VKResourceAllocator* out_allocator);
WisResult DX12CreateCommandQueue(DX12Device self,  WisQueueType type,  WisQueuePriority priority, DX12CommandQueue* out_queue);
WisResult VKCreateCommandQueue(VKDevice self,  WisQueueType type,  WisQueuePriority priority, VKCommandQueue* out_queue);
WisResult DX12CreateShader(DX12Device self,  void* data,  uint32_t size_bytes, DX12Shader* out_shader);
WisResult VKCreateShader(VKDevice self,  void* data,  uint32_t size_bytes, VKShader* out_shader);
WisResult DX12WaitForMultipleFences(DX12Device self,  DX12FenceView* fences,  uint64_t* values,  uint32_t count,  WisMutiWaitFlags wait_all,  uint64_t timeout);
WisResult VKWaitForMultipleFences(VKDevice self,  VKFenceView* fences,  uint64_t* values,  uint32_t count,  WisMutiWaitFlags wait_all,  uint64_t timeout);
WisResult DX12CreatePipelineState(DX12Device self,  DX12GraphicsPipelineDesc* desc, DX12PipelineState* out_pipeline_state);
WisResult VKCreatePipelineState(VKDevice self,  VKGraphicsPipelineDesc* desc, VKPipelineState* out_pipeline_state);
WisResult DX12CreateCommandList(DX12Device self,  WisQueueType type, DX12CommandList* out_command_list);
WisResult VKCreateCommandList(VKDevice self,  WisQueueType type, VKCommandList* out_command_list);
void DX12RootSignatureDestroy(DX12RootSignature self);
void VKRootSignatureDestroy(VKRootSignature self);
void DX12FenceDestroy(DX12Fence self);
void VKFenceDestroy(VKFence self);
uint64_t DX12GetCompletedValue(DX12Fence self);
uint64_t VKGetCompletedValue(VKFence self);
WisResult DX12Wait(DX12Fence self,  uint64_t value,  uint64_t timeout_ns);
WisResult VKWait(VKFence self,  uint64_t value,  uint64_t timeout_ns);
WisResult DX12Signal(DX12Fence self,  uint64_t value);
WisResult VKSignal(VKFence self,  uint64_t value);
void DX12ResourceAllocatorDestroy(DX12ResourceAllocator self);
void VKResourceAllocatorDestroy(VKResourceAllocator self);
void DX12CommandQueueDestroy(DX12CommandQueue self);
void VKCommandQueueDestroy(VKCommandQueue self);
WisResult DX12SignalQueue(DX12CommandQueue self,  DX12FenceView fence,  uint64_t value);
WisResult VKSignalQueue(VKCommandQueue self,  VKFenceView fence,  uint64_t value);
void DX12ExecuteCommandLists(DX12CommandQueue self,  DX12CommandListView* lists,  uint32_t count);
void VKExecuteCommandLists(VKCommandQueue self,  VKCommandListView* lists,  uint32_t count);
void DX12ShaderDestroy(DX12Shader self);
void VKShaderDestroy(VKShader self);
void DX12PipelineStateDestroy(DX12PipelineState self);
void VKPipelineStateDestroy(VKPipelineState self);
void DX12CommandListDestroy(DX12CommandList self);
void VKCommandListDestroy(VKCommandList self);
void DX12BufferDestroy(DX12Buffer self);
void VKBufferDestroy(VKBuffer self);
void SwapchainDestroy();
DX12CommandListView AsDX12CommandListView(DX12CommandList self);
VKCommandListView AsVKCommandListView(VKCommandList self);
DX12FenceView AsDX12FenceView(DX12Fence self);
VKFenceView AsVKFenceView(VKFence self);
DX12ShaderView AsDX12ShaderView(DX12Shader self);
VKShaderView AsVKShaderView(VKShader self);
DX12RootSignatureView AsDX12RootSignatureView(DX12RootSignature self);
VKRootSignatureView AsVKRootSignatureView(VKRootSignature self);
