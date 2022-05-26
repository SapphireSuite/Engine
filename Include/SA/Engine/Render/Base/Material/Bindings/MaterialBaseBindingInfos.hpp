// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_BASE_BINDING_INFOS
#define SAPPHIRE_ENGINE_MATERIAL_BASE_BINDING_INFOS

#include <cstdint>

namespace SA
{
	struct MaterialBaseBindingInfos
	{
		uint32_t offset = 0u;

		inline MaterialBaseBindingInfos(uint32_t _offset = 0u) noexcept :
			offset{ _offset }
		{
		}
	};
}

#endif // GUARD
