// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_VECTOR2_GUARD
#define SAPPHIRE_MATHS_VECTOR2_GUARD

#include <SA/Maths/Misc/Degree.hpp>
#include <SA/Maths/Algorithms/Tan.hpp>
#include <SA/Maths/Algorithms/Sqrt.hpp>
#include <SA/Maths/Algorithms/Lerp.hpp>

/**
*	\file Vector2.hpp
*
*	\brief <b>Vector 2</b> type implementation.
*
*	\ingroup Maths_Space
*	\{
*/


namespace Sa
{
	template <typename T>
	struct Vec3;

	/**
	*	\brief \e Vector 2 Sapphire's class.
	*
	*	\tparam T	Type of the vector.
	*/
	template <typename T>
	struct Vec2
	{
		/// Scalar type of the Vector.
		using Type = T;


		/// Vector's X component (axis value).
		T x = T();

		/// Vector's Y component (axis value).
		T y = T();

//{ Constants

		/// Zero vector constant { 0, 0 }.
		static const Vec2 Zero;

		/// One vector constant { 1, 1 }.
		static const Vec2 One;

		/// Right vector constant { 1, 0 }.
		static const Vec2 Right;

		/// Left vector constant { -1, 0 }.
		static const Vec2 Left;

		/// Up vector constant { 0, 1 }.
		static const Vec2 Up;

		/// Down vector constant { 0, -1 }.
		static const Vec2 Down;

//}

//{ Constructors

		/// \e Default constructor.
		Vec2() = default;


		/**
		*	\brief \e Value constructor.
		*
		*	\param[in] _x	X axis value.
		*	\param[in] _y	Y axis value.
		*/
		constexpr Vec2(T _x, T _y) noexcept;

		/**
		*	\brief \b Scale \e Value constructor.
		*
		*	\param[in] _scale	Axis value to apply on all axis.
		*/
		constexpr Vec2(T _scale) noexcept;


		/// Default move constructor.
		Vec2(Vec2&&) = default;

		/// Default copy constructor.
		Vec2(const Vec2&) = default;

		/**
		*	\brief \e Value constructor from another Vec2 type.
		*
		*	\tparam TIn			Type of the input Vec2.
		*
		*	\param[in] _other	Vec2 to construct from.
		*/
		template <typename TIn>
		constexpr Vec2(const Vec2<TIn>& _other) noexcept;

