// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_GLFW_WINDOWING_INTERFACE_GUARD
#define SAPPHIRE_ENGINE_GLFW_WINDOWING_INTERFACE_GUARD

#include <SA/Engine/Window/Base/AWindowInterface.hpp>
#include <SA/Engine/Window/GLFW/GLFWWindow.hpp>

#include <SA/Engine/HI/InterfaceList.hpp>

namespace SA::GLFW
{
	class WindowInterface : public AWindowInterface
	{
		InterfaceList<Window> mWindows;

	public:
		void Create() override final;
		void Destroy() override final;

		void Clear() override final;


		AWindow* CreateWindow(const WindowCreateInfos& _infos) override final;
		void DestroyWindow(AWindow* _window) override final;

		bool QueryRequiredExtensions(std::vector<const char*>& _extensions) const override final;
	};
}

#endif // GUARD
