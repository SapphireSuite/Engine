// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_UNIT_TEST_HELPER_GUARD
#define SAPPHIRE_UTH_UNIT_TEST_HELPER_GUARD

#include <SA/Collections/Debug>

#include <SA/Core/Algorithms/Equals.hpp>
#include <SA/Core/Algorithms/SizeOf.hpp>

#include <UTH/Instance.hpp>

namespace Sa::UTH
{
	/// \cond Internal

	#define __SA_UTH_CREATE_TEST(_func, ...) Sa::UTH::Test(\
		__SA_FILE_NAME,\
		__LINE__,\
		#_func,\
		_func,\
		SA_STR_ARGS(__VA_ARGS__)\
	)

	/// \endcond

	/**
	*	\brief Run a \e <b> Unit Test </b> using internal Equals implementation.
	*
	*	UTH::exit will be equal to EXIT_FAILURE (1) if at least one test failed.
	*
	*	\param[in] _lhs		Left hand side operand to test.
	*	\param[in] _rhs		Right hand side operand to test.
	*
	*	Additionnal params:
	*	uint32 size:		Size lenght to compare _lhs and _rhs are T*
	*	T epsilon			Epsilon value to allow threshold.
	*/
	#define SA_UTH_EQ(_lhs, _rhs, ...)\
	{\
		Sa::UTH::Intl::instance.Process(__SA_UTH_CREATE_TEST(\
			Sa::Equals(_lhs, _rhs, ##__VA_ARGS__),\
			_lhs, _rhs, ##__VA_ARGS__\
		));\
	}
}

#endif // GUARD
