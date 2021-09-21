// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/RawShader.hpp>

namespace Sa
{
	void RawShader::Reset()
	{
		stage = ShaderStage::Unknown;

		vertexLayout = 0u;

		data.clear();
		bindings.clear();
	}
}
