// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/Bindings/ARenderMaterialBinding.hpp>

namespace SA
{
	ARenderMaterialBinding::ARenderMaterialBinding(uint32_t _binding, uint32_t _set) noexcept :
		binding{ _binding },
		set{ _set }
	{
	}
}
