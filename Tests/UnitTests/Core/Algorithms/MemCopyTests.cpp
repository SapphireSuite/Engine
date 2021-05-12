// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Algorithms/MemCopy.hpp>
using namespace Sa;

void MemCopyTests()
{
	const int32 tab1[5]{ 1, 6, 89, 124, 4 };
	
	int32 tab2[5]{};
	MemCopy(tab1, tab2, 5);
	SA_UTH_EQ(tab1, tab2, 5);

	int32 tab3[3]{};
	MemCopy(tab1, tab3, 3);
	SA_UTH_EQ(tab1, tab3, 3);


	int32 tab4[7]{};
	MemCopy(tab1, tab4, 5);
	SA_UTH_EQ(tab1, tab4, 5);
	SA_UTH_EQ(tab4[5], 0);
	SA_UTH_EQ(tab4[6], 0);
}