// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <vector>

#include <UnitTestHelper.hpp>

#include <SA/Core/Algorithms/SizeOf.hpp>
using namespace Sa;

void SizeOfTests()
{
	const uint32 i = 0;
	SA_UTH_EQ(SizeOf(i), 1_ui64);
	SA_UTH_EQ(OctSizeOf(i), 4_ui64);
	SA_UTH_EQ(BitSizeOf(i), 32_ui64);

	const float f = 0.0f;
	SA_UTH_EQ(SizeOf(f), 1_ui64);
	SA_UTH_EQ(OctSizeOf(f), 4_ui64);
	SA_UTH_EQ(BitSizeOf(f), 32_ui64);

	const uint32 utab[]{ 4u, 132u, 553u, 16u };
	const uint64 uTabSize = sizeof(utab) / sizeof(uint32);
	SA_UTH_EQ(SizeOf(utab), uTabSize);
	SA_UTH_EQ(OctSizeOf(utab), sizeof(utab));
	SA_UTH_EQ(BitSizeOf(utab), 32_ui64 * uTabSize);

	const std::vector<float> v = { 1.0f, 0.32f, 78.2f, 1.24f, 462.2f };
	SA_UTH_EQ(SizeOf(v), v.size());
	SA_UTH_EQ(OctSizeOf(v), v.size() * sizeof(float));
	SA_UTH_EQ(BitSizeOf(v), v.size() * 32_ui64);
}
