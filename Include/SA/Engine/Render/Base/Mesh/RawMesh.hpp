// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RAW_MESH_GUARD
#define SAPPHIRE_ENGINE_RAW_MESH_GUARD

#include <cstdint>

#include <SA/Maths/Geometry/AABB3D.hpp>

#include <SA/Collections/SerializeBinary>

namespace SA
{
	struct RawMesh
	{
		std::vector<char> vertices;
		std::vector<uint32_t> indices;

		AABB3Df aabb;

		void Clear();
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const RawMesh& _raw, std::string& _dst);

		template <>
		bool FromBinary(RawMesh& _raw, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
