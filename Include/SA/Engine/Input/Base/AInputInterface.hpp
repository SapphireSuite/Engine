// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AINPUT_INTERFACE_GUARD
#define SAPPHIRE_ENGINE_AINPUT_INTERFACE_GUARD

#include <SA/Engine/HI/HardwareInterfaceBase.hpp>

#include <SA/Engine/Input/Base/AInputWindowContext.hpp>

namespace Sa
{
	class AWindow;

	class AInputInterface : public HardwareInterfaceBase
	{
	public:
		/**
		*	Virtual destructor.
		*	Ensure correct polymorphism destruction.
		*/
		virtual ~AInputInterface() = default;


		virtual void Update() = 0;

		virtual AInputWindowContext* CreateInputWindowContext(AWindow* _win) = 0;
		virtual void DestroyInputWindowContext(AInputWindowContext* _winContext) = 0;
	};
}

#endif // GUARD
