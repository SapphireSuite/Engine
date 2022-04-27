// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AWINDOW_SURFACE_GUARD
#define SAPPHIRE_ENGINE_AWINDOW_SURFACE_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

namespace Sa
{
	class AWindow;

    class AWindowSurface : protected HardwareInterface
	{
	protected:
		AWindow* mWindow = nullptr;

	public:
	    /**
		*	@brief Virtual destructor.
		*	Ensure correct polymorphism destruction.
		*/
		virtual ~AWindowSurface() = default;
	};
}

#endif // GUARD
