// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <UTH/Log.hpp>
#include <UTH/LogStream.hpp>

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
		const Log& uthLog = reinterpret_cast<const Sa::UTH::Log&>(_log);

		uthLog.Parse(
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

		// Ensure reset.
		SetColorFromStep(Step::None);

		std::wcout << std::endl;
		mHandle << std::endl;

		return *this;
	}
}
