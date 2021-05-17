// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

namespace Sa
{
//{ Constants

	template <typename T, MatrixMajor major>
	const Mat4<T, major> Mat4<T, major>::Zero
	{
		T(0), T(0), T(0), T(0),
		T(0), T(0), T(0), T(0),
		T(0), T(0), T(0), T(0),
		T(0), T(0), T(0), T(0)
	};

	template <typename T, MatrixMajor major>
	const Mat4<T, major> Mat4<T, major>::Identity
	{
		T(1), T(0), T(0), T(0),
		T(0), T(1), T(0), T(0),
		T(0), T(0), T(1), T(0),
		T(0), T(0), T(0), T(1)
	};

//}

//{ Constructors

	template <typename T, MatrixMajor major>
	template <typename TIn>
	constexpr Mat4<T, major>::Mat4(const Mat4<TIn, major>& _other) noexcept :
		Intl::Mat4_Base<T, major>(
			static_cast<T>(_other.e00), static_cast<T>(_other.e01), static_cast<T>(_other.e02), static_cast<T>(_other.e03),
			static_cast<T>(_other.e10), static_cast<T>(_other.e11), static_cast<T>(_other.e12), static_cast<T>(_other.e13),
			static_cast<T>(_other.e20), static_cast<T>(_other.e21), static_cast<T>(_other.e22), static_cast<T>(_other.e23),
			static_cast<T>(_other.e30), static_cast<T>(_other.e31), static_cast<T>(_other.e32), static_cast<T>(_other.e33)
		)
	{
	}

	template <typename T, MatrixMajor major>
	template <typename TIn>
	constexpr Mat4<T, major>::Mat4(const Mat3<TIn, major>& _other) noexcept :
		Intl::Mat4_Base<T, major>(
			static_cast<T>(_other.e00), static_cast<T>(_other.e01), static_cast<T>(_other.e02), T(0),
			static_cast<T>(_other.e10), static_cast<T>(_other.e11), static_cast<T>(_other.e12), T(0),
			static_cast<T>(_other.e20), static_cast<T>(_other.e21), static_cast<T>(_other.e22), T(0),
			T(0), T(0), T(0), T(1)
		)
	{
	}

//}

//{ Equals

	template <typename T, MatrixMajor major>
	constexpr bool Mat4<T, major>::IsZero() const noexcept
	{
		// Allows constexpr.

		return
			Sa::Equals0(e00) && Sa::Equals0(e01) && Sa::Equals0(e02) && Sa::Equals0(e03) &&
			Sa::Equals0(e10) && Sa::Equals0(e11) && Sa::Equals0(e12) && Sa::Equals0(e13) &&
			Sa::Equals0(e20) && Sa::Equals0(e21) && Sa::Equals0(e22) && Sa::Equals0(e23) &&
			Sa::Equals0(e30) && Sa::Equals0(e31) && Sa::Equals0(e32) && Sa::Equals0(e33);
	}

	template <typename T, MatrixMajor major>
	constexpr bool Mat4<T, major>::IsIdentity() const noexcept
	{
		// Allows constexpr.

		return
			Sa::Equals1(e00) && Sa::Equals0(e01) && Sa::Equals0(e02) && Sa::Equals0(e03) &&
			Sa::Equals0(e10) && Sa::Equals1(e11) && Sa::Equals0(e12) && Sa::Equals0(e13) &&
			Sa::Equals0(e20) && Sa::Equals0(e21) && Sa::Equals1(e22) && Sa::Equals0(e23) &&
			Sa::Equals0(e30) && Sa::Equals0(e31) && Sa::Equals0(e32) && Sa::Equals1(e33);
	}


