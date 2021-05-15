// Copyright 2020 Sapphire development team.All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_RADIAN_GUARD
#define SAPPHIRE_MATHS_RADIAN_GUARD

#include <cmath>

#include <SA/Core/Algorithms/Equals.hpp>

#include <SA/Maths/Misc/Constants.hpp>
#include <SA/Maths/Algorithms/Sign.hpp>

/**
*	\file Radian.hpp
*
*	\brief \b Radian type implementation.
*
*	\ingroup Maths_Misc
*	\{
*/

namespace Sa
{
	template <typename T>
	class Deg;

	/**
	*	\brief Maths \b Radian type.
	* 
	*	Handle Degree / Radian \b conversion.
	*/
	template <typename T>
	class Rad
	{
		/// Handled value.
		T mHandle = T(0.0);

	public:
		/// \b Default contructor.
		Rad() = default;

		/**
		*	\brief \e Value constructor without conversion.
		*
		*	\param[in] _rad		The value in radian to assign.
		*/
		constexpr Rad(T _rad) noexcept;

		/**
		*	\brief \e Value constructor without conversion.
		*
		*	\param[in] _other		The value in radian to assign.
		*/
		template <typename TIn>
		constexpr Rad(Rad<TIn> _other) noexcept;

		/**
		*	\brief \e Value constructor from radian.
		*
		*	\param[in] _deg		The value in degree to assign.
		*/
		template <typename TIn>
		constexpr Rad(Deg<TIn> _deg) noexcept;


		/**
		*	\brief \e Compare 2 Rad.
		*
		*	\param[in] _other		Other Rad to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold compare.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(Rad _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept;


		/**
		*	\brief clamp this angle between [-Pi, Pi].
		*/
		void Clamp() noexcept;


		/**
		*	\brief \b Add Radian to handle.
		*
		*	\param[in] _rhs		radian to add.
		*
		*	\return self Radian.
		*/
		Rad& operator+=(Rad _rhs) noexcept;

		/**
		*	\brief \b Substract Radian to handle.
		*
		*	\param[in] _rhs		radian to substract.
		*
		*	\return self Radian.
		*/
		Rad& operator-=(Rad _rhs) noexcept;

		/**
		*	\brief \b Scale angle.
		*
		*	\param[in] _scale	scale to apply.
		*
		*	\return this radian scaled.
		*/
		Rad& operator*=(T _scale) noexcept;

		/**
		*	\brief \b Unscale angle.
		*
		*	\param[in] _scale	un-scale to apply.
		*
		*	\return this radian unscaled.
		*/
		Rad& operator/=(T _scale);


		/**
		*	\brief \e Compare 2 radian equality.
		*
		*	\param[in] _rhs		Other radian to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(Rad _rhs) const noexcept;

		/**
		*	\brief \e Compare 2 radian inequality.
		*
		*	\param[in] _rhs		Other radian to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(Rad _rhs) const noexcept;


		/**
		*	\brief Access the handled value.
		*
		*	\return handle as \c float without conversion.
		*/
		constexpr operator T() const noexcept;


	#if SA_LOGGING

		/**
		*	\brief ToString implementation
		*
		*	Convert this degree as a string without conversion.
		*
		*	\return this as a string.
		*/
		std::string ToString() const noexcept;

	#endif
	};


	/// Alias for float Rad.
	using Radf = Rad<float>;

	/// Alias for double Rad.
	using Radd = Rad<double>;

	/// Template alias of Rad
	template <typename T>
	using Radian = Rad<T>;

	/**
	*	\brief _rad \b literal operator.
	*
	*	\param[in] _lit		Operand to convert to Radian.
	*
	*	\return \c Radian without maths-conversion.
	*/
	constexpr Radf operator""_rad(uint64 _lit) noexcept;

	/**
	*	\brief _rad \b literal operator.
	*
	*	\param[in] _lit		Operand to convert to Radian.
	*
	*	\return \c Radian without maths-conversion.
	*/
	constexpr Radf operator""_rad(long double _lit) noexcept;
}


/** \} */

#include <SA/Maths/Misc/Radian.inl>

#endif // GUARD
