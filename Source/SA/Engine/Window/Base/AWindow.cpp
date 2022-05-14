// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Window/Base/AWindow.hpp>

namespace SA
{
	WindowMode AWindow::GetWindowMode() const
	{
		return mWindowMode;
	}


	void AWindow::Create(const WindowCreateInfos& _infos)
	{
		(void)_infos;
		
		HardwareInterface::Create();
	}
}
