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

		bool Empty() const noexcept;
		void Clear();

		void AddShader(const ShaderDescriptor& _desc);

	private:
		void AddBindingSets(const ShaderDescriptor& _desc);
		void AddPushConstants(const ShaderDescriptor& _desc);
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const PipelineLayoutDescriptor& _desc, std::string& _dst);

		template <>
		bool FromBinary(PipelineLayoutDescriptor& _desc, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
