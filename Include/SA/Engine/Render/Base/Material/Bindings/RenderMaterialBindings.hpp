// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RENDER_MATERIAL_BINDINGS_GUARD
#define SAPPHIRE_ENGINE_RENDER_MATERIAL_BINDINGS_GUARD

#include <vector>

namespace SA
{
	class ARenderMaterialBinding;

	class RenderMaterialBindings : private std::vector<const ARenderMaterialBinding*>
	{
	public:
		using std::vector<const ARenderMaterialBinding*>::empty;
		using std::vector<const ARenderMaterialBinding*>::size;
		using std::vector<const ARenderMaterialBinding*>::begin;
		using std::vector<const ARenderMaterialBinding*>::end;
		using std::vector<const ARenderMaterialBinding*>::operator[];

		~RenderMaterialBindings();

		template <typename BindT, typename... Args>
		void Add(Args&&... _args)
		{
			emplace_back(new BindT(std::forward<Args>(_args)...));
		}
	};
}

#endif // GUARD
