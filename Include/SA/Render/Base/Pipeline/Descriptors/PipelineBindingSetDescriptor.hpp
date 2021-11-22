// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_BINDING_SET_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_PIPELINE_BINDING_SET_DESCRIPTOR_GUARD

#include <vector>

#include <SA/Render/Base/Shader/Descriptors/ShaderStage.hpp>
#include <SA/Render/Base/Shader/Descriptors/ShaderBindingDescriptor.hpp>

namespace Sa
{
	struct PipelineBindingDescriptor : public ShaderBindingDescriptor
	{
		Flags<ShaderStage> stageFlags;
	};

	struct PipelineBindingSetDescriptor
	{
		/// List of registered bindings for set.
		std::vector<PipelineBindingDescriptor> bindings;


		static PipelineBindingSetDescriptor modelBindSetDesc;
		static PipelineBindingSetDescriptor cameraBindSetDesc;
	};
}

#endif // GUARD
