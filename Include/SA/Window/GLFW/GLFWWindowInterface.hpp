// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_GLFW_WINDOW_INTERFACE_GUARD
#define SAPPHIRE_GLFW_WINDOW_INTERFACE_GUARD

#include <SA/Core/Support/API/GLFW.hpp>

#include <SA/Window/Base/AWindowInterface.hpp>

#include <SA/Window/GLFW/GLFWWindow.hpp>

namespace Sa::GLFW
{
	class WindowInterface : public AWindowInterface
	{
	public:
		void Create() override final;
		void Destroy() override final;

		AWindow* CreateWindow(const WindowCreateInfos& _infos) override final;
		void DestroyWindow(AWindow* _window) override final;

		bool QueryRequiredExtensions(std::vector<const char*>& _extensions) const override final;
	};
}

#endif // GUARD
