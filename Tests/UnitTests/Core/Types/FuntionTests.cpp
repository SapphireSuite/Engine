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

		Function f2 = Foo;
		SA_UTH_RMF(false, f2, IsEmpty);
		SA_UTH_EQ(f2(2), 4);

		A a;
		Function f3(&a, &A::Bar);
		SA_UTH_RMF(false, f3, IsEmpty);
		SA_UTH_EQ(f3(2), 6);
	}

	void MoveConstructors()
	{
		// Static function move.
		Function f1 = Foo;
		const Function f2 = std::move(f1);
		SA_UTH_MF(f1, IsEmpty);
		SA_UTH_EQ(f2(2), 4);

		// Member function move.
		A a;
		Function f3(&a, &A::Bar);
		const Function f4 = std::move(f3);
		SA_UTH_MF(f3, IsEmpty);
		SA_UTH_EQ(f4(2), 6);
	}

	void CopyConstructors()
	{
		// Static function copy.
		const Function f1 = Foo;
		const Function f2 = f1;
		SA_UTH_EQ(f2(2), 4);

		// Member function copy.
		A a;
		const Function f3(&a, &A::Bar);
		const Function f4 = f3;
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
		const Function f1 = Foo;
		const Function f2(&a, &A::Bar);

		SA_UTH_MF(f1, Equals, f1);
		SA_UTH_RMF(false, f1, Equals, f2);

		SA_UTH_OP(f1, ==, f1);
		SA_UTH_ROP(false, f1, ==, f2);

		SA_UTH_OP(f1, !=, f2);
		SA_UTH_ROP(false, f1, !=, f1);


		Function f3 = Foo;
		SA_UTH_RMF(false, f3, IsEmpty);

		f3.Clear();
		SA_UTH_MF(f3, IsEmpty);
	}


	void MoveOperators()
	{
		// Static function move.
		Function f1 = Foo;
		Function<int(int)> f2;
		f2 = std::move(f1);
		SA_UTH_MF(f1, IsEmpty);
		SA_UTH_EQ(f2(2), 4);

		// Member function move.
		A a;
		Function f3(&a, &A::Bar);
		Function<int(int)> f4;
		f4 = std::move(f3);
		SA_UTH_MF(f3, IsEmpty);
		SA_UTH_EQ(f4(2), 6);
	}

	void CopyOperators()
	{
		// Static function copy.
		const Function f1 = Foo;
		Function<int(int)> f2;
		f2 = f1;
		SA_UTH_EQ(f2(2), 4);

		// Member function copy.
		A a;
		const Function f3(&a, &A::Bar);
		Function<int(int)> f4;
		f4 = f3;
		SA_UTH_EQ(f4(2), 6);
	}

	void Operators()
	{
		SA_UTH_GP(MoveOperators());
		SA_UTH_GP(CopyOperators());
	}

	void Functions()
	{
		SA_UTH_GP(Constructors());
		SA_UTH_GP(Equals());
		SA_UTH_GP(Operators());
	}
}

namespace Sa::PackedFunction_UT
{
	int Foo(int _i, int _j)
	{
		return _i * 2 + _j;
	}

	class A
	{
	public:
		int Bar(int _i, int _j)
		{
			return _i * 3 + _j;
		}
	};

	void ValueConstructors()
	{
		PackedFunction<int(int)> f1;
		SA_UTH_MF(f1, IsEmpty);

		PackedFunction f2(Foo, 2, 3);
		SA_UTH_RMF(false, f2, IsEmpty);
		SA_UTH_EQ(f2(), 7);

		A a;
		PackedFunction f3(&a, &A::Bar, 2, 2);
		SA_UTH_RMF(false, f3, IsEmpty);
		SA_UTH_EQ(f3(), 8);
	}

	void MoveConstructors()
	{
		// Static function move.
		PackedFunction f1(Foo, 2, 3);
		const PackedFunction f2 = std::move(f1);
		SA_UTH_MF(f1, IsEmpty);
		SA_UTH_EQ(f2(), 7);

		// Member function move.
		A a;
		PackedFunction f3(&a, &A::Bar, 2, 2);
		const PackedFunction f4 = std::move(f3);
		SA_UTH_MF(f3, IsEmpty);
		SA_UTH_EQ(f4(), 8);
	}

	void CopyConstructors()
	{
		// Static function copy.
		const PackedFunction f1(Foo, 2, 3);
		const PackedFunction f2 = f1;
		SA_UTH_EQ(f2(), 7);

		// Member function copy.
		A a;
		const PackedFunction f3(&a, &A::Bar, 2, 2);
		const PackedFunction f4 = f3;
		SA_UTH_EQ(f4(), 8);
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
		const PackedFunction f1(Foo, 2, 3);
		const PackedFunction f2(&a, &A::Bar, 2, 2);

		SA_UTH_MF(f1, Equals, f1);
		SA_UTH_RMF(false, f1, Equals, f2);

		SA_UTH_OP(f1, ==, f1);
		SA_UTH_ROP(false, f1, ==, f2);

		SA_UTH_OP(f1, !=, f2);
		SA_UTH_ROP(false, f1, !=, f1);


		PackedFunction f3(Foo, 2, 3);
		SA_UTH_RMF(false, f3, IsEmpty);

		f3.Clear();
		SA_UTH_MF(f3, IsEmpty);
	}

	void Set()
	{
		PackedFunction<int(int, int)> f1;
		f1.Set(Foo, 2, 3);
		SA_UTH_EQ(f1(), 7);

		A a;
		f1.Set(&a, &A::Bar, 2, 2);
		SA_UTH_EQ(f1(), 8);
	}

	void MoveOperators()
	{
		// Static function move.
		PackedFunction f1(Foo, 2, 3);
		PackedFunction<int(int, int)> f2;
		f2 = std::move(f1);
		SA_UTH_MF(f1, IsEmpty);
		SA_UTH_EQ(f2(), 7);

		// Member function move.
		A a;
		PackedFunction f3(&a, &A::Bar, 2, 2);
		PackedFunction<int(int, int)> f4;
		f4 = std::move(f3);
		SA_UTH_MF(f3, IsEmpty);
		SA_UTH_EQ(f4(), 8);
	}

	void CopyOperators()
	{
		// Static function copy.
		const PackedFunction f1(Foo, 2, 3);
		PackedFunction<int(int, int)> f2;
		f2 = f1;
		SA_UTH_EQ(f2(), 7);

		// Member function copy.
		A a;
		const PackedFunction f3(&a, &A::Bar, 2, 2);
		PackedFunction<int(int, int)> f4;
		f4 = f3;
		SA_UTH_EQ(f4(), 8);
	}

	void Operators()
	{
		SA_UTH_GP(MoveOperators());
		SA_UTH_GP(CopyOperators());
	}

	void PackedFunctions()
	{
		SA_UTH_GP(Constructors());
		SA_UTH_GP(Equals());
		SA_UTH_GP(Set());
		SA_UTH_GP(Operators());
	}
}

void FunctionTests()
{
	using namespace Function_UT;
	using namespace PackedFunction_UT;

	SA_UTH_GP(Functions());
	SA_UTH_GP(PackedFunctions());
}
