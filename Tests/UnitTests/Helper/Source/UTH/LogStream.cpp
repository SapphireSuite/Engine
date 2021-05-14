// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <UTH/LogStream.hpp>

//#include <UTH/Instance.hpp>

#include <SA/Core/Debug/Log/Log_Token.hpp>

namespace Sa::UTH
{
	void LogStream::SetColorFromStep(Step _step) const
	{
		SetConsoleColor(mTheme[static_cast<uint8>(_step)]);
	}

	void LogStream::SetStepColor(Step _step, uint8 _cslColor) noexcept
	{
		mTheme[static_cast<uint8>(_step)] = _cslColor;
	}


	LogStream& LogStream::Output(const Sa::Log& _log)
	{
		Log_Token tkLog = reinterpret_cast<const Log_Token&>(_log);

		tkLog.Parse(
			this,

			[](void* _userData, wchar _token)
			{
				UTH::LogStream& stream = *reinterpret_cast<UTH::LogStream*>(_userData);

				stream.SetColorFromStep(static_cast<Step>(_token));
			},

			[](void* _userData, const std::wstring& _str)
			{
				UTH::LogStream& stream = *reinterpret_cast<UTH::LogStream*>(_userData);

				std::wcout << _str;
				stream.mHandle << _str;
			}
		);

		std::wcout << std::endl;
		mHandle << std::endl;

		return *this;
	}
}
