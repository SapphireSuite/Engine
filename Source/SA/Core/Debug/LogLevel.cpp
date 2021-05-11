// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/LogLevel.hpp>

namespace Sa
{
#if SA_LOGGING

	const wchar* GetLogLevelName(LogLevel _lvl) noexcept
	{
		switch (_lvl)
		{
			case LogLevel::Normal:
				return L"Normal";
			case LogLevel::Infos:
				return L"Infos";
			case LogLevel::Warning:
				return L"Warning";
			case LogLevel::Error:
				return L"Error";
			case LogLevel::AssertSuccess:
				return L"AssertSuccess";
			case LogLevel::AssertFailed:
				return L"AssertFailed";
			default:
				return L"Unknown";
		}
	}

#endif
}
