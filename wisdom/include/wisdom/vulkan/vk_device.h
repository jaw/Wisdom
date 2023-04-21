#pragma once
#include <wisdom/api/api_common.h>
#include <wisdom/vulkan/vk_adapter.h>
#include <wisdom/vulkan/vk_fence.h>
#include <wisdom/vulkan/vk_command_queue.h>
#include <wisdom/util/log_layer.h>
#include <wisdom/util/misc.h>
#include <unordered_set>
#include <wisdom/global/definitions.h>
#include <bitset>

namespace wis
{
	class VKDevice;

	template<>
	class Internal<VKDevice>
	{
	public:
		vk::Device GetDevice()const noexcept
		{
			return device.get();
		}
		wis::shared_handle<vk::Device> GetDeviceHandle()const noexcept
		{
			return device;
		}
	protected:
		wis::shared_handle<vk::Device> device;
	};

	using VKDeviceView = wis::shared_handle<vk::Device>;


	class VKDevice : public QueryInternal<VKDevice>
	{
		static inline constexpr const auto max_count = 4;
		static inline constexpr const auto max_ext_count = 16;
		struct QueueInfo
		{
			uint32_t index;
			uint32_t count;
		};
		struct QueueFormat
		{
			uint16_t queue_flags = 0;
			uint8_t count = 0;
			uint8_t family_index = 0;
			uint8_t last = 0;
		public:
			uint8_t GetNextInLine()noexcept
			{
				return std::exchange(last, (last + 1) % count);
			}
			bool Empty()const noexcept
			{
				return !count;
			}
		};
		enum class QueueTypes : uint8_t
		{
			graphics,
			compute,
			copy,
			video_decode
		};
		struct QueueResidency
		{
			static constexpr size_t QueueIndex(QueueOptions::Type type)
			{
				switch (type)
				{
				case wis::QueueOptions::Type::compute:
					return +QueueTypes::compute;
				case wis::QueueOptions::Type::copy:
					return +QueueTypes::copy;
				case wis::QueueOptions::Type::video_decode:
					return +QueueTypes::video_decode;
				}
				return 0;
			}
			static constexpr size_t QueueFlag(QueueTypes type)
			{
				using enum vk::QueueFlagBits;
				switch (type)
				{
				case wis::VKDevice::QueueTypes::copy:
					return +eTransfer;
				case wis::VKDevice::QueueTypes::compute:
					return +eCompute;
				case wis::VKDevice::QueueTypes::graphics:
					return +eGraphics;
				case wis::VKDevice::QueueTypes::video_decode:
					return +eVideoDecodeKHR;
				default:
					return 0;
				}
			}
		public:
			QueueFormat* GetOfType(QueueOptions::Type type)
			{
				auto idx = QueueIndex(type);
				auto* q = &available_queues[idx];

				if (!q->count)
				{
					idx = FindResembling(QueueTypes(idx));
					if (idx == -1)return nullptr;
					q = &available_queues[idx];
				}
				return q;
			}
			int32_t FindResembling(QueueTypes type)
			{
				for (size_t i = 0; i < max_count; i++)
				{
					auto& r = available_queues[i];
					if (r.queue_flags & QueueFlag(type))
						return i;
				}
				return -1;
			}
		public:
			std::array<QueueFormat, max_count> available_queues{};
		};