	template <typename T, MatrixMajor major>
	constexpr bool Mat4<T, major>::Equals(const Mat4& _other, T _threshold) const noexcept
	{
		// Allows constexpr.

		return
			Sa::Equals(e00, _other.e00, _threshold) &&
			Sa::Equals(e01, _other.e01, _threshold) &&
			Sa::Equals(e02, _other.e02, _threshold) &&
			Sa::Equals(e03, _other.e03, _threshold) &&
			Sa::Equals(e10, _other.e10, _threshold) &&
			Sa::Equals(e11, _other.e11, _threshold) &&
			Sa::Equals(e12, _other.e12, _threshold) &&
			Sa::Equals(e13, _other.e13, _threshold) &&
			Sa::Equals(e20, _other.e20, _threshold) &&
			Sa::Equals(e21, _other.e21, _threshold) &&
			Sa::Equals(e22, _other.e22, _threshold) &&
			Sa::Equals(e23, _other.e23, _threshold) &&
			Sa::Equals(e30, _other.e30, _threshold) &&
			Sa::Equals(e31, _other.e31, _threshold) &&
			Sa::Equals(e32, _other.e32, _threshold) &&
			Sa::Equals(e33, _other.e33, _threshold);
	}


	template <typename T, MatrixMajor major>
	constexpr bool Mat4<T, major>::operator==(const Mat4& _rhs) const noexcept
	{
		return Equals(_rhs);
	}

	template <typename T, MatrixMajor major>
	constexpr bool Mat4<T, major>::operator!=(const Mat4& _rhs) const noexcept
	{
		return !(*this == _rhs);
	}

//}

//{ Accessors

	template <typename T, MatrixMajor major>
	T* Mat4<T, major>::Data() noexcept
	{
		return &e00;
	}

	template <typename T, MatrixMajor major>
	const T* Mat4<T, major>::Data() const noexcept
	{
		return &e00;
	}


	template <typename T, MatrixMajor major>
	T& Mat4<T, major>::At(uint32 _index)
	{
		SA_ASSERT(OutOfRange, Maths, _index, 0u, 15u);

		return Data()[_index];

	}

	template <typename T, MatrixMajor major>
	const T& Mat4<T, major>::At(uint32 _index) const
	{
		SA_ASSERT(OutOfRange, Maths, _index, 0u, 15u);

		return Data()[_index];
	}

	template <typename T, MatrixMajor major>
	T& Mat4<T, major>::At(uint32 _x, uint32 _y)
	{
		SA_ASSERT(OutOfRange, Maths, _x, 0u, 4u);
		SA_ASSERT(OutOfRange, Maths, _y, 0u, 4u);

		return Data()[_x * 4u + _y];
	}

	template <typename T, MatrixMajor major>
	const T& Mat4<T, major>::At(uint32 _x, uint32 _y) const
	{
		SA_ASSERT(OutOfRange, Maths, _x, 0u, 4u);
		SA_ASSERT(OutOfRange, Maths, _y, 0u, 4u);

		return Data()[_x * 4u + _y];
	}


	template <typename T, MatrixMajor major>
	T& Mat4<T, major>::operator[](uint32 _index)
	{
		return At(_index);
	}

	template <typename T, MatrixMajor major>
	const T& Mat4<T, major>::operator[](uint32 _index) const
	{
		return At(_index);
	}

//}

//{ Transpose

	template <typename T, MatrixMajor major>
	Mat4<T, major>& Mat4<T, major>::Transpose() noexcept
	{
		std::swap(e01, e10);
		std::swap(e02, e20);
		std::swap(e03, e30);

		std::swap(e12, e21);
		std::swap(e13, e31);

		std::swap(e23, e32);

		return *this;
	}

	template <typename T, MatrixMajor major>
	constexpr Mat4<T, major> Mat4<T, major>::GetTransposed() const noexcept
	{
		// Allows constexpr.

		return Mat4(
			e00, e10, e20, e30,
			e01, e11, e21, e31,
			e02, e12, e22, e32,
			e03, e13, e23, e33
		);
	}

//}

//{ Inverse

