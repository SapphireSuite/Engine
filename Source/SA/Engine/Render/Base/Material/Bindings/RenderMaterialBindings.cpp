// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/Bindings/RenderMaterialBindings.hpp>

#include <Render/Base/Material/Bindings/ARenderMaterialBinding.hpp>

namespace SA
{
	RenderMaterialBindings::~RenderMaterialBindings()
	{
		for (auto bind : *this)
			delete bind;

		clear();
	}
}
