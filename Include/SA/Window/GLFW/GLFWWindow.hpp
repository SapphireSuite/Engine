// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_GLFW_WINDOW_GUARD
#define SAPPHIRE_WINDOW_GLFW_WINDOW_GUARD

#include <SA/API/GLFW.hpp>

#include <SA/Window/Base/IWindow.hpp>

#include <SA/Input/GLFW/GLFWInputSystem.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	class Window : public IWindow
	{
		GLFWwindow* mHandle = nullptr;

		GLFWInputSystem mInput;

	public:
		SA_ENGINE_API void Create(uint32 _width, uint32 _height, const std::string& _name = "Main Window") override final;
		SA_ENGINE_API void Destroy() override final;

		SA_ENGINE_API IInputSystem& GetInputSystem() override final;

		SA_ENGINE_API void Close() override final;
		SA_ENGINE_API bool ShouldClose() const override final;

		SA_ENGINE_API void Update() override final;
	};
}

#endif

#endif // GUARD
