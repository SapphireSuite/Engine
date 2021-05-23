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


	void ValueConstructors()
	{
		Function<int(int)> f1;
		SA_UTH_MF(f1, IsEmpty);

		Function<int(int)> f2 = Foo;
		SA_UTH_RMF(false, f2, IsEmpty);
		SA_UTH_EQ(f2(2), 4);

		A a;
		Function<int(int)> f3(&a, &A::Bar);
		SA_UTH_RMF(false, f3, IsEmpty);
		SA_UTH_EQ(f3(2), 6);
	}

	void MoveConstructors()
	{
		// Static function move.
		Function<int(int)> f1 = Foo;
		const Function<int(int)> f2 = std::move(f1);
		SA_UTH_MF(f1, IsEmpty);
		SA_UTH_EQ(f2(2), 4);

		// Member function move.
		A a;
		Function<int(int)> f3(&a, &A::Bar);
		const Function<int(int)> f4 = std::move(f3);
		SA_UTH_MF(f3, IsEmpty);
		SA_UTH_EQ(f4(2), 6);
	}

	void CopyConstructors()
	{
		// Static function copy.
		const Function<int(int)> f1 = Foo;
		const Function<int(int)> f2 = f1;
		SA_UTH_EQ(f2(2), 4);

		// Member function copy.
		A a;
		const Function<int(int)> f3(&a, &A::Bar);
		const Function<int(int)> f4 = f3;
		SA_UTH_EQ(f4(2), 6);
	}

	void Constructors()
	{
		SA_UTH_GP(ValueConstructors());
		SA_UTH_GP(MoveConstructors());
		SA_UTH_GP(CopyConstructors());
	}


	void Equals()
	{
		A a;
		const Function<int(int)> f1 = Foo;
		const Function<int(int)> f2(&a, &A::Bar);

		SA_UTH_MF(f1, Equals, f1);
		SA_UTH_RMF(false, f1, Equals, f2);

		SA_UTH_OP(f1, ==, f1);
		SA_UTH_ROP(false, f1, ==, f2);

		SA_UTH_OP(f1, !=, f2);
		SA_UTH_ROP(false, f1, !=, f1);


		Function<int(int)> f3 = Foo;
		SA_UTH_RMF(false, f3, IsEmpty);

		f3.Clear();
		SA_UTH_MF(f3, IsEmpty);
	}


	void MoveOperators()
	{
		// Static function move.
		Function<int(int)> f1 = Foo;
		Function<int(int)> f2;
		f2 = std::move(f1);
		SA_UTH_MF(f1, IsEmpty);
		SA_UTH_EQ(f2(2), 4);

		// Member function move.
		A a;
		Function<int(int)> f3(&a, &A::Bar);
		Function<int(int)> f4;
		f4 = std::move(f3);
		SA_UTH_MF(f3, IsEmpty);
		SA_UTH_EQ(f4(2), 6);
	}

	void CopyOperators()
	{
		// Static function copy.
		const Function<int(int)> f1 = Foo;
		Function<int(int)> f2;
		f2 = f1;
		SA_UTH_EQ(f2(2), 4);

		// Member function copy.
		A a;
		const Function<int(int)> f3(&a, &A::Bar);
		Function<int(int)> f4;
		f4 = f3;
		SA_UTH_EQ(f4(2), 6);
	}

	void Operators()
	{
		SA_UTH_GP(MoveOperators());
		SA_UTH_GP(CopyOperators());
	}
}

void FunctionTests()
{
	using namespace Function_UT;

	SA_UTH_GP(Constructors());
	SA_UTH_GP(Equals());
	SA_UTH_GP(Operators());
}
