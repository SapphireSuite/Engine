// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_TO_WSTRING_GUARD
#define SAPPHIRE_CORE_TO_WSTRING_GUARD

#include <string>
#include <vector>

#include <SA/Config.hpp>
#include <SA/Core/Debug/Config.hpp>

#include <SA/Core/Types/Int.hpp>
#include <SA/Core/Types/Char.hpp>
#include <SA/Core/Types/Variadics/HasMember.hpp>

/**
*	\file ToString.hpp
*
*	\brief \b Definition of Sapphire Engine \b ToString methods.
*
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// \cond Internal

	namespace Intl
	{
		SA_DEFINE_HAS_MEMBER(ToString);
		SA_DEFINE_HAS_MEMBER(ToWString);
	}

	/// \endcond

//{ ToString

	/**
	*	\brief ToString implementation used to print elem.
	*
	*	Define template specialization for simple class custom implementation.
	*
	*	\tparam T			Type of element.
	*	\param[in] _elem	Element to convert to string.
	*
	*	\return	std::string from element converted.
	*/
	template <typename T>
	std::string ToString(const T& _elem) noexcept;

	/**
	*	\brief ToString implementation used to print a pointer.
	*
	*	Define template specialization for simple class custom implementation.
	*
	*	\tparam T			Type of pointer.
	*	\param[in] _ptr		Pointer to convert to string.
	*
	*	\return	std::string from pointer converted.
	*/
	template <typename T>
	std::string ToString(T* _ptr) noexcept;

	/// \cond Internal

	/// ToString spec for tab.
	template <typename T>
	std::string ToString(const T* _elems, uint32 _size);

	/// ToString spec for vector.
	template <typename T>
	std::string ToString(const std::vector<T>& _vec) noexcept;


	/// ToString spec for cstr char*.
	template <>
	SA_ENGINE_API std::string ToString(const char* _cstr) noexcept;

	/// ToString spec for c++ str.
	template <>
	SA_ENGINE_API std::string ToString(const std::string& _str) noexcept;


	/// ToString stream operator for char*.
	template <typename T>
	std::string operator<<(const char* _lhs, const T& _rhs) noexcept;

	/// ToString stream operator for string.
	template <typename T>
	std::string operator<<(const std::string& _lhs, const T& _rhs) noexcept;

	/// \endcond

//}

//{ ToWString

	/**
	*	\brief ToWString implementation used to print elem.
	*
	*	Define template specialization for simple class custom implementation.
	*
	*	\tparam T			Type of element.
	*	\param[in] _elem	Element to convert to string.
	*
	*	\return	std::wstring from element converted.
	*/
	template <typename T>
	std::wstring ToWString(const T& _elem) noexcept;

	/**
	*	\brief ToWString implementation used to print a pointer.
	*
	*	Define template specialization for simple class custom implementation.
	*
	*	\tparam T			Type of pointer.
	*	\param[in] _ptr		Pointer to convert to string.
	*
	*	\return	std::wstring from pointer converted.
	*/
	template <typename T>
	std::wstring ToWString(T* _ptr) noexcept;

	/// \cond Internal

	/// ToWString spec for tab.
	template <typename T>
	std::wstring ToWString(const T* _elems, uint32 _size);

	/// ToWString spec for vector.
	template <typename T>
	std::wstring ToWString(const std::vector<T>& _vec) noexcept;


	/// ToWString spec for cstr char*.
	template <>
	SA_ENGINE_API std::wstring ToWString(const char* _cstr) noexcept;

	/// ToWString spec for cstr wchar*.
	template <>
	SA_ENGINE_API std::wstring ToWString(const wchar* _cwstr) noexcept;

	/// ToWString spec for c++ str.
	template <>
	SA_ENGINE_API std::wstring ToWString(const std::string& _str) noexcept;

	/// ToWString spec for c++ wstr.
	template <>
	SA_ENGINE_API std::wstring ToWString(const std::wstring& _wstr) noexcept;


	/// ToWString stream operator for char*.
	template <typename T>
	std::wstring operator<<(const char* _lhs, const T& _rhs) noexcept;

	/// ToWString stream operator for wchar*.
	template <typename T>
	std::wstring operator<<(const wchar* _lhs, const T& _rhs) noexcept;

	/// ToWString stream operator for wstring.
	template <typename T>
	std::wstring operator<<(const std::wstring& _lhs, const T& _rhs) noexcept;

	/// \endcond

//}

#endif
}


/** \} */

#include <SA/Core/Debug/ToString.inl>

#endif // GUARD
