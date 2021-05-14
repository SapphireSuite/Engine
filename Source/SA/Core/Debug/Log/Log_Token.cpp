// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/Log_Token.hpp>

#include <Core/Types/Int.hpp>

namespace Sa
{
#if SA_LOGGING

	Log_Token::Log_Token(
		const std::wstring& _file,
		uint32 _line,
		const std::string& _function,
		LogLevel _level,
		const std::wstring& _chanName,
		const std::wstring& _details
	) noexcept :
		Log(_file, _line, _function, L"", _level, _chanName, _details)
	{
	}


	void Log_Token::AddToken(wchar _token)
	{
		msg += L'\0';
		msg += _token;
	}

	void Log_Token::AddString(const std::wstring& _str)
	{
		msg += _str;
	}


	void Log_Token::Parse(void* _userData, void (*_onToken)(void*, wchar), void (*_onStr)(void*, const std::wstring&))
	{
		uint64 offset = 0u;
		uint64 index = 0u;

		while (true)
		{
			index = msg.find_first_of(L'\0', offset);

			if (_onStr)
				_onStr(_userData, msg.substr(offset, index - offset));

			if (index == uint64(-1))
				break;

			if (_onToken)
				_onToken(_userData, msg[index + 1]);

			offset = index + 2;
		}
	}

#endif
}
