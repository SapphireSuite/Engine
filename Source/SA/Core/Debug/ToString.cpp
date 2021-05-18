// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/ToString.hpp>

#include <cstring> // strlen.
#include <cstdlib> // mbstowcs (wstring convertion).

namespace Sa
{
#if SA_LOGGING

//{ ToString

	template <>
	std::string ToString(const char& _char) noexcept
	{
		return std::string(1u, _char);
	}

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
	std::wstring ToWString(const char& _char) noexcept
	{
		return std::wstring(1u, _char);
	}

	template <>
	std::wstring ToWString(const char* _cstr) noexcept
	{
		const uint32 length = static_cast<uint32>(strlen(_cstr));

		std::wstring res(length, L' ');

		std::mbstowcs(res.data(), _cstr, length);

		return res;
	}


	template <>
	std::wstring ToWString(const wchar& _char) noexcept
	{
		return std::wstring(1u, _char);
	}

	template <>
	std::wstring ToWString(const wchar* _cwstr) noexcept
	{
		return std::wstring(_cwstr);
	}


	template <>
	std::wstring ToWString(const std::string& _str) noexcept
	{
		std::wstring res(_str.length(), L' ');

		std::mbstowcs(res.data(), _str.c_str(), _str.length());

		return res;
	}

	template <>
	std::wstring ToWString(const std::wstring& _wstr) noexcept
	{
		return _wstr;
	}

//}

#endif
}
