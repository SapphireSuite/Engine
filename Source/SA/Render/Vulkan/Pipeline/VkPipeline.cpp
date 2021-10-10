// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/VkPipeline.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Shader/VkShader.hpp>
#include <Render/Vulkan/Pass/VkRenderPass.hpp>
#include <Render/Vulkan/VkFrame.hpp>
#include <Render/Vulkan/Pipeline/VkSpecConstantData.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	struct RenderPassAttachmentInfos
	{
		VkPipelineMultisampleStateCreateInfo multisamplingInfos{};
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};

		std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
		VkPipelineColorBlendStateCreateInfo colorBlendingInfo{};
	};


	VkPipelineLayout Pipeline::GetLayout() const noexcept
	{
		return mPipelineLayout;
	}

	const std::vector<VkDescriptorSetLayout>& Pipeline::GetDescriptorSetLayouts() const noexcept
	{
		return mDescriptorSetLayouts;
	}


	void Pipeline::Create(const ARenderDevice* _device, const RenderPipelineDescriptor& _desc)
	{
		const Device& vkDevice = _device->As<Device>();

		CreateDescriptorSetLayouts(vkDevice, _desc);

		CreatePipelineLayout(vkDevice);
		CreatePipelineHandle(vkDevice, _desc);
	}

	void Pipeline::Destroy(const ARenderDevice* _device)
	{
		const Device& vkDevice = _device->As<Device>();

		DestroyPipelineHandle(vkDevice);
		DestroyPipelineLayout(vkDevice);

		DestroyDescriptorSetLayouts(vkDevice);
	}

	void Pipeline::Bind(const ARenderFrame& _frame) const
	{
		const Frame& vkFrame = _frame.As<Frame>();

		vkCmdBindPipeline(vkFrame.cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, mHandle);
	}


	void Pipeline::CreateDescriptorSetLayouts(const Device& _device, const RenderPipelineDescriptor& _desc)
	{
		std::vector<std::vector<VkDescriptorSetLayoutBinding>> descSetLayouts;
		descSetLayouts.reserve(5); // Default is 3.

		for(uint32 i = 0; i < _desc.shaderInfos.bindingSets.size(); ++i)
		{
			auto& setDesc = _desc.shaderInfos.bindingSets[i];
			std::vector<VkDescriptorSetLayoutBinding>& descSetLayout = descSetLayouts.size() > i ? descSetLayouts[i] : descSetLayouts.emplace_back();

			for (auto& bind : setDesc.bindings)
			{
				VkDescriptorSetLayoutBinding& descBinding = descSetLayout.emplace_back();

				descBinding.binding = bind.binding;
				descBinding.descriptorType = API_GetDescriptorType(bind.type);
				descBinding.descriptorCount = bind.num;
				descBinding.stageFlags = API_GetShaderStageFlags(bind.stageFlags);
				descBinding.pImmutableSamplers = nullptr;
			}
		}

		// Create descriptor set layouts.
		mDescriptorSetLayouts.resize(descSetLayouts.size());

		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
		descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutInfo.pNext = nullptr;
		descriptorSetLayoutInfo.flags = 0u;

		for (uint32 i = 0; i < descSetLayouts.size(); ++i)
		{
			descriptorSetLayoutInfo.bindingCount = SizeOf<uint32>(descSetLayouts[i]);
			descriptorSetLayoutInfo.pBindings = descSetLayouts[i].data();

			SA_VK_ASSERT(vkCreateDescriptorSetLayout(_device, &descriptorSetLayoutInfo, nullptr, &mDescriptorSetLayouts[i]),
				L"Failed to create descriptor set layout!");
		}
	}

	void Pipeline::DestroyDescriptorSetLayouts(const Device& _device)
	{
		for(auto it = mDescriptorSetLayouts.begin(); it != mDescriptorSetLayouts.end(); ++it)
			vkDestroyDescriptorSetLayout(_device, *it, nullptr);

		mDescriptorSetLayouts.clear();
	}


	void Pipeline::CreatePipelineLayout(const Device& _device)
	{
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.pNext = nullptr;
		pipelineLayoutCreateInfo.flags = 0u;
		pipelineLayoutCreateInfo.setLayoutCount = SizeOf<uint32>(mDescriptorSetLayouts);
		pipelineLayoutCreateInfo.pSetLayouts = mDescriptorSetLayouts.data();
		pipelineLayoutCreateInfo.pushConstantRangeCount = 0u;
		pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;

		SA_VK_ASSERT(vkCreatePipelineLayout(_device, &pipelineLayoutCreateInfo, nullptr, &mPipelineLayout), L"Failed to create pipeline layout!");
	}

	void Pipeline::DestroyPipelineLayout(const Device& _device)
	{
		SA_ASSERT(Nullptr, SA / Render / Vulkan, mPipelineLayout, L"Destroy pipeline with null Pipeline Layout!");

		vkDestroyPipelineLayout(_device, mPipelineLayout, nullptr);
		mPipelineLayout = VK_NULL_HANDLE;
	}


	void Pipeline::CreatePipelineHandle(const Device& _device, const RenderPipelineDescriptor& _desc)
	{
		// Shaders
		SpecConstantData specConstData;
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
		FillShaderSpecConstants(specConstData, _desc.shaderInfos);
		FillShaderStages(shaderStages, specConstData, _desc.shaderInfos.stages);


		// Vertex input infos.
		std::unique_ptr<VkVertexInputBindingDescription> bindingDesc;
		std::unique_ptr<VkVertexInputAttributeDescription[]> attribDescs;
		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		FillVertexBindings(vertexInputInfo, bindingDesc, attribDescs, _desc.shaderInfos.vertexBindingLayout);


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

		const VkDynamicState dynamicState[]{ VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

		VkPipelineDynamicStateCreateInfo viewportDynamicInfo{};
		viewportDynamicInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		viewportDynamicInfo.pNext = nullptr;
		viewportDynamicInfo.flags = 0u;
		viewportDynamicInfo.dynamicStateCount = SizeOf<uint32>(dynamicState);
		viewportDynamicInfo.pDynamicStates = dynamicState;


		// Rasterization
		VkPipelineRasterizationStateCreateInfo rasterizerInfo{};
		FillRasterization(rasterizerInfo, _desc.modes);


		// Multisampling.
		RenderPassAttachmentInfos renderPassAttInfos{};
		FillRenderPassAttachments(renderPassAttInfos, _desc);


		// Create handle.
		VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
		pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineCreateInfo.pNext = nullptr;
		pipelineCreateInfo.flags = 0u;
		pipelineCreateInfo.stageCount = SizeOf<uint32>(shaderStages);
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
		pipelineCreateInfo.layout = mPipelineLayout;
		pipelineCreateInfo.renderPass = _desc.renderPass->As<RenderPass>();
		pipelineCreateInfo.subpass = _desc.subPassIndex;
		pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineCreateInfo.basePipelineIndex = -1;

		SA_VK_ASSERT(vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &mHandle),
			L"Failed to create graphics pipeline!");
	}

	void Pipeline::DestroyPipelineHandle(const Device& _device)
	{
		SA_ASSERT(Nullptr, SA / Render / Vulkan, mHandle, L"Destroy null Pipeline!");

		vkDestroyPipeline(_device, mHandle, nullptr);
		mHandle = VK_NULL_HANDLE;
	}


	void Pipeline::FillShaderSpecConstants(SpecConstantData& _specConstData,
		const PipelineShaderInfos& _shaderInfos)
	{
		for (auto& specPair : _shaderInfos.userSpecConstants)
			_specConstData.Add(specPair);

		for (auto& specPair : _shaderInfos.engineSpecConstants)
		{
			switch (specPair.id)
			{
				case SpecConstantID::RenderAPI:
					_specConstData.Add(SpecConstantID::RenderAPI, SpecConstantValue::Vulkan);
					break;
				default:
					SA_LOG(L"Shader Engine specialization constant [" << specPair.id << L"] not supported yet!", Warning, SA/Render/Vulkan);
					break;
			}
		}
	}

	void Pipeline::FillShaderStages(std::vector<VkPipelineShaderStageCreateInfo>& _stages,
		const SpecConstantData& _specConstData,
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
			vkStage.module = stage.shader->As<Shader>();
			vkStage.pName = "main";
			vkStage.pSpecializationInfo = &_specConstData.specInfo;
		}
	}

	void Pipeline::FillVertexBindings(VkPipelineVertexInputStateCreateInfo& _vertexInputInfo,
		std::unique_ptr<VkVertexInputBindingDescription>& _bindingDesc,
		std::unique_ptr<VkVertexInputAttributeDescription[]>& _attribDescs,
		const VertexBindingLayout& _vertexBindingLayout) noexcept
	{
		_bindingDesc = _vertexBindingLayout.GetBindingDescription();
		_attribDescs = _vertexBindingLayout.GetAttributeDescriptions();

		_vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		_vertexInputInfo.pNext = nullptr;
		_vertexInputInfo.flags = 0u;
		_vertexInputInfo.vertexBindingDescriptionCount = _vertexBindingLayout.GetBindingDescriptionNum();
		_vertexInputInfo.pVertexBindingDescriptions = _bindingDesc.get();
		_vertexInputInfo.vertexAttributeDescriptionCount = _vertexBindingLayout.GetAttributeDescriptionNum();
		_vertexInputInfo.pVertexAttributeDescriptions = _attribDescs.get();
	}

	void Pipeline::FillRasterization(VkPipelineRasterizationStateCreateInfo& _rasterizerInfo, const PipelineRenderModes& _modes) noexcept
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

	void Pipeline::FillRenderPassAttachments(struct RenderPassAttachmentInfos& _renderPassAttInfos, const RenderPipelineDescriptor& _desc) noexcept
	{
		const VkSampleCountFlagBits sampleCount = API_GetSampleCount(_desc.subPassDesc.sampling);

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
		uint32 colorAttachmentNum = 0u;

		for (auto it = _desc.subPassDesc.attachmentDescs.begin(); it != _desc.subPassDesc.attachmentDescs.end(); ++it)
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
		_renderPassAttInfos.colorBlendingInfo.attachmentCount = SizeOf<uint32>(_renderPassAttInfos.colorBlendAttachments);
		_renderPassAttInfos.colorBlendingInfo.pAttachments = _renderPassAttInfos.colorBlendAttachments.data();
		_renderPassAttInfos.colorBlendingInfo.blendConstants[0] = 0.0f;
		_renderPassAttInfos.colorBlendingInfo.blendConstants[1] = 0.0f;
		_renderPassAttInfos.colorBlendingInfo.blendConstants[2] = 0.0f;
		_renderPassAttInfos.colorBlendingInfo.blendConstants[3] = 0.0f;
	}
}

#endif
