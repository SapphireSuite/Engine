// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderBindingDescriptor.hpp>

#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
	namespace Serialize
	{
		void ToBinary(const ShaderBindingDescriptor& _obj, std::string& _str)
		{
			ToBinary(_obj.name, _str);
			ToBinary(_obj.typeName, _str);

			SA_SerializeEndBlock(ToBinary, _obj, type, _str);
		}

		void FromBinary(ShaderBindingDescriptor& _obj, Reader& _read)
		{
			FromBinary(_obj.name, _read);
			FromBinary(_obj.typeName, _read);

			SA_SerializeEndBlock(FromBinary, _obj, type, _read);
		}
	}
}
