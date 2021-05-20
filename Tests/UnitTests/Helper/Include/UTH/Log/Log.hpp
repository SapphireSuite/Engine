// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_LOG_GUARD
#define SAPPHIRE_UTH_LOG_GUARD

#include <UTH/Config.hpp>
#include <UTH/StringToken.hpp>

#include <SA/Core/Debug/Streams/ConsoleLogStream.hpp>
#include <SA/Core/Debug/Streams/FileLogStream.hpp>

namespace Sa::UTH
{
	class Log : public LogBase,
		public IConsoleLog, public IFileLog // Interfaces
	{
	public:
		uint32 tabNum = 0u;

		Log(LogLevel _lvl = LogLevel::Normal);

		virtual StringToken ToStringToken() const = 0;
		SA_UTH_API void Output(FileLogStream& _stream) const override final;
		SA_UTH_API void Output(ConsoleLogStream& _stream) const override final;
	};
}

#endif // GUARD
