// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_RESOURCE_INITIALIZER_GUARD
#define SAPPHIRE_ENGINE_ARENDER_RESOURCE_INITIALIZER_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

namespace Sa
{
	class ARenderResourceInitializer : protected HardwareInterface
	{
		using HardwareInterface::Clear; // not used.
	};
}

#endif // GUARD
