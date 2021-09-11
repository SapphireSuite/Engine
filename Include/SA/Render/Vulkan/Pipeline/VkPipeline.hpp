// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_PIPELINE_GUARD
#define SAPPHIRE_RENDER_VK_PIPELINE_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Render/Base/Pipeline/PipelineCreateInfos.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class Pipeline
	{
		VkPipeline mHandle = VK_NULL_HANDLE;
		VkPipelineLayout mPipelineLayout = VK_NULL_HANDLE;

		VkDescriptorSetLayout mDescriptorSetLayout = VK_NULL_HANDLE;

		void CreateDescriptorSetLayout(const Device& _device, const PipelineCreateInfos& _infos);
		void DestroyDescriptorSetLayout(const Device& _device);

		void CreatePipelineLayout(const Device& _device);
		void DestroyPipelineLayout(const Device& _device);

		void CreatePipelineHandle(const Device& _device, const PipelineCreateInfos& _infos);
		void DestroyPipelineHandle(const Device& _device);


		static void FillShaderStages(std::vector<VkPipelineShaderStageCreateInfo>& _stages, const std::vector<PipelineShaderInfos>& _shaders);

		static void FillVertexBindings(VkPipelineVertexInputStateCreateInfo& _vertexInputInfo, std::unique_ptr<VkVertexInputBindingDescription>& _bindingDesc,
			std::unique_ptr<VkVertexInputAttributeDescription[]>& _attribDescs, const VertexBindingLayout& _vertexBindingLayout) noexcept;

		static void FillRasterization(VkPipelineRasterizationStateCreateInfo& _rasterizerInfo, const PipelineRenderModes& _modes) noexcept;

		static void FillRenderPassAttachments(struct RenderPassAttachmentInfos& _renderPassAttInfos, const PipelineCreateInfos& _infos) noexcept;

	public:
		void Create(const Device& _device, const PipelineCreateInfos& _infos);
		void Destroy(const Device& _device);
	};
}

#endif

#endif // GUARD
