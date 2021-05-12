// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <Core/Debug/Log/Streams/LogConsoleStream.hpp>

namespace Sa
{
#if SA_LOGGING

	/// Global console output mutex: shared among all LogConsoleStream instances.
	std::mutex gCslMutex;

	uint32 GetThemeIndex(LogLevel _lvl)
	{
		unsigned long index = 0u;

#if SA_WIN

		_BitScanForward(&index, static_cast<uint32>(_lvl));

#else

		if (static_cast<uint32>(_lvl) != 0u)
			index = __builtin_ffs(static_cast<uint32>(_lvl)) - 1; // __builtin_ffs returns 1 + index if non zero.

#endif

		return index;
	}


	void LogConsoleStream::SetConsoleColorFromLvl(LogLevel _lvl) const
	{
		mThemeMutex.lock_shared();


		SetConsoleColor(mTheme[GetThemeIndex(_lvl)]);


		mThemeMutex.unlock_shared();
	}

	void LogConsoleStream::SetCslTheme(LogLevel _lvl, uint8 _cslColor) noexcept
	{
		mThemeMutex.lock();


		mTheme[GetThemeIndex(_lvl)] = _cslColor;


		mThemeMutex.unlock();
	}


	LogStream& LogConsoleStream::Output(const Sa::Log& _log)
	{
		gCslMutex.lock();


		SetConsoleColorFromLvl(_log.level);

		std::wcout << _log.ToWString() << std::endl;

		SetConsoleColor(CslColor::Reset);


		gCslMutex.unlock();

		return *this;
	}

#endif
}
