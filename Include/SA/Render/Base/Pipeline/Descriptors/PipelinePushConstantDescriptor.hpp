// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_PUSH_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_PIPELINE_PUSH_CONSTANT_DESCRIPTOR_GUARD

#include <SA/Render/Base/Shader/Descriptors/ShaderStage.hpp>
#include <SA/Render/Base/Shader/Descriptors/ShaderPushConstantDescriptor.hpp>

namespace Sa
{
	struct PipelinePushConstantDescriptor : public ShaderPushConstantDescriptor
	{
		Flags<ShaderStage> stageFlags;
	};
}

#endif // GUARD
