// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_LOG_STREAM_GUARD
#define SAPPHIRE_UTH_LOG_STREAM_GUARD

#include <UTH/Config.hpp>

#include <UTH/Step.hpp>

#include <SA/Core/Debug/ConsoleColor.hpp>
#include <SA/Core/Debug/Log/Streams/FileLogStream.hpp>

namespace Sa::UTH
{
	class LogStream : public FileLogStream
	{
		uint8 mTheme[10]
		{
			(uint8)ConsoleColor::Reset,							// None.
			ConsoleColor::Bright_FG | ConsoleColor::Magenta_FG,	// Init.
			ConsoleColor::Bright_FG | ConsoleColor::Magenta_FG,	// Exit.
			ConsoleColor::Bright_FG | ConsoleColor::Yellow_FG,	// Title.
			(uint8)ConsoleColor::Green_FG,						// Success.
			(uint8)ConsoleColor::Red_FG,						// Failure.
			ConsoleColor::Bright_FG | ConsoleColor::Blue_FG,	// GroupBegin.
			ConsoleColor::Bright_FG | ConsoleColor::Blue_FG,	// GroupEnd.
			ConsoleColor::Bright_FG | ConsoleColor::Yellow_FG,	// TestNum.
			(uint8)ConsoleColor::Yellow_FG						// ParamWarning.
		};

		/// Set console color from step using theme.
		void SetColorFromStep(Step _step) const;

	public:
		using FileLogStream::FileLogStream;

		/**
		*	\brief Set console color mask for step.
		*
		*	\param[in] _step		step to set new theme color.
		*	\param[in] _cslColor	console color mask from ConsoleColor enum.
		*/
		SA_UTH_API void SetStepColor(Step _step, uint8 _cslColor) noexcept;

		LogStream& Output(const Sa::Log& _log) override final;
	};
}

#endif // GUARD
