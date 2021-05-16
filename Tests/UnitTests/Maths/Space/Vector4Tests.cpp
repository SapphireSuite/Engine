// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Space/Vector2.hpp>
#include <SA/Maths/Space/Vector3.hpp>
#include <SA/Maths/Space/Vector4.hpp>
using namespace Sa;

namespace Sa::Vector4_UT
{
	Vec4f Generate()
	{
		return Vec4f(UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f));
	}

	void Constructors()
	{
		// Default constructor.
		const Vec4f v0;
		SA_UTH_EQ(v0.x, 0.0f);
		SA_UTH_EQ(v0.y, 0.0f);
		SA_UTH_EQ(v0.z, 0.0f);
		SA_UTH_EQ(v0.w, 0.0f);


		// Value constructor.
		const float v1X = UTH::Rand(-100.0f, 100.0f);
		const float v1Y = UTH::Rand(-100.0f, 100.0f);
		const float v1Z = UTH::Rand(-100.0f, 100.0f);
		const float v1W = UTH::Rand(-100.0f, 100.0f);
		const Vec4f v1(v1X, v1Y, v1Z, v1W);

		SA_UTH_EQ(v1.x, v1X);
		SA_UTH_EQ(v1.y, v1Y);
		SA_UTH_EQ(v1.z, v1Z);
		SA_UTH_EQ(v1.w, v1W);


		// Scale constructor.
		const float v2S = UTH::Rand(-100.0f, 100.0f);
		const Vec4f v2_scale(v2S);

		SA_UTH_EQ(v2_scale.x, v2S);
		SA_UTH_EQ(v2_scale.y, v2S);
		SA_UTH_EQ(v2_scale.z, v2S);
		SA_UTH_EQ(v2_scale.z, v2S);


		// Value cast constructor.
		const int32 v3X = UTH::Rand<int32>(-100, 100);
		const int32 v3Y = UTH::Rand<int32>(-100, 100);
		const int32 v3Z = UTH::Rand<int32>(-100, 100);
		const int32 v3W = UTH::Rand<int32>(-100, 100);
		const Vec4f v3(Vec4i(v3X, v3Y, v3Z, v3W));

		SA_UTH_EQ(v3.x, static_cast<float>(v3X));
		SA_UTH_EQ(v3.y, static_cast<float>(v3Y));
		SA_UTH_EQ(v3.z, static_cast<float>(v3Z));
		SA_UTH_EQ(v3.w, static_cast<float>(v3W));


		// Copy constructor.
		const Vec4f v4(v1);

		SA_UTH_EQ(v4.x, v1.x);
		SA_UTH_EQ(v4.y, v1.y);
		SA_UTH_EQ(v4.z, v1.z);
		SA_UTH_EQ(v4.w, v1.w);


		// From Vec2.
		const Vec2f v5(UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f));

		const float v6Z = UTH::Rand(-100.0f, 100.0f);
		const float v6W = UTH::Rand(-100.0f, 100.0f);
		const Vec4f v6(v5, v6Z, v6W);
		SA_UTH_EQ(v6.x, v5.x);
		SA_UTH_EQ(v6.y, v5.y);
		SA_UTH_EQ(v6.z, v6Z);
		SA_UTH_EQ(v6.w, v6W);


		// From 2 Vec2.
		const Vec2f v7(UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f));
		const Vec4f v8(v5, v7);
		SA_UTH_EQ(v8.x, v5.x);
		SA_UTH_EQ(v8.y, v5.y);
		SA_UTH_EQ(v8.z, v7.x);
		SA_UTH_EQ(v8.w, v7.y);


		// From Vec3.
		const Vec3f v9(UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f));
		const float v10W = UTH::Rand(-100.0f, 100.0f);

		const Vec4f v10(v9, v10W);
		SA_UTH_EQ(v10.x, v9.x);
		SA_UTH_EQ(v10.y, v9.y);
		SA_UTH_EQ(v10.z, v9.z);
		SA_UTH_EQ(v10.w, v10W);
	}

	void Equals()
	{
		const Vec4f v0;
		const Vec4f v1 = Generate();
		const Vec4f v2 = Generate();

		SA_UTH_RMF(false, v1, IsZero);
		SA_UTH_MF(v0, IsZero);

		SA_UTH_MF(v1, Equals, v1);
		SA_UTH_RMF(false, v1, Equals, v2);

		SA_UTH_OP(v1, ==, v1);
		SA_UTH_OP(v1, !=, v2);
	}

	void Accessors()
	{
		const Vec4f v1 = Generate();

		SA_UTH_EQ(v1[0], v1.x);
		SA_UTH_EQ(v1[1], v1.y);
		SA_UTH_EQ(v1[2], v1.z);
		SA_UTH_EQ(v1[3], v1.w);

		SA_UTH_EQ(v1.Data(), &v1.x);
		SA_UTH_EQ(const_cast<Vec4f&>(v1).Data(), &const_cast<Vec4f&>(v1).x);
	}
}

void Vector4Tests()
{
	using namespace Vector4_UT;

	SA_UTH_GP(Constructors());
	SA_UTH_GP(Equals());
	SA_UTH_GP(Accessors());
}
