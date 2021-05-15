// Copyright 2020 Sapphire development team.All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_COS_GUARD
#define SAPPHIRE_MATHS_COS_GUARD

#include <SA/Maths/Misc/Degree.hpp>
#include <SA/Maths/Misc/Radian.hpp>

/**
*	\file Cos.hpp
* 
*	\brief \b Cosinus method implementation.
* 
*	\ingroup Maths_Algorithms
*	\{
*/


namespace Sa
{
	namespace Maths
	{
		/**
		*	\brief \e Compute the \b cosine of the input.
		*
		*	\param[in] _in	Input in radian to compute cosine.
		*
		*	\return Cosine of the input.
		*/
		template <typename T>
		constexpr T Cos(Rad<T> _in) noexcept
		{
			return std::cos(static_cast<T>(_in));
		}

		/**
		*	\brief \e Compute the \b arc-cosine of the input.
		*
		*	\param[in] _in	Input to compute arc-cosine.
		*
		*	\return Arc-cosine in radian of the input.
		*/
		template <typename T>
		constexpr Rad<T> ACos(T _in) noexcept
		{
			return std::acos(_in);
		}
	}
}


/** \} */

#endif // GUARD
