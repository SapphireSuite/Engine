// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_GUARD
#define SAPPHIRE_CORE_LOG_GUARD

#include <string>

#include <SA/Core/Time/DateTime.hpp>

#include <SA/Core/Debug/LogLevel.hpp>

/**
*	\file Log.hpp
*
*	\brief Sapphire Engine Log class.
*
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/**
	*	\brief Sapphire Engine Log class.
	*
	*	Contains log infos.
	*/
	struct Log
	{
		/// File name.
		std::wstring file;

		/// Line number.
		uint32 line = 0u;

		/// Function name.
		std::string function;

		/// User string message.
		std::wstring msg = L"Hello, World!";

		/// Additional details string.
		std::wstring details;

		/// Output level.
		LogLevel level = LogLevel::Normal;

		/// Output channel name.
		std::wstring chanName = L"Default";

		/// Date time.
		DateTime date;

		/**
		*	\brief \e Value Constructor.
		*
		*	\param[in] _file		File of the Log.
		*	\param[in] _function	Function of the Log.
		*	\param[in] _line		Line of the Log.
		*	\param[in] _msg			Message of the Log.
		*	\param[in] _level		Level of the Log.
		*	\param[in] _chanName	Channel's name of the Log.
		*/
		SA_ENGINE_API Log(
			const std::wstring& _file,
			uint32 _line,
			const std::string& _function,
			const std::wstring& _msg = L"Hello, World!",
			LogLevel _level = LogLevel::Normal,
			const std::wstring& _chanName = L"Default",
			const std::wstring& _details = L""
		) noexcept;

		/// Convert this log to wstring.
		SA_ENGINE_API virtual std::wstring ToWString() const noexcept;
	};

#endif
}


/** \} */

#endif // GUARD
