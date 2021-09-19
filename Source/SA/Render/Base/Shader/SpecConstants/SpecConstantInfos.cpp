// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/SpecConstants/SpecConstantInfos.hpp>

namespace Sa
{
	SpecConstantInfos::~SpecConstantInfos()
	{
		for (auto it = specConsts.begin(); it != specConsts.end(); ++it)
			delete* it;

		specConsts.clear();
	}
}
