// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_VECTOR4_GUARD
#define SAPPHIRE_MATHS_VECTOR4_GUARD

#include <SA/Maths/Algorithms/Sqrt.hpp>
#include <SA/Maths/Algorithms/Lerp.hpp>

/**
*	\file Vector4.hpp
*
*	\brief <b>Vector 4</b> type implementation.
*
*	\ingroup Maths_Space
*	\{
*/


namespace Sa
{
	template <typename T>
	struct Vec2;

	template <typename T>
	struct Vec3;

	/**
	*	\brief \e Vector 4 Sapphire-Maths class.
	*
	*	\tparam T	Type of the vector.
	*/
	template <typename T>
	struct Vec4
	{
		/// Type of the Vector.
		using Type = T;

		/// Vector's X component (axis value).
		T x = T();

		/// Vector's Y component (axis value).
		T y = T();

		/// Vector's Z component (axis value).
		T z = T();

		/// Vector's W component (stored after xyz).
		T w = T();


//{ Constructors

		/// \e Default constructor.
		Vec4() = default;

		/**
		*	\brief \e Value constructor.
		*
		*	\param[in] _x	X axis value.
		*	\param[in] _y	Y axis value.
		*	\param[in] _z	Z axis value.
		*	\param[in] _w	W axis value.
		*/
		constexpr Vec4(T _x, T _y, T _z, T _w) noexcept;

		/**
		*	\brief \b Scale \e Value constructor.
		*
		*	\param[in] _scale	Axis value to apply on all axis.
		*/
		constexpr Vec4(T _scale) noexcept;


		/**
		*	\brief \e Value constructor from another Vec4 type.
		*
		*	\tparam TIn			Type of the input Vec3.
		*
		*	\param[in] _other	Vec4 to construct from.
		*/
		template <typename TIn>
		constexpr Vec4(const Vec4<TIn>&_other) noexcept;

		/**
		*	\brief \e Value constructor from Vec2.
		*
		*	\tparam TIn			Type of the in Vec2.
		*
		*	\param[in] _other	Vec2 to construct from.
		*	\param[in] _z		Z axis value.
		*	\param[in] _w		W axis value.
		*/
		template <typename TIn>
		constexpr Vec4(const Vec2<TIn>&_other, T _z = T(0), T _w = T(0)) noexcept;

		/**
		*	\brief \e Value constructor from 2 Vec2.
		*
		*	\tparam TIn			Type of the in Vec2.
		*
		*	\param[in] _v1		First Vec2 to construct from.
		*	\param[in] _v1		Second Vec2 to construct from.
		*/
		template <typename TIn>
		constexpr Vec4(const Vec2<TIn>&_v1, const Vec2<TIn>& _v2) noexcept;

		/**
		*	\brief \e Value constructor from Vec3.
		*
		*	\tparam TIn			Type of the in Vec3.
		*
		*	\param[in] _other	Vec4 to construct from.
		*	\param[in] _w		W axis value.
		*/
		template <typename TIn>
		constexpr Vec4(const Vec3<TIn>&_other, T _w = T(0)) noexcept;

//}

//{ Equals

		/**
		*	\brief Whether this vector is a zero vector.
		*
		*	\return True if this is a zero vector.
		*/
		constexpr bool IsZero() const noexcept;

		/**
		*	\brief \e Compare 2 vector.
		*
		*	\param[in] _other		Other vector to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold comparison.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(const Vec4& _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept;

//}

//{ Operators

		/**
		*	\brief \e Compare 2 vector equality.
		*
		*	\param[in] _rhs		Other vector to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(const Vec4& _rhs) const noexcept;

		/**
		*	\brief \e Compare 2 vector inequality.
		*
		*	\param[in] _rhs		Other vector to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(const Vec4& _rhs) const noexcept;

//}

//{ Acccessors

		/**
		*	\brief \e Getter of vector data
		*
		*	\return this vector as a T*.
		*/
		T* Data() noexcept;

		/**
		*	\brief <em> Const Getter </em> of vector data
		*
		*	\return this vector as a const T*.
		*/
		const T* Data() const noexcept;


		/**
		*	\brief \e Access operator by index: x, y, z, w using 0, 1, 2, 3.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		T& operator[](uint32 _index);

		/**
		*	\brief <em> Const Access </em> operator by index: x, y, z,w  using 0, 1, 2, 3.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		const T& operator[](uint32 _index) const;

//}


#if SA_LOGGING

		/**
		*	\brief ToString implementation
		*
		*	Convert this vector as a string.
		*
		*	\return this as a string.
		*/
		std::string ToString() const noexcept;

#endif
	};


//{ Aliases

	/// Alias for int32 Vec4.
	using Vec4i = Vec4<int32>;

	/// Alias for uint32 Vec4.
	using Vec4ui = Vec4<uint32>;

	/// Alias for float Vec4.
	using Vec4f = Vec4<float>;

	/// Alias for double Vec4.
	using Vec4d = Vec4<double>;


	/// Template alias of Vec4
	template <typename T>
	using Vector4 = Vec4<T>;

	/// Alias for int32 Vector4.
	using Vector4i = Vector4<int32>;

	/// Alias for uint32 Vector4.
	using Vector4ui = Vector4<uint32>;

	/// Alias for float Vector4.
	using Vector4f = Vector4<float>;

	/// Alias for double Vector4.
	using Vector4d = Vector4<double>;

//}
}


/** \} */

#include <SA/Maths/Space/Vector4.inl>

#endif // GUARD
