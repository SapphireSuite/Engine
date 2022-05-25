// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderVertexLayoutDescriptor.hpp>

namespace SA
{
	void ShaderVertexLayoutDescriptor::Clear()
	{
		locations.clear();
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderVertexLayoutDescriptor& _desc, std::string& _dst)
		{
			return ToBinary(_desc.locations, _dst);
		}

		template <>
		bool FromBinary(ShaderVertexLayoutDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			return FromBinary(_desc.locations, _src, _offset);
		}
	}
}
