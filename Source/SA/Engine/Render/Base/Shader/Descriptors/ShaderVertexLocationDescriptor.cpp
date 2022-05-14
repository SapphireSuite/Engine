// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderVertexLocationDescriptor.hpp>

namespace SA
{
	bool ShaderVertexLocationDescriptor::operator<(const ShaderVertexLocationDescriptor& _rhs) const noexcept
	{
		return location < _rhs.location;
	}
}
