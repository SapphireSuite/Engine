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


	void Logger::Register(LogStream& _stream)
	{
		std::lock_guard<std::mutex> lk(mStreamMutex);

		mOutStreams.push_back(&_stream);
	}

	bool Logger::Unregister(LogStream& _stream)
	{
		std::lock_guard<std::mutex> lk(mStreamMutex);

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
		std::lock_guard<std::mutex> lk(mStreamMutex);

		for (auto it = mOutStreams.begin(); it != mOutStreams.end(); ++it)
			(*it)->Output(_log);
	}

	void Logger::ProcessLog(const Log& _log)
	{
		// Level enabled.
		if (levelFlags & _log.level)
			Output(_log);

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
