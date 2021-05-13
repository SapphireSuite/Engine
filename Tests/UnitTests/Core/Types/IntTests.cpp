// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <cstdint>
#include <type_traits>

#include <SA/Core/Types/Int.hpp>
using namespace Sa;

void IntTests()
{
	// int8.
	static_assert(sizeof(int8) == 1, "Size of int8 is invalid!");
	static_assert(std::is_same<IntOfSize<1>, int8>::value, "int of size 1 must be int8 type!");
	//static_assert(std::is_same<int8, int8_t>::value, "int8 is not standard int8_t!");
	static_assert(7_i8 == static_cast<int8>(7), "Operator _i8 is invalid!");

	// uint8.
	static_assert(sizeof(uint8) == 1, "Size of uint8 is invalid!");
	static_assert(std::is_same<UIntOfSize<1>, uint8>::value, "uint of size 1 must be uint8 type!");
	//static_assert(std::is_same<uint8, uint8_t>::value, "uint8 is not standard uint8_t!");
	static_assert(7_ui8 == static_cast<uint8>(7), "Operator _ui8 is invalid!");


	// int16.
	static_assert(sizeof(int16) == 2, "Size of int16 is invalid!");
	static_assert(std::is_same<IntOfSize<2>, int16>::value, "int of size 2 must be int16 type!");
	//static_assert(std::is_same<int16, int16_t>::value, "int16 is not standard int16_t!");
	static_assert(689_i16 == static_cast<int16>(689), "Operator _i16 is invalid!");

	// uint16.
	static_assert(sizeof(uint16) == 2, "Size of uint16 is invalid!");
	static_assert(std::is_same<UIntOfSize<2>, uint16>::value, "uint of size 2 must be uint16 type!");
	//static_assert(std::is_same<uint16, uint16_t>::value, "uint16 is not standard uint16_t!");
	static_assert(689_ui16 == static_cast<uint16>(689), "Operator _ui16 is invalid!");


	// int32.
	static_assert(sizeof(int32) == 4, "Size of int32 is invalid!");
	static_assert(std::is_same<IntOfSize<4>, int32>::value, "int of size 4 must be int32 type!");
	//static_assert(std::is_same<int32, int32_t>::value, "int32 is not standard int32_t!");
	static_assert(684899_i32 == static_cast<int32>(684899), "Operator _i32 is invalid!");

	// uint32.
	static_assert(sizeof(uint32) == 4, "Size of uint32 is invalid!");
	static_assert(std::is_same<UIntOfSize<4>, uint32>::value, "uint of size 4 must be uint32 type!");
	//static_assert(std::is_same<uint32, uint32_t>::value, "uint32 is not standard uint32_t!");
	static_assert(684899_ui32 == static_cast<uint32>(684899), "Operator _ui32 is invalid!");


	// int64.
	static_assert(sizeof(int64) == 8, "Size of int64 is invalid!");
	static_assert(std::is_same<IntOfSize<8>, int64>::value, "int of size 8 must be int64 type!");
	//static_assert(std::is_same<int64, int64_t>::value, "int64 is not standard int64_t!");
	static_assert(6848489799_i64 == static_cast<int64>(6848489799), "Operator _i64 is invalid!");

	// uint64.
	static_assert(sizeof(uint64) == 8, "Size of uint64 is invalid!");
	static_assert(std::is_same<UIntOfSize<8>, uint64>::value, "uint of size 8 must be uint64 type!");
	//static_assert(std::is_same<uint64, uint64_t>::value, "uint64 is not standard uint64_t!");
	static_assert(6848489799_ui64 == static_cast<uint64>(6848489799), "Operator _ui64 is invalid!");
}
