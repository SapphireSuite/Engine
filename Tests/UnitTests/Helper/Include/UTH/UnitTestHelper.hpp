// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_UNIT_TEST_HELPER_GUARD
#define SAPPHIRE_UTH_UNIT_TEST_HELPER_GUARD

#include <SA/Core/Debug.hpp>

#include <SA/Core/Algorithms/Equals.hpp>
#include <SA/Core/Algorithms/SizeOf.hpp>

#include <UTH/Instance.hpp>

// TODO: Remove later, use Engine Random impl.
#include <UTH/Random.hpp>

/**
*	\file UnitTestHelper.hpp
* 
*	\brief UTH Helper macro definition file.
*	Include \<UnitTestHelper\>
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
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
		auto&& sLhs = _lhs;\
		auto&& sRhs = _rhs;\
		bool bRes = Sa::Equals(sLhs, sRhs, ##__VA_ARGS__);\
	\
		Sa::UTH::Intl::instance.Process(Sa::UTH::TestLog(\
			__SA_FILE_NAME,\
			__LINE__,\
			SA_STR(Sa::Equals(_lhs, _rhs, ##__VA_ARGS__)),\
			"",\
			bRes,\
			Sa::ArgsStr(#_lhs ", " #_rhs ", " #__VA_ARGS__, sLhs, sRhs, ##__VA_ARGS__)\
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
		bool bRes = _func(__VA_ARGS__);\
	\
		Sa::UTH::Intl::instance.Process(Sa::UTH::TestLog(\
			__SA_FILE_NAME,\
			__LINE__,\
			SA_STR(_func(__VA_ARGS__)),\
			"true",\
			bRes,\
			SA_STR_ARGS(__VA_ARGS__)\
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
		auto&& sRes = _res;\
		auto result = _func(__VA_ARGS__);\
		bool bRes = result == sRes;\
	\
		Sa::UTH::Intl::instance.Process(Sa::UTH::TestLog(\
			__SA_FILE_NAME,\
			__LINE__,\
			SA_STR(_func(__VA_ARGS__)),\
			#_res,\
			bRes,\
			Sa::ArgsStr(SA_STR(_func(__VA_ARGS__)) ", " #_res ", " #__VA_ARGS__, result, sRes, ##__VA_ARGS__)\
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
		bool bRes = (_caller)._func(__VA_ARGS__);\
	\
		Sa::UTH::Intl::instance.Process(Sa::UTH::TestLog(\
			__SA_FILE_NAME,\
			__LINE__,\
			SA_STR((_caller)._func(__VA_ARGS__)),\
			"true",\
			bRes,\
			SA_STR_ARGS(_caller, ##__VA_ARGS__)\
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
		auto&& sRes = _res;\
		auto result = (_caller)._func(__VA_ARGS__);\
		bool bRes = result == sRes;\
	\
		Sa::UTH::Intl::instance.Process(Sa::UTH::TestLog(\
			__SA_FILE_NAME,\
			__LINE__,\
			SA_STR((_caller)._func(__VA_ARGS__)),\
			#_res,\
			bRes,\
			Sa::ArgsStr(SA_STR((_caller)._func(__VA_ARGS__)) ", " #_res ", " #__VA_ARGS__, result, sRes, ##__VA_ARGS__)\
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
		auto&& sLhs = _lhs;\
		auto&& sRhs = _rhs;\
		bool bRes = sLhs _op sRhs;\
	\
		Sa::UTH::Intl::instance.Process(Sa::UTH::TestLog(\
			__SA_FILE_NAME,\
			__LINE__,\
			SA_STR(_lhs _op _rhs),\
			"",\
			bRes,\
			Sa::ArgsStr(#_lhs ", " #_rhs, sLhs, sRhs)\
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
		auto&& sLhs = _lhs;\
		auto&& sRhs = _rhs;\
		auto&& sRes = _res;\
		auto result = sLhs _op sRhs;\
		bool bRes = result == sRes;\
	\
		Sa::UTH::Intl::instance.Process(Sa::UTH::TestLog(\
			__SA_FILE_NAME,\
			__LINE__,\
			SA_STR(_lhs _op _rhs),\
			#_res,\
			bRes,\
			Sa::ArgsStr(SA_STR(_lhs _op _rhs) ", " #_res ", " #_lhs ", " #_rhs, result, sRes, sLhs, sRhs)\
		));\
	}

	/**
	*	\brief Begin a group of test with name.
	* 
	*	\param[in] _name	Name of the group.
	*/
	#define SA_UTH_GPB(_name) Sa::UTH::Intl::instance.BeginGroup(SA_WSTR(_name));

	/**
	*	\brief End current group.
	*/
	#define SA_UTH_GPE() Sa::UTH::Intl::instance.EndGroup();


	/**
	*	\brief Run a group of tests from a single function.
	*
	*	\param[in] _func	The function that own the group of tests.
	*/
	#define SA_UTH_GP(_func)\
	{\
		SA_UTH_GPB(_func)\
		_func;\
		SA_UTH_GPE()\
	}
}


/** \} */

#endif // GUARD
