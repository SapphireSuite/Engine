// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_AWINDOW_GUARD
#define SAPPHIRE_WINDOW_AWINDOW_GUARD

#include <SA/Core/Types/Abstract.hpp>
#include <SA/Core/Types/Variadics/Event.hpp>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Window/Base/WindowMode.hpp>

namespace Sa
{
	class AInputWindowContext;

	class AWindow : public Abstract
	{
		bool bMinimized = false;
		bool bMaximized = false;

		Vec2ui mSize;

		WindowMode mMode = WindowMode::Windowed;

	protected:
		void SetMinimized(bool _bIsMinimized);
		void SetMaximized(bool _bIsMaximized);

		void SetSize(const Vec2ui& _size);

	public:
		struct CreateInfos
		{
			Vec2ui dimension = Vec2ui{ 1200u, 800u };
			Vec2ui position;

			WindowMode mode = WindowMode::Windowed;

			std::string name = "Main Window";
		};

		Event<void(bool)> onMinimized;
		Event<void(bool)> onMaximized;

		Event<void(Vec2ui)> onResize;
		Event<void(WindowMode)> onWindowModeChange;


		bool IsMinimized() const;
		bool IsMaximized() const;

		const Vec2ui& GetSize() const;

		WindowMode GetWindowMode() const;
		SA_ENGINE_API virtual void SetWindowMode(WindowMode _mode);

		SA_ENGINE_API virtual void Create(const CreateInfos& _infos);
		virtual void Destroy() = 0;

		virtual AInputWindowContext* GetInputWindowContext() const = 0;

		virtual void Close() = 0;
		virtual bool ShouldClose() const = 0;
	};
}

#endif // GUARD
