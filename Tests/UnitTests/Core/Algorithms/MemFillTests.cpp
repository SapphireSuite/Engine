// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Algorithms/MemFill.hpp>
using namespace Sa;

void MemFillTests()
{
	char8 str[6]{};
	MemFill(str, 'y', 5);
	SA_UTH_EQ(str, "yyyyy", 5);
	SA_UTH_EQ(str[5], '\0');


	int32 tab1[5];
	const int32 res[]{ 808, 808, 808, 808, 808 };
	MemFill(tab1, 808, 5);
	SA_UTH_EQ(tab1, res, 5);
}