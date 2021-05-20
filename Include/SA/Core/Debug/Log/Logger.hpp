// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOGGER_GUARD
#define SAPPHIRE_CORE_LOGGER_GUARD

#include <vector>
#include <queue>
#include <unordered_map>

#include <mutex>
#include <thread>

#include <SA/Core/Debug/Log/Log.hpp>
#include <SA/Core/Debug/Log/LogChannel.hpp>
#include <SA/Core/Debug/Streams/ILogStream.hpp>

#include <SA/Core/Debug/Exceptions/Exception.hpp>

/**
*	\file Logger.hpp
* 
*	\brief <b>Debug Logger</b> class implementation.
* 
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// Debug Logger type.
	class Logger
	{
		/// Registered output streams.
		std::vector<ILogStream*> mOutStreams;
		std::mutex mStreamMutex;

		std::thread mThread;
		std::queue<const Log*> mLogQueue;
		std::mutex mLogQueueMutex;
		std::atomic<bool> mIsRunning = true;
		std::atomic<uint32> mQueueSize = 0u;


		/// Registered channels.
		std::unordered_map<std::wstring, LogChannel> mChannels;
		std::mutex mChannelMutex;

		bool ShouldLogChannel(const std::wstring& _chanName, LogLevel _level, uint32 _offset = 0u);


		const Log* Pop();

		/**
		*	\brief Output a log into registered streams.
		*
		*	\param[in] _log		Log to output.
		*/
		void Output(const Log& _log);

		/**
		*	\brief Process log.
		*
		*	Log only if both chan and lvl are enabled.
		*	Use SA_LOG as helper call.
		*
		*	\param[in] _log		Log to process.
		*/
		void ProcessLog(const Log& _log);

		/**
		*	\brief Process exception (internal implementation).
		*
		*	Log assertion on success, otherwise ask for throw.
		*	Called by Assert().
		*
		*	\param[in] _exc		exception to process.
		* 
		*	\return Should throw (typed) exception.
		*/
		SA_ENGINE_API bool ProcessAssert(const Exception& _exc);

	public:
		/// Enabled level flags for output.
		Flags<LogLevel, std::atomic<UIntOfSize<sizeof(LogLevel)>>> levelFlags = LogLevel::Default;

		SA_ENGINE_API Logger();
		SA_ENGINE_API ~Logger();


		SA_ENGINE_API LogChannel& GetChannel(const std::wstring& _chanName) noexcept;


		/**
		*	\brief Register a stream to output.
		* 
		*	\param[in] _stream	Stream to register.
		*/
		SA_ENGINE_API void Register(ILogStream& _stream);

		/**
		*	\brief Unregister a stream from output.
		*
		*	\param[in] _stream	Stream to unregister.
		*
		*	\return true on success.
		*/
		SA_ENGINE_API bool Unregister(ILogStream& _stream);


		SA_ENGINE_API void Push(const Log* _log);
		SA_ENGINE_API void Join();


		/**
		*	\brief Process exception.
		*
		*	Log assertion on success, otherwise throw exception.
		*	Use SA_ASSERT as helper call.
		*
		*	\tparam ExcepT		Exception type.
		*	\param[in] _exc		exception to process.
		*/
		template <typename ExcepT>
		void Assert(const ExcepT* _exc);
	};

#endif
}

#include <SA/Core/Debug/Log/Logger.inl>


/** \} */

#endif // GUARD
