// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_STRING_TOKEN_GUARD
#define SAPPHIRE_UTH_STRING_TOKEN_GUARD

#include <string>

#include <SA/Core/Types/Int.hpp>
#include <SA/Core/Types/Char.hpp>

namespace Sa::UTH
{
	class StringToken
	{
	public:
		std::wstring handle;

		template <typename T>
		void AppendToken(T _token)
		{
			handle += L'\0';
			handle += static_cast<wchar>(_token);
		}

		void AppendString(const std::wstring& _str);

		void EndOfLine(uint32 _tabNum = 0u);

		void Parse(void* _userData, void (*_onToken)(void*, wchar), void (*_onStr)(void*, const std::wstring&)) const;
	};
}

#endif // GUARD
