// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Time/Hour.hpp>

#include <Core/Time/Tick.hpp>
#include <Core/Time/MilliSecond.hpp>
#include <Core/Time/Second.hpp>
#include <Core/Time/Minute.hpp>

namespace Sa
{
	Hour::Hour(float _time) noexcept : mTime{ _time }
	{
	}

	Hour::Hour(uint64 _time) noexcept : mTime{ static_cast<float>(_time) }
	{
	}


	Hour::operator float() const noexcept
	{
		return mTime;
	}

	Hour::operator Tick() const noexcept
	{
		return Tick(mTime * ToTicks);
	}

	Hour::operator MilliSecond() const noexcept
	{
		return MilliSecond(mTime * ToMilliSeconds);
	}

	Hour::operator Second() const noexcept
	{
		return Second(mTime * ToSeconds);
	}

	Hour::operator Minute() const noexcept
	{
		return Minute(mTime * ToMinutes);
	}


	Hour operator""_hr(uint64 _lit) noexcept
	{
		return Hour(_lit);
	}

	Hour operator""_hr(long double _lit) noexcept
	{
		return Hour(static_cast<float>(_lit));
	}
}
