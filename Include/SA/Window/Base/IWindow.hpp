// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_IWINDOW_GUARD
#define SAPPHIRE_WINDOW_IWINDOW_GUARD

#include <SA/Core/Types/Int.hpp>
#include <SA/Core/Types/Interface.hpp>

#include <SA/Maths/Space/Vector2.hpp>

namespace Sa
{
	class IInputSystem;

	class IWindow : public Interface
	{
	protected:
		Vec2ui mSize;

	public:
		const Vec2ui& GetSize() const;

		SA_ENGINE_API virtual void Create(uint32 _width, uint32 _height, const std::string& _name = "Main Window");
		virtual void Destroy() = 0;

		virtual IInputSystem& GetInputSystem() = 0;

		virtual void Close() = 0;
		virtual bool ShouldClose() const = 0;

		SA_ENGINE_API virtual void Update();
	};
}

#endif // GUARD
