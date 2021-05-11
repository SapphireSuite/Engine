// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <type_traits>

#include <SA/Core/Types/Char.hpp>
using namespace Sa;

void CharTests()
{
	// int8.
	static_assert(sizeof(char8) == 1, "Size of char8 is invalid!");
	static_assert(std::is_same<CharOfSize<1>, char8>::value, "char of size 1 must be int8 type!");
	static_assert(7_c8 == static_cast<char8>(7), "Operator _c8 is invalid!");

	// int16.
	static_assert(sizeof(char16) == 2, "Size of char16 is invalid!");
	static_assert(std::is_same<CharOfSize<2>, char16>::value, "char of size 16 must be int8 type!");
	static_assert(689_c16 == static_cast<char16>(689), "Operator _c16 is invalid!");

	// int32.
	static_assert(sizeof(char32) == 4, "Size of char32 is invalid!");
	static_assert(std::is_same<CharOfSize<4>, char32>::value, "char of size 32 must be int8 type!");
	static_assert(684899_c32 == static_cast<char32>(684899), "Operator _c32 is invalid!");
}
