// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/SpecConstants/SpecConstantDescriptor.hpp>

#include <SA/Core/Serialize/Serializer.hpp>

namespace Sa
{
	bool SpecConstantDescriptor::operator<(const SpecConstantDescriptor& _rhs) const noexcept
	{
		return id < _rhs.id;
	}


	namespace Serialize
	{
		void ToBinary(const SpecConstantDescriptor& _obj, std::string& _str)
		{
			ToBinary(_obj.name, _str);
			ToBinary(_obj.id, _str);
		}

		void FromBinary(SpecConstantDescriptor& _obj, Reader& _read)
		{
			FromBinary(_obj.name, _read);
			FromBinary(_obj.id, _read);
		}
	}
}