	public:
		VKDevice() = default;
		explicit VKDevice(VKAdapterView adapter)
		{
			Initialize(adapter);
		}
	public:
		operator VKDeviceView()const noexcept
		{
			return GetDeviceHandle();
		}
		bool Initialize(VKAdapterView adapter)
		{
			GetQueueFamilies(adapter);
			std::array<vk::DeviceQueueCreateInfo, max_count> queue_infos{};
			size_t queue_count = 0;

			constexpr static float queue_priority = 1.0f;
			for (size_t queue_info_size = 0; queue_info_size < max_count; queue_info_size++)
			{
				auto& q_info = queue_infos[queue_info_size];
				auto q = queues.available_queues[queue_info_size];
				if (!q.count)continue;

				q_info.queueFamilyIndex = q.family_index;
				q_info.queueCount = 1; //hard wired for now
				q_info.pQueuePriorities = &queue_priority;
				queue_count++;
			}

			auto [exts, e_cnt] = RequestExtensions(adapter);

			void* device_create_info_next = nullptr;
			auto add_extension = [&](auto& extension)
			{
				extension.pNext = device_create_info_next;
				device_create_info_next = &extension;
			};

			auto physical_device_features = adapter.getFeatures();
			vk::PhysicalDeviceFeatures2 device_features;
			{
				device_features.features.robustBufferAccess = physical_device_features.robustBufferAccess;
				device_features.features.fullDrawIndexUint32 = physical_device_features.fullDrawIndexUint32;
				device_features.features.imageCubeArray = physical_device_features.imageCubeArray;
				device_features.features.independentBlend = physical_device_features.independentBlend;
				device_features.features.geometryShader = physical_device_features.geometryShader;
				device_features.features.tessellationShader = physical_device_features.tessellationShader;
				device_features.features.sampleRateShading = physical_device_features.sampleRateShading;
				device_features.features.dualSrcBlend = physical_device_features.dualSrcBlend;
				device_features.features.logicOp = physical_device_features.logicOp;
				device_features.features.multiDrawIndirect = physical_device_features.multiDrawIndirect;
				device_features.features.drawIndirectFirstInstance = physical_device_features.drawIndirectFirstInstance;
				device_features.features.depthClamp = physical_device_features.depthClamp;
				device_features.features.depthBiasClamp = physical_device_features.depthBiasClamp;
				device_features.features.fillModeNonSolid = physical_device_features.fillModeNonSolid;
				device_features.features.depthBounds = physical_device_features.depthBounds;
				device_features.features.wideLines = physical_device_features.wideLines;
				device_features.features.largePoints = physical_device_features.largePoints;
				device_features.features.alphaToOne = physical_device_features.alphaToOne;
				device_features.features.multiViewport = physical_device_features.multiViewport;
				device_features.features.samplerAnisotropy = physical_device_features.samplerAnisotropy;
				device_features.features.textureCompressionETC2 = physical_device_features.textureCompressionETC2;
				device_features.features.textureCompressionASTC_LDR = physical_device_features.textureCompressionASTC_LDR;
				device_features.features.textureCompressionBC = physical_device_features.textureCompressionBC;
				device_features.features.occlusionQueryPrecise = physical_device_features.occlusionQueryPrecise;
				device_features.features.pipelineStatisticsQuery = physical_device_features.pipelineStatisticsQuery;
				device_features.features.vertexPipelineStoresAndAtomics = physical_device_features.vertexPipelineStoresAndAtomics;
				device_features.features.fragmentStoresAndAtomics = physical_device_features.fragmentStoresAndAtomics;
				device_features.features.shaderTessellationAndGeometryPointSize = physical_device_features.shaderTessellationAndGeometryPointSize;
				device_features.features.shaderImageGatherExtended = physical_device_features.shaderImageGatherExtended;
				device_features.features.shaderStorageImageExtendedFormats = physical_device_features.shaderStorageImageExtendedFormats;
				device_features.features.shaderStorageImageMultisample = physical_device_features.shaderStorageImageMultisample;
				device_features.features.shaderStorageImageReadWithoutFormat = physical_device_features.shaderStorageImageReadWithoutFormat;
				device_features.features.shaderStorageImageWriteWithoutFormat = physical_device_features.shaderStorageImageWriteWithoutFormat;
				device_features.features.shaderUniformBufferArrayDynamicIndexing = physical_device_features.shaderUniformBufferArrayDynamicIndexing;
				device_features.features.shaderSampledImageArrayDynamicIndexing = physical_device_features.shaderSampledImageArrayDynamicIndexing;
				device_features.features.shaderStorageBufferArrayDynamicIndexing = physical_device_features.shaderStorageBufferArrayDynamicIndexing;
				device_features.features.shaderStorageImageArrayDynamicIndexing = physical_device_features.shaderStorageImageArrayDynamicIndexing;
				device_features.features.shaderClipDistance = physical_device_features.shaderClipDistance;
				device_features.features.shaderCullDistance = physical_device_features.shaderCullDistance;
				device_features.features.shaderFloat64 = physical_device_features.shaderFloat64;
				device_features.features.shaderInt64 = physical_device_features.shaderInt64;
				device_features.features.shaderInt16 = physical_device_features.shaderInt16;
				device_features.features.shaderResourceResidency = physical_device_features.shaderResourceResidency;
				device_features.features.shaderResourceMinLod = physical_device_features.shaderResourceMinLod;
				device_features.features.sparseBinding = physical_device_features.sparseBinding;
				device_features.features.sparseResidencyBuffer = physical_device_features.sparseResidencyBuffer;
				device_features.features.sparseResidencyImage2D = physical_device_features.sparseResidencyImage2D;
				device_features.features.sparseResidencyImage3D = physical_device_features.sparseResidencyImage3D;
				device_features.features.sparseResidency2Samples = physical_device_features.sparseResidency2Samples;
				device_features.features.sparseResidency4Samples = physical_device_features.sparseResidency4Samples;
				device_features.features.sparseResidency8Samples = physical_device_features.sparseResidency8Samples;
				device_features.features.sparseResidency16Samples = physical_device_features.sparseResidency16Samples;
				device_features.features.sparseResidencyAliased = physical_device_features.sparseResidencyAliased;
				device_features.features.variableMultisampleRate = physical_device_features.variableMultisampleRate;
				device_features.features.inheritedQueries = physical_device_features.inheritedQueries;
			}
			add_extension(device_features);

			vk::PhysicalDeviceSynchronization2Features sync2;
			sync2.synchronization2 = true;
			add_extension(sync2);

			vk::PhysicalDeviceVulkan12Features device_vulkan12_features;
			device_vulkan12_features.drawIndirectCount = draw_indirect_supported;
			device_vulkan12_features.bufferDeviceAddress = true;
			device_vulkan12_features.timelineSemaphore = true;
			device_vulkan12_features.runtimeDescriptorArray = true;
			device_vulkan12_features.descriptorBindingVariableDescriptorCount = true;
			add_extension(device_vulkan12_features);

			vk::PhysicalDeviceFragmentShadingRateFeaturesKHR fragment_shading_rate_features;
			fragment_shading_rate_features.attachmentFragmentShadingRate = vrs_supported;
			add_extension(fragment_shading_rate_features);

			vk::PhysicalDeviceRayTracingPipelineFeaturesKHR raytracing_pipeline_feature;
			raytracing_pipeline_feature.rayTracingPipeline = ray_tracing_supported;
			add_extension(raytracing_pipeline_feature);

			vk::PhysicalDeviceAccelerationStructureFeaturesKHR acceleration_structure_feature;
			acceleration_structure_feature.accelerationStructure = ray_tracing_supported;
			add_extension(acceleration_structure_feature);

			vk::PhysicalDeviceRayQueryFeaturesKHR rayquery_pipeline_feature;
			rayquery_pipeline_feature.rayQuery = ray_query_supported;
			raytracing_pipeline_feature.rayTraversalPrimitiveCulling = ray_query_supported;
			add_extension(rayquery_pipeline_feature);

			vk::DeviceCreateInfo desc{
				{}, uint32_t(queue_count), queue_infos.data(), 0, nullptr, e_cnt, exts.data(), nullptr, device_create_info_next
			};

			device = wis::shared_handle<vk::Device>{ adapter.createDevice(desc) };
			return device;
		}
	public:
		[[nodiscard]]
		VKCommandQueue CreateCommandQueue(QueueOptions options = QueueOptions{})
		{
			auto* queue = queues.GetOfType(options.type);
			if (!queue)return{};

			vk::DeviceQueueInfo2 info{
				{},
				queue->family_index,
				queue->GetNextInLine()
			};
			return VKCommandQueue{ device->getQueue2(info) };
		}

