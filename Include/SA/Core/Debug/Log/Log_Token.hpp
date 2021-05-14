// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_TOKEN_GUARD
#define SAPPHIRE_CORE_LOG_TOKEN_GUARD

#include <SA/Core/Types/Char.hpp>

#include <SA/Core/Debug/Log/Log.hpp>

/**
*	\file Log_Token.hpp
*
*	\brief \b Log with user-defined token in string implementation.
*
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// Log with  user-defined token.
	class Log_Token : public Log
	{
	public:
		/**
		*	\brief \e Value Constructor.
		*
		*	\param[in] _file		File of the Log.
		*	\param[in] _line		Line of the Log.
		*	\param[in] _function	Function of the Log.
		*	\param[in] _level		Level of the Log.
		*	\param[in] _chanName	Channel's name of the Log.
		*	\param[in] _details		Additional details to display.
		*/
		SA_ENGINE_API Log_Token(
			const std::wstring& _file,
			uint32 _line,
			const std::string& _function,
			LogLevel _level = LogLevel::Normal,
			const std::wstring& _chanName = L"Default",
			const std::wstring& _details = L""
		) noexcept;

		/**
		*	\brief Add a token to the current message.
		* 
		*	\param[in] _token	Token to add.
		*/
		SA_ENGINE_API void AddToken(wchar _token);

		/// \cond Internal

		template <typename T>
		void AddToken(T _token)
		{
			AddToken(static_cast<wchar>(_token));
		}

		/// \endcond.

		/**
		*	\brief Add a string to current message.
		* 
		*	\param[in] _str		String to append.
		*/
		SA_ENGINE_API void AddString(const std::wstring& _str);


		/**
		*	\brief Parse recorded message for output.
		* 
		*	\param[in] _userData	Pointer to user data to access in callbacks.
		*	\param[in] _onToken		Callback on token encountered while parsing.
		*	\param[in] _onStr		Callback on string encountered while parsing.
		*/
		SA_ENGINE_API void Parse(void* _userData, void (*_onToken)(void*, wchar), void (*_onStr)(void*, const std::wstring&));
	};

#endif
}


/** \} */

#endif // GUARD