	template <typename T, MatrixMajor major>
	T Mat4<T, major>::Determinant() const noexcept
	{
		const T det22_33_23_32 = e22 * e33 - e23 * e32;
		const T det12_33_13_32 = e12 * e33 - e13 * e32;
		const T det12_23_13_22 = e12 * e23 - e13 * e22;
		const T det02_33_03_32 = e02 * e33 - e03 * e32;
		const T det02_23_03_22 = e02 * e23 - e03 * e22;
		const T det02_13_03_12 = e02 * e13 - e03 * e12;

		return
			e00 * (e11 * det22_33_23_32 - e21 * det12_33_13_32 + e31 * det12_23_13_22) -
			e10 * (e01 * det22_33_23_32 - e21 * det02_33_03_32 + e31 * det02_23_03_22) +
			e20 * (e01 * det12_33_13_32 - e11 * det02_33_03_32 + e31 * det02_13_03_12) -
			e30 * (e01 * det12_23_13_22 - e11 * det02_23_03_22 + e21 * det02_13_03_12);
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>& Mat4<T, major>::Inverse() noexcept
	{
		return *this = GetInversed();
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::GetInversed() const noexcept
	{
		const T det = Determinant();

		SA_WARN(!Sa::Equals0(det), Maths, L"Inverse matrix with determinant == 0");

		Mat4 result;

		const T _01x12 = e01 * e12;
		const T _01x13 = e01 * e13;
		const T _01x22 = e01 * e22;
		const T _01x23 = e01 * e23;
		const T _01x32 = e01 * e32;
		const T _01x33 = e01 * e33;

		const T _02x11 = e02 * e11;
		const T _02x13 = e02 * e13;
		const T _02x21 = e02 * e21;
		const T _02x23 = e02 * e23;
		const T _02x31 = e02 * e31;
		const T _02x33 = e02 * e33;

		const T _03x11 = e03 * e11;
		const T _03x12 = e03 * e12;
		const T _03x21 = e03 * e21;
		const T _03x22 = e03 * e22;
		const T _03x31 = e03 * e31;
		const T _03x32 = e03 * e32;

		const T _11x22 = e11 * e22;
		const T _11x23 = e11 * e23;
		const T _11x32 = e11 * e32;
		const T _11x33 = e11 * e33;

		const T _12x21 = e12 * e21;
		const T _12x23 = e12 * e23;
		const T _12x31 = e12 * e31;
		const T _12x33 = e12 * e33;

		const T _13x21 = e13 * e21;
		const T _13x22 = e13 * e22;
		const T _13x31 = e13 * e31;
		const T _13x32 = e13 * e32;

		const T _21x32 = e21 * e32;
		const T _21x33 = e21 * e33;

		const T _22x31 = e22 * e31;
		const T _22x33 = e22 * e33;

		const T _23x31 = e23 * e31;
		const T _23x32 = e23 * e32;

		// Row 0.
		result.e00 =
			e11 * _22x33 -
			e11 * _23x32 -
			e21 * _12x33 +
			e21 * _13x32 +
			e31 * _12x23 -
			e31 * _13x22;

		result.e01 =
			-e01 * _22x33 +
			e01 * _23x32 +
			e21 * _02x33 -
			e21 * _03x32 -
			e31 * _02x23 +
			e31 * _03x22;

		result.e02 =
			e01 * _12x33 -
			e01 * _13x32 -
			e11 * _02x33 +
			e11 * _03x32 +
			e31 * _02x13 -
			e31 * _03x12;

		result.e03 =
			-e01 * _12x23 +
			e01 * _13x22 +
			e11 * _02x23 -
			e11 * _03x22 -
			e21 * _02x13 +
			e21 * _03x12;


		// Row 1
		result.e10 =
			-e10 * _22x33 +
			e10 * _23x32 +
			e20 * _12x33 -
			e20 * _13x32 -
			e30 * _12x23 +
			e30 * _13x22;

		result.e11 =
			e00 * _22x33 -
			e00 * _23x32 -
			e20 * _02x33 +
			e20 * _03x32 +
			e30 * _02x23 -
			e30 * _03x22;

		result.e12 =
			-e00 * _12x33 +
			e00 * _13x32 +
			e10 * _02x33 -
			e10 * _03x32 -
			e30 * _02x13 +
			e30 * _03x12;

		result.e13 =
			e00 * _12x23 -
			e00 * _13x22 -
			e10 * _02x23 +
			e10 * _03x22 +
			e20 * _02x13 -
			e20 * _03x12;


		// Row 2.
		result.e20 =
			e10 * _21x33 -
			e10 * _23x31 -
			e20 * _11x33 +
			e20 * _13x31 +
			e30 * _11x23 -
			e30 * _13x21;

		result.e21 =
			-e00 * _21x33 +
			e00 * _23x31 +
			e20 * _01x33 -
			e20 * _03x31 -
			e30 * _01x23 +
			e30 * _03x21;

		result.e22 =
			e00 * _11x33 -
			e00 * _13x31 -
			e10 * _01x33 +
			e10 * _03x31 +
			e30 * _01x13 -
			e30 * _03x11;

		result.e23 =
			-e00 * _11x23 +
			e00 * _13x21 +
			e10 * _01x23 -
			e10 * _03x21 -
			e20 * _01x13 +
			e20 * _03x11;


		// Row 3.
		result.e30 =
			-e10 * _21x32 +
			e10 * _22x31 +
			e20 * _11x32 -
			e20 * _12x31 -
			e30 * _11x22 +
			e30 * _12x21;

		result.e31 =
			e00 * _21x32 -
			e00 * _22x31 -
			e20 * _01x32 +
			e20 * _02x31 +
			e30 * _01x22 -
			e30 * _02x21;

		result.e32 =
			-e00 * _11x32 +
			e00 * _12x31 +
			e10 * _01x32 -
			e10 * _02x31 -
			e30 * _01x12 +
			e30 * _02x11;

		result.e33 =
			e00 * _11x22 -
			e00 * _12x21 -
			e10 * _01x22 +
			e10 * _02x21 +
			e20 * _01x12 -
			e20 * _02x11;


		result /= det;

		return result;
	}

//}
	
//{ Lerp

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::Lerp(const Mat4& _start, const Mat4& _end, float _alpha) noexcept
	{
		SA_WARN(_alpha >= 0.0f && _alpha <= 1.0f, Maths, L"Alpha[" << _alpha << L"] clamped to range [0, 1]! Use LerpUnclamped if intended instead.");

		return LerpUnclamped(_start, _end, std::clamp(_alpha, 0.0f, 1.0f));
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::LerpUnclamped(const Mat4& _start, const Mat4& _end, float _alpha) noexcept
	{
		return Mat4(
			Maths::LerpUnclamped(_start.e00, _end.e00, _alpha),
			Maths::LerpUnclamped(_start.e01, _end.e01, _alpha),
			Maths::LerpUnclamped(_start.e02, _end.e02, _alpha),
			Maths::LerpUnclamped(_start.e03, _end.e03, _alpha),
			Maths::LerpUnclamped(_start.e10, _end.e10, _alpha),
			Maths::LerpUnclamped(_start.e11, _end.e11, _alpha),
			Maths::LerpUnclamped(_start.e12, _end.e12, _alpha),
			Maths::LerpUnclamped(_start.e13, _end.e13, _alpha),
			Maths::LerpUnclamped(_start.e20, _end.e20, _alpha),
			Maths::LerpUnclamped(_start.e21, _end.e21, _alpha),
			Maths::LerpUnclamped(_start.e22, _end.e22, _alpha),
			Maths::LerpUnclamped(_start.e23, _end.e23, _alpha),
			Maths::LerpUnclamped(_start.e30, _end.e30, _alpha),
			Maths::LerpUnclamped(_start.e31, _end.e31, _alpha),
			Maths::LerpUnclamped(_start.e32, _end.e32, _alpha),
			Maths::LerpUnclamped(_start.e33, _end.e33, _alpha)
		);
	}

//}

//{ Transform

	template <typename T, MatrixMajor major>
	Mat4<T, major>& Mat4<T, major>::ApplyTranslation(const Vec3<T>& _transl) noexcept
	{
		e03 += _transl.x;
		e13 += _transl.y;
		e23 += _transl.z;

		return *this;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>& Mat4<T, major>::ApplyScale(const Vec3<T>& _scale) noexcept
	{
		e00 *= _scale.x;
		e01 *= _scale.x;
		e02 *= _scale.x;
		e03 *= _scale.x;

		e10 *= _scale.y;
		e11 *= _scale.y;
		e12 *= _scale.y;
		e13 *= _scale.y;

		e20 *= _scale.z;
		e21 *= _scale.z;
		e22 *= _scale.z;
		e23 *= _scale.z;

		return *this;
	}


	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::MakeTranslation(const Vec3<T>& _transl) noexcept
	{
		Mat4 result = Mat4::Identity;

		result.e03 = _transl.x;
		result.e13 = _transl.y;
		result.e23 = _transl.z;

		return result;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::MakeRotation(const Quat<T>& _rotation) noexcept
	{
		SA_WARN(_rotation.IsNormalized(), Maths, L"Quaternion should be normalized!");

		// Sources: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation

		const T XW2 = 2.0f * _rotation.x * _rotation.w;
		const T XX2 = 2.0f * _rotation.x * _rotation.x;
		const T XY2 = 2.0f * _rotation.x * _rotation.y;
		const T XZ2 = 2.0f * _rotation.x * _rotation.z;

		const T YW2 = 2.0f * _rotation.y * _rotation.w;
		const T YY2 = 2.0f * _rotation.y * _rotation.y;
		const T YZ2 = 2.0f * _rotation.y * _rotation.z;

		const T ZW2 = 2.0f * _rotation.z * _rotation.w;
		const T ZZ2 = 2.0f * _rotation.z * _rotation.z;

		return Mat4(
			1.0f - YY2 - ZZ2, XY2 - ZW2, XZ2 + YW2, 0.0f,
			XY2 + ZW2, 1.0f - XX2 - ZZ2, YZ2 - XW2, 0.0f,
			XZ2 - YW2, YZ2 + XW2, 1.0f - XX2 - YY2, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::MakeScale(const Vec3<T>& _scale) noexcept
	{
		Mat4 result = Mat4::Identity;

		result.e00 = _scale.x;
		result.e11 = _scale.y;
		result.e22 = _scale.z;

		return result;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>  Mat4<T, major>::MakeTransform(const Vec3<T>& _transl, const Quat<T>& _rotation) noexcept
	{
		Mat4<T, major> result = MakeRotation(_rotation);

		// Set translation.
		result.e03 = _transl.x;
		result.e13 = _transl.y;
		result.e23 = _transl.z;

		return result;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>  Mat4<T, major>::MakeTransform(const Vec3<T>& _transl, const Vec3<T>& _scale) noexcept
	{
		Mat4<T, major> result = MakeScale(_scale);

		// Set translation.
		result.e03 = _transl.x;
		result.e13 = _transl.y;
		result.e23 = _transl.z;

		return result;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>  Mat4<T, major>::MakeTransform(const Quat<T>& _rotation, const Vec3<T>& _scale) noexcept
	{
		return MakeRotation(_rotation).ApplyScale(_scale);
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>  Mat4<T, major>::MakeTransform(const Vec3<T>& _transl, const Quat<T>& _rotation, const Vec3<T>& _scale) noexcept
	{
		Mat4<T, major> result = MakeRotation(_rotation).ApplyScale(_scale);

		// Set Translation.
		result.e03 = _transl.x;
		result.e13 = _transl.y;
		result.e23 = _transl.z;

		return result;
	}


	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::MakePerspective(T _fov, T _aspect, T _near, T _far) noexcept
	{
		// TODO: Clean.
		//const float scale = 1.f / tanf((_fov / 2.f) * Maths::DegToRad);
		float tan_half_angle = static_cast<float>(std::tan(Maths::DegToRad * _fov / 2));

		return Mat4(
			1 / (_aspect * tan_half_angle), 0, 0, 0,
			0, 1 / (tan_half_angle), 0, 0,
			0, 0, -_far / (_far - _near), -(2 * _far * _near) / (_far - _near),
			0, 0, -1, 0
		);
	}

//}

//{ Operators

	template <typename T, MatrixMajor major>
	constexpr Mat4<T, major> Mat4<T, major>::operator-() const noexcept
	{
		// Allows constexpr.

		return Mat4(
			-e00, -e01, -e02, -e03,
			-e10, -e11, -e12, -e13,
			-e20, -e21, -e22, -e23,
			-e30, -e31, -e32, -e33
		);
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::operator*(T _scale) const noexcept
	{
		return Mat4(
			e00 * _scale, e01 * _scale, e02 * _scale, e03 * _scale,
			e10 * _scale, e11 * _scale, e12 * _scale, e13 * _scale,
			e20 * _scale, e21 * _scale, e22 * _scale, e23 * _scale,
			e30 * _scale, e31 * _scale, e32 * _scale, e33 * _scale
		);
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::operator/(T _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		return Mat4(
			e00 / _scale, e01 / _scale, e02 / _scale, e03 / _scale,
			e10 / _scale, e11 / _scale, e12 / _scale, e13 / _scale,
			e20 / _scale, e21 / _scale, e22 / _scale, e23 / _scale,
			e30 / _scale, e31 / _scale, e32 / _scale, e33 / _scale
		);
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::operator+(const Mat4& _rhs) const noexcept
	{
		return Mat4(
			e00 + _rhs.e00, e01 + _rhs.e01, e02 + _rhs.e02, e03 + _rhs.e03,
			e10 + _rhs.e10, e11 + _rhs.e11, e12 + _rhs.e12, e13 + _rhs.e13,
			e20 + _rhs.e20, e21 + _rhs.e21, e22 + _rhs.e22, e23 + _rhs.e23,
			e30 + _rhs.e30, e31 + _rhs.e31, e32 + _rhs.e32, e33 + _rhs.e33
		);
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::operator-(const Mat4& _rhs) const noexcept
	{
		return Mat4(
			e00 - _rhs.e00, e01 - _rhs.e01, e02 - _rhs.e02, e03 - _rhs.e03,
			e10 - _rhs.e10, e11 - _rhs.e11, e12 - _rhs.e12, e13 - _rhs.e13,
			e20 - _rhs.e20, e21 - _rhs.e21, e22 - _rhs.e22, e23 - _rhs.e23,
			e30 - _rhs.e30, e31 - _rhs.e31, e32 - _rhs.e32, e33 - _rhs.e33
		);
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::operator*(const Mat4& _rhs) const noexcept
	{
		return Mat4(
			e00 * _rhs.e00 + e01 * _rhs.e10 + e02 * _rhs.e20 + e03 * _rhs.e30,
			e00 * _rhs.e01 + e01 * _rhs.e11 + e02 * _rhs.e21 + e03 * _rhs.e31,
			e00 * _rhs.e02 + e01 * _rhs.e12 + e02 * _rhs.e22 + e03 * _rhs.e32,
			e00 * _rhs.e03 + e01 * _rhs.e13 + e02 * _rhs.e23 + e03 * _rhs.e33,

			e10 * _rhs.e00 + e11 * _rhs.e10 + e12 * _rhs.e20 + e13 * _rhs.e30,
			e10 * _rhs.e01 + e11 * _rhs.e11 + e12 * _rhs.e21 + e13 * _rhs.e31,
			e10 * _rhs.e02 + e11 * _rhs.e12 + e12 * _rhs.e22 + e13 * _rhs.e32,
			e10 * _rhs.e03 + e11 * _rhs.e13 + e12 * _rhs.e23 + e13 * _rhs.e33,

			e20 * _rhs.e00 + e21 * _rhs.e10 + e22 * _rhs.e20 + e23 * _rhs.e30,
			e20 * _rhs.e01 + e21 * _rhs.e11 + e22 * _rhs.e21 + e23 * _rhs.e31,
			e20 * _rhs.e02 + e21 * _rhs.e12 + e22 * _rhs.e22 + e23 * _rhs.e32,
			e20 * _rhs.e03 + e21 * _rhs.e13 + e22 * _rhs.e23 + e23 * _rhs.e33,

			e30 * _rhs.e00 + e31 * _rhs.e10 + e32 * _rhs.e20 + e33 * _rhs.e30,
			e30 * _rhs.e01 + e31 * _rhs.e11 + e32 * _rhs.e21 + e33 * _rhs.e31,
			e30 * _rhs.e02 + e31 * _rhs.e12 + e32 * _rhs.e22 + e33 * _rhs.e32,
			e30 * _rhs.e03 + e31 * _rhs.e13 + e32 * _rhs.e23 + e33 * _rhs.e33
		);
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> Mat4<T, major>::operator/(const Mat4& _rhs) const noexcept
	{
		return *this * _rhs.GetInversed();
	}


	template <typename T, MatrixMajor major>
	Vec3<T> Mat4<T, major>::operator*(const Vec3<T>& _rhs) const noexcept
	{
		return Vec3(
			e00 * _rhs.x + e01 * _rhs.y + e02 * _rhs.z,
			e10 * _rhs.x + e11 * _rhs.y + e12 * _rhs.z,
			e20 * _rhs.x + e21 * _rhs.y + e22 * _rhs.z
		);
	}

	template <typename T, MatrixMajor major>
	Vec4<T> Mat4<T, major>::operator*(const Vec4<T>& _rhs) const noexcept
	{
		return Vec4(
			e00 * _rhs.x + e01 * _rhs.y + e02 * _rhs.z + e03 * _rhs.w,
			e10 * _rhs.x + e11 * _rhs.y + e12 * _rhs.z + e13 * _rhs.w,
			e20 * _rhs.x + e21 * _rhs.y + e22 * _rhs.z + e23 * _rhs.w,
			e30 * _rhs.x + e31 * _rhs.y + e32 * _rhs.z + e33 * _rhs.w
		);
	}


	template <typename T, MatrixMajor major>
	Mat4<T, major>& Mat4<T, major>::operator*=(T _scale) noexcept
	{
		e00 *= _scale;
		e01 *= _scale;
		e02 *= _scale;
		e03 *= _scale;

		e10 *= _scale;
		e11 *= _scale;
		e12 *= _scale;
		e13 *= _scale;

		e20 *= _scale;
		e21 *= _scale;
		e22 *= _scale;
		e23 *= _scale;

		e30 *= _scale;
		e31 *= _scale;
		e32 *= _scale;
		e33 *= _scale;

		return *this;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>& Mat4<T, major>::operator/=(T _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division vy 0)!");

		e00 /= _scale;
		e01 /= _scale;
		e02 /= _scale;
		e03 /= _scale;

		e10 /= _scale;
		e11 /= _scale;
		e12 /= _scale;
		e13 /= _scale;

		e20 /= _scale;
		e21 /= _scale;
		e22 /= _scale;
		e23 /= _scale;

		e30 /= _scale;
		e31 /= _scale;
		e32 /= _scale;
		e33 /= _scale;

		return *this;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>& Mat4<T, major>::operator+=(const Mat4& _rhs) noexcept
	{
		e00 += _rhs.e00;
		e01 += _rhs.e01;
		e02 += _rhs.e02;
		e03 += _rhs.e03;

		e10 += _rhs.e10;
		e11 += _rhs.e11;
		e12 += _rhs.e12;
		e13 += _rhs.e13;

		e20 += _rhs.e20;
		e21 += _rhs.e21;
		e22 += _rhs.e22;
		e23 += _rhs.e23;

		e30 += _rhs.e30;
		e31 += _rhs.e31;
		e32 += _rhs.e32;
		e33 += _rhs.e33;

		return *this;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>& Mat4<T, major>::operator-=(const Mat4& _rhs) noexcept
	{
		e00 -= _rhs.e00;
		e01 -= _rhs.e01;
		e02 -= _rhs.e02;
		e03 -= _rhs.e03;

		e10 -= _rhs.e10;
		e11 -= _rhs.e11;
		e12 -= _rhs.e12;
		e13 -= _rhs.e13;

		e20 -= _rhs.e20;
		e21 -= _rhs.e21;
		e22 -= _rhs.e22;
		e23 -= _rhs.e23;

		e30 -= _rhs.e30;
		e31 -= _rhs.e31;
		e32 -= _rhs.e32;
		e33 -= _rhs.e33;

		return *this;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>& Mat4<T, major>::operator*=(const Mat4& _rhs) noexcept
	{
		return *this = *this * _rhs;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major>& Mat4<T, major>::operator/=(const Mat4& _rhs) noexcept
	{
		return *this = *this / _rhs;
	}

//}


#if SA_LOGGING

	template <typename T, MatrixMajor major>
	std::string Mat4<T, major>::ToString() const noexcept
	{
		// Keep memory order (Raw / column major).
		const T* const data = Data();

		return
			Sa::ToString(data[0]) + ", " +
			Sa::ToString(data[1]) + ", " +
			Sa::ToString(data[2]) + ", " +
			Sa::ToString(data[3]) + ",\n" +

			Sa::ToString(data[4]) + ", " +
			Sa::ToString(data[5]) + ", " +
			Sa::ToString(data[6]) + ", " +
			Sa::ToString(data[7]) + ",\n" +

			Sa::ToString(data[8]) + ", " +
			Sa::ToString(data[9]) + ", " +
			Sa::ToString(data[10]) + ", " +
			Sa::ToString(data[11]) + ",\n" +

			Sa::ToString(data[12]) + ", " +
			Sa::ToString(data[13]) + ", " +
			Sa::ToString(data[14]) + ", " +
			Sa::ToString(data[15]);
	}

#endif


	template <typename T, MatrixMajor major>
	Mat4<T, major> operator*(typename std::remove_cv<T>::type _lhs, const Mat4<T, major>& _rhs) noexcept
	{
		return _rhs * _lhs;
	}

	template <typename T, MatrixMajor major>
	Mat4<T, major> operator/(typename std::remove_cv<T>::type _lhs, const Mat4<T, major>& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.e00), Maths, L"Inverse scale matrix e00 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e01), Maths, L"Inverse scale matrix e01 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e02), Maths, L"Inverse scale matrix e02 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e03), Maths, L"Inverse scale matrix e03 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e10), Maths, L"Inverse scale matrix e10 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e11), Maths, L"Inverse scale matrix e11 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e12), Maths, L"Inverse scale matrix e12 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e13), Maths, L"Inverse scale matrix e13 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e20), Maths, L"Inverse scale matrix e20 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e21), Maths, L"Inverse scale matrix e21 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e22), Maths, L"Inverse scale matrix e22 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e23), Maths, L"Inverse scale matrix e23 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e30), Maths, L"Inverse scale matrix e30 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e31), Maths, L"Inverse scale matrix e31 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e32), Maths, L"Inverse scale matrix e32 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e33), Maths, L"Inverse scale matrix e33 == 0!");

		return Mat4<T, major>(
			_lhs / _rhs.e00, _lhs / _rhs.e01, _lhs / _rhs.e02, _lhs / _rhs.e03,
			_lhs / _rhs.e10, _lhs / _rhs.e11, _lhs / _rhs.e12, _lhs / _rhs.e13,
			_lhs / _rhs.e20, _lhs / _rhs.e21, _lhs / _rhs.e22, _lhs / _rhs.e23,
			_lhs / _rhs.e30, _lhs / _rhs.e31, _lhs / _rhs.e32, _lhs / _rhs.e33
		);
	}
}
