// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderVertexLocationDescriptor.hpp>

namespace SA
{
	bool ShaderVertexLocationDescriptor::operator<(const ShaderVertexLocationDescriptor& _rhs) const noexcept
	{
		return location < _rhs.location;
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderVertexLocationDescriptor& _desc, std::string& _dst)
		{
			ToBinary(_desc.name, _dst);
			ToBinary(_desc.location, _dst);
			ToBinary(_desc.size, _dst);

			return true;
		}

		template <>
		bool FromBinary(ShaderVertexLocationDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			FromBinary(_desc.name, _src, _offset);
			FromBinary(_desc.location, _src, _offset);
			FromBinary(_desc.size, _src, _offset);

			return true;
		}
	}
}
