// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/ShaderDescriptor.hpp>

namespace Sa
{
	namespace Serialize
	{
		void ToBinary(const ShaderDescriptor& _obj, std::string& _str)
		{
			ToBinary(_obj.stage, _str);

			if (_obj.stage == ShaderStage::Vertex)
				ToBinary(_obj.vertexLayout, _str);

			ToBinary(_obj.bindings, _str);
			ToBinary(_obj.specConstants, _str);
		}

		void FromBinary(ShaderDescriptor& _obj, Reader& _read)
		{
			FromBinary(_obj.stage, _read);

			if (_obj.stage == ShaderStage::Vertex)
				FromBinary(_obj.vertexLayout, _read);

			FromBinary(_obj.bindings, _read);
			FromBinary(_obj.specConstants, _read);
		}
	}
}
