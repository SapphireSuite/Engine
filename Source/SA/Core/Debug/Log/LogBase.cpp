// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Core/Debug/Log/LogBase.hpp>

namespace Sa
{
#if SA_LOGGING

	LogBase::LogBase(LogLevel _level, std::wstring&& _chanName) :
		level{ _level },
		chanName{ std::move(_chanName) }
	{
	}

#endif
}