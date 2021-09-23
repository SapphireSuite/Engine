// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Log/LogChannelFilter.hpp>

namespace Sa
{
#if SA_LOGGING

	bool LogChannelFilter::IsChannelEnabled(const std::wstring& _chanName, LogLevel _level, uint32 _offset)
	{
		int32 fIndex = static_cast<int32>(_chanName.find('/', _offset));

		if (fIndex == -1)
		{
			const LogChannel& channel = channels[_chanName];
			return channel.levelFlags & _level;
		}
		else
		{
			const LogChannel& channel = channels[_chanName.substr(0u, fIndex)];

			if (channel.levelFlags & _level)
				return IsChannelEnabled(_chanName, _level, fIndex + 1);

			return false;
		}
	}

#endif
}
