// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_MATRIX4_GUARD
#define SAPPHIRE_MATHS_MATRIX4_GUARD

#include <SA/Core/Support/Pragma.hpp>
#include <SA/Core/Support/Intrinsics.hpp>

#include <SA/Maths/Algorithms/Lerp.hpp>
#include <SA/Maths/Matrix/Matrix4Base.hpp>

/**
*	\file Matrix4.hpp
*
*	\brief <b>Matrix 4x4</b> type implementation.
*
*	\ingroup Maths
*	\{
*/


namespace Sa
{
	template <typename T>
	struct Vec3;

	template <typename T>
	struct Vec4;

	template <typename T>
	struct Quat;

	template <typename T, MatrixMajor major>
	struct Mat3;


	/**
	*	\brief \e Matrix 4x4 Sapphire-Maths class.
	*
	* 	must be align at 32 for intrinsics.
	* 
	*	\tparam T	Type of the matrix.
	*/

#if SA_INTRISC

	// Disable padding struct warning.
	SA_PRAGMA_SDWARN_MSVC(4324)

	template <typename T, MatrixMajor major = MatrixMajor::Default>
	struct alignas(32) Mat4 : public Intl::Mat4_Base<T, major>

#else

	template <typename T, MatrixMajor major = MatrixMajor::Default>
	struct Mat4 : public Intl::Mat4_Base<T, major>

#endif
	{
		using Intl::Mat4_Base<T, major>::e00;
		using Intl::Mat4_Base<T, major>::e01;
		using Intl::Mat4_Base<T, major>::e02;
		using Intl::Mat4_Base<T, major>::e03;

		using Intl::Mat4_Base<T, major>::e10;
		using Intl::Mat4_Base<T, major>::e11;
		using Intl::Mat4_Base<T, major>::e12;
		using Intl::Mat4_Base<T, major>::e13;

		using Intl::Mat4_Base<T, major>::e20;
		using Intl::Mat4_Base<T, major>::e21;
		using Intl::Mat4_Base<T, major>::e22;
		using Intl::Mat4_Base<T, major>::e23;

		using Intl::Mat4_Base<T, major>::e30;
		using Intl::Mat4_Base<T, major>::e31;
		using Intl::Mat4_Base<T, major>::e32;
		using Intl::Mat4_Base<T, major>::e33;

//{ Constants

		/**
		*	\brief Zero Mat4 constant
		* 
		*	{0, 0, 0, 0}
		*	{0, 0, 0, 0}
		*	{0, 0, 0, 0}
		*	{0, 0, 0, 0}
		*/
		static const Mat4 Zero;

		/**
		*	\brief Identity Mat4 constant
		* 
		*	{1, 0, 0, 0}
		*	{0, 1, 0, 0}
		*	{0, 0, 1, 0}
		*	{0, 0, 0, 1}
		*/
		static const Mat4 Identity;

//}

//{ Constructors

		using Intl::Mat4_Base<T, major>::Mat4_Base;

		/**
		*	\brief \e Value constructor from another Mat4 type.
		*
		*	\tparam TIn			Type of the input Mat4.
		*
		*	\param[in] _other	Mat4 to construct from.
		*/
		template <typename TIn>
		constexpr Mat4(const Mat4<TIn, major>& _other) noexcept;

		/**
		*	\brief \e Value constructor from another Mat3 type.
		*
		*	\tparam TIn			Type of the input Mat3.
		*
		*	\param[in] _other	Mat3 to construct from.
		*/
		template <typename TIn>
		constexpr Mat4(const Mat3<TIn, major>& _other) noexcept;

//{ Equals

		/**
		*	\brief Whether this matrix is a zero matrix.
		*
		*	\return True if this is a zero matrix.
		*/
		constexpr bool IsZero() const noexcept;

		/**
		*	\brief Whether this matrix is an identity matrix.
		*
		*	\return True if this is an identity matrix.
		*/
		constexpr bool IsIdentity() const noexcept;


		/**
		*	\brief \e Compare 2 Matrix.
		*
		*	\param[in] _other		Other matrix to compare to.
		*	\param[in] _threshold	Allowed threshold to accept equality.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(const Mat4& _other, T _threshold = std::numeric_limits<T>::epsilon()) const noexcept;


		/**
		*	\brief \e Compare 2 matrix equality.
		*
		*	\param[in] _rhs		Other matrix to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(const Mat4& _rhs) const noexcept;

		/**
		*	\brief \e Compare 2 matrix inequality.
		*
		*	\param[in] _rhs		Other matrix to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(const Mat4& _rhs) const noexcept;

//}

//{ Accessors

		/**
		*	\brief \e Getter of matrix data
		*
		*	\return this matrix as a T*.
		*/
		T* Data() noexcept;

		/**
		*	\brief <em> Const Getter </em> of matrix data
		*
		*	\return this matrix as a const T*.
		*/
		const T* Data() const noexcept;


		/**
		*	\brief \e Getter of Value at index.
		*
		*	\param[in] _index		Index to access.
		*
		*	\return element at index.
		*/
		T& At(uint32 _index);

		/**
		*	\brief <em> Const Getter </em> of Value at index.
		*
		*	\param[in] _index		Index to access.
		*
		*	\return element at index.
		*/
		const T& At(uint32 _index) const;

		/**
		*	\brief \e Getter of Value at (x;y).
		*
		*	\param[in] _x		row index.
		*	\param[in] _y		column index.
		*
		*	\return element at index.
		*/
		T& At(uint32 _x, uint32 _y);

		/**
		*	\brief <em> Const Getter </em> of Value at (x;y).
		*
		*	\param[in] _x		row index.
		*	\param[in] _y		column index.
		*
		*	\return element at index.
		*/
		const T& At(uint32 _x, uint32 _y) const;


		/**
		*	\brief \e Access operator by index.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		T& operator[](uint32 _index);

		/**
		*	\brief <em> Const Access </em> operator by index.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		const T& operator[](uint32 _index) const;

//}

//{ Transpose

		/**
		*	\brief \b Transpose this matrix.
		*
		*	\return self transposed matrix.
		*/
		Mat4& Transpose() noexcept;

		/**
		*	\brief \b Transpose this matrix.
		*
		*	\return new transposed matrix.
		*/
		constexpr Mat4 GetTransposed() const noexcept;

//}

//{ Inverse

		/**
		*	\brief \e Compute the determinant of the matrix.
		*
		*	\return Determinant of this matrix.
		*/
		T Determinant() const noexcept;

		/**
		*	\brief \b Inverse this matrix.
		*
		*	\return self inversed matrix.
		*/
		Mat4& Inverse() noexcept;

		/**
		*	\brief \b Inverse this matrix.
		*
		*	\return new inversed matrix.
		*/
		Mat4 GetInversed() const noexcept;

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
		static Mat4 Lerp(const Mat4& _start, const Mat4& _end, float _alpha) noexcept;

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
		static Mat4 LerpUnclamped(const Mat4& _start, const Mat4& _end, float _alpha) noexcept;

//}

//{ Transform

		/**
		*	\brief \b Optimized translation from Vec3.
		*
		*	Use this to apply scale instead of MakeTranslation() * m;
		*
		*	\param[in] _transl	Vector to translate
		*
		*	\return this matrix translated.
		*/
		Mat4& ApplyTranslation(const Vec3<T>& _transl) noexcept;

		/**
		*	\brief \b Optimized scale from Vec3.
		*
		*	Apply x scale on row 0.
		*	Apply y scale on row 1.
		*	Apply z scale on row 2.
		*	Use this to apply scale instead of MakeScale() * m;
		*
		*	\param[in] _scale	Vector for scaling.
		*
		*	\return this matrix scaled.
		*/
		Mat4& ApplyScale(const Vec3<T>& _scale) noexcept;


		/**
		*	\brief Make <b> translation matrix </b> from vector3.
		*
		*	\param[in] _transl	Vector to translate
		*
		*	\return translation matrix.
		*/
		static Mat4 MakeTranslation(const Vec3<T>& _transl) noexcept;

		/**
		*	\brief Make <b> rotation matrix </b> from quaternion.
		*
		*	\param[in] _rot	quaternion to use for rotation.
		*
		*	\return rotation matrix.
		*/
		static Mat4 MakeRotation(const Quat<T>& _rot) noexcept;

		/**
		*	\brief Make <b> scale matrix </b> from vector3.
		*
		*	\param[in] _scale	Vector for scaling.
		*
		*	\return scale matrix.
		*/
		static Mat4 MakeScale(const Vec3<T>& _scale) noexcept;

		/**
		*	\brief Make <b> transform matrix </b>.
		*
		*	\param[in] _transl		Vector for translation.
		*	\param[in] _rot	Quaternion for rotation.
		*
		*	\return transform matrix.
		*/
		static Mat4 MakeTransform(const Vec3<T>& _transl, const Quat<T>& _rot) noexcept;

		/**
		*	\brief Make <b> transform matrix </b>.
		*
		*	\param[in] _transl		Vector for translation.
		*	\param[in] _scale		Vector for scale.
		*
		*	\return transform matrix.
		*/
		static Mat4 MakeTransform(const Vec3<T>& _transl, const Vec3<T>& _scale) noexcept;

		/**
		*	\brief Make <b> transform matrix </b>.
		*
		*	\param[in] _rot	Quaternion for rotation.
		*	\param[in] _scale		Vector for scale.
		*
		*	\return transform matrix.
		*/
		static Mat4 MakeTransform(const Quat<T>& _rot, const Vec3<T>& _scale) noexcept;

		/**
		*	\brief Make <b> transform matrix </b>.
		*
		*	\param[in] _transl		Vector for translation.
		*	\param[in] _rot	Quaternion for rotation.
		*	\param[in] _scale		Vector for scale.
		*
		*	\return transform matrix.
		*/
		static Mat4 MakeTransform(const Vec3<T>& _transl, const Quat<T>& _rot, const Vec3<T>& _scale) noexcept;


		/**
		*	\brief Make <b> perspective matrix </b>.
		*
		*	\param[in] _fov			Perspective FOV.
		*	\param[in] _aspect		Aspect ratio (width/height).
		*	\param[in] _near		Near frustum.
		*	\param[in] _far			Far frustum.
		*
		*	\return perspective matrix.
		*/
		static Mat4 MakePerspective(T _fov = T(90.0), T _aspect = T(1.0), T _near = T(0.35), T _far = T(10.0)) noexcept;

//}

//{ Operators

		using Intl::Mat4_Base<T, major>::operator=;

		/**
		*	\brief \e Getter of the opposite signed matrix.
		*
		*	\return new opposite signed matrix.
		*/
		constexpr Mat4 operator-() const noexcept;

		/**
		*	\brief \b Scale each matrix component by _scale.
		*
		*	\param[in] _scale	Scale value to apply on all components.
		*
		*	\return new matrix scaled.
		*/
		Mat4 operator*(T _scale) const noexcept;

		/**
		*	\brief <b> Inverse Scale </b> each matrix component by _scale.
		*
		*	\param[in] _scale	Inverse scale value to apply on all components.
		*
		*	\return new matrix inverse-scaled.
		*/
		Mat4 operator/(T _scale) const noexcept;

		/**
		*	\brief \b Add term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to add.
		*
		*	\return new matrix result.
		*/
		Mat4 operator+(const Mat4& _rhs) const noexcept;

		/**
		*	\brief \b Subtract term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to substract.
		*
		*	\return new matrix result.
		*/
		Mat4 operator-(const Mat4& _rhs) const noexcept;

		/**
		*	\brief \b Multiply matrices.
		*
		*	\param[in] _rhs		Matrix to multiply to.
		*
		*	\return new matrix result.
		*/
		Mat4 operator*(const Mat4& _rhs) const noexcept;

		/**
		*	\brief \b Inverse multiply matrices.
		*
		*	\param[in] _rhs		Matrix to inverse multiply to.
		*
		*	\return new matrix result.
		*/
		Mat4 operator/(const Mat4& _rhs) const noexcept;


		/**
		*	\brief transform this vector by this matrix.
		*
		*	Ignore 4th row/column component.
		*
		*	\param[in] _rhs		Vector to transform.
		*
		*	\return Transformed vector.
		*/
		Vec3<T> operator*(const Vec3<T>&_rhs) const noexcept;

		/**
		*	\brief transform this vector by this matrix.
		*
		*	\param[in] _rhs		Vector to transform.
		*
		*	\return Transformed vector.
		*/
		Vec4<T> operator*(const Vec4<T>&_rhs) const noexcept;


		/**
		*	\brief \b Scale each matrix component by _scale.
		*
		*	\param[in] _scale	Scale value to apply on all components.
		*
		*	\return self matrix scaled.
		*/
		Mat4& operator*=(T _scale) noexcept;

		/**
		*	\brief <b> Inverse Scale </b> each matrix component by _scale.
		*
		*	\param[in] _scale	Inverse scale value to apply on all components.
		*
		*	\return self matrix inverse-scaled.
		*/
		Mat4& operator/=(T _scale) noexcept;

		/**
		*	\brief \b Add term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to add.
		*
		*	\return self matrix result.
		*/
		Mat4& operator+=(const Mat4& _rhs) noexcept;

		/**
		*	\brief \b Subtract term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to substract.
		*
		*	\return self matrix result.
		*/
		Mat4& operator-=(const Mat4& _rhs) noexcept;

		/**
		*	\brief \b Multiply matrices.
		*
		*	\param[in] _rhs		Matrix to multiply to.
		*
		*	\return self matrix result.
		*/
		Mat4& operator*=(const Mat4& _rhs) noexcept;

		/**
		*	\brief \b Inverse multiply matrices.
		*
		*	\param[in] _rhs		Matrix to inverse multiply to.
		*
		*	\return self matrix result.
		*/
		Mat4& operator/=(const Mat4& _rhs) noexcept;

//}


#if SA_LOGGING

		/**
		*	\brief ToString implementation
		*
		*	Convert this matrix as a string.
		*	Print element in memoro order.
		*
		*	\return this as a string.
		*/
		std::string ToString() const noexcept;

#endif
	};


