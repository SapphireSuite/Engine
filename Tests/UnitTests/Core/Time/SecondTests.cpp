// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Collections/Time>
using namespace Sa;

namespace Second_UT
{
	void Constants()
	{
		static_assert(1.0f / Second::ToTicks == Tick::ToSeconds, "1 / Second::ToTicks != Tick::ToSeconds");
		static_assert(1.0f / Second::ToMilliSeconds == MilliSecond::ToSeconds, "1 / Second::ToMilliSeconds != MilliSecond::ToSeconds!");
		static_assert(Second::ToMinutes == 1.0f / Minute::ToSeconds, "Second::ToMinutes != 1 / Minute::ToSeconds!");
		static_assert(Second::ToHours == 1.0f / Hour::ToSeconds, "Second::ToHours != 1 / Hour::ToSeconds!");
	}

	void Constructors()
	{
		const Second t1 = 2.5f;
		SA_UTH_EQ(static_cast<float>(t1), 2.5f);

		const Second t2 = 4000_ui64;
		SA_UTH_EQ(static_cast<uint64>(t2), 4000_ui64);


		const Tick tick = 1.0f;
		const Second t3 = tick;
		SA_UTH_EQ(static_cast<float>(t3), 0.000001f);

		const MilliSecond mil = 1.0f;
		const Second t4 = mil;
		SA_UTH_EQ(static_cast<float>(t4), 0.001f);

		const Minute min = 1.0f;
		const Second t5 = min;
		SA_UTH_EQ(static_cast<float>(t5), 60.0f);

		const Hour hour = 1.0f;
		const Second t6 = hour;
		SA_UTH_EQ(static_cast<float>(t6), 3600.0f);
	}

	void Casts()
	{
		const Second t1 = 2.5f;
		float f = static_cast<float>(t1);
		SA_UTH_EQ(f, 2.5f);

		const Second t2 = 4000_ui64;
		uint64 u = static_cast<uint64>(t2);
		SA_UTH_EQ(u, 4000_ui64);


		const Second t3 = 0.000001f;
		const Tick tick = t3.operator Tick();
		SA_UTH_EQ(static_cast<float>(tick), 1.0f);

		const Second t4 = 0.001f;
		const MilliSecond mil = t4.operator MilliSecond();
		SA_UTH_EQ(static_cast<float>(mil), 1.0f);

		const Second t5 = 60.0f;
		const Minute min = t5.operator Minute();
		SA_UTH_EQ(static_cast<float>(min), 1.0f);

		const Second t6 = 3600.0f;
		const Hour hour = t6.operator Hour();
		SA_UTH_EQ(static_cast<float>(hour), 1.0f);
	}

	void Literal()
	{
		const Second t1 = 2.5_sec;
		SA_UTH_EQ(static_cast<float>(t1), 2.5f);

		const Second t2 = 4000_sec;
		SA_UTH_EQ(static_cast<uint64>(t2), 4000_ui64);
	}
}


template <>
std::string UTH::ToString(const Second& _sec)
{
	return std::to_string(static_cast<float>(_sec)) + "sec";
}

void SecondTests()
{
	using namespace Second_UT;

	SA_UTH_GP(Constants());
	SA_UTH_GP(Constructors());
	SA_UTH_GP(Casts());
	SA_UTH_GP(Literal());
}
