// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/RawShader.hpp>

namespace Sa
{
	void RawShader::Reset()
	{
		data.clear();

		descriptor.stage = ShaderStage::Unknown;
		descriptor.vertexLayout = 0u;
		descriptor.bindings.clear();
	}
}
