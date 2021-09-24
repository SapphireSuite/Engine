// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_PIPELINE_GUARD
#define SAPPHIRE_RENDER_VK_PIPELINE_GUARD

#include <SA/Render/Base/Pipeline/APipeline.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;
	class SpecConstantData;

	class Pipeline : public APipeline
	{
		VkPipeline mHandle = VK_NULL_HANDLE;
		VkPipelineLayout mPipelineLayout = VK_NULL_HANDLE;

		std::vector<VkDescriptorSetLayout> mDescriptorSetLayouts;

		void CreateDescriptorSetLayouts(const Device& _device, const PipelineCreateInfos& _infos);
		void DestroyDescriptorSetLayouts(const Device& _device);

		void CreatePipelineLayout(const Device& _device);
		void DestroyPipelineLayout(const Device& _device);

		void CreatePipelineHandle(const Device& _device, const PipelineCreateInfos& _infos);
		void DestroyPipelineHandle(const Device& _device);


		static void FillShaderSpecConstants(std::vector<SpecConstantData>& _specConstDatas,
			const std::vector<PipelineShaderInfos>& _shaders);

		static void FillShaderStages(std::vector<VkPipelineShaderStageCreateInfo>& _stages,
			const std::vector<SpecConstantData>& _specConstDatas,
			const std::vector<PipelineShaderInfos>& _shaders);

		static void FillVertexBindings(VkPipelineVertexInputStateCreateInfo& _vertexInputInfo,
			std::unique_ptr<VkVertexInputBindingDescription>& _bindingDesc,
			std::unique_ptr<VkVertexInputAttributeDescription[]>& _attribDescs,
			const VertexBindingLayout& _vertexBindingLayout) noexcept;

		static void FillRasterization(VkPipelineRasterizationStateCreateInfo& _rasterizerInfo, const PipelineRenderModes& _modes) noexcept;

		static void FillRenderPassAttachments(struct RenderPassAttachmentInfos& _renderPassAttInfos, const PipelineCreateInfos& _infos) noexcept;

	public:
		VkPipelineLayout GetLayout() const noexcept;
		const std::vector<VkDescriptorSetLayout>& GetDescriptorSetLayouts() const noexcept;

		void Create(const ARenderDevice* _device, const PipelineCreateInfos& _infos) override final;
		void Destroy(const ARenderDevice* _device) override final;

		void Bind(const ARenderFrame& _frame) const override final;
	};
}

#endif

#endif // GUARD
