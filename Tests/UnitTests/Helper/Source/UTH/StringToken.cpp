// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/StringToken.hpp>

namespace Sa::UTH
{
	void StringToken::AppendString(const std::wstring& _str)
	{
		handle += _str;
	}

	void StringToken::EndOfLine(uint32 _tabNum)
	{
		handle += '\n';

		if (_tabNum)
			handle += std::wstring(_tabNum, '\t');
	}


	void StringToken::Parse(void* _userData, void (*_onToken)(void*, wchar), void (*_onStr)(void*, const std::wstring&)) const
	{
		uint64 offset = 0u;
		uint64 index = 0u;

		while (true)
		{
			index = handle.find_first_of(L'\0', offset);

			if (_onStr)
				_onStr(_userData, handle.substr(offset, index - offset));

			if (index == uint64(-1))
				break;

			if (_onToken)
				_onToken(_userData, handle[index + 1]);

			offset = index + 2;
		}
	}
}
