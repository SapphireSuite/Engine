// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/VkPipeline.hpp>

#include <HI/Cast.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pipeline/VkPipelineLayout.hpp>

namespace SA::VK
{
	namespace Intl
	{
		struct RenderPassAttachmentInfos
		{
			VkPipelineMultisampleStateCreateInfo multisamplingInfos{};
			VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};

			std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
			VkPipelineColorBlendStateCreateInfo colorBlendingInfo{};
		};

		void FillShaderStages(std::vector<VkPipelineShaderStageCreateInfo>& _stages,
			const std::vector<PipelineShaderStage>& _shaders)
		{
			_stages.reserve(_shaders.size());

			for(auto& stage : _shaders)
			{
				VkPipelineShaderStageCreateInfo& vkStage = _stages.emplace_back();
				vkStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				vkStage.pNext = nullptr;
				vkStage.flags = 0u;
				vkStage.stage = API_GetShaderStage(stage.stage);
				vkStage.module = CastRef<Shader>(stage.shader);
				vkStage.pName = "main";
				vkStage.pSpecializationInfo = nullptr;
			}
		}

		//TODO: Implement.
		// void FillVertexBindings(VkPipelineVertexInputStateCreateInfo& _vertexInputInfo,
		// 	std::unique_ptr<VkVertexInputBindingDescription>& _bindingDesc,
		// 	std::unique_ptr<VkVertexInputAttributeDescription[]>& _attribDescs,
		// 	const VertexBindingLayout& _vertexBindingLayout) noexcept
		// {
		// 	_bindingDesc = _vertexBindingLayout.GetBindingDescription();
		// 	_attribDescs = _vertexBindingLayout.GetAttributeDescriptions();

		// 	_vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		// 	_vertexInputInfo.pNext = nullptr;
		// 	_vertexInputInfo.flags = 0u;
		// 	_vertexInputInfo.vertexBindingDescriptionCount = _vertexBindingLayout.GetBindingDescriptionNum();
		// 	_vertexInputInfo.pVertexBindingDescriptions = _bindingDesc.get();
		// 	_vertexInputInfo.vertexAttributeDescriptionCount = _vertexBindingLayout.GetAttributeDescriptionNum();
		// 	_vertexInputInfo.pVertexAttributeDescriptions = _attribDescs.get();
		// }

		void FillRasterization(VkPipelineRasterizationStateCreateInfo& _rasterizerInfo, const PipelineRenderModes& _modes) noexcept
		{
			_rasterizerInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			_rasterizerInfo.pNext = nullptr;
			_rasterizerInfo.flags = 0u;
			_rasterizerInfo.depthClampEnable = VK_FALSE;
			_rasterizerInfo.rasterizerDiscardEnable = VK_FALSE;
			_rasterizerInfo.polygonMode = API_GetPolygonMode(_modes.polygon);
			_rasterizerInfo.cullMode = API_GetCullingMode(_modes.culling);
			_rasterizerInfo.frontFace = API_GetFrontFaceMode(_modes.frontFace);
			_rasterizerInfo.depthBiasEnable = VK_FALSE;
			_rasterizerInfo.depthBiasConstantFactor = 0.0f;
			_rasterizerInfo.depthBiasClamp = 0.0f;
			_rasterizerInfo.depthBiasSlopeFactor = 0.0f;
			_rasterizerInfo.lineWidth = 1.0f;
		}

