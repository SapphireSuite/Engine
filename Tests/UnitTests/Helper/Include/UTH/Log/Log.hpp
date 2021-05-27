// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_LOG_GUARD
#define SAPPHIRE_UTH_LOG_GUARD

#include <UTH/Config.hpp>
#include <UTH/StringToken.hpp>

#include <SA/Core/Debug/Streams/ConsoleLogStream.hpp>
#include <SA/Core/Debug/Streams/FileLogStream.hpp>

/**
*	\file UTH/Log/Log.hpp
* 
*	\brief UTH Base Log implementation.
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
	/// UTH Base Log class.
	class Log : public LogBase,
		public IConsoleLog, public IFileLog // Interfaces
	{
	public:
		/// Tab number to insert after end of line.
		uint32 tabNum = 0u;

		/**
		*	\brief \e Value constructor.
		* 
		*	\param[in] _lvl		Level of the log.
		*/
		Log(LogLevel _lvl = LogLevel::Normal);

		/**
		*	\brief Output this log as a StringToken.
		* 
		*	\return This log as a StringToken.
		*/
		virtual StringToken ToStringToken() const = 0;
		SA_UTH_API void Output(FileLogStream& _stream) const override final;
		SA_UTH_API void Output(ConsoleLogStream& _stream) const override final;
	};
}

/** \} */

#endif // GUARD
