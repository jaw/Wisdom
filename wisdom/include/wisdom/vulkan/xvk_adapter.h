#pragma once
#include <wisdom/api/consts.h>
#include <wisdom/api/internal.h>
#include <wisdom/vulkan/xvk_checks.h>
#include <wisdom/vulkan/xvk_views.h>
#include <wisvk/vk_loader.hpp>
#include <span>

namespace wis {
class VKAdapter;

template<>
struct Internal<VKAdapter> {
    VkPhysicalDevice adapter{};
    VkInstanceTable* instance_table{};
};

class VKAdapter : public QueryInternal<VKAdapter>
{
public:
    VKAdapter() noexcept = default;
    explicit VKAdapter(VkPhysicalDevice adapter, VkInstanceTable* instance_table) noexcept
        : QueryInternal(adapter, instance_table)
    {
    }
    operator bool() const noexcept { return adapter != nullptr; }
    operator VKAdapterHandle() const noexcept { return { adapter, instance_table }; }

public:
    wis::Result GetDesc(AdapterDesc* pout_desc) const noexcept
    {
        if (!pout_desc)
            return wis::make_result<FUNC, "AdapterDesc was nullptr">(VK_ERROR_UNKNOWN);

        auto& out_desc = *pout_desc;
        VkPhysicalDeviceIDProperties id_props{
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
            .pNext = nullptr,
            .deviceUUID = {},
            .dwisUUID = {},
            .deviceLUID = {},
            .deviceNodeMask = 0,
            .deviceLUIDValid = false,
        };
        VkPhysicalDeviceProperties2 properties{
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &id_props,
            .properties = {},
        };
        instance_table->vkGetPhysicalDeviceProperties2(adapter, &properties);

        auto& desc = properties.properties;

        VkPhysicalDeviceMemoryProperties memory_props{};
        instance_table->vkGetPhysicalDeviceMemoryProperties(adapter, &memory_props);

        uint64_t local_mem = 0;
        uint64_t system_mem = 0;
        std::span types{ memory_props.memoryTypes };

        for (auto& i : types) {
            if (i.propertyFlags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT &&
                memory_props.memoryHeaps[i.heapIndex].flags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) {
                local_mem = memory_props.memoryHeaps[i.heapIndex].size;
            }

            if (i.propertyFlags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                system_mem = memory_props.memoryHeaps[i.heapIndex].size;
            }
            if ((system_mem != 0u) && (local_mem != 0u))
                break;
        }

        AdapterFlags flag{
            (desc.deviceType & VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU > 0u) *
                    uint32_t(AdapterFlags::Remote) |
            (desc.deviceType & VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU > 0u) *
                    uint32_t(AdapterFlags::Software)
        };

        std::strncpy(const_cast<char*>(out_desc.description.data()), desc.deviceName, sizeof(out_desc.description) - 1);
        out_desc.vendor_id = desc.vendorID;

        out_desc.device_id = desc.deviceID;
        out_desc.subsys_id = desc.apiVersion;
        out_desc.revision = desc.dwisVersion;

        out_desc.dedicated_video_memory = local_mem;
        out_desc.dedicated_system_memory = 0;
        out_desc.shared_system_memory = system_mem;
        out_desc.adapter_id = reinterpret_cast<uint64_t&>(id_props.deviceLUID);
        out_desc.flags = wis::AdapterFlags(flag);
        return wis::success;
    }
};
} // namespace wis