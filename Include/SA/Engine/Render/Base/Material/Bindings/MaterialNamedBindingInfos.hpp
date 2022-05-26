// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_NAMED_BINDING_INFOS
#define SAPPHIRE_ENGINE_MATERIAL_NAMED_BINDING_INFOS

#include <string>

#include <SA/Engine/Render/Base/Material/Bindings/MaterialBaseBindingInfos.hpp>

namespace SA
{
	struct MaterialNamedBindingInfos : public MaterialBaseBindingInfos
	{
		std::string name;

		inline MaterialNamedBindingInfos(std::string _name, uint32_t _offset = 0u) noexcept :
			MaterialBaseBindingInfos(_offset),
			name{ std::move(_name) }
		{
		}
	};
}

#endif // GUARD