	/**
	*	\brief \b Scale each matrix components by _lhs.
	*
	*	\param[in] _lhs		Scale value to apply on all components.
	*	\param[in] _rhs		Matrix to scale.
	*
	*	\return new matrix scaled.
	*/
	template <typename T, MatrixMajor major>
	Mat4<T, major> operator*(typename std::remove_cv<T>::type _lhs, const Mat4<T, major>& _rhs) noexcept;

	/**
	*	\brief <b> Inverse Scale </b> each matrix components by _lhs.
	*
	*	\param[in] _lhs		Inverse scale value to apply on all components.
	*	\param[in] _rhs		Matrix to scale.
	*
	*	\return new matrix inverse-scaled.
	*/
	template <typename T, MatrixMajor major>
	Mat4<T, major> operator/(typename std::remove_cv<T>::type _lhs, const Mat4<T, major>& _rhs) noexcept;

//{ Aliases

	/// Alias for int32 Mat4.
	using Mat4i = Mat4<int32>;

	/// Alias for float Mat4.
	using Mat4f = Mat4<float>;

	/// Alias for double Mat4.
	using Mat4d = Mat4<double>;


	/// Template alias of Mat4
	template <typename T, MatrixMajor major = MatrixMajor::Default>
	using Matrix4 = Mat4<T>;

