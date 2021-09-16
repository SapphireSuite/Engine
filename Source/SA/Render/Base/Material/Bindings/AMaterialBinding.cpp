// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/Bindings/AMaterialBinding.hpp>

namespace Sa
{
	AMaterialBinding::AMaterialBinding(uint32 _binding, uint32 _descriptor) noexcept :
		binding{ _binding },
		descriptor{ _descriptor }
	{
	}
}
