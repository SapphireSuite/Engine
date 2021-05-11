// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/ToString.hpp>

#include <cstring> // strlen.

namespace Sa
{
#if SA_LOGGING

//{ ToString

	template <>
	std::string ToString(const char* _cstr) noexcept
	{
		return std::string(_cstr);
	}

	template <>
	std::string ToString(const std::string& _str) noexcept
	{
		return _str;
	}

//}

//{ ToWString

	template <>
	std::wstring ToWString(const char* _cstr) noexcept
	{
		return std::wstring(_cstr, _cstr + strlen(_cstr));
	}

	template <>
	std::wstring ToWString(const wchar* _cwstr) noexcept
	{
		return std::wstring(_cwstr);
	}

	template <>
	std::wstring ToWString(const std::string& _str) noexcept
	{
		return std::wstring(_str.begin(), _str.end());
	}

	template <>
	std::wstring ToWString(const std::wstring& _wstr) noexcept
	{
		return _wstr;
	}

//}

#endif
}
