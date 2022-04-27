// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AWINDOW_INTERFACE_GUARD
#define SAPPHIRE_ENGINE_AWINDOW_INTERFACE_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Window/Base/AWindow.hpp>

namespace Sa
{
	class AWindowInterface : protected HardwareInterface
	{
	public:
		/**
		*	Virtual destructor.
		*	Ensure correct polymorphism destruction.
		*/
		virtual ~AWindowInterface() = default;


		using HardwareInterface::Create;
		using HardwareInterface::Destroy;
		using HardwareInterface::Clear;


		/**
		*	Create window with implementation from the interface.
		* 
		*	\param[in] _infos	Create infos
		* 
		*	\return Created window.
		*/
		virtual AWindow* CreateWindow(const WindowCreateInfos& _infos) = 0;

		/**
		*	\brief Destroy window from interface.
		*	Window must have been created from this interface.
		* 
		*	\param[in] _window	Window to destroy.
		*/
		virtual void DestroyWindow(AWindow* _window) = 0;


		virtual bool QueryRequiredExtensions(std::vector<const char*>& _extensions) const;
	};
}

#endif // GUARD
