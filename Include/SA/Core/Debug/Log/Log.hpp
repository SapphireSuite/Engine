// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_GUARD
#define SAPPHIRE_CORE_LOG_GUARD

#include <string>

#include <SA/Core/Time/DateTime.hpp>

#include <SA/Core/Debug/Streams/ConsoleLogStream.hpp>
#include <SA/Core/Debug/Streams/FileLogStream.hpp>

/**
*	\file Log.hpp
*
*	\brief \b Log type implementation.
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
	class Log : public LogBase, 
		public IConsoleLog, public IFileLog // Interfaces
	{
	public:
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

		/// Date time.
		DateTime date;

		/**
		*	\brief \e Value Move Constructor.
		*
		*	\param[in] _file		File of the Log.
		*	\param[in] _line		Line of the Log.
		*	\param[in] _function	Function of the Log.
		*	\param[in] _msg			Message of the Log.
		*	\param[in] _level		Level of the Log.
		*	\param[in] _chanName	Channel's name of the Log.
		*	\param[in] _details		Additional details to display.
		*/
		SA_ENGINE_API Log(
			std::wstring&& _file,
			uint32 _line,
			std::string&& _function,
			std::wstring&& _msg = L"Hello, World!",
			LogLevel _level = LogLevel::Normal,
			std::wstring&& _chanName = L"Default",
			std::wstring&& _details = L""
		) noexcept;


		/**
		*	\brief ToWString implementation
		* 
		*	Convert this log to wstring.
		* 
		*	\return this as a wstring.
		*/
		SA_ENGINE_API std::wstring ToWString() const;

		SA_ENGINE_API void Output(ConsoleLogStream& _stream) const override;
		SA_ENGINE_API void Output(FileLogStream& _stream) const override;
	};

#endif
}


/** \} */

#endif // GUARD
