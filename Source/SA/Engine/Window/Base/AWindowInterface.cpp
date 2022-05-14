// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Window/Base/AWindowInterface.hpp>

namespace SA
{
	bool AWindowInterface::QueryRequiredExtensions(std::vector<const char*>& _extensions) const
	{
		(void)_extensions;

		return true;
	}
}
