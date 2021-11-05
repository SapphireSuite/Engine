// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderSpecConstantDescriptor.hpp>

#include <SA/Core/Serialize/Serializer.hpp>

namespace Sa
{
	bool ShaderSpecConstantDescriptor::operator<(const ShaderSpecConstantDescriptor& _rhs) const noexcept
	{
		return id < _rhs.id;
	}


	namespace Serialize
	{
		void ToBinary(const ShaderSpecConstantDescriptor& _obj, std::string& _str)
		{
			ToBinary(_obj.name, _str);
			ToBinary(_obj.id, _str);
		}

		void FromBinary(ShaderSpecConstantDescriptor& _obj, Reader& _read)
		{
			FromBinary(_obj.name, _read);
			FromBinary(_obj.id, _read);
		}
	}
}
