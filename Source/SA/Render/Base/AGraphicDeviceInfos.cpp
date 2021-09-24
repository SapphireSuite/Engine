// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Device/AGraphicDeviceInfos.hpp>

namespace Sa
{
	bool AGraphicDeviceInfos::SortScore(const AGraphicDeviceInfos& _lhs, const AGraphicDeviceInfos& _rhs) noexcept
	{
		return _lhs.score < _rhs.score;
	}
}
