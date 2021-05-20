// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <Core/Algorithms/BitScanForward.hpp>

#include <Core/Debug/Log/Streams/ConsoleLogStream.hpp>

namespace Sa
{
#if SA_LOGGING

	void ConsoleLogStream::SetConsoleColorFromLvl(LogLevel _lvl) const
	{
		mThemeMutex.lock_shared();


		SetConsoleColor(mTheme[BitScanForward(static_cast<uint32>(_lvl))]);


		mThemeMutex.unlock_shared();
	}

	void ConsoleLogStream::SetConsoleTheme(LogLevel _lvl, uint8 _cslColor) noexcept
	{
		mThemeMutex.lock();


		mTheme[BitScanForward(static_cast<uint32>(_lvl))] = _cslColor;


		mThemeMutex.unlock();
	}


	LogStream& ConsoleLogStream::Output(const Sa::Log& _log)
	{
		SetConsoleColorFromLvl(_log.level);

		std::wcout << _log.ToWString() << std::endl;

		SetConsoleColor(CslColor::Reset);

		return *this;
	}

#endif
}
