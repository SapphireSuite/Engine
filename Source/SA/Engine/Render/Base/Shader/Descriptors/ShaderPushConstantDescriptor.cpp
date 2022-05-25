// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderPushConstantDescriptor.hpp>

namespace SA
{
	bool ShaderPushConstantDescriptor::operator<(const ShaderPushConstantDescriptor& _rhs) const noexcept
	{
		return offset < _rhs.offset;
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderPushConstantDescriptor& _desc, std::string& _dst)
		{
			ToBinary(_desc.name, _dst);
			ToBinary(_desc.size, _dst);
			ToBinary(_desc.offset, _dst);

			return true;
		}

		template <>
		bool FromBinary(ShaderPushConstantDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			FromBinary(_desc.name, _src, _offset);
			FromBinary(_desc.size, _src, _offset);
			FromBinary(_desc.offset, _src, _offset);

			return true;
		}
	}
}
