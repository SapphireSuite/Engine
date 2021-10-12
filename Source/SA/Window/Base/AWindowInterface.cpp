// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Window/Base/AWindowInterface.hpp>

namespace Sa
{
	bool AWindowInterface::QueryRequiredExtensions(std::vector<const char*>& _extensions) const
	{
		(void)_extensions;

		return true;
	}
}
