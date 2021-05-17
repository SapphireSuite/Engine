// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

namespace Sa
{
//{ Constants

	template <typename T, MatrixMajor major>
	const Mat3<T, major> Mat3<T, major>::Zero
	{
		T(0), T(0), T(0),
		T(0), T(0), T(0),
		T(0), T(0), T(0)
	};

	template <typename T, MatrixMajor major>
	const Mat3<T, major> Mat3<T, major>::Identity
	{
		T(1), T(0), T(0),
		T(0), T(1), T(0),
		T(0), T(0), T(1)
	};

//}

//{ Constructors

	template <typename T, MatrixMajor major>
	template <typename TIn>
	constexpr Mat3<T, major>::Mat3(const Mat3<TIn, major>& _other) noexcept :
		Intl::Mat3_Base<T, major>(
			static_cast<T>(_other.e00), static_cast<T>(_other.e01), static_cast<T>(_other.e02),
			static_cast<T>(_other.e10), static_cast<T>(_other.e11), static_cast<T>(_other.e12),
			static_cast<T>(_other.e20), static_cast<T>(_other.e21), static_cast<T>(_other.e22)
		)
	{
	}

	template <typename T, MatrixMajor major>
	template <typename TIn>
	constexpr Mat3<T, major>::Mat3(const Mat4<TIn, major>& _other) noexcept :
		Intl::Mat3_Base<T, major>(
			static_cast<T>(_other.e00), static_cast<T>(_other.e01), static_cast<T>(_other.e02),
			static_cast<T>(_other.e10), static_cast<T>(_other.e11), static_cast<T>(_other.e12),
			static_cast<T>(_other.e20), static_cast<T>(_other.e21), static_cast<T>(_other.e22)
		)
	{
	}

//}

//{ Equals

	template <typename T, MatrixMajor major>
	constexpr bool Mat3<T, major>::IsZero() const noexcept
	{
		// Allows constexpr.

		return
			Sa::Equals0(e00) && Sa::Equals0(e01) && Sa::Equals0(e02) &&
			Sa::Equals0(e10) && Sa::Equals0(e11) && Sa::Equals0(e12) &&
			Sa::Equals0(e20) && Sa::Equals0(e21) && Sa::Equals0(e22);
	}

	template <typename T, MatrixMajor major>
	constexpr bool Mat3<T, major>::IsIdentity() const noexcept
	{
		// Allows constexpr.

		return
			Sa::Equals1(e00) && Sa::Equals0(e01) && Sa::Equals0(e02) &&
			Sa::Equals0(e10) && Sa::Equals1(e11) && Sa::Equals0(e12) &&
			Sa::Equals0(e20) && Sa::Equals0(e21) && Sa::Equals1(e22);
	}

	template <typename T, MatrixMajor major>
	constexpr bool Mat3<T, major>::Equals(const Mat3& _other, T _epsilon) const noexcept
	{
		// Allows constexpr.

		return
			Sa::Equals(e00, _other.e00, _epsilon) && Sa::Equals(e01, _other.e01, _epsilon) && Sa::Equals(e02, _other.e02, _epsilon) &&
			Sa::Equals(e10, _other.e10, _epsilon) && Sa::Equals(e11, _other.e11, _epsilon) && Sa::Equals(e12, _other.e12, _epsilon) &&
			Sa::Equals(e20, _other.e20, _epsilon) && Sa::Equals(e21, _other.e21, _epsilon) && Sa::Equals(e22, _other.e22, _epsilon);
	}


	template <typename T, MatrixMajor major>
	constexpr bool Mat3<T, major>::operator==(const Mat3& _rhs) const noexcept
	{
		return Equals(_rhs);
	}

	template <typename T, MatrixMajor major>
	constexpr bool Mat3<T, major>::operator!=(const Mat3& _rhs) const noexcept
	{
		return !(*this == _rhs);
	}

//}

//{ Accessors

	template <typename T, MatrixMajor major>
	T* Mat3<T, major>::Data() noexcept
	{
		return &e00;
	}

	template <typename T, MatrixMajor major>
	const T* Mat3<T, major>::Data() const noexcept
	{
		return &e00;
	}


	template <typename T, MatrixMajor major>
	T& Mat3<T, major>::At(uint32 _index)
	{
		SA_ASSERT(OutOfRange, Maths, _index, 0u, 8u);

		return Data()[_index];
	}

