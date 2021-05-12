// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOGGER_GUARD
#define SAPPHIRE_CORE_LOGGER_GUARD

#include <vector>

#include <SA/Core/Debug/Log/Log.hpp>
#include <SA/Core/Debug/Log/LogChannel.hpp>
#include <SA/Core/Debug/Log/Streams/LogStream.hpp>

#include <SA/Core/Debug/Exceptions/Exception.hpp>

namespace Sa
{
#if SA_LOGGING

	class Logger
	{
		std::vector<LogStream*> mOutStreams;

		/**
		*	\brief Output a log.
		*
		*	\param[in] _log		Log to output.
		*/
		void Output(const Sa::Log& _log) noexcept;

	public:
		Flags<LogLevel> levelFlags = LogLevel::Default;

		/**
		*	\brief Register a stream to output.
		* 
		*	\param[in] _stream	Stream to register.
		*/
		SA_ENGINE_API void Register(LogStream& _stream);

		/**
		*	\brief Unregister a stream from output.
		*
		*	\param[in] _stream	Stream to unregister.
		*
		*	\return true on success.
		*/
		SA_ENGINE_API bool Unregister(LogStream& _stream);


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
