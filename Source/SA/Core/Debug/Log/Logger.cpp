// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/Logger.hpp>

namespace Sa
{
#if SA_LOGGING

	void Logger::Register(LogStream& _stream)
	{
		mOutStreams.push_back(&_stream);
	}

	bool Logger::Unregister(LogStream& _stream)
	{
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


	void Logger::Log(const Sa::Log& _log) noexcept
	{
		// Level disabled.
		if (static_cast<bool>(levelFlags & _log.level) == 0)
			return;

		Output(_log);
	}

	void Logger::Output(const Sa::Log& _log) noexcept
	{
		for (auto it = mOutStreams.begin(); it != mOutStreams.end(); ++it)
			(*it)->Output(_log);
	}

#endif
}