		/**
		*	\brief \e Value constructor from Vec3.
		*
		*	\tparam TIn			Type of the input Vec3.
		*
		*	\param[in] _other	Vec3 to construct from.
		*/
		template <typename TIn>
		constexpr Vec2(const Vec3<TIn>& _other) noexcept;

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
		constexpr bool Equals(const Vec2& _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept;


		/**
		*	\brief \e Compare 2 vector equality.
		*
		*	\param[in] _rhs		Other vector to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(const Vec2 & _rhs) const noexcept;

		/**
		*	\brief \e Compare 2 vector inequality.
		*
		*	\param[in] _rhs		Other vector to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(const Vec2 & _rhs) const noexcept;

//}

//{ Accessors

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
		*	\brief \e Access operator by index: x, y using 0, 1.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		T& operator[](uint32 _index);

		/**
		*	\brief <em> Const Access </em> operator by index: x, y using 0, 1.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		const T& operator[](uint32 _index) const;

//}

//{ Length

		/**
		*	\brief \e Getter of the /b length of this vector.
		*
		*	\return Length of this vector.
		*/
		constexpr T Length() const noexcept;

		/**
		*	\brief \e Getter of the <b> Squared Length </b> of this vector.
		*
		*	\return Squared length of this vector.
		*/
		constexpr T SqrLength() const noexcept;


		/**
		*	\brief \b Normalize this vector.
		*
		*	\return self vector normalized.
		*/
		Vec2& Normalize() noexcept;

		/**
		*	\brief \b Normalize this vector.
		*
		*	\return new normalized vector.
		*/
		Vec2 GetNormalized() const noexcept;

		/**
		*	\brief Whether this vector is normalized.
		*
		*	\return True if this vector is normalized, otherwise false.
		*/
		constexpr bool IsNormalized() const noexcept;

//}

//{ Project

		/**
		*	\brief \b Reflect this vector over the normal.
		*
		*	\param[in] _normal		Normal used for reflection.
		*	\param[in] _elasticity		Elasticity reflection coefficient (use 1.0f for full reflection).
		*
		*	\return new vector reflected.
		*/
		Vec2 Reflect(const Vec2& _normal, float _elasticity = 1.0f) const noexcept;

		/**
		*	\brief \b Project this vector onto an other vector.
		*
		*	Reference: https://en.wikipedia.org/wiki/Vector_projection
		*
		*	\param[in] _other	Vector used for projection.
		*
		*	\return new  vector projected.
		*/
		Vec2 ProjectOnTo(const Vec2& _other) const noexcept;

		/**
		*	\brief \b Project this vector onto s normal.
		*
		*	Assume _normal is normalized.
		*	Use ProjectOnTo() for non normalized vector.
		*	Reference: https://en.wikipedia.org/wiki/Vector_projection
		*
		*	\param[in] _normal		Normal used for projection.
		*
		*	\return new vector projected.
		*/
		Vec2 ProjectOnToNormal(const Vec2& _normal) const noexcept;

		/**
		*	\brief \e Compute the perpendicular vector to this vector.
		*
		*	Rotate this vector 90 degrees in trigonomety direction (counter-clockwise).
		*
		*	\return new vector rotated.
		*/
		Vec2 Perpendicular() const noexcept;

//}

//{ Dot/Cross

		/**
		*	\brief \e Compute the <b> Dot product </b> between _lhs and _rhs.
		*
		*	\param[in] _lhs		Left hand side operand to compute dot product with.
		*	\param[in] _rhs		Right hand side operand to compute dot product with.
		*
		*	\return <b> Dot product </b> between _lhs and _rhs.
		*/
		static constexpr T Dot(const Vec2& _lhs, const Vec2& _rhs) noexcept;

		/**
		*	\brief \e Compute the <b> Cross product </b> between _lhs and _rhs.
		*
		*	\param[in] _lhs		Left hand side operand to compute cross product with.
		*	\param[in] _rhs		Right hand side operand to compute cross product with.
		*
		*	\return <b> Cross product </b> between _lhs and _rhs.
		*/
		static constexpr T Cross(const Vec2& _lhs, const Vec2& _rhs) noexcept;

//}

//{ Angle

		/**
		*	\brief \e Compute the <b> Signed Angle </b> between _start and _end.
		*
		*	\param[in] _start		Starting point to compute angle from.
		*	\param[in] _end			Ending point to compute angle to.
		*
		*	\return <b> Signed Angle </b> between _start and _end.
		*/
		static Deg<T> Angle(const Vec2& _start, const Vec2& _end) noexcept;

		/**
		*	\brief \e Compute the <b> Unsigned Angle </b> between _start and _end.
		*
		*	\param[in] _start		Starting point to compute angle from.
		*	\param[in] _end			Ending point to compute angle to.
		*
		*	\return <b> Unsigned Angle </b> between _start and _end.
		*/
		static Deg<T> AngleUnsigned(const Vec2& _start, const Vec2& _end) noexcept;

//}

//{ Dist/Dir

		/**
		*	\brief \e Compute the <b> Distance </b> between _start and _end.
		*
		*	\param[in] _start		Left hand side operand to compute distance with.
		*	\param[in] _end			Right hand side operand to compute distance with.
		*
		*	\return <b> Distance </b> between _start and _end.
		*/
		static constexpr T Dist(const Vec2& _start, const Vec2& _end) noexcept;

		/**
		*	\brief \e Compute the <b> Squared Distance </b> between _start and _end.
		*
		*	\param[in] _start		Left hand side operand to compute squared distance with.
		*	\param[in] _end			Right hand side operand to compute squared distance with.
		*
		*	\return <b> Squared Distance </b> between _start and _rhs.
		*/
		static constexpr T SqrDist(const Vec2& _start, const Vec2& _end) noexcept;

		/**
		*	\brief \e Compute the <b> Non-Normalized Direction </b> from _start to _end.
		*
		*	Direction get not normalized. Use DirN instead.
		*
		*	\param[in] _start		Starting point to compute direction from.
		*	\param[in] _end			ending point to compute direction to.
		*
		*	\return <b> Non-Normalized Direction </b> from _start to _end.
		*/
		static constexpr Vec2 Dir(const Vec2& _start, const Vec2& _end) noexcept;

		/**
		*	\brief \e Compute the <b> Normalized Direction </b> from _start to _end.
		*
		*	\param[in] _start		Starting point to compute direction from.
		*	\param[in] _end			ending point to compute direction to.
		*
		*	\return <b> Normalized Direction </b> from _start to _end.
		*/
		static constexpr Vec2 DirN(const Vec2& _start, const Vec2& _end) noexcept;

//}

//{ Lerp
		/**
		*	\brief <b> Clamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\param _start	Starting point of the lerp.
		*	\param _end		Ending point of the lerp.
		*	\param _alpha	Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		static Vec2 Lerp(const Vec2& _start, const Vec2& _end, float _alpha) noexcept;

		/**
		*	\brief <b> Unclamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\param _start	Starting point of the lerp.
		*	\param _end		Ending point of the lerp.
		*	\param _alpha	Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		static Vec2 LerpUnclamped(const Vec2& _start, const Vec2& _end, float _alpha) noexcept;

		/**
		*	\brief <b> Clamped SLerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Slerp
		*
		*	\param _start	Starting point of the lerp.
		*	\param _end		Ending point of the lerp.
		*	\param _alpha	Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		static Vec2 SLerp(const Vec2& _start, const Vec2& _end, float _alpha) noexcept;

		/**
		*	\brief <b> Unclamped SLerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Slerp
		*
		*	\param _start	Starting point of the lerp.
		*	\param _end		Ending point of the lerp.
		*	\param _alpha	Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		static Vec2 SLerpUnclamped(const Vec2& _start, const Vec2& _end, float _alpha) noexcept;

//}

//{ Operators

		/// Default assignment move operator.
		Vec2& operator=(Vec2&&) = default;

		/// Default assignment copy operator.
		Vec2& operator=(const Vec2&) = default;


		/**
		*	\brief \e Getter of the opposite signed vector.
		*
		*	\return new opposite signed vector.
		*/
		constexpr Vec2 operator-() const noexcept;

		/**
		*	\brief \b Scale each vector axis by _scale.
		*
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return new vector scaled.
		*/
		constexpr Vec2 operator*(T _scale) const noexcept;

		/**
		*	\brief <b> Inverse Scale </b> each vector axis by _scale.
		*
		*	\param[in] _scale	Inverse scale value to apply on all axis.
		*
		*	\return new vector inverse-scaled.
		*/
		Vec2 operator/(T _scale) const noexcept;

		/**
		*	\brief \b Add term by term vector values.
		*
		*	\param[in] _rhs		Vector to add.
		*
		*	\return new vector result.
		*/
		constexpr Vec2 operator+(const Vec2& _rhs) const noexcept;

		/**
		*	\brief \b Subtract term by term vector values.
		*
		*	\param[in] _rhs		Vector to substract.
		*
		*	\return new vector result.
		*/
		constexpr Vec2 operator-(const Vec2& _rhs) const noexcept;

		/**
		*	\brief \b Multiply term by term vector values.
		*
		*	\param[in] _rhs		Vector to multiply.
		*
		*	\return new vector result.
		*/
		constexpr Vec2 operator*(const Vec2& _rhs) const noexcept;

		/**
		*	\brief \b Divide term by term vector values.
		*
		*	\param[in] _rhs		Vector to divide.
		*
		*	\return new vector result.
		*/
		Vec2 operator/(const Vec2& _rhs) const noexcept;

		/**
		*	\brief \e Compute the <b> Dot product </b> between this and _rhs.
		*
		*	\param[in] _rhs			Right hand side operand vector to compute dot product with.
		*
		*	\return <b> Dot product </b> between this vector and _other.
		*/
		constexpr T operator|(const Vec2& _rhs) const noexcept;

		/**
		*	\brief \e Compute the <b> Cross product </b> between this and _rhs.
		*
		*	\param[in] _rhs			Right hand side operand vector to compute cross product with.
		*
		*	\return <b> Cross product </b> between this vector and _other.
		*/
		constexpr T operator^(const Vec2& _rhs) const noexcept;


		/**
		*	\brief \b Scale each vector axis by _scale.
		*
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return self vector scaled.
		*/
		Vec2& operator*=(T _scale) noexcept;

		/**
		*	\brief <b> Inverse Scale </b> each vector axis by _scale.
		*
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return self vector inverse-scaled.
		*/
		Vec2& operator/=(T _scale) noexcept;

		/**
		*	\brief \b Add term by term vector values.
		*
		*	\param[in] _rhs		Vector to add.
		*
		*	\return self vector result.
		*/
		Vec2& operator+=(const Vec2& _rhs) noexcept;

		/**
		*	\brief \b Substract term by term vector values.
		*
		*	\param[in] _rhs		Vector to substract.
		*
		*	\return self vector result.
		*/
		Vec2& operator-=(const Vec2& _rhs) noexcept;

		/**
		*	\brief \b Multiply term by term vector values.
		*
		*	\param[in] _rhs		Vector to multiply.
		*
		*	\return self vector result.
		*/
		Vec2 operator*=(const Vec2& _rhs) noexcept;

		/**
		*	\brief \b Divide term by term vector values.
		*
		*	\param[in] _rhs		Vector to divide.
		*
		*	\return self vector result.
		*/
		Vec2 operator/=(const Vec2& _rhs) noexcept;

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


	/**
	*	\brief \b Scale each vector axis by _lhs.
	*
	*	\param[in] _lhs		Scale value to apply on all axis.
	*	\param[in] _rhs		Vector to scale.
	*
	*	\return new vector scaled.
	*/
	template <typename T>
	constexpr Vec2<T> operator*(typename std::remove_cv<T>::type _lhs, const Vec2<T>& _rhs) noexcept;

	/**
	*	\brief <b> Inverse Scale </b> each vector axis by _lhs.
	*
	*	\param[in] _lhs		Inverse scale value to apply on all axis.
	*	\param[in] _rhs		Vector to scale.
	*
	*	\return new vector inverse-scaled.
	*/
	template <typename T>
	constexpr Vec2<T> operator/(typename std::remove_cv<T>::type _lhs, const Vec2<T>& _rhs) noexcept;


//{ Aliases

	/// Alias for int32 Vec2.
	using Vec2i = Vec2<int32>;

	/// Alias for uint32 Vec2.
	using Vec2ui = Vec2<uint32>;

	/// Alias for float Vec2.
	using Vec2f = Vec2<float>;

	/// Alias for double Vec2.
	using Vec2d = Vec2<double>;


	/// Template alias of Vec2
	template <typename T>
	using Vector2 = Vec2<T>;

	/// Alias for int32 Vector2.
	using Vector2i = Vector2<int32>;

	/// Alias for uint32 Vector2.
	using Vector2ui = Vector2<uint32>;

	/// Alias for float Vector2.
	using Vector2f = Vector2<float>;

	/// Alias for double Vector2.
	using Vector2d = Vector2<double>;

//}
}


/** \} */

#include <SA/Maths/Space/Vector2.inl>

#endif // GUARD
