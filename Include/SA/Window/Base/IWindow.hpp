// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_IWINDOW_GUARD
#define SAPPHIRE_WINDOW_IWINDOW_GUARD

#include <SA/Core/Types/Interface.hpp>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Core/Types/Variadics/Event.hpp>

namespace Sa
{
	class IInputSystem;

	class IWindow : public Interface
	{
		Vec2ui mSize;
		bool bMinimized = false;

	protected:
		void SetSize(const Vec2ui& _size);
		void SetMinimized(bool _bIsMinimized);

	public:
		Event<void(Vec2ui)> onResize;
		Event<void(bool)> onMinimized;

		const Vec2ui& GetSize() const;
		bool IsMinimized() const;

		SA_ENGINE_API virtual void Create(uint32 _width, uint32 _height, const std::string& _name = "Main Window");
		virtual void Destroy() = 0;

		virtual IInputSystem& GetInputSystem() = 0;

		virtual void Close() = 0;
		virtual bool ShouldClose() const = 0;

		SA_ENGINE_API virtual void Update();
	};
}

#endif // GUARD
