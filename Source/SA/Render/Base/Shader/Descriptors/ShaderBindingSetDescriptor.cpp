// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderBindingSetDescriptor.hpp>

#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
	namespace Serialize
	{
		void ToBinary(const ShaderBindingSetDescriptor& _obj, std::string& _str)
		{
			ToBinary(_obj.bindings, _str);
		}

		void FromBinary(ShaderBindingSetDescriptor& _obj, Reader& _read)
		{
			FromBinary(_obj.bindings, _read);
		}
	}
}
