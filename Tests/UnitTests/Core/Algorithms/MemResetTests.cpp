// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Algorithms/MemReset.hpp>
using namespace Sa;

void MemResetTests()
{
	char8 str[6]{ "yyyyy" };
	MemReset(str, 5);
	SA_UTH_EQ(str, "\0\0\0\0\0", 5);


	int32 tab1[5]{ 808, 808, 808, 808, 808 };
	const int32 res[]{ 0, 0, 0, 0, 0 };
	MemReset(tab1, 5);
	SA_UTH_EQ(tab1, res, 5);
}