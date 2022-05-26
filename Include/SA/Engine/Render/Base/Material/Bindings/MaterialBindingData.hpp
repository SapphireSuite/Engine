// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MATERIAL_BINDING_DATA_GUARD
#define SAPPHIRE_ENGINE_MATERIAL_BINDING_DATA_GUARD

#include <vector>
#include <utility>

#include <SA/Engine/Render/Base/Material/Bindings/MaterialStaticBindingInfos.hpp>
#include <SA/Engine/Render/Base/Material/Bindings/MaterialNamedBindingInfos.hpp>

#include <SA/Engine/Render/Base/Material/Bindings/IBOBinding.hpp>

namespace SA
{
	struct MaterialBindingData
	{
		std::vector<std::pair<MaterialStaticBindingInfos, ARenderMaterialBinding*>> staticBindings;
		std::vector<std::pair<MaterialNamedBindingInfos, ARenderMaterialBinding*>> namedBindings;

		~MaterialBindingData();


		bool Empty() const noexcept;

		void Clear();


		template <typename BindT, typename... Args>
		void Add(MaterialStaticBindingInfos _infos, Args&&... _args)
		{
			staticBindings.emplace_back(std::make_pair(std::move(_infos), new BindT(std::forward<Args>(_args)...)));
		}

		template <typename BindT, typename... Args>
		void Add(MaterialNamedBindingInfos _infos, Args&&... _args)
		{
			namedBindings.emplace_back(std::make_pair(std::move(_infos), new BindT(std::forward<Args>(_args)...)));
		}
	};
}

#endif // GUARD
