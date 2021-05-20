// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/ILog.hpp>

namespace Sa
{
#if SA_LOGGING

	const LogBase& ILog::GetBase() const
	{
		// Assume this inherit from log base.
		return dynamic_cast<const LogBase&>(*this);
	}

#endif
}