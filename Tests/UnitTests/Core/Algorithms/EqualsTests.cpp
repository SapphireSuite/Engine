// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Algorithms/Equals.hpp>
using namespace Sa;

namespace Sa::Equals_UT
{
	struct V2
	{
		float x = 0.0f;
		float y = 0.0f;

		bool Equals(const V2& _other, float _epsilon = std::numeric_limits<float>::epsilon()) const
		{
			return Sa::Equals(x, _other.x, _epsilon) && Sa::Equals(y, _other.y, _epsilon);
		}
	};

	void IntTests()
	{
		const int32 i0 = 0;
		const int32 i1 = 1;
		const int32 i4 = 4;

		SA_UTH_RSF(true, Equals, i4, i4);
		SA_UTH_RSF(false, Equals, i1, i4);

		SA_UTH_RSF(true, Equals0, i0);
		SA_UTH_RSF(false, Equals0, i1);

		SA_UTH_RSF(true, Equals1, i1);
		SA_UTH_RSF(false, Equals1, i0);
	}

	void FloatTests()
	{
		const float f0 = 0.0f;
		const float f0e = 0.0f + std::numeric_limits<float>::epsilon();
		const float f1 = 1.0f;
		const float f1e = 1.0f + std::numeric_limits<float>::epsilon();
		const float f4 = 4.25f;
		const float f4e = 4.25f + std::numeric_limits<float>::epsilon();

		SA_UTH_RSF(true, Equals, f4, f4);
		SA_UTH_RSF(true, Equals, f4, f4e);
		SA_UTH_RSF(false, Equals, f1, f4);

		SA_UTH_RSF(true, Equals0, f0);
		SA_UTH_RSF(true, Equals0, f0e);
		SA_UTH_RSF(false, Equals0, f1);

		SA_UTH_RSF(true, Equals1, f1);
		SA_UTH_RSF(true, Equals1, f1e);
		SA_UTH_RSF(false, Equals1, f0);
	}

	void TabTests()
	{
		const float fTab0[] = { 0.0f, 1.0f, 2.2546f, 4.25f, 1.26f };
		const float fTab0e[] = {
			fTab0[0] + std::numeric_limits<float>::epsilon(),
			fTab0[1] + std::numeric_limits<float>::epsilon(),
			fTab0[2] + std::numeric_limits<float>::epsilon(),
			fTab0[3] + std::numeric_limits<float>::epsilon(),
			fTab0[4] + std::numeric_limits<float>::epsilon()
		};

		const float fTab1[] = { 0.0f, 1.0f, 2.2546f, 4.258f, 1.26f };

		SA_UTH_RSF(true, Equals, fTab0, fTab0, 5u);
		SA_UTH_RSF(true, Equals, fTab0, fTab0e, 5u);
		SA_UTH_RSF(false, Equals, fTab0, fTab1, 5u);
		SA_UTH_RSF(true, Equals, fTab0, fTab1, 3u);
	}

	void Vec2Tests()
	{
		const V2 v1{ 1.2f, 2.35f };
		const V2 v1e{ v1.x + std::numeric_limits<float>::epsilon(), v1.y + std::numeric_limits<float>::epsilon() };
		const V2 v2{ 3.2f, 15.2f };

		SA_UTH_RMF(true, v1, Equals, v1);
		SA_UTH_RSF(true, Equals, v1, v1, std::numeric_limits<float>::epsilon());

		SA_UTH_RMF(true, v1, Equals, v1e);
		SA_UTH_RSF(true, Equals, v1, v1e, std::numeric_limits<float>::epsilon());

		SA_UTH_RMF(false, v1, Equals, v2);
		SA_UTH_RSF(false, Equals, v1, v2, std::numeric_limits<float>::epsilon());
	}
}

void EqualsTests()
{
	using namespace Sa::Equals_UT;

	SA_UTH_GP(IntTests());
	SA_UTH_GP(FloatTests());
	SA_UTH_GP(TabTests());
	SA_UTH_GP(Vec2Tests());
}
