// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Algorithms/Sign.hpp>
using namespace Sa;

namespace Sa::Sign_UT
{
}

void SignTests()
{
	const int32 i1 = 10;
	SA_UTH_EQ(Maths::Sign(i1), 1);

	const int32 i2 = -25;
	SA_UTH_EQ(Maths::Sign(i2), -1);


	SA_LOGLVL_DIS_SECTB(Warning)

		const uint32 ui1 = 10;
		SA_UTH_EQ(Maths::Sign(ui1), 1); // Intended warning.
	
	SA_LOGLVL_DIS_SECTE()


	const float f1 = 13.2446f;
	SA_UTH_EQ(Maths::Sign(f1), 1);

	const float f2 = -26.45f;
	SA_UTH_EQ(Maths::Sign(f2), -1);


	const double d1 = 13.2446;
	SA_UTH_EQ(Maths::Sign(d1), 1);

	const double d2 = -26.45;
	SA_UTH_EQ(Maths::Sign(d2), -1);
}
