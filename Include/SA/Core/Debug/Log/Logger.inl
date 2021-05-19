// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
#if SA_LOGGING

	template <typename ExcepT>
	void Logger::Assert(const ExcepT* _exc)
	{
		if(ProcessAssert(*_exc))
			throw *_exc;
	}

#endif
}
