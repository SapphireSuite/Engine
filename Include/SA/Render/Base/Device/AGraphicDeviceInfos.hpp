// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_AGRAPHIC_DEVICE_INFOS_GUARD
#define SAPPHIRE_RENDER_AGRAPHIC_DEVICE_INFOS_GUARD

#include <string>

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	struct AGraphicDeviceInfos
	{
		uint32 ID = uint32(-1);
		
		std::string name;

		uint32 score = 0;

		static bool SortScore(const AGraphicDeviceInfos& _lhs, const AGraphicDeviceInfos& _rhs) noexcept;
	};
}

#endif // GUARD