// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_PUSH_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_PUSH_CONSTANT_DESCRIPTOR_GUARD

#include <SA/Collections/SerializeBinary>

#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderStage.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderPushConstantDescriptor.hpp>

namespace SA
{
	struct PipelinePushConstantDescriptor
	{
		uint32_t size = 0u;

		uint32_t offset = ~uint32_t();

		ShaderStage stage;
	};


	namespace Ser
	{
		template <>
		struct TypeSpecs<PipelinePushConstantDescriptor>
		{
			static constexpr bool bContinuousData = true;
		};
	}
}

#endif // GUARD
