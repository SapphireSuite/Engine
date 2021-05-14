// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_TOKEN_GUARD
#define SAPPHIRE_CORE_LOG_TOKEN_GUARD

#include <SA/Core/Types/Char.hpp>

#include <SA/Core/Debug/Log/Log.hpp>

namespace Sa
{
#if SA_LOGGING

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

		SA_ENGINE_API void AddToken(wchar _token);

		template <typename T>
		void AddToken(T _token)
		{
			AddToken(static_cast<wchar>(_token));
		}

		SA_ENGINE_API void AddString(const std::wstring& _str);

		SA_ENGINE_API void Parse(void* _userData, void (*_onToken)(void*, wchar), void (*_onStr)(void*, const std::wstring&));
	};

#endif
}

#endif // GUARD
