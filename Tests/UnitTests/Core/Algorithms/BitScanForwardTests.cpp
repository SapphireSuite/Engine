// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Algorithms/BitScanForward.hpp>
using namespace Sa;

void BitScanForwardTests()
{
	const uint32 m1 = 1 << 2;
	SA_UTH_EQ(Sa::BitScanForward(m1), 2u);

	const uint32 m2 = (1 << 2) + (1 << 0);
	SA_UTH_EQ(Sa::BitScanForward(m2), 0u);

	const uint32 m3 = 1 << 20;
	SA_UTH_EQ(Sa::BitScanForward(m3), 20u);
}