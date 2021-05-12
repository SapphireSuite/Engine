// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Types/Variadics/Event.hpp>
using namespace Sa;

namespace Sa::Event_UT
{
//{ Variables

	int gFoo = 0;
	int RFoo(int i)
	{
		return gFoo += i;
	}
	void Foo(int i)
	{
		RFoo(i);
	}

	struct A
	{
		static int sBar;

		static int RBar(int i)
		{
			return sBar += 2 * i;
		}
		static void Bar(int i)
		{
			RBar(i);
		}
	};
	int A::sBar = 0;

	struct B
	{
		int pim = 0;

		int RPim(int i)
		{
			return pim += i;
		}
		void Pim(int i)
		{
			RPim(i);
		}
	};

	int gLambda = 0;
	auto rlambda = [](int _i) { return gLambda += 3 * _i; };
	auto lambda = [](int _i) { rlambda(_i); };

//}

//{ Tests

	void Empty()
	{
		Event<void(int)> e;

		SA_UTH_EQ(e.IsEmpty(), true);

		e += Foo;
		SA_UTH_EQ(e.IsEmpty(), false);

		e -= Foo;
		SA_UTH_EQ(e.IsEmpty(), true);

		e.Add(Foo);
		SA_UTH_EQ(e.IsEmpty(), false);

		e.Remove(Foo);
		SA_UTH_EQ(e.IsEmpty(), true);

		e.Add(Foo);
		e.RRemove(Foo);
		SA_UTH_EQ(e.IsEmpty(), true);
	}

	void Clear()
	{
		Event<void(int)> e;

		e.Clear();

		SA_UTH_EQ(e.IsEmpty(), true);

		e += Foo;

		e.Clear();
		SA_UTH_EQ(e.IsEmpty(), true);

		B b;
		e.Add(&b, &B::Pim);

		e.Clear();
		SA_UTH_EQ(e.IsEmpty(), true);

		e += Foo;
		e.Add(&b, &B::Pim);

		e.Clear();
		SA_UTH_EQ(e.IsEmpty(), true);
	}

	void Execute()
	{
		gFoo = 0;
		A::sBar = 0;
		gLambda = 0;

		Event<void(int)> e;

		e += Foo;
		e += &A::Bar;
		e += lambda;

		e(4);

		SA_UTH_EQ(gFoo, 4);
		SA_UTH_EQ(A::sBar, 8);
		SA_UTH_EQ(gLambda, 12);


		e += Foo;
		e -= lambda;

		B b1;
		e.Add(&b1, &B::Pim);

		e(7);
		SA_UTH_EQ(gFoo, 18);
		SA_UTH_EQ(A::sBar, 22);
		SA_UTH_EQ(gLambda, 12);
		SA_UTH_EQ(b1.pim, 7);


		SA_UTH_EQ(e.RRemove(Foo), true);
		SA_UTH_EQ(e.Remove(&b1, &B::Pim), true);

		e(2);
		SA_UTH_EQ(gFoo, 20);
		SA_UTH_EQ(A::sBar, 26);
		SA_UTH_EQ(gLambda, 12);
		SA_UTH_EQ(b1.pim, 7);

		SA_UTH_EQ(e.RRemove(Foo), true);
		SA_UTH_EQ(e.RRemove(A::Bar), true);
		SA_UTH_EQ(e.Remove(Foo), false);
		SA_UTH_EQ(e.Remove(A::Bar), false);

		e(1);
		SA_UTH_EQ(gFoo, 20);
		SA_UTH_EQ(A::sBar, 26);

		e += Foo;
		e.Clear();
		SA_UTH_EQ(gFoo, 20);
	}

	void ExecuteR()
	{
		gFoo = 0;
		A::sBar = 0;
		gLambda = 0;

		Event<int(int)> e;
		std::vector<int> res;

		e += RFoo;
		e += &A::RBar;
		e += rlambda;

		e.Execute(res, 4);

		SA_UTH_EQ(gFoo, 4);
		SA_UTH_EQ(A::sBar, 8);
		SA_UTH_EQ(gLambda, 12);

		int exp_res1[]{ 4, 8, 12 };
		SA_UTH_EQ(res.data(), exp_res1, 3);



		e += RFoo;
		e -= rlambda;

		B b1;
		e.Add(&b1, &B::RPim);

		e(res, 7);
		SA_UTH_EQ(gFoo, 18);
		SA_UTH_EQ(A::sBar, 22);
		SA_UTH_EQ(gLambda, 12);
		SA_UTH_EQ(b1.pim, 7);

		int exp_res2[]{ 4, 8, 12, 11, 22, 18, 7 }; // Append result at the end.
		SA_UTH_EQ(res.data(), exp_res2, 7);

		SA_UTH_EQ(e.RRemove(RFoo), true);
		SA_UTH_EQ(e.Remove(&b1, &B::RPim), true);

		e(2);
		SA_UTH_EQ(gFoo, 20);
		SA_UTH_EQ(A::sBar, 26);
		SA_UTH_EQ(gLambda, 12);
		SA_UTH_EQ(b1.pim, 7);

		SA_UTH_EQ(e.RRemove(RFoo), true);
		SA_UTH_EQ(e.RRemove(A::RBar), true);
		SA_UTH_EQ(e.Remove(RFoo), false);
		SA_UTH_EQ(e.Remove(A::RBar), false);

		e(1);
		SA_UTH_EQ(gFoo, 20);
		SA_UTH_EQ(A::sBar, 26);

		e += RFoo;
		e.Clear();
		SA_UTH_EQ(gFoo, 20);
	}

//}
}

void EventTests()
{
	using namespace Event_UT;

	SA_UTH_GP(Empty());
	SA_UTH_GP(Clear());
	SA_UTH_GP(Execute());
	SA_UTH_GP(ExecuteR());

}