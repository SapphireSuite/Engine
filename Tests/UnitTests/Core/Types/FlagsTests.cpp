// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Types/Variadics/Flags.hpp>
using namespace Sa;

namespace Flags_UT
{
	enum class TestFlags : uint8
	{
		None = 0u,

		F1 = 1u << 0u,
		F2 = 1u << 1u,
		F3 = 1u << 2u,
		F4 = 1u << 3u,
		F5 = 1u << 4u,
		F6 = 1u << 5u,
		F7 = 1u << 6u,
		F8 = 1u << 7u,

		Max = 0xFF
	};
	SA_DEFINE_ENUM_FLAGS(TestFlags);


	void EnumOp()
	{
		SA_UTH_GPB(Operator | )
		{
			const uint8 b1 = TestFlags::F1 | TestFlags::F2;
			const uint8 b1_res = static_cast<uint8>(TestFlags::F1) | static_cast<uint8>(TestFlags::F2);
			SA_UTH_EQ(b1, b1_res);

			const uint8 b2 = b1 | TestFlags::F6;
			const uint8 b2_res = b1_res | static_cast<uint8>(TestFlags::F6);
			SA_UTH_EQ(b2, b2_res);

			const uint8 b3 = TestFlags::F1 | TestFlags::F2 | TestFlags::F6;
			const uint8 b3_res = static_cast<uint8>(TestFlags::F1) | static_cast<uint8>(TestFlags::F2) | static_cast<uint8>(TestFlags::F6);
			SA_UTH_EQ(b3, b3_res);

			uint8 b4 = b3;
			b4 |= TestFlags::F7;
			const uint8 b4_res = b3_res | static_cast<uint8>(TestFlags::F7);
			SA_UTH_EQ(b4, b4_res);
		}
		SA_UTH_GPE();


		SA_UTH_GPB(Operator&)
		{
			const uint8 b26 = TestFlags::F2 | TestFlags::F6;
			const uint8 bmax = static_cast<uint8>(TestFlags::Max);

			const uint8 b1 = TestFlags::F2 & TestFlags::Max;
			SA_UTH_EQ(b1, static_cast<uint8>(TestFlags::F2));

			const uint8 b2 = bmax & TestFlags::F6;
			SA_UTH_EQ(b2, static_cast<uint8>(TestFlags::F6));

			const uint8 b3 = b26 & TestFlags::Max & TestFlags::F6;
			SA_UTH_EQ(b3, static_cast<uint8>(TestFlags::F6));

			uint8 b4 = b1;
			b4 &= TestFlags::F7;
			SA_UTH_EQ(b4, 0_ui8);
		}
		SA_UTH_GPE();


		SA_UTH_GPB(Operator^)
		{
			const uint8 b1 = TestFlags::F1 ^ TestFlags::F2;
			const uint8 b1_res = static_cast<uint8>(TestFlags::F1) ^ static_cast<uint8>(TestFlags::F2);
			SA_UTH_EQ(b1, b1_res);

			const uint8 b2 = b1 ^ TestFlags::F1;
			SA_UTH_EQ(b2, static_cast<uint8>(TestFlags::F2));

			const uint8 b3 = TestFlags::F1 ^ TestFlags::F2 ^ TestFlags::F6 ^ TestFlags::F2;
			const uint8 b3_res = static_cast<uint8>(TestFlags::F1) | static_cast<uint8>(TestFlags::F6);
			SA_UTH_EQ(b3, b3_res);


			uint8 b4 = b1;
			b4 ^= TestFlags::F1;
			SA_UTH_EQ(b4, static_cast<uint8>(TestFlags::F2));
		}
		SA_UTH_GPE();


		SA_UTH_GPB(Operator ~)
		{
			uint8 b1 = ~TestFlags::F2;
			uint8 b1_res = static_cast<uint8>(TestFlags::Max) - static_cast<uint8>(TestFlags::F2);
			SA_UTH_EQ(b1, b1_res);
		}
		SA_UTH_GPE();
	}

