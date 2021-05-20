// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <Core/Algorithms/BitScanForward.hpp>

#include <Core/Debug/Streams/ConsoleLogStream.hpp>

namespace Sa
{
#if SA_LOGGING

//{ ConsoleLogStream

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

	std::wostream& ConsoleLogStream::operator<<(const std::wstring& _str)
	{
		return std::wcout << _str;
	}

//}

//{ IConsoleLog

	void IConsoleLog::Output(ConsoleLogStream& _stream) const
	{
		_stream.SetConsoleColorFromLvl(GetBase().level);

		ILogT<ConsoleLogStream>::Output(_stream);

		Sa::SetConsoleColor(CslColor::Reset);
	}

//}

#endif
}
