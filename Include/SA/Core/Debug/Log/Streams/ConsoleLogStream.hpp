// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_CONSOLE_STREAM_GUARD
#define SAPPHIRE_CORE_LOG_CONSOLE_STREAM_GUARD

#include <shared_mutex>

#include <SA/Core/Debug/ConsoleColor.hpp>

#include <SA/Core/Debug/Log/Streams/LogStream.hpp>

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

	/// Log console stream type.
	class ConsoleLogStream : public LogStream
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

		/// Set console color from log level using theme.
		void SetConsoleColorFromLvl(LogLevel _lvl) const;

	public:
		/**
		*	\brief Set console color mask for loglevel.
		* 
		*	\param[in] _lvl			log level to set new theme color.
		*	\param[in] _cslColor	console color mask from ConsoleColor enum.
		*/
		SA_ENGINE_API void SetConsoleTheme(LogLevel _lvl, uint8 _cslColor) noexcept;

		SA_ENGINE_API LogStream& Output(const Sa::Log& _log) override final;
	};

#endif
}


/** \} */

#endif // GUARD