	template <typename T, MatrixMajor major>
	const T& Mat3<T, major>::At(uint32 _index) const
	{
		SA_ASSERT(OutOfRange, Maths, _index, 0u, 8u);

		return Data()[_index];
	}

	template <typename T, MatrixMajor major>
	T& Mat3<T, major>::At(uint32 _x, uint32 _y)
	{
		SA_ASSERT(OutOfRange, Maths, _x, 0u, 3u);
		SA_ASSERT(OutOfRange, Maths, _y, 0u, 3u);

		return Data()[_x * 3u + _y];
	}

	template <typename T, MatrixMajor major>
	const T& Mat3<T, major>::At(uint32 _x, uint32 _y) const
	{
		SA_ASSERT(OutOfRange, Maths, _x, 0u, 3u);
		SA_ASSERT(OutOfRange, Maths, _y, 0u, 3u);

		return Data()[_x * 3u + _y];
	}


	template <typename T, MatrixMajor major>
	T& Mat3<T, major>::operator[](uint32 _index)
	{
		return At(_index);
	}

	template <typename T, MatrixMajor major>
	const T& Mat3<T, major>::operator[](uint32 _index) const
	{
		return At(_index);
	}

//}


//{ Transpose

	template <typename T, MatrixMajor major>
	Mat3<T, major>& Mat3<T, major>::Transpose() noexcept
	{
		std::swap(e01, e10);
		std::swap(e02, e20);
		std::swap(e12, e21);

		return *this;
	}

	template <typename T, MatrixMajor major>
	constexpr Mat3<T, major> Mat3<T, major>::GetTransposed() const noexcept
	{
		// Allows constexpr.

		return Mat3(
			e00, e10, e20,
			e01, e11, e21,
			e02, e12, e22
		);
	}

//}

//{ Inverse

