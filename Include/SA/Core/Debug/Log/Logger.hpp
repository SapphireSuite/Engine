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

		std::thread mThread;
		std::queue<const LogBase*> mLogQueue;
		std::mutex mLogQueueMutex;
		std::atomic<bool> mIsRunning = true;
		std::atomic<uint32> mQueueSize = 0u;


		/// Registered channels.
		std::unordered_map<std::wstring, LogChannel> mChannels;
		std::mutex mChannelMutex;

		bool ShouldLogChannel(const std::wstring& _chanName, LogLevel _level, uint32 _offset = 0u);


		const LogBase* Pop();

		/**
		*	\brief Output a log into registered streams.
		*
		*	\param[in] _log		Log to output.
		*/
		SA_ENGINE_API void Output(const LogBase& _log);

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

		/**
		*	\e Constructor
		*	Create Log thread.
		*/
		SA_ENGINE_API Logger();

		/**
		*	\e Destructor
		*	Join and end Log thread.
		*/
		SA_ENGINE_API ~Logger();


		/**
		*	\brief Get log channel from name.
		* 
		*	\param[in] _chanName	Channel's name.
		* 
		*	\return registered LogChannel.
		*/
		SA_ENGINE_API LogChannel& GetChannel(const std::wstring& _chanName) noexcept;


		/**
		*	\brief Register a stream to output.
		* 
		*	\param[in] _stream	Stream to register.
		*/
		SA_ENGINE_API void Register(LogStreamBase& _stream);

		/**
		*	\brief Unregister a stream from output.
		*
		*	\param[in] _stream	Stream to unregister.
		*
		*	\return true on success.
		*/
		SA_ENGINE_API bool Unregister(LogStreamBase& _stream);


		/**
		*	\brief Push a new log in queue.
		* 
		*	\tparam LogT		Log type.
		*	\param[in] _log		Log to push.
		*/
		template <typename LogT>
		void Push(LogT&& _log);

		/**
		*	\brief Join current queue.
		*	Make this thread wait until log queue is empty.
		*/
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
		void Assert(ExcepT&& _exc);
	};

#endif
}

#include <SA/Core/Debug/Log/Logger.inl>


/** \} */

#endif // GUARD
