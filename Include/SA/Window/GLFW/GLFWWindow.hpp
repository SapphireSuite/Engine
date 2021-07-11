// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_GLFW_WINDOW_GUARD
#define SAPPHIRE_WINDOW_GLFW_WINDOW_GUARD

#include <SA/API/GLFW.hpp>

#include <SA/Window/Base/IWindow.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	class InputWindowContext;

	class Window : public IWindow
	{
		GLFWwindow* mHandle = nullptr;

		Vec2ui mSavedSize;
		Vec2i mSavedPosition;

		static void MinimizedCallback(GLFWwindow* _handle, int32 _minimized);
		static void MaximizedCallback(GLFWwindow* _handle, int32 _maximized);
		static void ResizeCallback(GLFWwindow* _handle, int32 _width, int32 _height);

		GLFWmonitor* GetCurrentMonitor();

	public:
		using CreateInfos = IWindow::CreateInfos;


		InputWindowContext* inputWinContext = nullptr;


		SA_ENGINE_API void SetWindowMode(WindowMode _mode) override final;

		SA_ENGINE_API void Create(const CreateInfos& _infos) override final;
		SA_ENGINE_API void Destroy() override final;

		SA_ENGINE_API IInputWindowContext* GetInputWindowContext() const override final;

		SA_ENGINE_API void Close() override final;
		SA_ENGINE_API bool ShouldClose() const override final;

		GLFWwindow* GetHandle() const;
	};
}

#endif

#endif // GUARD
