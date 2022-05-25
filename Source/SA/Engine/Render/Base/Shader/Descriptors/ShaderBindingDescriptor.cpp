// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderBindingDescriptor.hpp>

namespace SA
{
	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderBindingDescriptor& _desc, std::string& _dst)
		{
			ToBinary(_desc.name, _dst);
			ToBinary(_desc.dataTypeName, _dst);
			ToBinary(_desc.type, _dst);
			ToBinary(_desc.binding, _dst);
			ToBinary(_desc.num, _dst);
			ToBinary(_desc.inAttachIndex, _dst);

			return true;
		}

		template <>
		bool FromBinary(ShaderBindingDescriptor& _desc, const std::string& _src, size_t& _offset)
		{
			FromBinary(_desc.name, _src, _offset);
			FromBinary(_desc.dataTypeName, _src, _offset);
			FromBinary(_desc.type, _src, _offset);
			FromBinary(_desc.binding, _src, _offset);
			FromBinary(_desc.num, _src, _offset);
			FromBinary(_desc.inAttachIndex, _src, _offset);

			return true;
		}
	}
}
