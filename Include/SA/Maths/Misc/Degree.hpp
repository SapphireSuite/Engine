// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_DEGREE_GUARD
#define SAPPHIRE_MATHS_DEGREE_GUARD

#include <cmath>

#include <SA/Core/Algorithms/Equals.hpp>

#include <SA/Maths/Misc/Constants.hpp>
#include <SA/Maths/Algorithms/Sign.hpp>

/**
*	\file Degree.hpp
*
*	\brief \b Degree type implementation.
*
*	\ingroup Maths_Misc
*	\{
*/


namespace Sa
{
	template <typename T>
	class Rad;

	/**
	*	\brief Maths \b Degree type.
	* 
	*	Handle Degree / Radian \b conversion.
	*/
	template <typename T>
	class Deg
	{
		/// Handled value.
		T mHandle = T(0);

	public:
		/// Default contructor.
		Deg() = default;

		/**
		*	\brief \e Value constructor without conversion.
		*
		*	\param[in] _deg		The value in degree to assign.
		*/
		constexpr Deg(T _deg) noexcept;

		/**
		*	\brief \e Value constructor without conversion.
		*
		*	\param[in] _other		The value in degree to assign.
		*/
		template <typename TIn>
		constexpr Deg(Deg<TIn> _other) noexcept;

		/**
		*	\brief \e Value constructor from radian.
		*
		*	\param[in] _rad		The value in radian to assign.
		*/
		template <typename TIn>
		constexpr Deg(Rad<TIn> _rad) noexcept;


		/**
		*	\brief \e Compare 2 Deg.
		*
		*	\param[in] _other		Other Deg to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold compare.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(Deg _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept;


		/// clamp this angle between [-180, 180].
		void Clamp() noexcept;


		/**
		*	\brief \e Getter of the opposite signed degree.
		*
		*	\return new opposite signed degree.
		*/
		constexpr Deg operator-() const noexcept;

		/**
		*	\brief \b Add degrees to handle.
		*
		*	\param[in] _rhs		degrees to add.
		*
		*	\return new degree result.
		*/
		constexpr Deg operator+(Deg _rhs) const noexcept;

		/**
		*	\brief \b Substract degrees to handle.
		*
		*	\param[in] _rhs		degrees to substract.
		*
		*	\return new degree result.
		*/
		constexpr Deg operator-(Deg _rhs) const noexcept;

		/**
		*	\brief \b Scale angle.
		*
		*	\param[in] _scale	scale to apply.
		*
		*	\return new degree result.
		*/
		constexpr Deg operator*(T _scale) const noexcept;

		/**
		*	\brief \b Unscale angle.
		*
		*	\param[in] _scale	un-scale to apply.
		*
		*	\return new degree result.
		*/
		Deg operator/(T _scale) const;


		/**
		*	\brief \b Add degrees to handle.
		*
		*	\param[in] _rhs		degrees to add.
		*
		*	\return self degree.
		*/
		Deg& operator+=(Deg _rhs) noexcept;

		/**
		*	\brief \b Substract degrees to handle.
		*
		*	\param[in] _rhs		degrees to substract.
		*
		*	\return self degree.
		*/
		Deg& operator-=(Deg _rhs) noexcept;

		/**
		*	\brief \b Scale angle.
		*
		*	\param[in] _scale	scale to apply.
		*
		*	\return this degree scaled.
		*/
		Deg& operator*=(T _scale) noexcept;

		/**
		*	\brief \b Unscale angle.
		*
		*	\param[in] _scale	un-scale to apply.
		*
		*	\return this degree unscaled.
		*/
		Deg& operator/=(T _scale);


		/**
		*	\brief \e Compare 2 degree equality.
		*
		*	\param[in] _rhs		Other degree to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(Deg _rhs) const noexcept;

		/**
		*	\brief \e Compare 2 degree inequality.
		*
		*	\param[in] _rhs		Other degree to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(Deg _rhs) const noexcept;


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


	/// Alias for float Deg.
	using Degf = Deg<float>;

	/// Alias for double Deg.
	using Degd = Deg<double>;

	/// Template alias of Deg
	template <typename T>
	using Degree = Deg<T>;


	/**
	*	\brief _deg \b literal operator.
	*
	*	\param[in] _lit		Operand to convert to Degree.
	*
	*	\return \c Degree without maths-conversion.
	*/
	constexpr Degf operator""_deg(uint64 _lit) noexcept;

	/**
	*	\brief _deg \b literal operator.
	*
	*	\param[in] _lit		Operand to convert to Degree.
	*
	*	\return \c Degree without maths-conversion.
	*/
	constexpr Degf operator""_deg(long double _lit) noexcept;
}


/** \} */

#include <SA/Maths/Misc/Degree.inl>

#endif // GUARD
