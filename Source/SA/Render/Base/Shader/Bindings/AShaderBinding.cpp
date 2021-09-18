// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Bindings/AShaderBinding.hpp>

namespace Sa
{
	AShaderBinding::AShaderBinding(uint32 _binding, uint32 _descriptor) noexcept :
		binding{ _binding },
		descriptor{ _descriptor }
	{
	}
}
