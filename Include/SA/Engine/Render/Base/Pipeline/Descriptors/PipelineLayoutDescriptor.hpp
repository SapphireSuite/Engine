// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_LAYOUT_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_LAYOUT_DESCRIPTOR_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelineBindingSetDescriptor.hpp>
#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelinePushConstantDescriptor.hpp>

namespace SA
{
	struct ShaderDescriptor;
	struct ShaderBindingSetDescriptor;
	struct ShaderPushConstantDescriptor;

	struct PipelineLayoutDescriptor
	{
		std::vector<PipelineBindingSetDescriptor> bindSetDescs;
		std::vector<PipelinePushConstantDescriptor> pushConstDescs;

		void AddShader(const ShaderDescriptor& _desc);

	private:
		void AddBindingSets(const ShaderDescriptor& _desc);
		void AddPushConstants(const ShaderDescriptor& _desc);
	};
}

#endif // GUARD
