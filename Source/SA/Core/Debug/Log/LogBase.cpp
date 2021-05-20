// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Core/Debug/Log/LogBase.hpp>

namespace Sa
{
	LogBase::LogBase(LogLevel _level, const std::wstring& _chanName) :
		level{ _level },
		chanName{ _chanName }
	{
	}
}
