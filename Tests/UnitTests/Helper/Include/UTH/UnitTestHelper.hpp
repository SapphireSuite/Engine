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

	#define __SA_UTH_CREATE_FT(_func, ...) Sa::UTH::Test(\
		__SA_FILE_NAME,\
		__LINE__,\
		#_func "(" #__VA_ARGS__ ")",\
		"true",\
		_func(__VA_ARGS__),\
		SA_STR_ARGS(__VA_ARGS__)\
	)

	/**
	*	Handle single test-function call.
	*	(_expRes) == _func(__VA_ARGS__)
	*	SA_STR_ARGS(_func(__VA_ARGS__), _expRes, ##__VA_ARGS__)
	*/
	#define __SA_UTH_CREATE_RFT(_expRes, _res, _func, ...) Sa::UTH::Test(\
		__SA_FILE_NAME,\
		__LINE__,\
		#_func "(" #__VA_ARGS__ ")",\
		#_expRes,\
		(_expRes) == _res,\
		ArgsStr(#_func "(" #__VA_ARGS__ "), " #_expRes ", " #__VA_ARGS__, _res, _expRes, ##__VA_ARGS__)\
	)


	#define __SA_UTH_CREATE_OPT(_lhs, _op, _rhs) Sa::UTH::Test(\
		__SA_FILE_NAME,\
		__LINE__,\
		#_lhs " " #_op " " #_rhs,\
		"",\
		_lhs _op _rhs,\
		SA_STR_ARGS(_lhs, _rhs)\
	)

	#define __SA_UTH_CREATE_ROPT(_expRes, _lhs, _op, _rhs) Sa::UTH::Test(\
		__SA_FILE_NAME,\
		__LINE__,\
		"(" #_lhs " " #_op " " #_rhs ")",\
		#_expRes,\
		(_lhs _op _rhs) == _expRes,\
		SA_STR_ARGS(_lhs _op _rhs, _expRes, _lhs, _rhs)\
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
		Sa::UTH::Intl::instance.Process(__SA_UTH_CREATE_FT(\
			Sa::Equals,\
			_lhs, _rhs, ##__VA_ARGS__\
		));\
	}

	/**
	*	\brief Run a \e <b> Unit Test </b> using a static function.
	*
	*	UTH::exit will be equal to EXIT_FAILURE (1) if at least one test failed.
	*
	*	\param[in] _func	Function to test with ... args.
	*/
	#define SA_UTH_SF(_func, ...)\
	{\
		Sa::UTH::Intl::instance.Process(__SA_UTH_CREATE_FT(\
			_func,\
			##__VA_ARGS__\
		));\
	}

	/**
	*	\brief Run a \e <b> Unit Test </b> using a static function with return value.
	*
	*	UTH::exit will be equal to EXIT_FAILURE (1) if at least one test failed.
	*
	*	\param[in] _res		Value to compare with _func result.
	*	\param[in] _func	Function to test with ... args.
	*/
	#define SA_UTH_RSF(_res, _func, ...)\
	{\
		Sa::UTH::Intl::instance.Process(__SA_UTH_CREATE_RFT(\
			_res,\
			_func(__VA_ARGS__),\
			_func,\
			##__VA_ARGS__\
		));\
	}

	/**
	*	\brief Run a \e <b> Unit Test </b> using a member function.
	*
	*	UTH::exit will be equal to EXIT_FAILURE (1) if at least one test failed.
	*
	*	\param[in] _caller	caller of the functin _func.
	*	\param[in] _func	Function to test with ... args.
	*/
	#define SA_UTH_MF(_caller, _func, ...)\
	{\
		Sa::UTH::Intl::instance.Process(__SA_UTH_CREATE_FT(\
			(_caller)._func,\
			##__VA_ARGS__\
		));\
	}

	/**
	*	\brief Run a \e <b> Unit Test </b> using a member function with return value.
	*
	*	UTH::exit will be equal to EXIT_FAILURE (1) if at least one test failed.
	*
	*	\param[in] _res		Value to compare with _func result.
	*	\param[in] _caller	caller of the functin _func.
	*	\param[in] _func	Function to test with ... args.
	*/
	#define SA_UTH_RMF(_res, _caller, _func, ...)\
	{\
		Sa::UTH::Intl::instance.Process(__SA_UTH_CREATE_RFT(\
			_res,\
			(_caller)._func(__VA_ARGS__),\
			(_caller)._func,\
			##__VA_ARGS__\
		));\
	}

	/**
	*	\brief Run a \e <b> Unit Test </b> using an operator.
	*
	*	UTH::exit will be equal to EXIT_FAILURE (1) if at least one test failed.
	*
	*	\param[in] _lhs		Left hand side operand to test.
	*	\param[in] _op		Operator of the test between _lhs and _rhs.
	*	\param[in] _rhs		Right hand side operand to test.
	*/
	#define SA_UTH_OP(_lhs, _op, _rhs)\
	{\
		Sa::UTH::Intl::instance.Process(__SA_UTH_CREATE_OPT(\
			_lhs, _op, _rhs\
		));\
	}

	/**
	*	\brief Run a \e <b> Unit Test </b> using an operator with return value.
	*
	*	UTH::exit will be equal to EXIT_FAILURE (1) if at least one test failed.
	*
	*	\param[in] _res		Value to compare with operator result.
	*	\param[in] _lhs		Left hand side operand to test.
	*	\param[in] _op		Operator of the test between _lhs and _rhs.
	*	\param[in] _rhs		Right hand side operand to test.
	*/
	#define SA_UTH_ROP(_res, _lhs, _op, _rhs)\
	{\
		Sa::UTH::Intl::instance.Process(__SA_UTH_CREATE_ROPT(\
			_res,\
			_lhs, _op, _rhs\
		));\
	}
}

#endif // GUARD
