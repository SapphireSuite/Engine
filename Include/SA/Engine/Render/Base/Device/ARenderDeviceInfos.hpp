// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_DEVICE_INFOS_GUARD
#define SAPPHIRE_ENGINE_ARENDER_DEVICE_INFOS_GUARD

#include <string>
#include <cstdint>

namespace Sa
{
	class ARenderDeviceInfos
	{
	public:
	    /**
		*	Virtual destructor.
		*	Ensure correct polymorphism destruction.
		*/
		virtual ~ARenderDeviceInfos() = default;

		virtual uint32_t GetID() const noexcept = 0;
		virtual std::string GetName() const noexcept = 0;

		uint32_t score = 0;

		inline static bool SortScore(const ARenderDeviceInfos& _lhs, const ARenderDeviceInfos& _rhs) noexcept
		{
			return _lhs.score < _rhs.score;
		}
	};	
}


#endif // GUARD
