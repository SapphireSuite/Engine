// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
#if SA_LOGGING

	template <typename LogT>
	void Logger::Push(LogT&& _log)
	{
		mLogQueueMutex.lock();

		mLogQueue.push(new LogT(std::forward<LogT>(_log)));

		mLogQueueMutex.unlock();

		++mQueueSize;
	}

	template <typename ExcepT>
	void Logger::Assert(ExcepT&& _exc)
	{
		if (_exc.level == LogLevel::AssertSuccess)
			Push(std::forward<ExcepT>(_exc)); // Simple log.
		else
		{
			// Force instant output (ignore level and channel).
			Output(_exc);

			throw std::forward<ExcepT>(_exc);
		}
	}

#endif
}
