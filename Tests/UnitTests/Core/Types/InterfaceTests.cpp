// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Types/Interface.hpp>
using namespace Sa;

namespace Sa::Interface_UT
{
	class A : public Interface
	{
	};

	class B : public A
	{
	};

	class C
	{
	};

	void Ref()
	{
		B b1;
		A& a1 = b1;
		const A& ca2 = b1;

		a1.As<B>();
		ca2.As<B>();

#if SA_LOGGING

		bool bException = false;
		
		try
		{
			a1.As<C>();
		}
		catch (const Exception_Nullptr& _e)
		{
			(void)_e;
			bException = true;
		}

		SA_UTH_EQ(bException, true);

#endif
	}

	void Ptr()
	{
		B b1;
		A* a1 = &b1;
		const A* ca2 = &b1;

		a1->AsPtr<B>();
		ca2->AsPtr<B>();

#if SA_LOGGING

		bool bException = false;

		try
		{
			a1->AsPtr<C>();
		}
		catch (const Exception_Nullptr& _e)
		{
			(void)_e;
			bException = true;
		}

		SA_UTH_EQ(bException, true);

#endif
	}
}

void InterfaceTest()
{
	using namespace Interface_UT;

	SA_UTH_GP(Ref());
	SA_UTH_GP(Ptr());
}
