// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/RawShader.hpp>

#include <Core/Serialize/Serializer.hpp>

namespace Sa
{
	void RawShader::Clear()
	{
		data.clear();
	}


	namespace Serialize
	{
		void ToBinary(const RawShader& _obj, std::string& _str)
		{
			ToBinary(_obj.data, _str);
		}

		void FromBinary(RawShader& _obj, Reader& _read)
		{
			FromBinary(_obj.data, _read);
		}
	}
}
