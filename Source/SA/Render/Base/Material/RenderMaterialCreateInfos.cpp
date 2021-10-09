// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/RenderMaterialCreateInfos.hpp>

namespace Sa
{
	RenderMaterialCreateInfos::~RenderMaterialCreateInfos()
	{
		for (auto bind : bindings)
			delete bind;

		bindings.clear();
	}
}
