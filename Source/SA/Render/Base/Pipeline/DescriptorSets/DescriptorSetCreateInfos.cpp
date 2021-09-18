// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/DescriptorSets/DescriptorSetCreateInfos.hpp>

namespace Sa
{
	DescriptorSetCreateInfos::~DescriptorSetCreateInfos()
	{
		for (auto it = bindings.begin(); it != bindings.end(); ++it)
			delete* it;

		bindings.clear();
	}
}