		[[nodiscard]]
		VKFence CreateFence()const
		{
			vk::SemaphoreTypeCreateInfo timeline_desc
			{
				vk::SemaphoreType::eTimeline,
					0
			};
			vk::SemaphoreCreateInfo desc
			{
				{}, & timeline_desc
			};
			return VKFence{ wis::shared_handle<vk::Semaphore>{device->createSemaphore(desc), device} };
		}

	private:
		void GetQueueFamilies(VKAdapterView adapter)noexcept
		{
			using namespace river::flags;
			auto family_props = adapter.getQueueFamilyProperties();
			wis::lib_info(std::format("The system supports {} queue families", family_props.size()));

			for (uint8_t i = 0; i < family_props.size(); i++)
			{
				using enum vk::QueueFlagBits;
				auto& family = family_props[i];
				if ((family.queueFlags & eGraphics) == eGraphics && queues.available_queues[+QueueTypes::graphics].Empty())
				{
					queues.available_queues[+QueueTypes::graphics] = {
						.queue_flags = uint16_t(uint32_t(family.queueFlags)),
						.count = uint8_t(family.queueCount),
						.family_index = i,
					};
					continue;
				}
				if ((family.queueFlags & eCompute) == eCompute && queues.available_queues[+QueueTypes::compute].Empty())
				{
					queues.available_queues[+QueueTypes::compute] = {
						.queue_flags = uint16_t(uint32_t(family.queueFlags)),
						.count = uint8_t(family.queueCount),
						.family_index = i,
					};
					continue;
				}
				if ((family.queueFlags & eVideoDecodeKHR) == eVideoDecodeKHR && queues.available_queues[+QueueTypes::video_decode].Empty())
				{
					queues.available_queues[+QueueTypes::video_decode] = {
						.queue_flags = uint16_t(uint32_t(family.queueFlags)),
						.count = uint8_t(family.queueCount),
						.family_index = i,
					};
					continue;
				}
				if ((family.queueFlags & eTransfer) == eTransfer && queues.available_queues[+QueueTypes::copy].Empty())
				{
					queues.available_queues[+QueueTypes::copy] = {
						.queue_flags = uint16_t(uint32_t(family.queueFlags)),
						.count = uint8_t(family.queueCount),
						.family_index = i,
					};
					continue;
				}
			}
		}

