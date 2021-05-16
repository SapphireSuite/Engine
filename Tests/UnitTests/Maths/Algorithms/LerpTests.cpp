// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Algorithms/Lerp.hpp>
using namespace Sa;

namespace Sa::Lerp_UT
{
	void Lerp()
	{
		SA_UTH_RSF(1.0f, Maths::Lerp, 1.0f, 5.0f, 0.0f);
		SA_UTH_RSF(5.0f, Maths::Lerp, 1.0f, 5.0f, 1.0f);
		SA_UTH_RSF(3.0f, Maths::Lerp, 1.0f, 5.0f, 0.5f);
		SA_UTH_RSF(1.0f, Maths::Lerp, 1.0f, 5.0f, -1.0f); // Intended warning.
		SA_UTH_RSF(5.0f, Maths::Lerp, 1.0f, 5.0f, 2.0f); // Intended warning.


		SA_UTH_RSF(1.0f, Maths::LerpUnclamped, 1.0f, 5.0f, 0.0f);
		SA_UTH_RSF(5.0f, Maths::LerpUnclamped, 1.0f, 5.0f, 1.0f);
		SA_UTH_RSF(3.0f, Maths::LerpUnclamped, 1.0f, 5.0f, 0.5f);
		SA_UTH_RSF(-3.0f, Maths::LerpUnclamped, 1.0f, 5.0f, -1.0f);
		SA_UTH_RSF(9.0f, Maths::LerpUnclamped, 1.0f, 5.0f, 2.0f);
	}

	void SLerp()
	{
		// ToDo: Implement later.
	}
}

void LerpTests()
{
	using namespace Lerp_UT;

	SA_UTH_GP(Lerp());
	SA_UTH_GP(SLerp());
}
