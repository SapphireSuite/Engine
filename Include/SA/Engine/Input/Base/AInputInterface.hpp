// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AINPUT_INTERFACE_GUARD
#define SAPPHIRE_ENGINE_AINPUT_INTERFACE_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Input/Base/AInputWindowContext.hpp>

namespace SA
{
	class AWindow;

	class AInputInterface : protected HardwareInterface
	{
	public:
		using HardwareInterface::Create;
		using HardwareInterface::Destroy;
		using HardwareInterface::Clear;

		virtual void Update() = 0;


		virtual AInputWindowContext* CreateInputWindowContext(AWindow* _win) = 0;
		virtual void DestroyInputWindowContext(AInputWindowContext* _winContext) = 0;
	};
}

#endif // GUARD
