// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/Log.hpp>
#include <Core/Debug/ToString.hpp>

#include <Core/Time/Time.hpp>

namespace Sa
{
#if SA_LOGGING

	Log::Log(
		std::wstring&& _file,
		uint32 _line,
		std::string&& _function,
		std::wstring&& _msg,
		LogLevel _level,
		std::wstring&& _chanName,
		std::wstring&& _details
	) noexcept :
		LogBase(_level, std::move(_chanName)),
		file{ std::move(_file) },
		line{ _line },
		function{ std::move(_function) },
		msg{ std::move(_msg) },
		details{ std::move(_details) },
		date{ Time::Date() }
	{
	}


	std::wstring Log::ToWString() const
	{
		std::wstring str;

		// Output date.
		str << L'[' << Sa::ToWString(date.hour) << L':' << Sa::ToWString(date.minute) << L':' << Sa::ToWString(date.second) << L"] ";

		// Output level and channel.
		str << L'{' << Sa::ToWString(GetLogLevelName(level)) << Sa::ToWString(L" - ") << chanName << L'}';

		// Output location.
		str << L'\t' << file << L':' << Sa::ToWString(line) << L" - " << Sa::ToWString(function) << L'\n';

		// Output message.
		str << std::wstring(L"Msg:\t") << msg << L'\n';

		if(!details.empty())
			str << std::wstring(L"Dets:\t") << details << L'\n';

		return str;
	}

#endif
}