	/// Alias for int32 Matrix4.
	using Matrix4i = Matrix4<int32>;

	/// Alias for float Matrix4.
	using Matrix4f = Matrix4<float>;

	/// Alias for double Matrix4.
	using Matrix4d = Matrix4<double>;


	/// Alias for row major int32 Mat4.
	using RMat4i = Mat4<int32, MatrixMajor::Row>;

	/// Alias for row major float Mat4.
	using RMat4f = Mat4<float, MatrixMajor::Row>;

	/// Alias for row major double Mat4.
	using RMat4d = Mat4<double, MatrixMajor::Row>;


	/// Alias for column major int32 Mat4.
	using CMat4i = Mat4<int32, MatrixMajor::Column>;

	/// Alias for column major float Mat4.
	using CMat4f = Mat4<float, MatrixMajor::Column>;

	/// Alias for column major double Mat4.
	using CMat4d = Mat4<double, MatrixMajor::Column>;

//}

	/// \cond Internal

#if SA_INTRISC_AVX // SIMD int32

//{ Row Major

	template <>
	SA_ENGINE_API RMat4i RMat4i::operator*(int32 _scale) const noexcept;

#if SA_INTRISC_SVML
	template <>
	SA_ENGINE_API RMat4i RMat4i::operator/(int32 _scale) const noexcept;
#endif

