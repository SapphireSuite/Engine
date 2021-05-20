// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/Logger.hpp>

namespace Sa
{
#if SA_LOGGING

	Logger::Logger()
	{
		// if mQueueSize: dequeue, else yield.
		mThread = std::thread([this]()
		{
			while (mIsRunning || mQueueSize)
			{
				// Dequeue.
				while (mQueueSize)
				{
					const Log* log = Pop();

					ProcessLog(*log);

					delete log;
				}

				// Wait for queue.
				std::this_thread::yield();
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

	void Logger::Register(ILogStream& _stream)
	{
		std::lock_guard lk(mStreamMutex);

		mOutStreams.push_back(&_stream);
	}

	bool Logger::Unregister(ILogStream& _stream)
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


	void Logger::Output(const Log& _log)
	{
		std::lock_guard lk(mStreamMutex);

		for (auto it = mOutStreams.begin(); it != mOutStreams.end(); ++it)
			(*it)->Output(_log);
	}

	void Logger::ProcessLog(const Log& _log)
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

		// Decrement after process (correct Join).
		--mQueueSize;
	}

	bool Logger::ProcessAssert(const Exception& _exc)
	{
		if (_exc.level == LogLevel::AssertSuccess)
		{
			Push(&_exc); // Simple log.

			return false; // Do not throw.
		}
		else
		{
			// Force instant output (ignore level and channel).
			Output(_exc);

			return true; // Ask for throw.
		}
	}


	const Log* Logger::Pop()
	{
		mLogQueueMutex.lock();

		const Log* log = mLogQueue.front();

		mLogQueue.pop();

		mLogQueueMutex.unlock();

		// Decrement after process (correct Join).
		//--mQueueSize;

		return log;
	}

	void Logger::Push(const Log* _log)
	{
		mLogQueueMutex.lock();

		mLogQueue.push(_log);

		mLogQueueMutex.unlock();

		++mQueueSize;
	}

	void Logger::Join()
	{
		// Wait for empty queue (all log processed).
		while (mQueueSize)
			std::this_thread::yield();
	}

#endif
}
