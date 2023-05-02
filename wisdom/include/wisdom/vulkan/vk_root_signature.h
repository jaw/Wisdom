#pragma once
#include <wisdom/api/api_internal.h>
#include <wisdom/vulkan/vk_shared_handle.h>

namespace wis
{
	class VKRootSignature;

	template<>
	class Internal<VKRootSignature>
	{
	public:
		Internal() = default;
		Internal(wis::shared_handle<vk::PipelineLayout> root) :root(std::move(root)) {}
	public:
		auto GetRootSignature()const noexcept
		{
			return root.get();
		}
	protected:
		wis::shared_handle<vk::PipelineLayout> root;
	};

	using VKRootSignatureView = vk::PipelineLayout;

	class VKRootSignature : public QueryInternal<VKRootSignature>
	{
	public:
		VKRootSignature() = default;
		explicit VKRootSignature(wis::shared_handle<vk::PipelineLayout> root)
			:QueryInternal(std::move(root))
		{}
	public:
		operator VKRootSignatureView()const noexcept
		{
			return GetRootSignature();
		}
	};
}