	template <>
	SA_ENGINE_API RMat4i RMat4i::operator+(const RMat4i& _rhs) const noexcept;

	template <>
	SA_ENGINE_API RMat4i RMat4i::operator-(const RMat4i& _rhs) const noexcept;

	template <>
	SA_ENGINE_API RMat4i RMat4i::operator*(const RMat4i& _rhs) const noexcept;


	template <>
	SA_ENGINE_API Vec3<int32> RMat4i::operator*(const Vec3<int32>& _rhs) const noexcept;

	template <>
	SA_ENGINE_API Vec4<int32> RMat4i::operator*(const Vec4<int32>& _rhs) const noexcept;


	template <>
	SA_ENGINE_API RMat4i& RMat4i::operator*=(int32 _scale) noexcept;

#if SA_INTRISC_SVML
	template <>
	SA_ENGINE_API RMat4i& RMat4i::operator/=(int32 _scale) noexcept;
#endif

	template <>
	SA_ENGINE_API RMat4i& RMat4i::operator+=(const RMat4i& _rhs) noexcept;

	template <>
	SA_ENGINE_API RMat4i& RMat4i::operator-=(const RMat4i& _rhs) noexcept;

//}

//{ Column Major

	template <>
	SA_ENGINE_API CMat4i CMat4i::operator*(int32 _scale) const noexcept;

#if SA_INTRISC_SVML
	template <>
	SA_ENGINE_API CMat4i CMat4i::operator/(int32 _scale) const noexcept;
#endif