	void Constructors()
	{
		Flags<TestFlags> f1;
		SA_UTH_EQ(static_cast<uint8>(f1), 0_ui8);

		Flags<TestFlags> f2 = TestFlags::F2;
		SA_UTH_EQ(static_cast<uint8>(f2), static_cast<uint8>(TestFlags::F2));

		Flags<TestFlags> f3 = TestFlags::F1 | TestFlags::F2;
		SA_UTH_EQ(static_cast<uint8>(f3), (TestFlags::F1 | TestFlags::F2));

		Flags<TestFlags> f4 = f3;
		SA_UTH_EQ(static_cast<uint8>(f4), static_cast<uint8>(f3));
	}

	void Equals()
	{
		const Flags<TestFlags> f1 = TestFlags::F5;
		const Flags<TestFlags> f2 = TestFlags::F2 | TestFlags::F8;
		const Flags<TestFlags> f3 = f2;

		SA_UTH_MF(f1, Equals, TestFlags::F5);
		SA_UTH_OP(f1, ==, TestFlags::F5);

		SA_UTH_MF(f2, Equals, (TestFlags::F2 | TestFlags::F8));
		SA_UTH_OP(f2, ==, (TestFlags::F2 | TestFlags::F8));

		SA_UTH_MF(f2, Equals, f3);
		SA_UTH_OP(f2, ==, f3);


		SA_UTH_RMF(false, f1, Equals, TestFlags::F4);
		SA_UTH_OP(f1, !=, TestFlags::F4);

		SA_UTH_RMF(false, f2, Equals, (TestFlags::F6 | TestFlags::F8));
		SA_UTH_OP(f2, !=, (TestFlags::F6 | TestFlags::F8));

		SA_UTH_RMF(false, f2, Equals, f1);
		SA_UTH_OP(f2, !=, f1);
	}

	void IsSet()
	{
		Flags<TestFlags> f1 = TestFlags::F2 | TestFlags::F4;
		SA_UTH_RMF(true, f1, IsSet, TestFlags::F2);
		SA_UTH_RMF(true, f1, IsSet, TestFlags::F4);
		SA_UTH_RMF(false, f1, IsSet, TestFlags::F3);

		SA_UTH_RMF(true, f1, AreSet, TestFlags::F2 | TestFlags::F4);
		SA_UTH_RMF(true, f1, AreSet, static_cast<uint8>(TestFlags::F2));
		SA_UTH_RMF(false, f1, AreSet, TestFlags::F1 | TestFlags::F2 | TestFlags::F4);
	}

	void AddRemove()
	{
		Flags<TestFlags> f1;
		f1.Add(TestFlags::F5);
		SA_UTH_OP(f1, ==, TestFlags::F5);

		f1.Add(TestFlags::F2 | TestFlags::F3);
		SA_UTH_OP(f1, ==, TestFlags::F2 | TestFlags::F3 | TestFlags::F5);

		f1.Remove(TestFlags::F5);
		SA_UTH_OP(f1, ==, TestFlags::F2 | TestFlags::F3);

		f1.Remove(TestFlags::F2 | TestFlags::F3);
		SA_UTH_OP(f1, ==, 0_ui8);
	}

