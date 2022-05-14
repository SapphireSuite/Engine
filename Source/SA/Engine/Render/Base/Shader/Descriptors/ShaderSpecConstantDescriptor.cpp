// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderSpecConstantDescriptor.hpp>

namespace SA
{
	bool ShaderSpecConstantDescriptor::operator<(const ShaderSpecConstantDescriptor& _rhs) const noexcept
	{
		return id < _rhs.id;
	}
}
