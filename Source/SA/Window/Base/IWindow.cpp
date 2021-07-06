// Copyright 2020 Sapphire development team. All Rights Reserved.

#include <Window/Base/IWindow.hpp>

#include <Input/Base/IInputSystem.hpp>

namespace Sa
{
	void IWindow::Update()
	{
		GetInputSystem().Update();
	}
}
