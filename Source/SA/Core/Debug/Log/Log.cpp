// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/Log.hpp>

#include <Core/Time/Time.hpp>

namespace Sa
{
#if SA_LOGGING

	Log::Log(
		const std::wstring& _file,
		uint32 _line,
		const std::string& _function,
		const std::wstring& _msg,
		LogLevel _level,
		const std::wstring& _chanName,
		const std::wstring& _details
	) noexcept :
		file{ _file },
		line{ _line },
		function{ _function },
		msg{ _msg },
		details{ _details },
		level{ _level },
		chanName{ _chanName },
		date{ Time::Date() }
	{
	}

	std::wstring Log::ToWString() const
	{
		std::wstring str;

		// Output date.
		str += L'[' + std::to_wstring(date.hour) + L':' + std::to_wstring(date.minute) + L':' + std::to_wstring(date.second) + L"] ";

		// Output level and channel.
		str += L'{' + std::wstring(GetLogLevelName(level)) + std::wstring(L" - ") + chanName + L'}';

		// Output location.
		str += L'\t' + file + L':' + std::to_wstring(line) + L" - " + std::wstring(function.begin(), function.end()) + L'\n';

		// Output message.
		str += std::wstring(L"Msg:\t") + msg + L'\n';

		if(!details.empty())
			str += std::wstring(L"Dets:\t") + details + L'\n';

		return str;
	}

#endif
}
