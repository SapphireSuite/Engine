// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/Logger.hpp>

#include <Collections/Debug>

namespace Sa
{
#if SA_LOGGING

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


	bool Logger::ShouldLogChannel(const std::wstring& _chanName, LogLevel _level, uint32 _offset)
	{
		int32 fIndex = static_cast<int32>(_chanName.find('/', _offset));

		if (fIndex == -1)
		{
			const LogChannel& channel = mChannels[_chanName];
			return channel.levelFlags & _level;
		}
		else
		{
			const LogChannel& channel = mChannels[_chanName.substr(0u, fIndex)];

			if (channel.levelFlags & _level)
				return ShouldLogChannel(_chanName, _level, fIndex + 1);

			return false;
		}
	}

	LogChannel& Logger::GetChannel(const std::wstring& _chanName) noexcept
	{
		std::lock_guard lk(mChannelMutex);

		return mChannels[_chanName];
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

			bool bShouldLogChan = ShouldLogChannel(_log.chanName, _log.level);

			mChannelMutex.unlock();

			// Channel enabled.
			if(bShouldLogChan)
				Output(_log);
		}

		/**
		*	Decrement after process
		*	Ensure correct Join.
		*	no error because only 1 thread running (mProcessingCount not needed).
		*/
		--mQueueSize;
	}

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

	void Logger::Join(ThreadJoinMode _mode)
	{
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
	}

#endif
}
