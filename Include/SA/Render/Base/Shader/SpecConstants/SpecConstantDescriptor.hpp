// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SPEC_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SPEC_CONSTANT_DESCRIPTOR_GUARD

#include <string>

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	struct SpecConstantDescriptor
	{
		std::string name;

		// Name first for block serialization.

		uint32 id = 0u;
	};
}

#endif // GUARD