	template <>
	SA_ENGINE_API CMat4i CMat4i::operator+(const CMat4i& _rhs) const noexcept;

	template <>
	SA_ENGINE_API CMat4i CMat4i::operator-(const CMat4i& _rhs) const noexcept;

	template <>
	SA_ENGINE_API CMat4i CMat4i::operator*(const CMat4i& _rhs) const noexcept;


	template <>
	SA_ENGINE_API Vec3<int32> CMat4i::operator*(const Vec3<int32>& _rhs) const noexcept;

	template <>
	SA_ENGINE_API Vec4<int32> CMat4i::operator*(const Vec4<int32>& _rhs) const noexcept;


	template <>
	SA_ENGINE_API CMat4i& CMat4i::operator*=(int32 _scale) noexcept;

#if SA_INTRISC_SVML
	template <>
	SA_ENGINE_API CMat4i& CMat4i::operator/=(int32 _scale) noexcept;
#endif

	template <>
	SA_ENGINE_API CMat4i& CMat4i::operator+=(const CMat4i& _rhs) noexcept;

	template <>
	SA_ENGINE_API CMat4i& CMat4i::operator-=(const CMat4i& _rhs) noexcept;

//}

#endif

#if SA_INTRISC_SSE // SIMD float

//{ Row Major

	template <>
	SA_ENGINE_API float RMat4f::Determinant() const noexcept;

