// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Time/MilliSecond.hpp>

#include <Core/Time/Tick.hpp>
#include <Core/Time/Second.hpp>
#include <Core/Time/Minute.hpp>
#include <Core/Time/Hour.hpp>

namespace Sa
{
	MilliSecond::MilliSecond(float _time) noexcept : mTime{ _time }
	{
	}

	MilliSecond::MilliSecond(uint64 _time) noexcept : mTime{ static_cast<float>(_time) }
	{
	}


	MilliSecond::operator float() const noexcept
	{
		return mTime;
	}

	MilliSecond::operator Tick() const noexcept
	{
		return Tick(mTime * ToTicks);
	}

	MilliSecond::operator Second() const noexcept
	{
		return Second(mTime * ToSeconds);
	}

	MilliSecond::operator Minute() const noexcept
	{
		return Minute(mTime * ToMinutes);
	}

	MilliSecond::operator Hour() const noexcept
	{
		return Hour(mTime * ToHours);
	}


#if SA_LOGGING

	std::string MilliSecond::ToString() const noexcept
	{
		return std::to_string(mTime) + "ms";
	}

#endif


	MilliSecond operator""_ms(uint64 _lit) noexcept
	{
		return MilliSecond(_lit);
	}

	MilliSecond operator""_ms(long double _lit) noexcept
	{
		return MilliSecond(static_cast<float>(_lit));
	}
}
