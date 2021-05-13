// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_EQUALS_GUARD
#define SAPPHIRE_CORE_EQUALS_GUARD

#include <limits>

#include <SA/Core/Types/Int.hpp>
#include <SA/Core/Types/Variadics/HasMember.hpp>

/**
*	\file Equals.hpp
* 
*	\brief \b Define Sapphire Engine Equals algorithms.
* 
*	\ingroup Core_Algorithms
*	\{
*/


namespace Sa
{
	/// \cond Internal

	namespace Intl
	{
		SA_DEFINE_HAS_MEMBER(Equals)
	}

	/// \endcond

	/**
	*	\brief Helper Equals function using epsilon.
	*
	*	\tparam T			Type of operands.
	*	\tparam EpsT		Type of epsilon.
	*
	*	\param[in] _lhs		Left hand side operand to compare.
	*	\param[in] _rhs		Right hand side operand to compare.
	*	\param[in] _epsilon	Epsilon value for threshold compare.
	*
	*	\return	True on equality, otherwise false.
	*/
	template <typename T, typename EpsT = T>
	bool Equals(const T& _lhs, const T& _rhs, EpsT _epsilon = std::numeric_limits<T>::epsilon())
	{
		// Is native type?
		if constexpr (std::is_arithmetic<T>::value)
		{
			if constexpr (std::is_integral<T>::value)
			{
				// Simple comparison for int.

				return _lhs == _rhs;
			}
			else
			{
				// Epsilon comparison for floating points.

				return std::abs(_lhs - _rhs) <= _epsilon;
			}
		}
		else if constexpr (Intl::HMOT_Equals<T, bool(const T&, EpsT) const>::value)
		{
			// User defined Equals method.

			return _lhs.Equals(_rhs, _epsilon);
		}
		else
		{
			// Default comparison method.

			return _lhs == _rhs;
		}
	}

	/**
	*	\brief Helper Equals function for tab using epsilon.
	*
	*	\tparam T		Type of operands.
	*	\tparam EpsT	Type of epsilon.
	*
	*	\param[in] _lhs		Left hand side operand to compare.
	*	\param[in] _rhs		Right hand side operand to compare.
	*	\param[in] _size	Size of tabs to compare compare.
	*	\param[in] _epsilon	Epsilon value for threshold compare.
	*
	*	\return	True on equality, otherwise false.
	*/
	template <typename T, typename EpsT = T>
	bool Equals(const T* _lhs, const T* _rhs, uint32 _size, EpsT _epsilon = std::numeric_limits<T>::epsilon())
	{
		for (uint32 i = 0u; i < _size; ++i)
		{
			if (!Equals(_lhs[i], _rhs[i], _epsilon))
				return false;
		}

		return true;
	}

	/**
	*	\brief \e Compare one T to 0.
	*
	*	\tparam T		Type of input.
	*	\tparam EpsT	Type of epsilon.
	* 
	*	\param[in] _in			Operand to compare to 0.
	*	\param[in] _epsilon	Allowed threshold to accept equality.
	*
	*	\return Whether _in is equal to 0.
	*/
	template <typename T, typename EpsT = T>
	constexpr bool Equals0(T _in, EpsT _epsilon = std::numeric_limits<T>::epsilon()) noexcept
	{
		return Equals(_in, T(), _epsilon);
	}

	/**
	*	\brief \e Compare one T to 1.
	*
	*	\tparam T		Type of input.
	*	\tparam EpsT	Type of epsilon.
	* 
	*	\param[in] _in			Operand to compare to 1.
	*	\param[in] _epsilon	Allowed threshold to accept equality.
	*
	*	\return Whether _in is equal to 1.
	*/
	template <typename T, typename EpsT = T>
	constexpr bool Equals1(T _in, EpsT _epsilon = std::numeric_limits<T>::epsilon()) noexcept
	{
		return Equals(_in, T(1), _epsilon);
	}
}


/** \} */

#endif // GUARD
