// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Log.hpp>

#include <UTH/Instance.hpp>

namespace Sa::UTH
{
	Log::Log(
		const std::wstring& _file,
		uint32 _line,
		const std::string& _function
	) noexcept :
		Log_Token(_file, _line, _function, LogLevel::Normal, L"UTH")
	{
		mTabNum = Intl::instance.GetGroupNum();
		msg.append(mTabNum, L'\t');
	}

	void Log::EndOfLine()
	{
		msg += L'\n';
		msg.append(mTabNum, L'\t');
	}
}
