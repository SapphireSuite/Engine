// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Core/Debug/Streams/ILogStream.hpp>

namespace Sa
{
#if SA_LOGGING

	ILogStream& ILogStream::operator<<(const Sa::ILog& _log)
	{
		return Output(_log);
	}

#endif
}
