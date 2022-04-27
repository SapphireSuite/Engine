// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AWINDOW_GUARD
#define SAPPHIRE_ENGINE_AWINDOW_GUARD

#include <SA/Event/Event.hpp>

#include <SA/Engine/Window/Base/WindowCreateInfos.hpp>

/**
*	\file AWindow.hpp
*	
*	\brief \e Abstract Window class.
* 
*	\ingroup Window
*	\{
*/

namespace Sa
{
	//class AInputWindowContext;

#if SA_VULKAN

	namespace Vk
	{
		class Instance;
		class WindowSurface;
	}

#endif

	/**
	*	\brief Window \e Abstract class
	*/
	class AWindow
	{
	protected:

		/// Current window mode.
		WindowMode mWindowMode = WindowMode::Windowed;

	public:
		/**
		*	Virtual destructor.
		*	Ensure correct polymorphism destruction.
		*/
		virtual ~AWindow() = default;
		
		
		/// Resize window callback event.
		Event<void(Vec2ui)> onResize;


		/// Minimized window callback event.
		Event<void(bool)> onMinimized;

		/// Maximized window callback event.
		Event<void(bool)> onMaximized;


		/// WindowMode change callback event.
		Event<void(WindowMode)> onWindowModeChange;

		/// CursorMode change callback event.
		Event<void(Flags<CursorMode>)> onCursorModeChange;


		/**
		*	\brief \e Getter of window's size.
		* 
		*	\returns current window's size.
		*/
		virtual Vec2ui GetSize() const = 0;

		virtual void SetSize(const Vec2ui& _size) = 0;


		/**
		*	\brief \e Getter of window's position.
		*
		*	\returns current window's position.
		*/
		virtual Vec2ui GetPosition() const = 0;

		virtual void SetPosition(const Vec2ui& _size) = 0;


		/**
		*	\brief \e Getter of window's mode.
		* 
		*	\returns current window's mode.
		*/
		WindowMode GetWindowMode() const;

		/**
		*	\brief \e Setter of window's mode.
		*	Call onWindowModeChange event.
		* 
		*	\param[in] _mode	New window mode.
		*/
		virtual void SetWindowMode(WindowMode _mode) = 0;


		/**
		*	\brief \e Getter of minimized state.
		*
		*	\returns current minimized state.
		*/
		virtual bool IsMinimized() const = 0;

		virtual void Minimize(bool _bMinimized) = 0;


		/**
		*	\brief \e Getter of maximized state.
		*
		*	\returns current maximized state.
		*/
		virtual bool IsMaximized() const = 0;

		virtual void Maximize(bool _bMaximized) = 0;


		/**
		*	\brief \e Getter of window's cursor mode.
		*
		*	\returns current window's cursor mode.
		*/
		virtual Flags<CursorMode> GetCursorMode() const = 0;

		/**
		*	\brief \e Setter of window's cursor mode.
		* 
		*	\param[in] _flags	New cursor mode.
		*/
		virtual void SetCursorMode(Flags<CursorMode> _flags) = 0;


		/**
		*	\brief Create window from infos.
		* 
		*	\param[in] _infos	Creation arguments.
		*/
		virtual void Create(const WindowCreateInfos& _infos) = 0;

		/**
		*	\brief Destroy this window.
		*/
		virtual void Destroy() = 0;


		///**
		//*	\brief \b Abstract \e Getter of InputWindowContext bound from InputSystem.
		//* 
		//*	\returns \b Abstract bound InputWindowContext.
		//*/
		////virtual AInputWindowContext* GetInputWindowContext() const = 0;

		/**
		*	\brief Close current window.
		*/
		virtual void Close() = 0;

		/**
		*	\brief Whether this window should close.
		* 
		*	\returns current closed state.
		*/
		virtual bool ShouldClose() const = 0;


#if SA_VULKAN

		// virtual Vk::WindowSurface CreateVkWindowSurface(const Vk::Instance& _instance) const = 0;
		// virtual void DestroyVkWindowSurface(const Vk::Instance& _instance, Vk::WindowSurface& _surface) const = 0;

#endif
	};
}


/** \} */

#endif // GUARD
