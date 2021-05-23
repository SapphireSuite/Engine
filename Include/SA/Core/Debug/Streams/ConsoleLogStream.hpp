// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_CONSOLE_STREAM_GUARD
#define SAPPHIRE_CORE_LOG_CONSOLE_STREAM_GUARD

#include <shared_mutex>

#include <SA/Core/Debug/ConsoleColor.hpp>

#include <SA/Core/Debug/Log/ILog.hpp>
#include <SA/Core/Debug/Log/LogLevel.hpp>
#include <SA/Core/Debug/Streams/LogStreamBase.hpp>

/**
*	\file ConsoleLogStream.hpp
*
*	\brief Log <b>console stream</b> type implementation.
*
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

//{ ConsoleLogStream

	class IConsoleLog;

	/// Log console stream type.
	class ConsoleLogStream : public LogStreamBaseT<ConsoleLogStream, IConsoleLog>
	{
		/// Console color theme by LogLevel.
		uint8 mTheme[6]
		{
			CslColor::Reset | CslColor::Bright_FG,		// Normal.
			CslColor::Blue_FG | CslColor::Bright_FG,	// Infos.
			(uint8)CslColor::Yellow_FG,					// Warning.
			CslColor::Red_FG | CslColor::Bright_FG,		// Error.
			CslColor::Green_FG | CslColor::Bright_FG,	// AssertSuccessColor.
			CslColor::Magenta_FG | CslColor::Bright_FG,	// AssertFailureColor.
		};

		/// Theme access mutex.
		mutable std::shared_mutex mThemeMutex;

	public:
		/**
		*	\brief Set console color from log level using theme.
		* 
		*	\param[in] _lvl		LogLevel to use for theme.
		*/
		void SetConsoleColorFromLvl(LogLevel _lvl) const;

		/**
		*	\brief Set console color mask for loglevel.
		* 
		*	\param[in] _lvl			log level to set new theme color.
		*	\param[in] _cslColor	console color mask from ConsoleColor enum.
		*/
		SA_ENGINE_API void SetConsoleTheme(LogLevel _lvl, uint8 _cslColor) noexcept;


		/**
		*	\brief Output wstring into the stream.
		* 
		*	\param[in] _str		String to output.
		* 
		*	\return handled std::wostream.
		*/
		SA_ENGINE_API std::wostream& operator<<(const std::wstring& _str);
	};

//}

//{ IConsoleLog

	/// Console Log interface implementation.
	class IConsoleLog : public ILogT<ConsoleLogStream>
	{
	};

//}

#endif
}


/** \} */

#endif // GUARD