	void Operators()
	{
		SA_UTH_GPB(Operator = )
		{
			Flags<TestFlags> f1;

			f1 = TestFlags::F8;
			SA_UTH_OP(f1, ==, TestFlags::F8);

			f1 = TestFlags::F5 | TestFlags::F7;
			SA_UTH_OP(f1, ==, (TestFlags::F5 | TestFlags::F7));

			const Flags<TestFlags> f2 = TestFlags::F2 | TestFlags::F4;

			f1 = f2;
			SA_UTH_EQ(f1, f2);
		}
		SA_UTH_GPE();


		SA_UTH_GPB(Operator | )
		{
			Flags<TestFlags> f1 = TestFlags::F8;

			uint8 b78 = f1 | TestFlags::F7;
			SA_UTH_EQ(b78, (TestFlags::F7 | TestFlags::F8));

			f1 |= TestFlags::F6;
			SA_UTH_OP(f1, ==, (TestFlags::F6 | TestFlags::F8));

			f1 |= b78;
			SA_UTH_OP(f1, ==, (TestFlags::F6 | TestFlags::F7 | TestFlags::F8));

			const Flags<TestFlags> f2 = TestFlags::F2;
			f1 |= f2;
			SA_UTH_OP(f1, ==, (TestFlags::F2 | TestFlags::F6 | TestFlags::F7 | TestFlags::F8));

		}
		SA_UTH_GPE();


		SA_UTH_GPB(Operator&)
		{
			Flags<TestFlags> f1 = TestFlags::F2 | TestFlags::F6 | TestFlags::F7 | TestFlags::F8;

			uint8 b78 = f1 & (TestFlags::F1 | TestFlags::F6 | TestFlags::F7);
			SA_UTH_EQ(b78, (TestFlags::F6 | TestFlags::F7));

			f1 &= TestFlags::F1 | TestFlags::F2 | TestFlags::F6;
			SA_UTH_OP(f1, ==, (TestFlags::F2 | TestFlags::F6));

			f1 &= b78;
			SA_UTH_OP(f1, ==, TestFlags::F6);

			const Flags<TestFlags> f2 = TestFlags::F2 | TestFlags::F6 | TestFlags::F8;
			f1 &= f2;
			SA_UTH_OP(f1, ==, TestFlags::F6);

		}
		SA_UTH_GPE();


		SA_UTH_GPB(Operator^)
		{
			Flags<TestFlags> f1 = TestFlags::F2 | TestFlags::F6 | TestFlags::F7 | TestFlags::F8;

			uint8 b78 = f1 ^ (TestFlags::F1 | TestFlags::F6 | TestFlags::F7);
			SA_UTH_EQ(b78, (TestFlags::F1 | TestFlags::F2 | TestFlags::F8));

			f1 ^= TestFlags::F1 | TestFlags::F2 | TestFlags::F6;
			SA_UTH_OP(f1, ==, (TestFlags::F1 | TestFlags::F7 | TestFlags::F8));

			f1 ^= b78;
			SA_UTH_OP(f1, ==, (TestFlags::F2 | TestFlags::F7));

			const Flags<TestFlags> f2 = TestFlags::F1 | TestFlags::F2 | TestFlags::F7 | TestFlags::F8;
			f1 ^= f2;
			SA_UTH_OP(f1, ==, (TestFlags::F1 | TestFlags::F8));

		}
		SA_UTH_GPE();


		SA_UTH_GPB(Operator ~)
		{
			const Flags<TestFlags> f1 = TestFlags::F2 | TestFlags::F6 | TestFlags::F7 | TestFlags::F8;
			const Flags<TestFlags> f2 = ~f1;

			SA_UTH_OP(f2, ==, (TestFlags::F1 | TestFlags::F3 | TestFlags::F4 | TestFlags::F5));
		}
		SA_UTH_GPE();

		SA_UTH_GPB(Operator Cast)
		{
			const Flags<TestFlags> f1 = TestFlags::F2 | TestFlags::F8;

			const uint8 b1 = f1;
			SA_UTH_OP(f1, ==, b1);

			const Flags<TestFlags> f2;

			bool bb1 = f1;
			bool bb2 = f2;
			SA_UTH_OP(bb1, ==, true);
			SA_UTH_OP(bb2, ==, false);
		}
		SA_UTH_GPE();
	}
}

template <>
std::string UTH::ToString(const Flags<Flags_UT::TestFlags>& _flags)
{
	return std::to_string(_flags);
}

void FlagsTests()
{
	using namespace Flags_UT;

	SA_UTH_GP(EnumOp());
	SA_UTH_GP(Constructors());
	SA_UTH_GP(Equals());
	SA_UTH_GP(IsSet());
	SA_UTH_GP(AddRemove());
	SA_UTH_GP(Operators());
}
