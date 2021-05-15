// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Misc/Degree.hpp>
#include <SA/Maths/Misc/Radian.hpp>
using namespace Sa;

namespace Sa::Radian_UT
{
	void Literals()
	{
		const Radf r1 = 1.3_rad;
		SA_UTH_EQ(static_cast<float>(r1), 1.3f);

		const Radf r2 = 4_rad;
		SA_UTH_EQ(static_cast<float>(r2), 4.0f);
	}

	void Constructors()
	{
		const Radf r1;
		SA_UTH_EQ(r1, 0.0_rad);

		const Radd dr4 = 4.23;
		const Radf r4 = dr4;
		SA_UTH_EQ(r4, 4.23_rad);

		const Degf d5 = 180_deg;
		const Radf r5 = d5;
		SA_UTH_EQ(r5, Radf(Maths::Pi));
	}

	void Equals()
	{
		const Radf r1 = 1.3_rad;
		const Radf r2 = 4_rad;

		SA_UTH_MF(r1, Equals, r1);
		SA_UTH_RMF(false, r1, Equals, r2);

		SA_UTH_OP(r1, == , r1);
		SA_UTH_ROP(false, r1, == , r2);

		SA_UTH_OP(r1, != , r2);
		SA_UTH_ROP(false, r1, != , r1);
	}

	void Clamp()
	{
		Radf r1 = 1.26_rad;
		r1.Clamp();
		SA_UTH_EQ(r1, 1.26_rad);

		Radf r2 = Maths::Pi + 1.26_rad;
		r2.Clamp();
		SA_UTH_EQ(r2, Radf(-1.8815926_rad));

		Radf r3 = 3 * Maths::Pi + 1.26_rad;
		r3.Clamp();
		SA_UTH_EQ(r3, Radf(-1.8815926_rad));

		Radf r4 = -Maths::Pi - 1.26_rad;
		r4.Clamp();
		SA_UTH_EQ(r4, Radf(1.8815926_rad));

		Radf r5 = 3 * -Maths::Pi - 1.26_rad;
		r5.Clamp();
		SA_UTH_EQ(r5, Radf(1.8815926_rad));
	}

	void Operators()
	{
		const Radf r1 = 10_rad;
		const Radf r2 = 23_rad;

		SA_UTH_EQ(-r1, -10.0f);
		SA_UTH_EQ(r1 + r2, 33.0f);
		SA_UTH_EQ(r2 - r1, 13.0f);
		SA_UTH_EQ(r1 * 3, 30.0f);
		SA_UTH_EQ(r1 / 2, 5.0f);

		Radf r3;
		r3 += 11_rad;
		SA_UTH_EQ(r3, 11_rad);

		r3 -= 3_rad;
		SA_UTH_EQ(r3, 8_rad);

		r3 *= 2;
		SA_UTH_EQ(r3, 16_rad);

		r3 /= 8;
		SA_UTH_EQ(r3, 2_rad);
	}
}

void RadianTests()
{
	using namespace Radian_UT;

	SA_UTH_GP(Literals());
	SA_UTH_GP(Constructors());
	SA_UTH_GP(Equals());
	SA_UTH_GP(Clamp());
	SA_UTH_GP(Operators());
}
