// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Algorithms/Cos.hpp>
#include <SA/Maths/Algorithms/Sin.hpp>
#include <SA/Maths/Algorithms/Tan.hpp>
using namespace Sa;

namespace Sa::CosSinTan_UT
{
	const float feps = std::numeric_limits<float>::epsilon();

	void Cos()
	{
		SA_UTH_EQ(Maths::Cos<float>(0.0f), 1.0f);
		SA_UTH_EQ(Maths::Cos<float>(Maths::Pi), -1.0f);
		SA_UTH_EQ(Maths::Cos<float>(Maths::PiOv2), 0.0f, feps);
		SA_UTH_EQ(Maths::Cos<float>(40_deg), 0.76604425f, 2 * feps);
		SA_UTH_EQ(Maths::Cos<float>(0.698132_rad), 0.76604425f);
	}

	void Sin()
	{
		SA_UTH_EQ(Maths::Sin<float>(Maths::Pi), 0.0f, feps);
		SA_UTH_EQ(Maths::Sin<float>(Maths::PiOv2), 1.0f);
		SA_UTH_EQ(Maths::Sin<float>(-Maths::PiOv2), -1.0f);
		SA_UTH_EQ(Maths::Sin<float>(40_deg), 0.64278781f, 2 * feps);
		SA_UTH_EQ(Maths::Sin<float>(0.698132_rad), 0.64278781f);
	}

	void Tan()
	{
		SA_UTH_EQ(Maths::Tan<float>(Maths::Pi), 0.0f, feps);
		SA_UTH_EQ(Maths::Tan<float>(Maths::PiOv3), 1.7320509f);
		SA_UTH_EQ(Maths::Tan<float>(-Maths::PiOv6), -0.57735025f, feps);
		SA_UTH_EQ(Maths::Tan<float>(40_deg), 0.83910012f, 0.000001f);
		SA_UTH_EQ(Maths::Tan<float>(0.698132_rad), 0.83910012f);
	}
}

void CosSinTanTests()
{
	using namespace CosSinTan_UT;

	SA_UTH_GP(Cos());
	SA_UTH_GP(Sin());
	SA_UTH_GP(Tan());
}
