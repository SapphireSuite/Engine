// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Log.hpp>

#include <UTH/Instance.hpp>

//#include <UTH/Verbosity.hpp>

namespace Sa::UTH
{
	Log::Log(
		const std::wstring& _file,
		uint32 _line,
		const std::string& _function
	) noexcept :
		Log_Token(_file, _line, _function, LogLevel::Normal, L"UTH")
	{
		//if ((verbosity & Verbosity::GroupStart) | (verbosity & Verbosity::GroupExit))
		{
			mTabNum = Intl::instance.GetGroupNum();
			msg.append(mTabNum, L'\t');
		}
	}

	void Log::EndOfLine()
	{
		msg += L'\n';

		//if ((verbosity & Verbosity::GroupStart) | (verbosity & Verbosity::GroupExit))
			msg.append(mTabNum, L'\t');
	}
}
