// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Collections/Time>
using namespace Sa;

namespace Sa::Minute_UT
{
	void Constants()
	{
		static_assert(1.0f / Minute::ToTicks == Tick::ToMinutes, "1 / Minute::ToTicks != Tick::ToMinutes");
		static_assert(1.0f / Minute::ToMilliSeconds == MilliSecond::ToMinutes, "1 / Minute::ToMilliSeconds != MilliSecond::ToMinutes!");
		static_assert(1.0f / Minute::ToSeconds == Second::ToMinutes, "1 / Minute::ToSeconds != Second::ToMinutes!");
		static_assert(Minute::ToHours == 1.0f / Hour::ToMinutes, "Minute::ToHours != 1 / Hour::ToMinutes!");
	}

	void Constructors()
	{
		const Minute t1 = 2.5f;
		SA_UTH_EQ(static_cast<float>(t1), 2.5f);

		const Minute t2 = 4000_ui64;
		SA_UTH_EQ(static_cast<uint64>(t2), 4000_ui64);


		const Tick tick = 60.0f;
		const Minute t3 = tick;
		SA_UTH_EQ(static_cast<float>(t3), 0.000001f);

		const MilliSecond mil = 6.0f;
		const Minute t4 = mil;
		SA_UTH_EQ(static_cast<float>(t4), 0.0001f, std::numeric_limits<float>::epsilon());

		const Second sec = 6.0f;
		const Minute t5 = sec;
		SA_UTH_EQ(static_cast<float>(t5), 0.1f, std::numeric_limits<float>::epsilon());

		const Hour hour = 1.0f;
		const Minute t6 = hour;
		SA_UTH_EQ(static_cast<float>(t6), 60.0f);
	}

	void Casts()
	{
		const Minute t1 = 2.5f;
		float f = static_cast<float>(t1);
		SA_UTH_EQ(f, 2.5f);

		const Minute t2 = 4000_ui64;
		uint64 u = static_cast<uint64>(t2);
		SA_UTH_EQ(u, 4000_ui64);


		const Minute t3 = 0.000001f;
		const Tick tick = t3.operator Tick();
		SA_UTH_EQ(static_cast<float>(tick), 60.0f);

		const Minute t4 = 0.0001f;
		const MilliSecond mil = t4.operator MilliSecond();
		SA_UTH_EQ(static_cast<float>(mil), 6.0f);

		const Minute t5 = 0.1f;
		const Second sec = t5.operator Second();
		SA_UTH_EQ(static_cast<float>(sec), 6.0f);

		const Minute t6 = 60.0f;
		const Hour hour = t6.operator Hour();
		SA_UTH_EQ(static_cast<float>(hour), 1.0f);
	}

	void Literal()
	{
		const Minute t1 = 2.5_min;
		SA_UTH_EQ(static_cast<float>(t1), 2.5f);

		const Minute t2 = 4000_min;
		SA_UTH_EQ(static_cast<uint64>(t2), 4000_ui64);
	}
}


void MinuteTests()
{
	using namespace Minute_UT;

	SA_UTH_GP(Constants());
	SA_UTH_GP(Constructors());
	SA_UTH_GP(Casts());
	SA_UTH_GP(Literal());
}
