// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHRIRE_ENGINE_ARENDER_PIPELINE_LAYOUT_GUARD
#define SAPPHRIRE_ENGINE_ARENDER_PIPELINE_LAYOUT_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelineLayoutDescriptor.hpp>

namespace SA
{
	class ARenderPipelineLayout : protected HardwareInterface
	{
		using HardwareInterface::Clear; // not used.
	};
}

#endif // GUARD
