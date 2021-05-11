// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOGGER_GUARD
#define SAPPHIRE_CORE_LOGGER_GUARD

#include <fstream>
#include <mutex>

#include <SA/Core/Debug/Log.hpp>
#include <SA/Core/Debug/LogChannel.hpp>
#include <SA/Core/Debug/Exceptions/Exception.hpp>

namespace Sa
{
#if SA_LOGGING

	class Logger
	{
		std::wfstream mLogFile;

		std::mutex mFileMutex;

		/// Create log and log backup files.
		void CreateLogFile(const std::string& _fileName);

		/**
		*	\brief Output a log.
		*
		*	\param[in] _log		Log to output.
		*/
		void Output(const Sa::Log& _log) noexcept;

	public:
		Flags<LogLevel> levelFlags = LogLevel::Default;


		/// Default constuctor.
		SA_ENGINE_API Logger(const std::string& _fileName = "log") noexcept;

		SA_ENGINE_API ~Logger() noexcept;


		/**
		*	\brief Process log.
		*
		*	Log only if both chan and lvl are enabled.
		*	Use SA_LOG as helper call.
		*
		*	\param[in] _log		Log to process.
		*/
		SA_ENGINE_API void Log(const Sa::Log& _log) noexcept;

		/**
		*	\brief Process exception.
		*
		*	Log assertion on success, otherwise throw exception.
		*	Use SA_ASSERT as helper call.
		*
		*	\param[in] _exception	exception to process.
		*/
		SA_ENGINE_API void Assert(const Exception& _exception);
	};

#endif
}

#endif // GUARD
