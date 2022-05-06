// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderPushConstantDescriptor.hpp>

namespace Sa
{
	bool ShaderPushConstantDescriptor::operator<(const ShaderPushConstantDescriptor& _rhs) const noexcept
	{
		return offset < _rhs.offset;
	}
}
