// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Types/Variadics/HasMember.hpp>
using namespace Sa;

namespace Sa::HasMember_UT
{
	SA_DEFINE_HAS_MEMBER(X);
	SA_DEFINE_HAS_MEMBER(Foo);
	SA_DEFINE_HAS_MEMBER(Bar);

	struct A
	{
		float X;

		void Foo()
		{
		}
	};

	struct B
	{
		float Y;

		template <typename T>
		void Bar()
		{
		}
	};

	struct C
	{
		int X;

		void Foo(int _i)
		{
			(void)_i;
		}
	};
}

void HasMemberTests()
{
	using namespace HasMember_UT;

	SA_UTH_EQ(HM_X<A>::value, true);
	SA_UTH_EQ(HM_X<B>::value, false);
	SA_UTH_EQ(HM_X<C>::value, true);

	SA_UTH_EQ((HMOT_X<A, float>::value), true);
	SA_UTH_EQ((HMOT_X<B, float>::value), false);
	SA_UTH_EQ((HMOT_X<C, float>::value), false);


	SA_UTH_EQ(HM_Foo<A>::value, true);
	SA_UTH_EQ(HM_Foo<B>::value, false);
	SA_UTH_EQ(HM_Foo<C>::value, true);

	SA_UTH_EQ((HMOT_Foo<A, void()>::value), true);
	SA_UTH_EQ((HMOT_Foo<B, void()>::value), false);
	SA_UTH_EQ((HMOT_Foo<C, void()>::value), false);
	SA_UTH_EQ((HMOT_Foo<C, void(int)>::value), true);


	SA_UTH_EQ(HM_Bar<A>::value, false);
	SA_UTH_EQ(HM_Bar<B>::value, true);
}
