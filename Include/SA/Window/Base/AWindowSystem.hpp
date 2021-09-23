// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_AWINDOW_SYSTEM_GUARD
#define SAPPHIRE_WINDOW_AWINDOW_SYSTEM_GUARD

#include <SA/Core/Types/ASystem.hpp>

namespace Sa
{
	class AWindowSystem : public ASystem
	{
	public:
		virtual bool QueryRequiredExtensions(std::vector<const char*>& _extensions) const;
	};
}

#endif // GUARD
