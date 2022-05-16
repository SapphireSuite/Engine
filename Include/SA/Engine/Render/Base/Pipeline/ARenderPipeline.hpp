// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHRIRE_ENGINE_ARENDER_PIPELINE_GUARD
#define SAPPHRIRE_ENGINE_ARENDER_PIPELINE_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Render/Base/Pipeline/Descriptors/RenderPipelineDescriptor.hpp>

namespace SA
{
	class ARenderPipeline : protected HardwareInterface
	{
		using HardwareInterface::Clear; // not used.
	};
}

#endif // GUARD
