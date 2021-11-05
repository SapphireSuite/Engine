// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderPushConstantDescriptor.hpp>

#include <SA/Core/Serialize/Serializer.hpp>

namespace Sa
{
	bool ShaderPushConstantDescriptor::operator<(const ShaderPushConstantDescriptor& _rhs) const noexcept
	{
		return offset < _rhs.offset;
	}


	namespace Serialize
	{
		void ToBinary(const ShaderPushConstantDescriptor& _obj, std::string& _str)
		{
			ToBinary(_obj.name, _str);
			ToBinary(_obj.size, _str);
			ToBinary(_obj.offset, _str);
		}

		void FromBinary(ShaderPushConstantDescriptor& _obj, Reader& _read)
		{
			FromBinary(_obj.name, _read);
			FromBinary(_obj.size, _read);
			FromBinary(_obj.offset, _read);
		}
	}
}
