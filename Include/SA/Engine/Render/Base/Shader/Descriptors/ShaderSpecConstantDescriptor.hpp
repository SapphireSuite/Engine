// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_SPEC_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_SPEC_CONSTANT_DESCRIPTOR_GUARD

#include <cstdint>

#include <SA/Collections/SerializeBinary>

namespace SA
{
	struct ShaderSpecConstantDescriptor
	{
		std::string name;

		uint32_t id = 0u;

		bool operator<(const ShaderSpecConstantDescriptor& _rhs) const noexcept;
	};

	
	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderSpecConstantDescriptor& _desc, std::string& _dst);

		template <>
		bool FromBinary(ShaderSpecConstantDescriptor& _desc, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
