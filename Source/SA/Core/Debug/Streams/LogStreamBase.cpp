// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Core/Debug/Streams/LogStreamBase.hpp>

namespace Sa
{
#if SA_LOGGING

	LogStreamBase& LogStreamBase::operator<<(const LogBase& _log)
	{
		return Output(_log);
	}

#endif
}
