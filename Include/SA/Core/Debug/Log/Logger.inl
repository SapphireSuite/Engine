// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
#if SA_LOGGING

	template <typename ExcepT>
	void Logger::Assert(const ExcepT& _exception)
	{
		if (_exception.level == LogLevel::AssertSuccess)
			Log(_exception); // Simple log.
		else
		{
			// Force output with level in channel.
			Output(_exception);

			throw _exception;
		}
	}

#endif
}
