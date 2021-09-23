// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Bindings/ShaderBindingDescriptor.hpp>

#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
	namespace Serialize
	{
		void ToBinary(const ShaderBindingDescriptor& _obj, std::string& _str)
		{
			ToBinary(_obj.name, _str);
			Intl::ToBinary(&_obj.type, sizeof(ShaderBindingDescriptor) - offsetof(ShaderBindingDescriptor, type), _str);
		}

		void FromBinary(ShaderBindingDescriptor& _obj, Reader& _read)
		{
			FromBinary(_obj.name, _read);
			Intl::FromBinary(&_obj.type, sizeof(ShaderBindingDescriptor) - offsetof(ShaderBindingDescriptor, type), _read);
		}
	}
}
