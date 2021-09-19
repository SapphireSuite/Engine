// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/SpecConstants/SpecConstant.hpp>

namespace Sa
{
	namespace Intl
	{
		SpecConstantBase::SpecConstantBase(uint32 _id, uint32 _size) noexcept :
			id{ _id },
			size{ _size }
		{
		}
	}
}