	template <>
	SA_ENGINE_API RMat4f RMat4f::GetInversed() const noexcept;


	template <>
	SA_ENGINE_API RMat4f& RMat4f::ApplyScale(const Vec3<float>& _scale) noexcept;


	template <>
	SA_ENGINE_API RMat4f RMat4f::MakeRotation(const Quat<float>& _rot) noexcept;


	template <>
	SA_ENGINE_API RMat4f RMat4f::operator*(float _scale) const noexcept;

	template <>
	SA_ENGINE_API RMat4f RMat4f::operator/(float _scale) const noexcept;

	template <>
	SA_ENGINE_API RMat4f RMat4f::operator+(const RMat4f& _rhs) const noexcept;

	template <>
	SA_ENGINE_API RMat4f RMat4f::operator-(const RMat4f& _rhs) const noexcept;

	template <>
	SA_ENGINE_API RMat4f RMat4f::operator*(const RMat4f& _rhs) const noexcept;


	template <>
	SA_ENGINE_API Vec3<float> RMat4f::operator*(const Vec3<float>& _rhs) const noexcept;

	template <>
	SA_ENGINE_API Vec4<float> RMat4f::operator*(const Vec4<float>& _rhs) const noexcept;


	template <>
	SA_ENGINE_API RMat4f& RMat4f::operator*=(float _scale) noexcept;

	template <>
	SA_ENGINE_API RMat4f& RMat4f::operator/=(float _scale) noexcept;

	template <>
	SA_ENGINE_API RMat4f& RMat4f::operator+=(const RMat4f& _rhs) noexcept;

	template <>
	SA_ENGINE_API RMat4f& RMat4f::operator-=(const RMat4f& _rhs) noexcept;


	template <>
	SA_ENGINE_API RMat4f operator/(float _lhs, const RMat4f& _rhs) noexcept;

//}

//{ Column Major

	template <>
	SA_ENGINE_API float CMat4f::Determinant() const noexcept;

	template <>
	SA_ENGINE_API CMat4f CMat4f::GetInversed() const noexcept;


	template <>
	SA_ENGINE_API CMat4f& CMat4f::ApplyScale(const Vec3<float>& _scale) noexcept;


	template <>
	SA_ENGINE_API CMat4f CMat4f::MakeRotation(const Quat<float>& _rot) noexcept;


	template <>
	SA_ENGINE_API CMat4f CMat4f::operator*(float _scale) const noexcept;

	template <>
	SA_ENGINE_API CMat4f CMat4f::operator/(float _scale) const noexcept;

	template <>
	SA_ENGINE_API CMat4f CMat4f::operator+(const CMat4f& _rhs) const noexcept;

	template <>
	SA_ENGINE_API CMat4f CMat4f::operator-(const CMat4f& _rhs) const noexcept;

	template <>
	SA_ENGINE_API CMat4f CMat4f::operator*(const CMat4f& _rhs) const noexcept;


	template <>
	SA_ENGINE_API Vec3<float> CMat4f::operator*(const Vec3<float>& _rhs) const noexcept;

	template <>
	SA_ENGINE_API Vec4<float> CMat4f::operator*(const Vec4<float>& _rhs) const noexcept;


	template <>
	SA_ENGINE_API CMat4f& CMat4f::operator*=(float _scale) noexcept;

	template <>
	SA_ENGINE_API CMat4f& CMat4f::operator/=(float _scale) noexcept;

	template <>
	SA_ENGINE_API CMat4f& CMat4f::operator+=(const CMat4f& _rhs) noexcept;

	template <>
	SA_ENGINE_API CMat4f& CMat4f::operator-=(const CMat4f& _rhs) noexcept;


	template <>
	SA_ENGINE_API CMat4f operator/(float _lhs, const CMat4f& _rhs) noexcept;

//}

#endif

#if SA_INTRISC_AVX // SIMD double

//{ Row Major

	template <>
	SA_ENGINE_API double RMat4d::Determinant() const noexcept;

