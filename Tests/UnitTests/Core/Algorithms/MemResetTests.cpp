// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Core/Algorithms/MemReset.hpp>
using namespace Sa;

void MemResetTests()
{
	char8 str[6]{ "yyyyy" };
	char8 resC[]{ "\0\0\0\0\0" };
	MemReset(str, 5u);
	SA_UTH_EQ(str, resC, 5u);


	int32 tab1[5]{ 808, 808, 808, 808, 808 };
	int32 resI[]{ 0, 0, 0, 0, 0 };
	MemReset(tab1, 5u);
	SA_UTH_EQ(tab1, resI, 5u);
}