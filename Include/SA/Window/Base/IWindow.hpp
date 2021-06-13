// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_IWINDOW_GUARD
#define SAPPHIRE_WINDOW_IWINDOW_GUARD

#include <SA/Core/Types/Int.hpp>
#include <SA/Core/Types/Interface.hpp>

#include <SA/Input/InputSystem.hpp>

namespace Sa
{
	class IWindow : public Interface
	{
	public:
		InputSystem input;

		virtual void Create(uint32 _width, uint32 _height, const std::string& _name = "Main Window") = 0;
		virtual void Destroy() = 0;

		virtual bool ShouldClose() const = 0;
	};
}

#endif // GUARD