		[[nodiscard]]
		std::pair<std::array<const char*, max_ext_count>, uint32_t> RequestExtensions(VKAdapterView adapter)noexcept
		{
			constexpr static std::array req_extension{
				VK_KHR_SWAPCHAIN_EXTENSION_NAME,
					VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
					VK_KHR_RAY_QUERY_EXTENSION_NAME,
					VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
					VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
					VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME,
					VK_KHR_MAINTENANCE3_EXTENSION_NAME,
					VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
					VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME,
					VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME,
					VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME,
					VK_KHR_MAINTENANCE1_EXTENSION_NAME,
					VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME,
					VK_EXT_MEMORY_BUDGET_EXTENSION_NAME,
					VK_NV_MESH_SHADER_EXTENSION_NAME,
					VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME,
			};


			auto extensions = adapter.enumerateDeviceExtensionProperties();
			std::unordered_set<std::string_view, wis::string_hash> ext_set;
			ext_set.reserve(extensions.size());

			for (const auto& e : extensions)
				ext_set.emplace(e.extensionName.data());

			std::array<const char*, max_ext_count> avail_exts{};
			uint32_t size = 0;

			for (auto* i : req_extension)
			{
				if (!ext_set.contains(i))continue;
				avail_exts[size++] = i;

				if (i == VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME)
					vrs_supported = true;
				else if (i == VK_NV_MESH_SHADER_EXTENSION_NAME)
					mesh_shader_supported = true;
				else if (i == VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME)
					ray_tracing_supported = true;
				else if (i == VK_KHR_RAY_QUERY_EXTENSION_NAME)
					ray_query_supported = true;
				else if (i == VK_KHR_DRAW_INDIRECT_COUNT_EXTENSION_NAME)
					draw_indirect_supported = true;
			}

			if constexpr (wis::debug_mode)
			{
				wis::lib_info("Active Device Extensions:");
				std::ranges::for_each_n(avail_exts.begin(), size, [](const char* s) {
					wis::lib_info(std::format("\t{}", s));
					});
			}

			return { avail_exts, size };
		}
	private:
		QueueResidency queues{};
		bool vrs_supported : 1 = false;
		bool mesh_shader_supported : 1 = false;
		bool ray_tracing_supported : 1 = false;
		bool ray_query_supported : 1 = false;
		bool draw_indirect_supported : 1 = false;
	};
}