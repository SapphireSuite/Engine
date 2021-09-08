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
#include <SA/Core/Debug/Streams/LogStreamBase.hpp>

#include <SA/Core/Debug/Exceptions/Exception.hpp>

#include <SA/Core/Thread/Queue/ThreadJoinMode.hpp>

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
		std::vector<LogStreamBase*> mOutStreams;
		std::mutex mStreamMutex;

#if __SA_LOG_THREAD

		std::thread mThread;
		std::queue<const LogBase*> mLogQueue;
		std::mutex mLogQueueMutex;
		std::atomic<bool> mIsRunning = true;
		std::atomic<uint32> mQueueSize = 0u;

#endif

		/// Registered channels.
		std::unordered_map<std::wstring, LogChannel> mChannels;
		std::mutex mChannelMutex;

		bool ShouldLogChannel(const std::wstring& _chanName, LogLevel _level, uint32 _offset = 0u);

#if __SA_LOG_THREAD

		const LogBase* Pop();

#endif

		/**
		*	\brief Output a log into registered streams.
		*
		*	\param[in] _log		Log to output.
		*/
		void Output(const LogBase& _log);

		/**
		*	\brief Process log.
		*
		*	Log only if both chan and lvl are enabled.
		*	Use SA_LOG as helper call.
		*
		*	\param[in] _log		Log to process.
		*/
		void ProcessLog(const LogBase& _log);

	public:
		/// Enabled level flags for output.
		Flags<LogLevel, std::atomic<UIntOfSize<sizeof(LogLevel)>>> levelFlags = LogLevel::Default;


#if __SA_LOG_THREAD

		/**
		*	\e Constructor
		*	Create Log thread.
		*/
		Logger();

		/**
		*	\e Destructor
		*	Join and end Log thread.
		*/
		~Logger();

#endif


		/**
		*	\brief Get log channel from name.
		* 
		*	\param[in] _chanName	Channel's name.
		* 
		*	\return registered LogChannel.
		*/
		LogChannel& GetChannel(const std::wstring& _chanName) noexcept;


		/**
		*	\brief Register a stream to output.
		* 
		*	\param[in] _stream	Stream to register.
		*/
		void Register(LogStreamBase& _stream);

		/**
		*	\brief Unregister a stream from output.
		*
		*	\param[in] _stream	Stream to unregister.
		*
		*	\return true on success.
		*/
		bool Unregister(LogStreamBase& _stream);


		/**
		*	\brief Push a new log in queue.
		* 
		*	\tparam LogT		Log type.
		*	\param[in] _log		Log to push.
		*/
		template <typename LogT>
		void Push(LogT&& _log);


		/**
		*	\brief Join current queue. Only if __SA_LOG_THREAD = 1.
		* 
		*	\param[in] _mode	Queue join mode.
		*/
		void Join(ThreadJoinMode _mode = ThreadJoinMode::Complete);


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
		void Assert(ExcepT&& _exc);
	};

#endif
}

#include <SA/Core/Debug/Log/Logger.inl>


/** \} */

#endif // GUARD
