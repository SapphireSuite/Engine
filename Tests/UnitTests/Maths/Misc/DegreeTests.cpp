// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Misc/Degree.hpp>
#include <SA/Maths/Misc/Radian.hpp>
using namespace Sa;

namespace Sa::Degree_UT
{
	void Literals()
	{
		const Degf d1 = 1.3_deg;
		SA_UTH_EQ(static_cast<float>(d1), 1.3f);

		const Degf d2 = 4_deg;
		SA_UTH_EQ(static_cast<float>(d2), 4.0f);
	}

	void Constructors()
	{
		const Degf d1;
		SA_UTH_EQ(d1, 0.0_deg);

		const Degd dd4 = 4.23;
		const Degf d4 = dd4;
		SA_UTH_EQ(d4, 4.23_deg);

		const Radf r5 = Maths::Pi;
		const Degf d5 = r5;
		SA_UTH_EQ(d5, 180.0_deg);
	}

	void Equals()
	{
		const Degf d1 = 1.3_deg;
		const Degf d2 = 4_deg;

		SA_UTH_MF(d1, Equals, d1);
		SA_UTH_RMF(false, d1, Equals, d2);

		SA_UTH_OP(d1, ==, d1);
		SA_UTH_ROP(false, d1, == , d2);

		SA_UTH_OP(d1, != , d2);
		SA_UTH_ROP(false, d1, != , d1);
	}

	void Clamp()
	{
		Degf d1 = 10_deg;
		d1.Clamp();
		SA_UTH_EQ(d1, 10_deg);

		Degf d2 = 310_deg;
		d2.Clamp();
		SA_UTH_EQ(d2, Degf(-50_deg));

		Degf d3 = 670_deg;
		d3.Clamp();
		SA_UTH_EQ(d3, Degf(-50_deg));

		Degf d4 = -200_deg;
		d4.Clamp();
		SA_UTH_EQ(d4, 160_deg);

		Degf d5 = -560_deg;
		d5.Clamp();
		SA_UTH_EQ(d5, 160_deg);
	}

	void Operators()
	{
		const Degf d1 = 10_deg;
		const Degf d2 = 23_deg;

		SA_UTH_EQ(-d1, -10.0_deg);
		SA_UTH_EQ(d1 + d2, 33.0_deg);
		SA_UTH_EQ(d2 - d1, 13.0_deg);
		SA_UTH_EQ(d1 * 3.0f, 30.0_deg);
		SA_UTH_EQ(d1 / 2.0f, 5.0_deg);

		Degf d3;
		d3 += 11_deg;
		SA_UTH_EQ(d3, 11_deg);

		d3 -= 3_deg;
		SA_UTH_EQ(d3, 8_deg);

		d3 *= 2;
		SA_UTH_EQ(d3, 16_deg);

		d3 /= 8;
		SA_UTH_EQ(d3, 2_deg);
	}
}

void DegreeTests()
{
	using namespace Degree_UT;

	SA_UTH_GP(Literals());
	SA_UTH_GP(Constructors());
	SA_UTH_GP(Equals());
	SA_UTH_GP(Clamp());
	SA_UTH_GP(Operators());
}
