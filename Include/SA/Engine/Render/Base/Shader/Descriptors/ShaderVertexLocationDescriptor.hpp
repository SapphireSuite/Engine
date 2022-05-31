// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_VERTEX_LOCATION_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_VERTEX_LOCATION_DESCRIPTOR_GUARD

#include <cstdint>

#include <SA/Collections/SerializeBinary>

namespace SA
{
	struct ShaderVertexLocationDescriptor
	{
		std::string name;

		uint32_t location = 0u;

		/// Size in bytes.
		uint32_t size = 0u;

		bool operator<(const ShaderVertexLocationDescriptor& _rhs) const noexcept;
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderVertexLocationDescriptor& _desc, std::string& _dst);

		template <>
		bool FromBinary(ShaderVertexLocationDescriptor& _desc, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
