// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
#if SA_LOGGING

	template <typename ExcepT>
	void Logger::Assert(const ExcepT& _exception)
	{
		if(Assert_Impl(_exception))
			throw _exception;
	}

#endif
}
