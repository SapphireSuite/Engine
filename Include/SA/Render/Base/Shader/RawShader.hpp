// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RAW_SHADER_GUARD
#define SAPPHIRE_RENDER_RAW_SHADER_GUARD

#include <SA/Render/Base/Shader/ShaderDescriptor.hpp>

namespace Sa
{
	struct RawShader
	{
		std::vector<uint32> data;
		ShaderDescriptor descriptor;

		void Reset();
	};


	namespace Serialize
	{
		void ToBinary(const RawShader& _obj, std::string& _str);
		void FromBinary(RawShader& _obj, Reader& _read);
	}
}

#endif // GUARD
