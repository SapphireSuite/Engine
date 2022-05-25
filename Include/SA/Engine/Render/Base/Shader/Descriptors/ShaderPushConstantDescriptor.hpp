// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_PUSH_CONSTANT_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_PUSH_CONSTANT_DESCRIPTOR_GUARD

#include <cstdint>

#include <SA/Collections/SerializeBinary>

namespace SA
{
	struct ShaderPushConstantDescriptor
	{
		std::string name;

		uint32_t size = 0u;

		uint32_t offset = 0u;

		bool operator<(const ShaderPushConstantDescriptor& _rhs) const noexcept;
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderPushConstantDescriptor& _desc, std::string& _dst);

		template <>
		bool FromBinary(ShaderPushConstantDescriptor& _desc, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
