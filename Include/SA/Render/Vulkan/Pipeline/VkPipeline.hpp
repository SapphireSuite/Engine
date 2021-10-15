// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_PIPELINE_GUARD
#define SAPPHIRE_RENDER_VK_PIPELINE_GUARD

#include <SA/Render/Base/Pipeline/ARenderPipeline.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;
	class SpecConstantData;
	class EngineDescriptorSetLayouts;

	class Pipeline : public ARenderPipeline
	{
		VkPipeline mHandle = VK_NULL_HANDLE;
		VkPipelineLayout mPipelineLayout = VK_NULL_HANDLE;

		VkDescriptorSetLayout mMainDescriptorSetLayout = VK_NULL_HANDLE;

		void CreateMainDescriptorSetLayout(const Device& _device, const RenderPipelineDescriptor& _desc);
		void DestroyMainDescriptorSetLayout(const Device& _device);

		void CreatePipelineLayout(const Device& _device, const RenderPipelineDescriptor& _desc, const EngineDescriptorSetLayouts& _enDescSetLayouts);
		void DestroyPipelineLayout(const Device& _device);

		void CreatePipelineHandle(const Device& _device, const RenderPipelineDescriptor& _desc);
		void DestroyPipelineHandle(const Device& _device);


		static void FillShaderSpecConstants(SpecConstantData& _specConstData,
			const PipelineShaderInfos& _shaderInfos);

		static void FillShaderStages(std::vector<VkPipelineShaderStageCreateInfo>& _stages,
			const SpecConstantData& _specConstData,
			const std::vector<PipelineShaderStage>& _shaders);

		static void FillVertexBindings(VkPipelineVertexInputStateCreateInfo& _vertexInputInfo,
			std::unique_ptr<VkVertexInputBindingDescription>& _bindingDesc,
			std::unique_ptr<VkVertexInputAttributeDescription[]>& _attribDescs,
			const VertexBindingLayout& _vertexBindingLayout) noexcept;

		static void FillRasterization(VkPipelineRasterizationStateCreateInfo& _rasterizerInfo, const PipelineRenderModes& _modes) noexcept;

		static void FillRenderPassAttachments(struct RenderPassAttachmentInfos& _renderPassAttInfos, const RenderPipelineDescriptor& _desc) noexcept;

	public:
		VkPipelineLayout GetLayout() const noexcept;
		VkDescriptorSetLayout GetMainDescriptorSetLayout() const noexcept;

		void Create(const Device& _device, const RenderPipelineDescriptor& _desc, const EngineDescriptorSetLayouts& _enDescSetLayouts);
		void Destroy(const Device& _device);

		void Bind(const ARenderFrame& _frame) const override final;
	};
}

#endif

#endif // GUARD
