// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_GLFW_WINDOW_GUARD
#define SAPPHIRE_WINDOW_GLFW_WINDOW_GUARD

#include <SA/Window/Base/AWindow.hpp>

#include <SA/Core/Support/API/GLFW.hpp>

#if SA_GLFW

/**
*	\file GLFWWindow.hpp
* 
*	\brief GLFW implementation of window interface.
* 
*	\ingroup Window
*	\{
*/


namespace Sa::GLFW
{
	class InputWindowContext;

	/// GLFW Window class implementation.
	class Window : public AWindow
	{
		/// Internal GLFW handle.
		GLFWwindow* mHandle = nullptr;

		/// Saved size.
		Vec2ui mSavedSize;

		/// Saved position.
		Vec2i mSavedPosition;


		/**
		*	\brief Minimized Callback bound to GLFW lib.
		* 
		*	\param[in] _handle		GLFW internal handle.
		*	\param[in] _minimized	GLFW new minimized state.
		*/
		static void MinimizedCallback(GLFWwindow* _handle, int32 _minimized);

		/**
		*	\brief Maximized Callback bound to GLFW lib.
		* 
		*	\param[in] _handle		GLFW internal handle.
		*	\param[in] maximized	GLFW new maximized state.
		*/
		static void MaximizedCallback(GLFWwindow* _handle, int32 _maximized);

		/**
		*	\brief Resize Callback bound to GLFW lib.
		* 
		*	\param[in] _handle		GLFW internal handle.
		*	\param[in] _width		GLFW new window's width.
		*	\param[in] _height		GLFW new window's height.
		*/
		static void ResizeCallback(GLFWwindow* _handle, int32 _width, int32 _height);


		/**
		*	\brief Get this window most used monitor.
		* 
		*	\returns GLFW most used monitor
		*/
		GLFWmonitor* GetCurrentMonitor() const;

	public:
		/// Create Infos alias.
		using CreateInfos = AWindow::CreateInfos;


		/// Bound InputWindowContext from InputSystem.
		InputWindowContext* inputWinContext = nullptr;


		SA_ENGINE_API void SetWindowMode(WindowMode _mode) override final;

		SA_ENGINE_API void Create(const CreateInfos& _infos) override final;
		SA_ENGINE_API void Destroy() override final;

		SA_ENGINE_API AInputWindowContext* GetInputWindowContext() const override final;

		SA_ENGINE_API void Close() override final;
		SA_ENGINE_API bool ShouldClose() const override final;

#if SA_VULKAN

		SA_ENGINE_API Vk::RenderSurface CreateVkRenderSurface(const Vk::RenderInstance& _instance) const override final;

#endif

		/**
		*	\brief \e Getter of GLFW internal handle.
		* 
		*	\returns GLFW internal handle.
		*/
		GLFWwindow* GetHandle() const;
	};
}


/** \} */

#endif

#endif // GUARD
