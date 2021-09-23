// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_SIGN_GUARD
#define SAPPHIRE_MATHS_SIGN_GUARD

#include <SA/Core/Debug.hpp>

/**
*	\file Sign.hpp
*
*	\brief \b Sign algorithm implementation.
* 
*	\ingroup Maths_Algorithms
*	\{
*/


namespace Sa
{
	namespace Maths
	{
		/**
		*	\brief \e Getter of the \b sign of the input as an int.
		*
		*	Return Values:
		*	_in > 0: 1
		*	_in < 0: -1
		*	_in == 0: 0
		* 
		*	\tparam T	Input type.
		* 
		*	\param[in] _in	Input to get sign.
		*
		*	\return Sign of the input.
		*/
		template <typename T>
		constexpr int32 Sign(T _in) noexcept
		{
			if constexpr (std::is_signed<T>::value)
				return (T(0) < _in) - (_in < T(0));
			else
			{
				(void)_in;
				SA_LOG(L"Get Sign of an unsigned type [" << typeid(T).name() << L"]", Warning, Maths);
				
				return T(1);
			}
		}
	}
}


/** \} */

#endif // GUARD
