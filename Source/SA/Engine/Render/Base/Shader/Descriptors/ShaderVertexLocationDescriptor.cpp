// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderVertexLocationDescriptor.hpp>

namespace Sa
{
	bool ShaderVertexLocationDescriptor::operator<(const ShaderVertexLocationDescriptor& _rhs) const noexcept
	{
		return location < _rhs.location;
	}
}
