// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/LogLevel.hpp>

#include <Core/Debug/Debug.hpp>

#include <Core/Algorithms/BitScanForward.hpp>

namespace Sa
{
#if SA_LOGGING

	const wchar* GetLogLevelName(LogLevel _lvl) noexcept
	{
		static constexpr const wchar* names[]{ L"Unknown", L"Normal", L"Infos", L"Warning", L"Error", L"AssertSuccess", L"AssertFailed" };

		return names[BitScanForward(static_cast<uint32>(_lvl)) + 1u];
	}


	RAII<LogLevel>::RAII(LogLevel _lvl, bool _bJoinOnEnd) noexcept :
		mHandle{ _lvl },
		bJoinOnEnd{ _bJoinOnEnd }
	{
		Debug::logger.levelFlags.Remove(mHandle);
	}

	RAII<LogLevel>::~RAII() noexcept
	{
		if (bJoinOnEnd)
			Debug::logger.Join();

		Debug::logger.levelFlags.Add(mHandle);
	}

#endif
}
