// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/LogLevel.hpp>

#include <Core/Support/Intrinsics.hpp>

namespace Sa
{
#if SA_LOGGING

	const wchar* GetLogLevelName(LogLevel _lvl) noexcept
	{
		static constexpr const wchar* names[]{ L"Unknown", L"Normal", L"Infos", L"Warning", L"Error", L"AssertSuccess", L"AssertFailed" };

		unsigned long index = 0u;

#if SA_WIN

		if (_BitScanForward(&index, static_cast<uint32>(_lvl)))
			++index;
#else

		index = __builtin_ffs(static_cast<uint32>(_lvl));

#endif
		return names[index];
	}

#endif
}
