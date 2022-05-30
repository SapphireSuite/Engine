// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_BINDING_SET_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_BINDING_SET_DESCRIPTOR_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelineBindingDescriptor.hpp>

namespace SA
{
	struct PipelineBindingSetDescriptor
	{
		/// List of registered bindings for set.
		std::vector<PipelineBindingDescriptor> bindings;
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const PipelineBindingSetDescriptor& _desc, std::string& _dst);

		template <>
		bool FromBinary(PipelineBindingSetDescriptor& _desc, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
