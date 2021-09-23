// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/Logger.hpp>

#include <Core/Debug.hpp>

namespace Sa
{
#if SA_LOGGING

#if __SA_LOG_THREAD

	Logger::Logger()
	{

		// if mQueueSize: dequeue, else yield.
		mThread = std::thread([this]()
		{
			while (mIsRunning)
			{
				// Wait for queue.
				std::this_thread::yield();

				// Dequeue.
				while (mQueueSize)
				{
					const LogBase* log = Pop();

					ProcessLog(*log);

					delete log;
				}
			}
		});

	}

	Logger::~Logger()
	{
		Join();

		mIsRunning = false;

		if (mThread.joinable())
			mThread.join();
	}

#endif

	LogChannel& Logger::GetChannel(const std::wstring& _chanName) noexcept
	{
		std::lock_guard lk(mChannelMutex);

		return mChannelFilter.channels[_chanName];
	}

	void Logger::Register(LogStreamBase& _stream)
	{
		std::lock_guard lk(mStreamMutex);

		mOutStreams.push_back(&_stream);
	}

	bool Logger::Unregister(LogStreamBase& _stream)
	{
		std::lock_guard lk(mStreamMutex);

		for (auto it = mOutStreams.begin(); it != mOutStreams.end(); ++it)
		{
			if (*it == &_stream)
			{
				mOutStreams.erase(it);
				return true;
			}
		}

		return false;
	}


	void Logger::Output(const LogBase& _log)
	{
		std::lock_guard lk(mStreamMutex);

		for (auto it = mOutStreams.begin(); it != mOutStreams.end(); ++it)
			(*it)->Output(_log);
	}

	void Logger::ProcessLog(const LogBase& _log)
	{
		// Level enabled.
		if (levelFlags & _log.level)
		{
			mChannelMutex.lock();

			bool bShouldLogChan = mChannelFilter.IsChannelEnabled(_log.chanName, _log.level);

			mChannelMutex.unlock();

			// Channel enabled.
			if(bShouldLogChan)
				Output(_log);
		}

#if __SA_LOG_THREAD
		/**
		*	Decrement after process
		*	Ensure correct Join.
		*	no error because only 1 thread running (mProcessingCount not needed).
		*/
		--mQueueSize;

#endif
	}

#if __SA_LOG_THREAD

	const LogBase* Logger::Pop()
	{
		mLogQueueMutex.lock();

		const LogBase* log = mLogQueue.front();

		mLogQueue.pop();

		mLogQueueMutex.unlock();

		// Decrement after process.
		//--mQueueSize;

		return log;
	}

#endif


	void Logger::Join(ThreadJoinMode _mode)
	{
#if __SA_LOG_THREAD

		switch (_mode)
		{
			case ThreadJoinMode::Complete:
			{
				// Wait for empty queue (all log processed).
				while (mQueueSize)
					std::this_thread::yield();

				break;
			}
			case ThreadJoinMode::Abandon:
			{
				if (mQueueSize > 1)
					mQueueSize = 1;

				// Wait for empty queue (current log processed).
				while (mQueueSize)
					std::this_thread::yield();

				break;
			}
			default:
			{
				SA_LOG(L"ThreadJoinMode [" << _mode << L"] not supported yet!", Warning, Core);
				break;
			}
		}

#else

		(void)_mode;

#endif
	}

#endif
}
