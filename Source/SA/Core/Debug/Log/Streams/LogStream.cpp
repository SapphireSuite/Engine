// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/Streams/LogStream.hpp>

namespace Sa
{
#if SA_LOGGING

	LogStream& LogStream::operator<<(const Sa::Log& _log)
	{
		return Output(_log);
	}

#endif
}
