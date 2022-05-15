// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_PUSH_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_PUSH_CONSTANT_DESCRIPTOR_GUARD

#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderStage.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderPushConstantDescriptor.hpp>

namespace SA
{
	struct PipelinePushConstantDescriptor : public ShaderPushConstantDescriptor
	{
		Flags<ShaderStage> stageFlags;
	};
}

#endif // GUARD
