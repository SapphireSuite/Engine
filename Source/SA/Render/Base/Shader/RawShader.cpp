// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/RawShader.hpp>

#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
	void RawShader::Reset()
	{
		data.clear();

		descriptor.Reset();
	}


	namespace Serialize
	{
		void ToBinary(const RawShader& _obj, std::string& _str)
		{
			ToBinary(_obj.data, _str);
			ToBinary(_obj.descriptor, _str);
		}

		void FromBinary(RawShader& _obj, Reader& _read)
		{
			FromBinary(_obj.data, _read);
			FromBinary(_obj.descriptor, _read);
		}
	}
}
