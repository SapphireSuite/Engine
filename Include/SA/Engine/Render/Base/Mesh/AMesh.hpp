// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AMESH_GUARD
#define SAPPHIRE_ENGINE_AMESH_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

namespace Sa
{
	class AMesh : protected HardwareInterface
	{
		using HardwareInterface::Clear; // not used.
	};
}

#endif // GUARD
