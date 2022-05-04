// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_PASS_GUARD
#define SAPPHIRE_ENGINE_ARENDER_PASS_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Render/Base/Pass/RenderPassDescriptor.hpp>

namespace Sa
{
	class ARenderPass : protected HardwareInterface
	{
		using HardwareInterface::Clear; // not used.
	};
}

#endif // GUARD
