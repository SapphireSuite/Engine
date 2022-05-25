// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Mesh/RawMesh.hpp>

namespace SA
{
	void RawMesh::Clear()
	{
		vertices.clear();
		indices.clear();
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const RawMesh& _raw, std::string& _dst)
		{
			ToBinary(_raw.vertices, _dst);
			ToBinary(_raw.indices, _dst);

			return true;
		}

		template <>
		bool FromBinary(RawMesh& _raw, const std::string& _src, size_t& _offset)
		{
			FromBinary(_raw.vertices, _src, _offset);
			FromBinary(_raw.indices, _src, _offset);

			return true;
		}
	}
}
