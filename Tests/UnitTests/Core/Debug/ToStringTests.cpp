// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Core/Debug/ToString.hpp>
using namespace Sa;

#if SA_LOGGING

namespace Sa::ToString_UT
{
	enum class TestEnum
	{
		V1 = 1,
		V2 = 2
	};

	struct A
	{
		int i = 0;

		std::string ToString() const { return std::to_string(i); }
	};

	struct B
	{
		int i = 0;

		std::string ToString() const { return std::to_string(i); }
		std::wstring ToWString() const { return std::to_wstring(i) + L'W'; }
	};

	void ToStringFunc()
	{
		const std::string helloStr = "Hello";
		SA_UTH_EQ(ToString("Hello"), helloStr);

		SA_UTH_EQ(ToString(helloStr), helloStr);

		const int i = 5498;
		SA_UTH_EQ(ToString(i), std::to_string(i));
		SA_UTH_EQ(ToString(2.5f), std::to_string(2.5f));
		SA_UTH_EQ(ToString(TestEnum::V2), std::string("2"));
		SA_UTH_EQ(ToString(&i), "0x" + std::to_string(reinterpret_cast<uint64>(&i)));

		const A a1{ 9 };
		SA_UTH_EQ(ToString(a1), std::to_string(a1.i));

		const B b1{ 4 };
		SA_UTH_EQ(ToString(b1), std::to_string(b1.i));

		int tab1[]{ 5, 6, 3, 4 };
		SA_UTH_EQ(ToString(tab1, 4), std::string("{ 5, 6, 3, 4 }"));

		std::vector<int> v1 = { 6, 8, 1, 3, 4 };
		SA_UTH_EQ(ToString(v1), std::string("{ 6, 8, 1, 3, 4 }"));


		const std::wstring h5 = std::wstring(L"Hello") << ", World!" << L" WIDE " << 5;
		SA_UTH_EQ(h5, std::wstring(L"Hello, World! WIDE 5"));
	}

	void ToWStringFunc()
	{
		const std::string helloStr = "Hello";
		const std::wstring whelloStr = L"Hello";
		SA_UTH_EQ(ToWString("Hello"), whelloStr);
		SA_UTH_EQ(ToWString(L"Hello"), whelloStr);

		SA_UTH_EQ(ToWString(helloStr), whelloStr);
		SA_UTH_EQ(ToWString(whelloStr), whelloStr);

		const int i = 5498;
		SA_UTH_EQ(ToWString(i), std::to_wstring(i));
		SA_UTH_EQ(ToWString(2.5f), std::to_wstring(2.5f));
		SA_UTH_EQ(ToWString(TestEnum::V2), std::wstring(L"2"));
		SA_UTH_EQ(ToWString(&i), L"0x" + std::to_wstring(reinterpret_cast<uint64>(&i)));

		const A a1{ 9 };
		SA_UTH_EQ(ToWString(a1), std::to_wstring(a1.i));

		const B b1{ 4 };
		SA_UTH_EQ(ToWString(b1), std::to_wstring(b1.i) + L'W');

		int tab1[]{ 5, 6, 3, 4 };
		auto aaa = ToWString(tab1, 4);
		SA_UTH_EQ(ToWString(tab1, 4), std::wstring(L"{ 5, 6, 3, 4 }"));

		std::vector<int> v1 = { 6, 8, 1, 3, 4 };
		SA_UTH_EQ(ToWString(v1), std::wstring(L"{ 6, 8, 1, 3, 4 }"));


		const std::string h5 = std::string("Hello") << ", World! " << 5;
		SA_UTH_EQ(h5, std::string("Hello, World! 5"));
	}
}


void ToStringTests()
{
	using namespace ToString_UT;

	SA_UTH_GP(ToStringFunc());
	SA_UTH_GP(ToWStringFunc());
}

#else

void ToStringTests()
{
}

#endif