// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/Base/Material/MaterialCreateInfos.hpp>

namespace Sa
{
	MaterialCreateInfos::~MaterialCreateInfos()
	{
		for (auto it = bindings.begin(); it != bindings.end(); ++it)
			delete *it;

		bindings.clear();
	}
}
