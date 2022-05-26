// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_BINDING_SET_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_BINDING_SET_DESCRIPTOR_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderStage.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderBindingDescriptor.hpp>

namespace SA
{
	struct PipelineBindingDescriptor : public ShaderBindingDescriptor
	{
		Flags<ShaderStage> stageFlags;

		PipelineBindingDescriptor() = default;
		PipelineBindingDescriptor(ShaderBindingDescriptor&& _other) noexcept : ShaderBindingDescriptor(std::move(_other)) {}
		PipelineBindingDescriptor(const ShaderBindingDescriptor& _other) noexcept : ShaderBindingDescriptor(_other) {}
	};

	struct PipelineBindingSetDescriptor
	{
		/// List of registered bindings for set.
		std::vector<PipelineBindingDescriptor> bindings;
	};
}

#endif // GUARD
