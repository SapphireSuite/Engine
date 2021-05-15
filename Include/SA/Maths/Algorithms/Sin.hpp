// Copyright 2020 Sapphire development team.All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_SIN_GUARD
#define SAPPHIRE_MATHS_SIN_GUARD

#include <SA/Maths/Misc/Degree.hpp>
#include <SA/Maths/Misc/Radian.hpp>

/**
*	\file Sin.hpp
*
*	\brief \b Sinus method implementation.
*
*	\ingroup Maths_Algorithms
*	\{
*/


namespace Sa
{
	namespace Maths
	{
		/**
		*	\brief \e Compute the \b sine of the input.
		*
		*	\param[in] _in	Input in radian to compute sine.
		*
		*	\return Sine of the input.
		*/
		template <typename T>
		constexpr T Sin(Rad<T> _in) noexcept
		{
			return std::sin(static_cast<T>(_in));
		}

		/**
		*	\brief \e Compute the \b arc-sine of the input.
		*
		*	\param[in] _in	Input to compute arc-sine.
		*
		*	\return Arc-sine in radian of the input.
		*/
		template <typename T>
		constexpr Rad<T> ASin(T _in) noexcept
		{
			return std::asin(_in);
		}
	}
}


/** \} */

#endif // GUARD
