#ifndef VK_ROOT_SIGNATURE_H
#define VK_ROOT_SIGNATURE_H
#include <wisdom/global/internal.h>
#include <wisdom/vulkan/vk_views.h>
#include <wisdom/vulkan/vk_handles.h>

namespace wis {
class VKRootSignature;

template<>
struct Internal<VKRootSignature> {
    wis::managed_handle_ex<VkPipelineLayout> root;
    std::unique_ptr<VkDescriptorSetLayout[]> vk_dsls;
    uint32_t dsl_count = 0;

    Internal() noexcept = default;
    Internal(wis::managed_handle_ex<VkPipelineLayout> root, std::unique_ptr<VkDescriptorSetLayout[]> vk_dsls, uint32_t dsl_count) noexcept
        : root(std::move(root)), vk_dsls(std::move(vk_dsls)), dsl_count(dsl_count)
    {
    }

    Internal(Internal&&) noexcept = default;
    Internal& operator=(Internal&& o) noexcept
    {
        if (this == &o) {
            return *this;
        }
        Destroy();
        root = std::move(o.root);
        vk_dsls = std::move(o.vk_dsls);
        dsl_count = o.dsl_count;
        return *this;
    }

    ~Internal()
    {
        Destroy();
    }

    void Destroy() noexcept
    {
        if (root) {
            auto& device = root.header().parent;
            for (uint32_t i = 0; i < dsl_count; ++i) {
                device.table().vkDestroyDescriptorSetLayout(device.get(), vk_dsls[i], nullptr);
            }
        }
    }
};

/// @brief Root signature
class VKRootSignature : public QueryInternal<VKRootSignature>
{
public:
    VKRootSignature() = default;
    explicit VKRootSignature(wis::managed_handle_ex<VkPipelineLayout> root, std::unique_ptr<VkDescriptorSetLayout[]> vk_dsls, uint32_t dsl_count) noexcept
        : QueryInternal(std::move(root), std::move(vk_dsls), dsl_count)
    {
    }
    operator VKRootSignatureView() const noexcept
    {
        return root.get();
    }
    operator VKRootSignatureView2() const noexcept
    {
        return vk_dsls.get();
    }
    operator bool() const noexcept
    {
        return bool(root);
    }
};
} // namespace wis

#endif // VK_ROOT_SIGNATURE_H
