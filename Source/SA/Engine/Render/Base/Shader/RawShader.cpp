// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/RawShader.hpp>

namespace SA
{
	void RawShader::Clear()
	{
		data.clear();
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const RawShader& _raw, std::string& _dst)
		{
			return ToBinary(_raw.data, _dst);
		}

		template <>
		bool FromBinary(RawShader& _raw, const std::string& _src, size_t& _offset)
		{
			return FromBinary(_raw.data, _src, _offset);
		}
	}
}
