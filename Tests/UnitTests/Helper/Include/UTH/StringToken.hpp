// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_STRING_TOKEN_GUARD
#define SAPPHIRE_UTH_STRING_TOKEN_GUARD

#include <string>

#include <SA/Core/Types/Int.hpp>
#include <SA/Core/Types/Char.hpp>

/**
*	\file StringToken.hpp
* 
*	\brief String with in-placed token for future processing.
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
	/// StringToken class.
	class StringToken
	{
	public:
		/// Handled wstring.
		std::wstring handle;

		/**
		*	\brief Append a token of type T.
		* 
		*	\tparam T			Type of token to append.
		*	\param[in] _token	Token value to append.
		*/
		template <typename T>
		void AppendToken(T _token)
		{
			handle += L'\0';
			handle += static_cast<wchar>(_token);
		}

		/**
		*	\brief Append a wstring.
		* 
		*	\param[in] _str		String to append.
		*/
		void AppendString(const std::wstring& _str);

		/**
		*	\brief Append a end of line.
		* 
		*	\param[in] _tabNum	Number of tab to insert after end of line.
		*/
		void EndOfLine(uint32 _tabNum = 0u);

		/**
		*	\brief Parse StringToken and trigger callback on token/string parsing.
		* 
		*	\param[in] _userData	Pointer for user data value.
		*	\param[in] _onToken		Callback on token parsed.
		*	\param[in] _onStr		Callback on string parsed.
		*/
		void Parse(void* _userData, void (*_onToken)(void*, wchar), void (*_onStr)(void*, const std::wstring&)) const;
	};
}


/** \} */

#endif // GUARD
