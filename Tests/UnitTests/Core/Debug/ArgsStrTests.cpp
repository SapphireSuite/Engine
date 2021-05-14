// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Core/Debug/ArgsStr.hpp>
using namespace Sa;

namespace Sa::ArgsStr_UT
{
	struct A
	{
		int j = 0;

		std::string ToString() const
		{
			return "A[" + std::to_string(j) + ']';
		}
	};

	int Foo(int _a, int _b)
	{
		return _a + _b;
	}

	template <typename T1, typename T2>
	float Bar(T1 _a, T2 _b)
	{
		return _a * _b;
	}
}

void ArgsStrTests()
{
#if SA_LOGGING

	using namespace ArgsStr_UT;

	const int i = 5;
	const float f = 2.3f;
	const A a{ 6 };

	const ArgsStr aStr = SA_STR_ARGS(i, f, a, Foo(10, 4), Bar<float, int>(0.5f, 2));

	SA_UTH_EQ(aStr.params[0].name, std::string("i"));
	SA_UTH_EQ(aStr.params[0].value, std::string("5"));

	SA_UTH_EQ(aStr.params[1].name, std::string("f"));
	SA_UTH_EQ(aStr.params[1].value, std::string("2.300000"));

	SA_UTH_EQ(aStr.params[2].name, std::string("a"));
	SA_UTH_EQ(aStr.params[2].value, std::string("A[6]"));

	SA_UTH_EQ(aStr.params[3].name, std::string("Foo(10, 4)"));
	SA_UTH_EQ(aStr.params[3].value, std::string("14"));

	SA_UTH_EQ(aStr.params[4].name, std::string("Bar<float, int>(0.5f, 2)"));
	SA_UTH_EQ(aStr.params[4].value, std::string("1.000000"));


	SA_UTH_EQ(aStr[2].name, aStr.params[2].name);
	SA_UTH_EQ(aStr[2].value, aStr.params[2].value);

	SA_UTH_EQ(aStr->begin(), aStr.params.begin());

#endif
}
