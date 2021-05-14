// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <UTH/UnitTestHelper.hpp>
using namespace Sa;

#include <SA/Collections/Debug>

bool BarT()
{
	//std::cout << "CCCCCBarT()" << std::endl;
	return true;
}

bool BarF()
{
	//std::cout << "CCCCCBarF()" << std::endl;
	return false;
}

bool Foo(int _i)
{
	std::cout << "CCCCCFoo()" << std::endl;
	return _i;
}

class A
{
public:
	bool Foo(int _i)
	{
		std::cout << "CCCCFoo()" << std::endl;
		return _i;
	}

	int Triple(int _i)
	{
		std::cout << "CCCCTriple()" << std::endl;
		return _i * 3;
	}

	static int Double(int _i)
	{
		std::cout << "CCCCDouble()" << std::endl;
		return _i * 2;
	}
};


int AAA()
{
	std::cout << "CCCCAAA()" << std::endl;

	return 0;
}

int main()
{
	const float f1 = 5.24f;
	const float f2 = 12.56f;
	const float f3 = f1 + std::numeric_limits<float>::epsilon();
	const float f4 = f1 + 2 * std::numeric_limits<float>::epsilon();

	SA_UTH_EQ(f1,f2);
	SA_UTH_EQ(f1, f3);
	SA_UTH_EQ(f1, f4, 2 * std::numeric_limits<float>::epsilon());

	SA_UTH_EQ(AAA(), 0);
	SA_UTH_EQ(AAA(), 1);


	SA_UTH_SF(BarT);
	SA_UTH_SF(BarF);

	uint32 i0 = 0u;
	uint32 i4 = 4u;
	uint32 i6 = 6u;

	SA_UTH_SF(Foo, i0);
	SA_UTH_SF(Foo, i4);

	SA_UTH_RSF(8, A::Double, i4);
	SA_UTH_RSF(12, A::Double, i6);
	SA_UTH_RSF(i4, A::Double, i6);

	A a1;
	SA_UTH_MF(a1, Foo, i0);
	SA_UTH_MF(a1, Foo, i4);

	SA_UTH_RMF(12, a1, Triple, i4);
	SA_UTH_RMF(i6, a1, Triple, i4);

	SA_UTH_OP(i6, ==, i4);
	SA_UTH_ROP(false, i6, ==, i4);
	SA_UTH_ROP(true, i6, ==, i4);
	 
	SA_UTH_OP(Foo(8), ==, Foo(0));
	SA_UTH_ROP(A::Double(0), Foo(8), == , Foo(0));
	SA_UTH_ROP(A::Double(1), Foo(8), == , Foo(0));

	return Sa::UTH::Intl::instance.Exit();
}