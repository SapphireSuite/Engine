// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ACUBEMAP_GUARD
#define SAPPHIRE_ENGINE_ACUBEMAP_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Render/Base/Texture/RawCubemap.hpp>

namespace SA
{
	class ACubemap : protected HardwareInterface
	{
		using HardwareInterface::Clear; // Not used.
	};
}

#endif // GUARD