		void FillRenderPassAttachments(struct RenderPassAttachmentInfos& _renderPassAttInfos, const PipelineRenderPassInfos& _passInfos) noexcept
		{
			const VkSampleCountFlagBits sampleCount = API_GetSampleCount(_passInfos.subPassDesc.sampling);

			// MultiSampling.
			_renderPassAttInfos.multisamplingInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			_renderPassAttInfos.multisamplingInfos.pNext = nullptr;
			_renderPassAttInfos.multisamplingInfos.flags = 0u;
			_renderPassAttInfos.multisamplingInfos.rasterizationSamples = sampleCount;
			_renderPassAttInfos.multisamplingInfos.sampleShadingEnable = sampleCount != VK_SAMPLE_COUNT_1_BIT;
			_renderPassAttInfos.multisamplingInfos.minSampleShading = 0.2f;
			_renderPassAttInfos.multisamplingInfos.pSampleMask = nullptr;
			_renderPassAttInfos.multisamplingInfos.alphaToCoverageEnable = VK_FALSE;
			_renderPassAttInfos.multisamplingInfos.alphaToOneEnable = VK_FALSE;

			// Depth stencil.
			_renderPassAttInfos.depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			_renderPassAttInfos.depthStencilInfo.pNext = nullptr;
			_renderPassAttInfos.depthStencilInfo.flags = 0u;
			_renderPassAttInfos.depthStencilInfo.depthTestEnable = VK_TRUE;
			_renderPassAttInfos.depthStencilInfo.depthWriteEnable = VK_TRUE;
			_renderPassAttInfos.depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
			_renderPassAttInfos.depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
			_renderPassAttInfos.depthStencilInfo.stencilTestEnable = VK_FALSE;
			_renderPassAttInfos.depthStencilInfo.front = {};
			_renderPassAttInfos.depthStencilInfo.back = {};
			_renderPassAttInfos.depthStencilInfo.minDepthBounds = 0.0f;
			_renderPassAttInfos.depthStencilInfo.maxDepthBounds = 1.0f;


			// Color attachments.
			VkPipelineColorBlendAttachmentState colorBlendAttachment{};
			colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

			// Query color attachments only.
			uint32_t colorAttachmentNum = 0u;

			for (auto it = _passInfos.subPassDesc.attachmentDescs.begin(); it != _passInfos.subPassDesc.attachmentDescs.end(); ++it)
			{
				if (!IsDepthFormat(it->format))
					++colorAttachmentNum;
			}

			_renderPassAttInfos.colorBlendAttachments.resize(colorAttachmentNum, colorBlendAttachment);


			// Color blending.
			_renderPassAttInfos.colorBlendingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			_renderPassAttInfos.colorBlendingInfo.pNext = nullptr;
			_renderPassAttInfos.colorBlendingInfo.flags = 0u;
			_renderPassAttInfos.colorBlendingInfo.logicOpEnable = VK_FALSE;
			_renderPassAttInfos.colorBlendingInfo.logicOp = VK_LOGIC_OP_COPY;
			_renderPassAttInfos.colorBlendingInfo.attachmentCount = static_cast<uint32_t>(_renderPassAttInfos.colorBlendAttachments.size());
			_renderPassAttInfos.colorBlendingInfo.pAttachments = _renderPassAttInfos.colorBlendAttachments.data();
			_renderPassAttInfos.colorBlendingInfo.blendConstants[0] = 0.0f;
			_renderPassAttInfos.colorBlendingInfo.blendConstants[1] = 0.0f;
			_renderPassAttInfos.colorBlendingInfo.blendConstants[2] = 0.0f;
			_renderPassAttInfos.colorBlendingInfo.blendConstants[3] = 0.0f;
		}
	}


	void Pipeline::Create(const Device& _device, const RenderPipelineDescriptor& _desc, const PipelineLayout& _layout)
	{
		ARenderPipeline::Create();

		// Shaders
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
		Intl::FillShaderStages(shaderStages, _desc.shaderInfos.stages);


		//TODO: Implement.
		// Vertex input infos.
		// std::unique_ptr<VkVertexInputBindingDescription> bindingDesc;
		// std::unique_ptr<VkVertexInputAttributeDescription[]> attribDescs;
		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		// Intl::FillVertexBindings(vertexInputInfo, bindingDesc, attribDescs, _desc.shaderInfos.vertexBindingLayout);


		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
		inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssemblyInfo.pNext = nullptr;
		inputAssemblyInfo.flags = 0;
		inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;


		// Viewport & Scissor.
		// TODO: CLEAN.
		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = 1200.0f;
		viewport.height = 800.0f;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{};
		scissor.offset = VkOffset2D{ 0, 0 };
		scissor.extent = VkExtent2D{ 1200, 800 };

		VkPipelineViewportStateCreateInfo viewportStateInfo{};
		viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportStateInfo.pNext = nullptr;
		viewportStateInfo.flags = 0u;
		viewportStateInfo.viewportCount = 1u;
		viewportStateInfo.pViewports = &viewport;
		viewportStateInfo.scissorCount = 1u;
		viewportStateInfo.pScissors = &scissor;


		// Rasterization
		VkPipelineRasterizationStateCreateInfo rasterizerInfo{};
		Intl::FillRasterization(rasterizerInfo, _desc.modes);


		// Multisampling.
		Intl::RenderPassAttachmentInfos renderPassAttInfos{};
		Intl::FillRenderPassAttachments(renderPassAttInfos, _desc.passInfos);


		// Create handle.
		VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
		pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineCreateInfo.pNext = nullptr;
		pipelineCreateInfo.flags = 0u;
		pipelineCreateInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
		pipelineCreateInfo.pStages = shaderStages.data();
		pipelineCreateInfo.pVertexInputState = &vertexInputInfo;
		pipelineCreateInfo.pInputAssemblyState = &inputAssemblyInfo;
		pipelineCreateInfo.pTessellationState = nullptr;
		pipelineCreateInfo.pViewportState = &viewportStateInfo;
		pipelineCreateInfo.pRasterizationState = &rasterizerInfo;
		pipelineCreateInfo.pMultisampleState = &renderPassAttInfos.multisamplingInfos;
		pipelineCreateInfo.pDepthStencilState = &renderPassAttInfos.depthStencilInfo;
		pipelineCreateInfo.pColorBlendState = &renderPassAttInfos.colorBlendingInfo;
		pipelineCreateInfo.pDynamicState = nullptr;
		pipelineCreateInfo.layout = _layout;
		pipelineCreateInfo.renderPass = CastRef<RenderPass>(_desc.passInfos.renderPass);
		pipelineCreateInfo.subpass = _desc.passInfos.subPassIndex;
		pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineCreateInfo.basePipelineIndex = -1;

		SA_VK_ASSERT(vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &mHandle),
			L"Failed to create graphics pipeline!");


		SA_LOG(L"Pipeline [" << mHandle << L"] created.", Infos, SA/Engine/Render/Vulkan);
	}
	
	void Pipeline::Destroy(const Device& _device)
	{
		ARenderPipeline::Destroy();

		vkDestroyPipeline(_device, mHandle, nullptr);

		SA_LOG(L"Pipeline [" << mHandle << L"] destroyed.", Infos, SA/Engine/Render/Vulkan);
		mHandle = VK_NULL_HANDLE;
	}
}
