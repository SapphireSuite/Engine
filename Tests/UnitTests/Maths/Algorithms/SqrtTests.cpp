// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Algorithms/Sqrt.hpp>
using namespace Sa;

void SqrtTests()
{
	SA_UTH_RSF(0.0f, Maths::Sqrt, 0.0f);
	SA_UTH_RSF(1.0f, Maths::Sqrt, 1.0f);
	SA_UTH_RSF(1.4142135f, Maths::Sqrt, 2.0f);
	SA_UTH_RSF(2.0f, Maths::Sqrt, 4.0f);
	SA_UTH_RSF(5.0f, Maths::Sqrt, 25.0f);
}