	template <>
	SA_ENGINE_API RMat4d RMat4d::GetInversed() const noexcept;


	template <>
	SA_ENGINE_API RMat4d& RMat4d::ApplyScale(const Vec3<double>& _scale) noexcept;


	template <>
	SA_ENGINE_API RMat4d RMat4d::MakeRotation(const Quat<double>& _rot) noexcept;


	template <>
	SA_ENGINE_API RMat4d RMat4d::operator*(double _scale) const noexcept;

	template <>
	SA_ENGINE_API RMat4d RMat4d::operator/(double _scale) const noexcept;

	template <>
	SA_ENGINE_API RMat4d RMat4d::operator+(const RMat4d& _rhs) const noexcept;

	template <>
	SA_ENGINE_API RMat4d RMat4d::operator-(const RMat4d& _rhs) const noexcept;

	template <>
	SA_ENGINE_API RMat4d RMat4d::operator*(const RMat4d& _rhs) const noexcept;


	template <>
	SA_ENGINE_API Vec3<double> RMat4d::operator*(const Vec3<double>& _rhs) const noexcept;

	template <>
	SA_ENGINE_API Vec4<double> RMat4d::operator*(const Vec4<double>& _rhs) const noexcept;


	template <>
	SA_ENGINE_API RMat4d& RMat4d::operator*=(double _scale) noexcept;

	template <>
	SA_ENGINE_API RMat4d& RMat4d::operator/=(double _scale) noexcept;

	template <>
	SA_ENGINE_API RMat4d& RMat4d::operator+=(const RMat4d& _rhs) noexcept;

	template <>
	SA_ENGINE_API RMat4d& RMat4d::operator-=(const RMat4d& _rhs) noexcept;


	template <>
	SA_ENGINE_API RMat4d operator/(double _lhs, const RMat4d& _rhs) noexcept;

//}

//{ Column Major

	template <>
	SA_ENGINE_API double CMat4d::Determinant() const noexcept;

	template <>
	SA_ENGINE_API CMat4d CMat4d::GetInversed() const noexcept;


	template <>
	SA_ENGINE_API CMat4d& CMat4d::ApplyScale(const Vec3<double>& _scale) noexcept;


	template <>
	SA_ENGINE_API CMat4d CMat4d::MakeRotation(const Quat<double>& _rot) noexcept;


	template <>
	SA_ENGINE_API CMat4d CMat4d::operator*(double _scale) const noexcept;

	template <>
	SA_ENGINE_API CMat4d CMat4d::operator/(double _scale) const noexcept;

	template <>
	SA_ENGINE_API CMat4d CMat4d::operator+(const CMat4d& _rhs) const noexcept;

	template <>
	SA_ENGINE_API CMat4d CMat4d::operator-(const CMat4d& _rhs) const noexcept;

	template <>
	SA_ENGINE_API CMat4d CMat4d::operator*(const CMat4d& _rhs) const noexcept;


	template <>
	SA_ENGINE_API Vec3<double> CMat4d::operator*(const Vec3<double>& _rhs) const noexcept;

	template <>
	SA_ENGINE_API Vec4<double> CMat4d::operator*(const Vec4<double>& _rhs) const noexcept;


	template <>
	SA_ENGINE_API CMat4d& CMat4d::operator*=(double _scale) noexcept;

	template <>
	SA_ENGINE_API CMat4d& CMat4d::operator/=(double _scale) noexcept;

	template <>
	SA_ENGINE_API CMat4d& CMat4d::operator+=(const CMat4d& _rhs) noexcept;

	template <>
	SA_ENGINE_API CMat4d& CMat4d::operator-=(const CMat4d& _rhs) noexcept;


	template <>
	SA_ENGINE_API CMat4d operator/(double _lhs, const CMat4d& _rhs) noexcept;

//}

#endif

	/// \endcond
}


/** \} */

#include <SA/Maths/Matrix/Matrix4.inl>

#endif // GUARD
