// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
#if SA_LOGGING

//{ ToString

	template <typename T>
	std::string ToString(const T& _elem) noexcept
	{
		if constexpr(std::is_arithmetic<T>::value)
			return std::to_string(_elem);
		else if constexpr (std::is_enum<T>::value)
			return std::to_string(static_cast<uint32>(_elem));
		else if constexpr (Intl::HM_ToString<T>::value)
			return _elem.ToString();
		else
			return std::string();
	}

	template <typename T>
	std::string ToString(T* _ptr) noexcept
	{
		return "0x" + std::to_string(reinterpret_cast<uint64>(_ptr));
	}


	/// \cond Internal

	template <typename R, typename C, typename... Args>
	std::string ToString(R(C::* _ptr)(Args...)) noexcept
	{
		(void)_ptr;
		return "0x<MemberFunctionPointer>";
	}

	template <typename T>
	std::string ToString(const T* _elems, uint32 _size)
	{
		std::string res = "{ ";

		for (uint32 i = 0; i < _size; ++i)
			res += ToString(_elems[i]) + ", ";

		res[res.size() - 2] = ' ';
		res[res.size() - 1] = '}';

		return res;
	}

	template <typename T>
	std::string ToString(const std::vector<T>& _vec) noexcept
	{
		return ToString(_vec.data(), static_cast<uint32>(_vec.size()));
	}


	template <typename T>
	std::string operator<<(const char* _lhs, const T& _rhs) noexcept
	{
		return ToString(_lhs) + ToString(_rhs);
	}

	template <typename T>
	std::string operator<<(const std::string& _lhs, const T& _rhs) noexcept
	{
		return _lhs + ToString(_rhs);
	}

	/// \endcond

//}

//{ ToWString

	template <typename T>
	std::wstring ToWString(const T& _elem) noexcept
	{
		if constexpr (std::is_arithmetic<T>::value)
			return std::to_wstring(_elem);
		else if constexpr (std::is_enum<T>::value)
			return std::to_wstring(static_cast<uint32>(_elem));
		else if constexpr (Intl::HM_ToWString<T>::value)
			return _elem.ToWString();
		else
			return ToWString(ToString(_elem)); // Try to find any ToString and convert.
	}

	template <typename T>
	std::wstring ToWString(T* _ptr) noexcept
	{
		return L"0x" + std::to_wstring(reinterpret_cast<uint64>(_ptr));
	}


	/// \cond Internal

	template <typename R, typename C, typename... Args>
	std::wstring ToWString(R(C::* _ptr)(Args...)) noexcept
	{
		(void)_ptr;
		return L"0x<MemberFunctionPointer>";
	}

	template <typename T>
	std::wstring ToWString(const T* _elems, uint32 _size)
	{
		std::wstring res = L"{ ";

		for (uint32 i = 0u; i < _size; ++i)
			res += ToWString(_elems[i]) + L", ";

		res[res.size() - 2] = L' ';
		res[res.size() - 1] = L'}';

		return res;
	}

	template <typename T>
	std::wstring ToWString(const std::vector<T>& _vec) noexcept
	{
		return ToWString(_vec.data(), static_cast<uint32>(_vec.size()));
	}


	template <typename T>
	std::wstring operator<<(const char* _lhs, const T& _rhs) noexcept
	{
		return ToWString(_lhs) + ToWString(_rhs);
	}

	template <typename T>
	std::wstring operator<<(const wchar* _lhs, const T& _rhs) noexcept
	{
		return ToWString(_lhs) + ToWString(_rhs);
	}

	template <typename T>
	std::wstring operator<<(const std::wstring& _lhs, const T& _rhs) noexcept
	{
		return _lhs + ToWString(_rhs);
	}

	/// \endcond

//}

#endif
}
