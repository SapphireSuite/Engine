// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderSpecConstantDescriptor.hpp>

namespace SA
{
	bool ShaderSpecConstantDescriptor::operator<(const ShaderSpecConstantDescriptor& _rhs) const noexcept
	{
		return id < _rhs.id;
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderSpecConstantDescriptor& _desc, std::string& _dst)
		{
			ToBinary(_desc.name, _dst);
			ToBinary(_desc.id, _dst);

			return true;
		}

		template <>
		bool FromBinary(ShaderSpecConstantDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			FromBinary(_desc.name, _src, _offset);
			FromBinary(_desc.id, _src, _offset);

			return true;
		}
	}
}
