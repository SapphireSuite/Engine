// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Collections/Debug>
using namespace Sa;

namespace Sa::Exception_UT
{
	void DefaultTests()
	{
		SA_ASSERT(Default, AsChan, true, L"Default success test!");

#if SA_LOGGING

		try
		{
			SA_ASSERT(Default, AsChan, false, L"Default failure test!");
		}
		catch (const Exception_Default& _e)
		{
			std::wcout << L"Exception caugth: " << _e.msg << '\n' << std::endl;
		}

#else

		SA_ASSERT(Default, AsChan, false, L"Default failure test!");

#endif
	}

	void NonZeroTests()
	{
		SA_ASSERT(NonZero, AsChan, 4u, L"NonZero success test!");

#if SA_LOGGING

		try
		{
			SA_ASSERT(NonZero, AsChan, 0u, L"NonZero success test!");
		}
		catch (const Exception_NonZero& _e)
		{
			std::wcout << L"Exception caugth: " << _e.msg << '\n' << std::endl;
		}

#else

		SA_ASSERT(NonZero, AsChan, 0u, L"NonZero success test!");

#endif
	}

	void NullptrTests()
	{
		const int i = 8;
		const int* testPtr = &i;

		SA_ASSERT(Nullptr, AsChan, testPtr, L"Nullptr success test!");

		testPtr = nullptr;

#if SA_LOGGING

		try
		{
			SA_ASSERT(Nullptr, AsChan, testPtr, L"Nullptr success test!");
		}
		catch (const Exception_Nullptr& _e)
		{
			std::wcout << L"Exception caugth: " << _e.msg << '\n' << std::endl;
		}

#else

		SA_ASSERT(Nullptr, AsChan, testPtr, L"Nullptr success test!");

#endif
	}

	void OutOfRangeTests()
	{
		SA_ASSERT(OutOfRange, AsChan, 4u, 0u, 8u, L"OutOfRange success test");

#if SA_LOGGING

		try
		{
			SA_ASSERT(OutOfRange, AsChan, 10u, 0u, 8u, L"OutOfRange failure test");
		}
		catch (const Exception_OutOfRange& _e)
		{
			std::wcout << L"Exception caugth: " << _e.msg << '\n' << _e.details << '\n' << std::endl;

			SA_UTH_EQ(_e.currIndex, 10u);
			SA_UTH_EQ(_e.minBound, 0u);
			SA_UTH_EQ(_e.maxBound, 8u);
		}

#else

		SA_ASSERT(OutOfRange, AsChan, 4u, 0u, 8u, L"OutOfRange success test");

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