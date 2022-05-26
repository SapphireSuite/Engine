// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_STATIC_BINDING_INFOS
#define SAPPHIRE_ENGINE_MATERIAL_STATIC_BINDING_INFOS

#include <SA/Engine/Render/Base/Material/Bindings/MaterialBaseBindingInfos.hpp>

namespace SA
{
	struct MaterialStaticBindingInfos : public MaterialBaseBindingInfos
	{
		uint32_t binding = 0u;
		uint32_t set = 0u;

		inline MaterialStaticBindingInfos(uint32_t _binding = 0u, uint32_t _set = 0u, uint32_t _offset = 0u) noexcept :
			MaterialBaseBindingInfos(_offset),
			binding{ _binding },
			set{ _set }
		{
		}
	};
}

#endif // GUARD
