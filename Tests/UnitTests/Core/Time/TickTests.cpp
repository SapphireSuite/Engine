// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Collections/Time>
using namespace Sa;

namespace Sa::Tick_UT
{
	void Constants()
	{
		static_assert(Tick::ToMilliSeconds == 1.0f / MilliSecond::ToTicks, "Tick::ToMilliSeconds != 1 / MilliSecond::ToTicks!");
		static_assert(Tick::ToSeconds == 1.0f / Second::ToTicks, "Tick::ToSeconds != 1 / Second::ToTicks!");
		static_assert(Tick::ToMinutes == 1.0f / Minute::ToTicks, "Tick::ToMinutes != 1 / Minute::ToTicks!");
		static_assert(Tick::ToHours == 1.0f / Hour::ToTicks, "Tick::ToHours != 1 / Hour::ToTicks!");
	}

	void Constructors()
	{
		const Tick t1 = 2.5f;
		SA_UTH_EQ(static_cast<float>(t1), 2.5f);

		const Tick t2 = 4000_ui64;
		SA_UTH_EQ(static_cast<uint64>(t2), 4000_ui64);


		const MilliSecond mil = 1.0f;
		const Tick t3 = mil;
		SA_UTH_EQ(static_cast<float>(t3), 1000.0f);

		const Second sec = 1.0f;
		const Tick t4 = sec;
		SA_UTH_EQ(static_cast<float>(t4), 1000000.0f);

		const Minute min = 1.0f;
		const Tick t5 = min;
		SA_UTH_EQ(static_cast<float>(t5), 60000000.0f);

		const Hour hour = 1.0f;
		const Tick t6 = hour;
		SA_UTH_EQ(static_cast<float>(t6), 3600000000.0f);
	}

	void Casts()
	{
		const Tick t1 = 2.5f;
		float f = static_cast<float>(t1);
		SA_UTH_EQ(f, 2.5f);

		const Tick t2 = 4000_ui64;
		uint64 u = static_cast<uint64>(t2);
		SA_UTH_EQ(u, 4000_ui64);


		const Tick t3 = 1000.0f;
		const MilliSecond mil = t3.operator MilliSecond();
		SA_UTH_EQ(static_cast<float>(mil), 1.0f);

		const Tick t4 = 1000000.0f;
		const Second sec = t4.operator Second();
		SA_UTH_EQ(static_cast<float>(sec), 1.0f);

		const Tick t5 = 60000000.0f;
		const Minute min = t5.operator Minute();
		SA_UTH_EQ(static_cast<float>(min), 1.0f);

		const Tick t6 = 3600000000.0f;
		const Hour hour = t6.operator Hour();
		SA_UTH_EQ(static_cast<float>(hour), 1.0f);
	}

	void Literal()
	{
		const Tick t1 = 2.5_tk;
		SA_UTH_EQ(static_cast<float>(t1), 2.5f);

		const Tick t2 = 4000_tk;
		SA_UTH_EQ(static_cast<uint64>(t2), 4000_ui64);
	}
}


template <>
std::string UTH::ToString(const Tick& _tick)
{
	return std::to_string(static_cast<float>(_tick)) + "tk";
}

void TickTests()
{
	using namespace Tick_UT;

	SA_UTH_GP(Constants());
	SA_UTH_GP(Constructors());
	SA_UTH_GP(Casts());
	SA_UTH_GP(Literal());
}
