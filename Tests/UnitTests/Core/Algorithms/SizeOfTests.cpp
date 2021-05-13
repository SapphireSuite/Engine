// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <vector>

#include <UnitTestHelper.hpp>

#include <SA/Core/Algorithms/SizeOf.hpp>
using namespace Sa;

namespace SizeOf_UT
{
	void Int()
	{
		const uint32 i = 0;
		SA_UTH_EQ(SizeOf(i), 1_ui64);
		SA_UTH_EQ(OctSizeOf(i), 4_ui64);
		SA_UTH_EQ(BitSizeOf(i), 32_ui64);
	}

	void Float()
	{
		const float f = 0.0f;
		SA_UTH_EQ(SizeOf(f), 1_ui64);
		SA_UTH_EQ(OctSizeOf(f), 4_ui64);
		SA_UTH_EQ(BitSizeOf(f), 32_ui64);
	}

	void Tab()
	{
		//const uint32 utab[]{ 4u, 132u, 553u, 16u };
		//const uint64 uTabSize = sizeof(utab) / sizeof(uint32);
		//SA_UTH_EQ(SizeOf(utab), uTabSize);
		//SA_UTH_EQ(OctSizeOf(utab), sizeof(utab));
		//SA_UTH_EQ(BitSizeOf(utab), 32_ui64 * uTabSize);
	}

	void Vector()
	{
		const std::vector<float> v = { 1.0f, 0.32f, 78.2f, 1.24f, 462.2f };
		SA_UTH_EQ(SizeOf(v), (uint64)v.size());
		SA_UTH_EQ(OctSizeOf(v), (uint64)v.size() * sizeof(float));
		SA_UTH_EQ(BitSizeOf(v), (uint64)v.size() * 32_ui64);
	}

	void Args()
	{
		SA_UTH_EQ(SizeOfArgs(), 0_ui64);
		SA_UTH_EQ(SizeOfArgs(2, 2.3f, "Hello"), 3_ui64);
	}
}

void SizeOfTests()
{
	using namespace SizeOf_UT;

	SA_UTH_GP(Int());
	SA_UTH_GP(Float());
	SA_UTH_GP(Tab());
	SA_UTH_GP(Vector());
	SA_UTH_GP(Args());
}
