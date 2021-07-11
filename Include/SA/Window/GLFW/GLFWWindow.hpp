// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_GLFW_WINDOW_GUARD
#define SAPPHIRE_WINDOW_GLFW_WINDOW_GUARD

#include <SA/Window/Base/IWindow.hpp>

#include <SA/Input/GLFW/GLFWInputSystem.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	class Window : public IWindow
	{
		GLFWwindow* mHandle = nullptr;

		GLFWInputSystem mInput;

		Vec2ui mSavedSize;
		Vec2i mSavedPosition;

		static void MinimizedCallback(GLFWwindow* _handle, int32 _minimized);
		static void MaximizedCallback(GLFWwindow* _handle, int32 _maximized);
		static void ResizeCallback(GLFWwindow* _handle, int32 _width, int32 _height);

		GLFWmonitor* GetCurrentMonitor();

	public:
		SA_ENGINE_API void SetWindowMode(WindowMode _mode) override final;

		SA_ENGINE_API void Create(const CreateInfos& _infos) override final;
		SA_ENGINE_API void Destroy() override final;

		SA_ENGINE_API IInputSystem& GetInputSystem() override final;

		SA_ENGINE_API void Close() override final;
		SA_ENGINE_API bool ShouldClose() const override final;
	};
}

#endif

#endif // GUARD
