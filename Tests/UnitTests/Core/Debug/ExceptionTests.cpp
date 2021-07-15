// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <UnitTestHelper>

#include <SA/Collections/Debug>
using namespace Sa;

namespace Sa::Exception_UT
{
	void DefaultTests()
	{
		const bool bTrue = true;
		const bool bFalse = false;

		SA_ASSERT(Default, AsChan, bTrue, L"Default success test!");

#if SA_DEBUG

		try
		{
			SA_ASSERT(Default, AsChan, bFalse, L"Default failure test!");
		}
		catch (const Exception_Default& _e)
		{
			Debug::logger.Join();
			std::wcout << L"Exception caugth: " << _e.msg << '\n' << std::endl;
		}

#else

		(void)bTrue;
		(void)bFalse;

		SA_ASSERT(Default, AsChan, bFalse, L"Default failure test!");

#endif
	}

	void NonZeroTests()
	{
		const uint32 zeroI = 0u;
		const uint32 nonZeroI = 4u;

		SA_ASSERT(NonZero, AsChan, nonZeroI, L"NonZero success test!");

#if SA_DEBUG

		try
		{
			SA_ASSERT(NonZero, AsChan, zeroI, L"NonZero failure test!");
		}
		catch (const Exception_NonZero& _e)
		{
			Debug::logger.Join();
			std::wcout << L"Exception caugth: " << _e.msg << '\n' << std::endl;
		}

#else

		(void)zeroI;
		(void)nonZeroI;

		SA_ASSERT(NonZero, AsChan, zeroI, L"NonZero failure test!");

#endif
	}

	void NullptrTests()
	{
		const int i = 8;
		const int* testPtr = &i;

		SA_ASSERT(Nullptr, AsChan, testPtr, L"Nullptr success test!");

		testPtr = nullptr;

#if SA_DEBUG

		try
		{
			SA_ASSERT(Nullptr, AsChan, testPtr, L"Nullptr failure test!");
		}
		catch (const Exception_Nullptr& _e)
		{
			Debug::logger.Join();
			std::wcout << L"Exception caugth: " << _e.msg << '\n' << std::endl;
		}

#else

		SA_ASSERT(Nullptr, AsChan, testPtr, L"Nullptr failure test!");

#endif
	}

	void OutOfRangeTests()
	{
		const uint32 min = 0u;
		const uint32 max = 8u;
		const uint32 goodI = 4u;
		const uint32 wrongI = 10u;

		SA_ASSERT(OutOfRange, AsChan, goodI, min, max, L"OutOfRange success test");

#if SA_DEBUG

		try
		{
			SA_ASSERT(OutOfRange, AsChan, wrongI, min, max, L"OutOfRange failure test");
		}
		catch (const Exception_OutOfRange& _e)
		{
			Debug::logger.Join();
			std::wcout << L"Exception caugth: " << _e.msg << '\n' << _e.details << '\n' << std::endl;

			SA_UTH_EQ(_e.currIndex, wrongI);
			SA_UTH_EQ(_e.minBound, min);
			SA_UTH_EQ(_e.maxBound, max);
		}

#else

		(void)min;
		(void)max;
		(void)goodI;
		(void)wrongI;

		SA_ASSERT(OutOfRange, AsChan, wrongI, min, max, L"OutOfRange failure test");

#endif
	}
}

void ExceptionTests()
{
	using namespace Exception_UT;

#if SA_LOGGING
	Debug::logger.levelFlags = LogLevel::Max;
#endif

	SA_UTH_GP(DefaultTests());
	SA_UTH_GP(NonZeroTests());
	SA_UTH_GP(NullptrTests());
	SA_UTH_GP(OutOfRangeTests());
}