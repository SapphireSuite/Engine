// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Core/Misc/Random.hpp>
using namespace Sa;

namespace Sa::Random_UT
{
	void Generator()
	{
		RandomEngine en1{ 12 };
		const uint32 gen1[]{
			Random<uint32>::Value(1u, 10u, &en1),
			Random<uint32>::Value(1u, 10u, &en1),
			Random<uint32>::Value(1u, 10u, &en1),
			Random<uint32>::Value(1u, 10u, &en1),
			Random<uint32>::Value(1u, 10u, &en1),
			Random<uint32>::Value(1u, 10u, &en1),
			Random<uint32>::Value(1u, 10u, &en1),
			Random<uint32>::Value(1u, 10u, &en1),
			Random<uint32>::Value(1u, 10u, &en1),
			Random<uint32>::Value(1u, 10u, &en1)
		};

		const uint32 res1[]{ 7u, 5u, 2u, 4u, 5u, 9u, 7u, 5u, 2u, 7u };
		// const uint32 res1[]{ 1u, 6u, 1u, 5u, 4u, 6u, 6u, 2u, 2u, 2u }; // Unix

		SA_UTH_EQ(gen1, res1, 10u);
		//for (uint32 i = 0u; i < 10u; ++i)
		//	SA_UTH_EQ(gen1[i], res1[i]);


		RandomEngine en2{ 3024 };
		const uint32 gen2[]{
			Random<uint32>::Value(1u, 10u, &en2),
			Random<uint32>::Value(1u, 10u, &en2),
			Random<uint32>::Value(1u, 10u, &en2),
			Random<uint32>::Value(1u, 10u, &en2),
			Random<uint32>::Value(1u, 10u, &en2),
			Random<uint32>::Value(1u, 10u, &en2),
			Random<uint32>::Value(1u, 10u, &en2),
			Random<uint32>::Value(1u, 10u, &en2),
			Random<uint32>::Value(1u, 10u, &en2),
			Random<uint32>::Value(1u, 10u, &en2)
		};

		const uint32 res2[]{ 8u, 9u, 7u, 2u, 7u, 6u, 8u, 9u, 5u, 4u };
		// const uint32 res2[]{ 1u, 7u, 9u, 9u, 1u, 2u, 3u, 8u, 2u, 5u }; // Unix.

		SA_UTH_EQ(gen2, res2, 10u);
		//for (uint32 i = 0u; i < 10u; ++i)
		//	SA_UTH_EQ(gen2[i], res2[i]);

		// Same seed as en1.
		RandomEngine en3{ 12 };
		const uint32 gen3[]{
			Random<uint32>::Value(1u, 10u, &en3),
			Random<uint32>::Value(1u, 10u, &en3),
			Random<uint32>::Value(1u, 10u, &en3),
			Random<uint32>::Value(1u, 10u, &en3),
			Random<uint32>::Value(1u, 10u, &en3),
			Random<uint32>::Value(1u, 10u, &en3),
			Random<uint32>::Value(1u, 10u, &en3),
			Random<uint32>::Value(1u, 10u, &en3),
			Random<uint32>::Value(1u, 10u, &en3),
			Random<uint32>::Value(1u, 10u, &en3)
		};

		SA_UTH_EQ(gen3, gen1, 10u);
		//for (uint32 i = 0u; i < 10u; ++i)
		//	SA_UTH_EQ(gen3[i], gen1[i]);
	}

	void Bool()
	{
		RandomEngine en{ 3 };
		const bool gen[]{
			Random<bool>::Value(&en),
			Random<bool>::Value(&en),
			Random<bool>::Value(&en),
			Random<bool>::Value(&en),
			Random<bool>::Value(&en),
		};

		const bool res[]{ false, false, true, true, false };
		//const bool res[]{ false, false, false, false, true }; // Unix.

		SA_UTH_EQ(gen, res, 5u);
		//for (uint32 i = 0u; i < 5u; ++i)
		//	SA_UTH_EQ(gen[i], res[i]);
	}

	void Float()
	{
		bool bError = false;
		float fError = -1.0f;
		double dError = -1.0;

		for (uint32 i = 0u; i < 100u; ++i)
		{
			const float f = Random<float>::Value01();
			if (f <= 0.0f || f > 1.0f)
			{
				bError = true;
				fError = f;
				break;
			}

			const double d = Random<double>::Value01();
			if (d <= 0.0 || d > 1.0)
			{
				bError = true;
				dError = d;
				break;
			}
		}

		SA_UTH_EQ(bError, false);

		if (bError)
		{
			if (fError != -1.0f)
			{
				SA_UTH_OP(fError, <= , 0.0f);
				SA_UTH_OP(fError, > , 1.0f);
			}

			if (dError != -1.0)
			{
				SA_UTH_OP(dError, <= , 0.0);
				SA_UTH_OP(dError, > , 1.0);
			}
		}
	}
}

void RandomTests()
{
	using namespace Random_UT;

	SA_UTH_GP(Generator());
	SA_UTH_GP(Bool());
	SA_UTH_GP(Float());
}
