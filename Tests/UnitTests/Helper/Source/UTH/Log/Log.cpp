// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Log/Log.hpp>

#include <UTH/Step.hpp>
#include <UTH/Instance.hpp>

namespace Sa::UTH
{
	Log::Log(LogLevel _lvl) :
		LogBase(_lvl, L"UTH"),
		tabNum { Intl::instance.GetGroupNum() }
	{
	}


	void Log::Output(FileLogStream& _stream) const
	{
		StringToken str = ToStringToken();

		str.Parse(&_stream, nullptr,

			[](void* _userData, const std::wstring& _str)
			{
				FileLogStream& stream = *reinterpret_cast<FileLogStream*>(_userData);

				stream << _str;
			}
		);

		_stream << L"" << std::endl;
	}

	void Log::Output(ConsoleLogStream& _stream) const
	{
		StringToken str = ToStringToken();

		str.Parse(&_stream,

			[](void* _userData, wchar _token)
			{
				(void)_userData;
				cslTheme.SetConsoleColorFromStep(static_cast<Step>(_token));
			},

			[](void* _userData, const std::wstring& _str)
			{
				ConsoleLogStream& stream = *reinterpret_cast<ConsoleLogStream*>(_userData);

				stream << _str;
			}
		);

		cslTheme.SetConsoleColorFromStep(Step::None);

		_stream << L"" << std::endl;
	}
}
