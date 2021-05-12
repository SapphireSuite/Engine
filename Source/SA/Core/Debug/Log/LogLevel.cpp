// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/LogLevel.hpp>

#include <Core/Algorithms/BitScanForward.hpp>

namespace Sa
{
#if SA_LOGGING

	const wchar* GetLogLevelName(LogLevel _lvl) noexcept
	{
		static constexpr const wchar* names[]{ L"Unknown", L"Normal", L"Infos", L"Warning", L"Error", L"AssertSuccess", L"AssertFailed" };

		return names[BitScanForward(static_cast<uint32>(_lvl)) + 1u];
	}

#endif
}
