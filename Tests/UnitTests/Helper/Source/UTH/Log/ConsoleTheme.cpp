// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Log/ConsoleTheme.hpp>

namespace Sa::UTH
{
	void ConsoleTheme::SetConsoleColorFromStep(Step _step) const
	{
		SetConsoleColor(mTheme[static_cast<uint8>(_step)]);
	}
}