	template <typename T, MatrixMajor major>
	T Mat3<T, major>::Determinant() const noexcept
	{
		return
			e00 * e11 * e22 +
			e01 * e12 * e20 +
			e02 * e10 * e21 -
			e20 * e11 * e02 -
			e21 * e12 * e00 -
			e22 * e10 * e01;
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major>& Mat3<T, major>::Inverse() noexcept
	{
		return *this = GetInversed();
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::GetInversed() const noexcept
	{
		const T det = Determinant();

		SA_WARN(!Sa::Equals0(det), Maths, L"Inverse matrix with determinant == 0");

		return (1.0f / det) * Mat3(
			e11 * e22 - e21 * e12, e02 * e21 - e01 * e22, e01 * e12 - e11 * e02,
			e12 * e20 - e10 * e22, e00 * e22 - e20 * e02, e02 * e10 - e00 * e12,
			e10 * e21 - e20 * e11, e01 * e20 - e00 * e21, e00 * e11 - e10 * e01
		);
	}

//}

//{ Lerp

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::Lerp(const Mat3& _start, const Mat3& _end, float _alpha) noexcept
	{
		SA_WARN(_alpha >= 0.0f && _alpha <= 1.0f, Maths, L"Alpha[" << _alpha << L"] clamped to range [0, 1]! Use LerpUnclamped if intended instead.");

		return LerpUnclamped(_start, _end, std::clamp(_alpha, 0.0f, 1.0f));
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::LerpUnclamped(const Mat3& _start, const Mat3& _end, float _alpha) noexcept
	{
		return Mat3(
			Maths::LerpUnclamped(_start.e00, _end.e00, _alpha),
			Maths::LerpUnclamped(_start.e01, _end.e01, _alpha),
			Maths::LerpUnclamped(_start.e02, _end.e02, _alpha),
			Maths::LerpUnclamped(_start.e10, _end.e10, _alpha),
			Maths::LerpUnclamped(_start.e11, _end.e11, _alpha),
			Maths::LerpUnclamped(_start.e12, _end.e12, _alpha),
			Maths::LerpUnclamped(_start.e20, _end.e20, _alpha),
			Maths::LerpUnclamped(_start.e21, _end.e21, _alpha),
			Maths::LerpUnclamped(_start.e22, _end.e22, _alpha)
		);
	}

//}

//{ Transform

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::MakeRotation(const Quat<T>& _rot) noexcept
	{
		SA_WARN(_rot.IsNormalized(), Maths, L"Quaternion should be normalized!");

		// Sources: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation

		const T XW2 = 2.0f * _rot.x * _rot.w;
		const T XX2 = 2.0f * _rot.x * _rot.x;
		const T XY2 = 2.0f * _rot.x * _rot.y;
		const T XZ2 = 2.0f * _rot.x * _rot.z;

		const T YW2 = 2.0f * _rot.y * _rot.w;
		const T YY2 = 2.0f * _rot.y * _rot.y;
		const T YZ2 = 2.0f * _rot.y * _rot.z;

		const T ZW2 = 2.0f * _rot.z * _rot.w;
		const T ZZ2 = 2.0f * _rot.z * _rot.z;

		return Mat3(
			1.0f - YY2 - ZZ2, XY2 - ZW2, XZ2 + YW2,
			XY2 + ZW2, 1.0f - XX2 - ZZ2, YZ2 - XW2,
			XZ2 - YW2, YZ2 + XW2, 1.0f - XX2 - YY2
		);
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::MakeScale(const Vec3<T>& _scale) noexcept
	{
		Mat3 result = Mat3::Identity;

		result.e00 = _scale.x;
		result.e11 = _scale.y;
		result.e22 = _scale.z;

		return result;
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major>  Mat3<T, major>::MakeTransform(const Quat<T>& _rot, const Vec3<T>& _scale) noexcept
	{
		return MakeRotation(_rot).ApplyScale(_scale);
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major>& Mat3<T, major>::ApplyScale(const Vec3<T>& _scale) noexcept
	{
		e00 *= _scale.x;
		e01 *= _scale.x;
		e02 *= _scale.x;

		e10 *= _scale.y;
		e11 *= _scale.y;
		e12 *= _scale.y;

		e20 *= _scale.z;
		e21 *= _scale.z;
		e22 *= _scale.z;

		return *this;
	}

//}

//{ Operators

	template <typename T, MatrixMajor major>
	constexpr Mat3<T, major> Mat3<T, major>::operator-() const noexcept
	{
		// Allows constexpr

		return Mat3(
			-e00, -e01, -e02,
			-e10, -e11, -e12,
			-e20, -e21, -e22
		);
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::operator*(T _scale) const noexcept
	{
		return Mat3(
			e00 * _scale, e01 * _scale, e02 * _scale,
			e10 * _scale, e11 * _scale, e12 * _scale,
			e20 * _scale, e21 * _scale, e22 * _scale
		);
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::operator/(T _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		return Mat3(
			e00 / _scale, e01 / _scale, e02 / _scale,
			e10 / _scale, e11 / _scale, e12 / _scale,
			e20 / _scale, e21 / _scale, e22 / _scale
		);
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::operator+(const Mat3& _rhs) const noexcept
	{
		return Mat3(
			e00 + _rhs.e00, e01 + _rhs.e01, e02 + _rhs.e02,
			e10 + _rhs.e10, e11 + _rhs.e11, e12 + _rhs.e12,
			e20 + _rhs.e20, e21 + _rhs.e21, e22 + _rhs.e22
		);
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::operator-(const Mat3& _rhs) const noexcept
	{
		return Mat3(
			e00 - _rhs.e00, e01 - _rhs.e01, e02 - _rhs.e02,
			e10 - _rhs.e10, e11 - _rhs.e11, e12 - _rhs.e12,
			e20 - _rhs.e20, e21 - _rhs.e21, e22 - _rhs.e22
		);
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::operator*(const Mat3& _rhs) const noexcept
	{
		return Mat3(
			e00 * _rhs.e00 + e01 * _rhs.e10 + e02 * _rhs.e20,
			e00 * _rhs.e01 + e01 * _rhs.e11 + e02 * _rhs.e21,
			e00 * _rhs.e02 + e01 * _rhs.e12 + e02 * _rhs.e22,

			e10 * _rhs.e00 + e11 * _rhs.e10 + e12 * _rhs.e20,
			e10 * _rhs.e01 + e11 * _rhs.e11 + e12 * _rhs.e21,
			e10 * _rhs.e02 + e11 * _rhs.e12 + e12 * _rhs.e22,

			e20 * _rhs.e00 + e21 * _rhs.e10 + e22 * _rhs.e20,
			e20 * _rhs.e01 + e21 * _rhs.e11 + e22 * _rhs.e21,
			e20 * _rhs.e02 + e21 * _rhs.e12 + e22 * _rhs.e22
		);
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major> Mat3<T, major>::operator/(const Mat3& _rhs) const noexcept
	{
		return *this * _rhs.GetInversed();
	}


	template <typename T, MatrixMajor major>
	Vec3<T> Mat3<T, major>::operator*(const Vec3<T>& _rhs) const noexcept
	{
		return Vec3(
			e00 * _rhs.x + e01 * _rhs.y + e02 * _rhs.z,
			e10 * _rhs.x + e11 * _rhs.y + e12 * _rhs.z,
			e20 * _rhs.x + e21 * _rhs.y + e22 * _rhs.z
		);
	}


	template <typename T, MatrixMajor major>
	Mat3<T, major>& Mat3<T, major>::operator*=(T _scale) noexcept
	{
		e00 *= _scale;
		e01 *= _scale;
		e02 *= _scale;

		e10 *= _scale;
		e11 *= _scale;
		e12 *= _scale;

		e20 *= _scale;
		e21 *= _scale;
		e22 *= _scale;

		return *this;
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major>& Mat3<T, major>::operator/=(T _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		e00 /= _scale;
		e01 /= _scale;
		e02 /= _scale;

		e10 /= _scale;
		e11 /= _scale;
		e12 /= _scale;

		e20 /= _scale;
		e21 /= _scale;
		e22 /= _scale;

		return *this;
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major>& Mat3<T, major>::operator+=(const Mat3& _rhs) noexcept
	{
		e00 += _rhs.e00;
		e01 += _rhs.e01;
		e02 += _rhs.e02;

		e10 += _rhs.e10;
		e11 += _rhs.e11;
		e12 += _rhs.e12;

		e20 += _rhs.e20;
		e21 += _rhs.e21;
		e22 += _rhs.e22;

		return *this;
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major>& Mat3<T, major>::operator-=(const Mat3& _rhs) noexcept
	{
		e00 -= _rhs.e00;
		e01 -= _rhs.e01;
		e02 -= _rhs.e02;

		e10 -= _rhs.e10;
		e11 -= _rhs.e11;
		e12 -= _rhs.e12;

		e20 -= _rhs.e20;
		e21 -= _rhs.e21;
		e22 -= _rhs.e22;

		return *this;
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major>& Mat3<T, major>::operator*=(const Mat3& _rhs) noexcept
	{
		return *this = *this * _rhs;
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major>& Mat3<T, major>::operator/=(const Mat3& _rhs) noexcept
	{
		return *this = *this / _rhs;
	}

//}


#if SA_LOGGING

	template <typename T, MatrixMajor major>
	std::string Mat3<T, major>::ToString() const noexcept
	{
		// Keep memory order (Raw / column major).
		const T* const data = Data();

		return
			Sa::ToString(data[0]) + ", " +
			Sa::ToString(data[1]) + ", " +
			Sa::ToString(data[2]) + ",\n " +

			Sa::ToString(data[3]) + ", " +
			Sa::ToString(data[4]) + ", " +
			Sa::ToString(data[5]) + ",\n " +

			Sa::ToString(data[6]) + ", " +
			Sa::ToString(data[7]) + ", " +
			Sa::ToString(data[8]);
	}

#endif


	template <typename T, MatrixMajor major>
	Mat3<T, major> operator*(typename std::remove_cv<T>::type _lhs, const Mat3<T, major>& _rhs) noexcept
	{
		return _rhs * _lhs;
	}

	template <typename T, MatrixMajor major>
	Mat3<T, major> operator/(typename std::remove_cv<T>::type _lhs, const Mat3<T, major>& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.e00), Maths, L"Inverse scale matrix e00 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e01), Maths, L"Inverse scale matrix e01 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e02), Maths, L"Inverse scale matrix e02 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e10), Maths, L"Inverse scale matrix e10 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e11), Maths, L"Inverse scale matrix e11 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e12), Maths, L"Inverse scale matrix e12 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e20), Maths, L"Inverse scale matrix e20 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e21), Maths, L"Inverse scale matrix e21 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e22), Maths, L"Inverse scale matrix e22 == 0!");


		return Mat3<T>(
			_lhs / _rhs.e00, _lhs / _rhs.e01, _lhs / _rhs.e02,
			_lhs / _rhs.e10, _lhs / _rhs.e11, _lhs / _rhs.e12,
			_lhs / _rhs.e20, _lhs / _rhs.e21, _lhs / _rhs.e22
		);
	}
}
