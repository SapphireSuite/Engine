// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_SPEC_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_SPEC_CONSTANT_DESCRIPTOR_GUARD

#include <string>
#include <cstdint>

namespace SA
{
	struct ShaderSpecConstantDescriptor
	{
		std::string name;

		uint32_t id = 0u;

		bool operator<(const ShaderSpecConstantDescriptor& _rhs) const noexcept;
	};
}

#endif // GUARD
