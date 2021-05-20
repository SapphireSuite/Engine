// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Log/Log.hpp>

#include <UTH/Step.hpp>
#include <UTH/Instance.hpp>

namespace Sa::UTH
{
	uint8 theme[10]
	{
		(uint8)ConsoleColor::Reset,							// None.
		ConsoleColor::Bright_FG | ConsoleColor::Magenta_FG,	// Init.
		ConsoleColor::Bright_FG | ConsoleColor::Magenta_FG,	// Exit.
		ConsoleColor::Bright_FG | ConsoleColor::Yellow_FG,	// Title.
		(uint8)ConsoleColor::Green_FG,						// Success.
		(uint8)ConsoleColor::Red_FG,						// Failure.
		ConsoleColor::Bright_FG | ConsoleColor::Blue_FG,	// Group.
		ConsoleColor::Bright_FG | ConsoleColor::Yellow_FG,	// TestNum.
		(uint8)ConsoleColor::Yellow_FG						// ParamWarning.
	};

	void SetConsoleColorFromStep(Step _step)
	{
		SetConsoleColor(theme[static_cast<uint8>(_step)]);
	}


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
				SetConsoleColorFromStep(static_cast<Step>(_token));
			},

			[](void* _userData, const std::wstring& _str)
			{
				ConsoleLogStream& stream = *reinterpret_cast<ConsoleLogStream*>(_userData);

				stream << _str;
			}
		);

		SetConsoleColorFromStep(Step::None);

		_stream << L"" << std::endl;
	}
}
