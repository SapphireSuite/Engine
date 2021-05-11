// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Time/Second.hpp>

#include <Core/Time/Tick.hpp>
#include <Core/Time/MilliSecond.hpp>
#include <Core/Time/Minute.hpp>
#include <Core/Time/Hour.hpp>

namespace Sa
{
	Second::Second(float _time) noexcept : mTime{ _time }
	{
	}

	Second::Second(uint64 _time) noexcept : mTime{ static_cast<float>(_time) }
	{
	}


	Second::operator float() const noexcept
	{
		return mTime;
	}

	Second::operator Tick() const noexcept
	{
		return Tick(mTime * ToTicks);
	}

	Second::operator MilliSecond() const noexcept
	{
		return MilliSecond(mTime * ToMilliSeconds);
	}

	Second::operator Minute() const noexcept
	{
		return Minute(mTime * ToMinutes);
	}

	Second::operator Hour() const noexcept
	{
		return Hour(mTime * ToHours);
	}


	Second operator""_sec(uint64 _lit) noexcept
	{
		return Second(_lit);
	}

	Second operator""_sec(long double _lit) noexcept
	{
		return Second(static_cast<float>(_lit));
	}
}
