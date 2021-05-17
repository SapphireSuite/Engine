// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Space/Vector2.hpp>
#include <SA/Maths/Space/Vector3.hpp>
using namespace Sa;

namespace Sa::Vector2_UT
{
	Vec2f Generate()
	{
		return Vec2f(UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f));
	}

	void Constants()
	{
		SA_UTH_EQ(Vec2f::Zero.x, 0.0f);
		SA_UTH_EQ(Vec2f::Zero.y, 0.0f);

		SA_UTH_EQ(Vec2f::One.x, 1.0f);
		SA_UTH_EQ(Vec2f::One.y, 1.0f);


		// X Axis.
		SA_UTH_EQ(Vec2f::Right.x, 1.0f);
		SA_UTH_EQ(Vec2f::Right.y, 0.0f);

		SA_UTH_EQ(Vec2f::Left.x, -1.0f);
		SA_UTH_EQ(Vec2f::Left.y, 0.0f);


		// Y Axis.
		SA_UTH_EQ(Vec2f::Up.x, 0.0f);
		SA_UTH_EQ(Vec2f::Up.y, 1.0f);

		SA_UTH_EQ(Vec2f::Down.x, 0.0f);
		SA_UTH_EQ(Vec2f::Down.y, -1.0f);
	}

	void Constructors()
	{
		// Default constructor.
		const Vec2f v0;
		SA_UTH_EQ(v0.x, 0.0f);
		SA_UTH_EQ(v0.y, 0.0f);


		// Value constructor.
		const float v1X = UTH::Rand(-100.0f, 100.0f);
		const float v1Y = UTH::Rand(-100.0f, 100.0f);
		const Vec2f v1(v1X, v1Y);

		SA_UTH_EQ(v1.x, v1X);
		SA_UTH_EQ(v1.y, v1Y);


		// Scale constructor.
		const float v2S = UTH::Rand(-100.0f, 100.0f);
		const Vec2f v2_scale(v2S);

		SA_UTH_EQ(v2_scale.x, v2S);
		SA_UTH_EQ(v2_scale.y, v2S);


		// Value cast constructor.
		const int32 v3X = UTH::Rand<int32>(-100, 100);
		const int32 v3Y = UTH::Rand<int32>(-100, 100);
		const Vec2f v3(Vec2i(v3X, v3Y));

		SA_UTH_EQ(v3.x, static_cast<float>(v3X));
		SA_UTH_EQ(v3.y, static_cast<float>(v3Y));


		// Copy constructor.
		const Vec2f v4(v1);

		SA_UTH_EQ(v4.x, v1.x);
		SA_UTH_EQ(v4.y, v1.y);


		// From Vec3.
		const Vec3f v5(UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f));

		const Vec2f v6(v5);
		SA_UTH_EQ(v6.x, v5.x);
		SA_UTH_EQ(v6.y, v5.y);
	}

	void Equals()
	{
		const Vec2f v1 = Generate();
		const Vec2f v2 = Generate();

		SA_UTH_RMF(false, v1, IsZero);
		SA_UTH_MF(Vec2f::Zero, IsZero);

		SA_UTH_MF(v1, Equals, v1);
		SA_UTH_RMF(false, v1, Equals, v2);

		SA_UTH_OP(v1, ==, v1);
		SA_UTH_OP(v1, !=, v2);
	}

	void Lenght()
	{
		Vec2f v1 = Generate();

		const float vLenSqr = v1.x * v1.x + v1.y * v1.y;
		const float vLen = Maths::Sqrt(vLenSqr);
		SA_UTH_RMF(vLen, v1, Length);
		SA_UTH_RMF(vLenSqr, v1, SqrLength);

		const Vec2f nV1 = v1.GetNormalized();
		SA_UTH_EQ(nV1.x, v1.x / vLen);
		SA_UTH_EQ(nV1.y, v1.y / vLen);

		SA_UTH_MF(nV1, IsNormalized);
		SA_UTH_EQ(nV1.Length(), 1.0f, std::numeric_limits<float>::epsilon());
		SA_UTH_RMF(false, v1, IsNormalized);

		v1.Normalize();
		SA_UTH_OP(v1, ==, nV1);
	}

	void Projection()
	{
		// Reflect
		const Vec2f v1(1.0f, 1.0f);
		const Vec2f norm(-1.0f, 0.0f);
		const Vec2f refl = Vec2f(-1.0f, 1.0f);
		SA_UTH_RMF(refl, v1, Reflect, norm);


		//// TODO: Projections.
		////SA_UTH_EQ(true, false);
	}

	void DotCross()
	{
		const Vec2f v1 = Generate();
		const Vec2f v2 = Generate();

		float dot = v1.x * v2.x + v1.y * v2.y;
		SA_UTH_RSF(dot, Vec2f::Dot, v1, v2);
		SA_UTH_ROP(dot, v1, |, v2);


		float cross = v1.x * v2.y + v1.y * v2.x;
		SA_UTH_RSF(cross, Vec2f::Cross, v1, v2);
		SA_UTH_ROP(cross, v1, ^, v2);
	}

	void Angle()
	{
		const Vec2f v1(-2.0, 1.0);
		const Vec2f v2(1.0, 2.0);

		SA_UTH_RSF(Degf(-90.0_deg), Vec2f::Angle, v1, v2);
		SA_UTH_RSF(90.0_deg, Vec2f::AngleUnsigned, v1, v2);
	}

	void Dist()
	{
		const Vec2f v1 = Generate();
		const Vec2f v2 = Generate();

		SA_UTH_RSF((v1 - v2).Length(), Vec2f::Dist, v1, v2);
		SA_UTH_RSF((v1 - v2).SqrLength(), Vec2f::SqrDist, v1, v2);
	}

	void Dir()
	{
		const Vec2f v1 = Generate();
		const Vec2f v2 = Generate();
		const Vec2f vDir = v2 - v1;

		SA_UTH_RSF(vDir, Vec2f::Dir, v1, v2);
		SA_UTH_RSF(vDir.GetNormalized(), Vec2f::DirN, v1, v2);
	}

	void Lerp()
	{
		const Vec2f v1(2.0f, 2.0f);
		const Vec2f v2(-2.0f, 4.0f);

		const Vec2f lerp_res05 = Vec2f(0.0f, 3.0f);
		SA_UTH_RSF(lerp_res05, Vec2f::Lerp, v1, v2, 0.5f);


		SA_LOGLVL_DIS_SECTB(Warning)

			// Intended warning.
			SA_UTH_RSF(v2, Vec2f::Lerp, v1, v2, 2.0f);

		SA_LOGLVL_DIS_SECTE()


		const Vec2f ulerp_res1 = Vec2f(6.0f, 0.0f);
		SA_UTH_RSF(ulerp_res1, Vec2f::LerpUnclamped, v1, v2, -1.0f);


		const Vec2f slerp_v1(2.0f, 2.0f);
		const Vec2f slerp_v2(-2.0f, 2.0f);
		const Vec2f slerp_res05 = Vec2f(0.0f, slerp_v1.Length());
		SA_UTH_RSF(slerp_res05, Vec2f::SLerp, slerp_v1, slerp_v2, 0.5f);
	}


	void Operators()
	{
		const Vec2f v1 = Generate();

		const Vec2f mv1 = Vec2f(-v1.x, -v1.y);
		SA_UTH_EQ(-v1, mv1);

		// Scalar Scale.
		float scale = UTH::Rand(-100.0f, 100.0f);
		const Vec2f sv1 = Vec2f(v1.x * scale, v1.y * scale);
		SA_UTH_EQ(v1 * scale, sv1);
		SA_UTH_EQ(scale * v1, sv1);

		const Vec2f usv1 = Vec2f(v1.x / scale, v1.y / scale);
		const Vec2f susv1 = Vec2f(scale / v1.x, scale / v1.y);
		SA_UTH_EQ(v1 / scale, usv1);
		SA_UTH_EQ(scale / v1, susv1);


		// Vec2 operators.
		const Vec2f v2 = Generate();

		const Vec2f v1pv2 = Vec2f(v1.x + v2.x, v1.y + v2.y);
		SA_UTH_EQ(v1 + v2, v1pv2);

		const Vec2f v1mv2 = Vec2f(v1.x - v2.x, v1.y - v2.y);
		SA_UTH_EQ(v1 - v2, v1mv2);

		const Vec2f v1mltv2 = Vec2f(v1.x * v2.x, v1.y * v2.y);
		SA_UTH_EQ(v1 * v2, v1mltv2);

		const Vec2f v1dv2 = Vec2f(v1.x / v2.x, v1.y / v2.y);
		SA_UTH_EQ(v1 / v2, v1dv2);


		// op *= scalar.
		Vec2f v3 = v1;
		v3 *= scale;
		SA_UTH_EQ(v3, sv1);


		// op /= scalar.
		Vec2f v4 = v1;
		v4 /= scale;
		SA_UTH_EQ(v4, usv1);


		// op += Vec2.
		Vec2f v5 = v1;
		v5 += v2;
		SA_UTH_EQ(v5, v1pv2);

		// op -= Vec2.
		Vec2f v6 = v1;
		v6 -= v2;
		SA_UTH_EQ(v6, v1mv2);


		// op *= Vec2.
		Vec2f v7 = v1;
		v7 *= v2;
		SA_UTH_EQ(v7, v1mltv2);


		// op /= Vec2.
		Vec2f v8 = v1;
		v8 /= v2;
		SA_UTH_EQ(v8, v1dv2);
	}

	void Accessors()
	{
		const Vec2f v1 = Generate();

		SA_UTH_EQ(v1[0], v1.x);
		SA_UTH_EQ(v1[1], v1.y);

		SA_UTH_EQ(v1.Data(), &v1.x);
		SA_UTH_EQ(const_cast<Vec2f&>(v1).Data(), &const_cast<Vec2f&>(v1).x);
	}
}

void Vector2Tests()
{
	using namespace Vector2_UT;

	SA_UTH_GP(Constants());
	SA_UTH_GP(Constructors());
	SA_UTH_GP(Equals());
	SA_UTH_GP(Lenght());
	SA_UTH_GP(Projection());
	SA_UTH_GP(DotCross());
	SA_UTH_GP(Angle());
	SA_UTH_GP(Dist());
	SA_UTH_GP(Dir());
	SA_UTH_GP(Lerp());
	SA_UTH_GP(Operators());
	SA_UTH_GP(Accessors());
}
