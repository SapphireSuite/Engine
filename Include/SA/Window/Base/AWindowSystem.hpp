// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_AWINDOW_SYSTEM_GUARD
#define SAPPHIRE_WINDOW_AWINDOW_SYSTEM_GUARD

#include <SA/Core/Types/Abstract.hpp>

namespace Sa
{
	class AWindowSystem : public Abstract
	{
	public:
		virtual void Create() = 0;
		virtual void Destroy() = 0;

		virtual bool QueryRequiredExtensions(std::vector<const char*>& _extensions) const;
	};
}

#endif // GUARD
