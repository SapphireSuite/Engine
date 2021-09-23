// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Window/Base/AWindowSystem.hpp>

namespace Sa
{
	bool AWindowSystem::QueryRequiredExtensions(std::vector<const char*>& _extensions) const
	{
		(void)_extensions;

		return true;
	}
}
