// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_AWINDOW_GUARD
#define SAPPHIRE_WINDOW_AWINDOW_GUARD

#include <SA/Core/Types/Abstract.hpp>
#include <SA/Core/Types/Variadics/Event.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Window/Base/WindowMode.hpp>
#include <SA/Window/Base/CursorMode.hpp>

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
	class AInputWindowContext;

	namespace Vk
	{
		class RenderInstance;
		class RenderSurface;
	}


	/**
	*	\brief Window \e Abstract class
	*/
	class AWindow : public Abstract
	{
		bool bMinimized = false;
		bool bMaximized = false;

		/// Current size (dimension).
		Vec2ui mSize;

		/// Current mode.
		WindowMode mMode = WindowMode::Windowed;

	protected:

		/**
		*	\brief Set Minimized state.
		*	Call onMinimized event.
		* 
		*	\param[in] _bIsMinimized	New minimized state.
		*/
		void SetMinimized(bool _bIsMinimized);

		/**
		*	\brief Set Maximized state.
		*	Call onMaximized event.
		* 
		*	\param[in] _bIsMaximized	New maximized state.
		*/
		void SetMaximized(bool _bIsMaximized);


		/**
		*	\brief Set window size.
		*	Call onResize event.
		* 
		*	\param[in] _size	New size.
		*/
		void SetSize(const Vec2ui& _size);

	public:
		/// Create infos struct
		struct CreateInfos
		{
			/// Window size.
			Vec2ui dimension = Vec2ui{ 1200u, 800u };

			/// Window position on screen.
			Vec2ui position;

			/// Window mode.
			WindowMode mode = WindowMode::Windowed;

			Flags<CursorMode> cursorFlags;

			/// Window name.
			std::string name = "Main Window";
		};

		/// Minimized callback event.
		Event<void(bool)> onMinimized;

		/// Maximized callback event.
		Event<void(bool)> onMaximized;

		/// Resize window callback event.
		Event<void(Vec2ui)> onResize;

		/// WindowMode change callback event.
		Event<void(WindowMode)> onWindowModeChange;


		/**
		*	\brief \e Getter of minimized state.
		* 
		*	\returns current minimized state.
		*/
		bool IsMinimized() const;

		/**
		*	\brief \e Getter of maximized state.
		* 
		*	\returns current maximized state.
		*/
		bool IsMaximized() const;

		/**
		*	\brief \e Getter of window's size.
		* 
		*	\returns current window's size.
		*/
		const Vec2ui& GetSize() const;

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
		virtual void SetWindowMode(WindowMode _mode);

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
		virtual void Create(const CreateInfos& _infos);

		/**
		*	\brief Destroy this window.
		*/
		virtual void Destroy() = 0;


		/**
		*	\brief \b Abstract \e Getter of InputWindowContext bound from InputSystem.
		* 
		*	\returns \b Abstract bound InputWindowContext.
		*/
		virtual AInputWindowContext* GetInputWindowContext() const = 0;

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

		virtual Vk::RenderSurface CreateVkRenderSurface(const Vk::RenderInstance& _instance) const = 0;

#endif
	};
}


/** \} */

#endif // GUARD
