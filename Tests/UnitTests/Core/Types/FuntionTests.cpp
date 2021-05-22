// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Core/Types/Variadics/Function.hpp>
using namespace Sa;

namespace Sa::Function_UT
{
	int Foo(int _i)
	{
		return _i * 2;
	}

	class A
	{
	public:
		int Bar(int _i)
		{
			return _i * 3;
		}
	};
}

void FunctionTests()
{
	using namespace Function_UT;

	Function<int(int)> f1;

	SA_UTH_MF(f1, IsEmpty);

	f1 = Foo;
	SA_UTH_EQ(f1(2), 4);

	A a;
	f1.Set(&a, &A::Bar);
	SA_UTH_EQ(f1(2), 6);

	SA_UTH_RMF(false, f1, IsEmpty);

	f1.Clear();
	SA_UTH_MF(f1, IsEmpty);
}
