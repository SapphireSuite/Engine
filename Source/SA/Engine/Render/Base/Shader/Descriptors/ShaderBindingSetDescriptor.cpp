// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderBindingSetDescriptor.hpp>

namespace SA
{
	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderBindingSetDescriptor& _desc, std::string& _dst)
		{
			return ToBinary(_desc.bindings, _dst);
		}

		template <>
		bool FromBinary(ShaderBindingSetDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			return FromBinary(_desc.bindings, _src, _offset);
		}
	}
}
