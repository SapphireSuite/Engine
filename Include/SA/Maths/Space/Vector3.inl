// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

namespace Sa
{
	template <typename T>
	const Vec3<T> Vec3<T>::Zero{ T(0), T(0), T(0) };

	template <typename T>
	const Vec3<T> Vec3<T>::One{ T(1), T(1), T(1) };

	template <typename T>
	const Vec3<T> Vec3<T>::Right{ T(1), T(0), T(0) };

	template <typename T>
	const Vec3<T> Vec3<T>::Left{ T(-1), T(0), T(0) };

	template <typename T>
	const Vec3<T> Vec3<T>::Up{ T(0), T(1), T(0) };

	template <typename T>
	const Vec3<T> Vec3<T>::Down{ T(0), T(-1), T(0) };

	template <typename T>
	const Vec3<T> Vec3<T>::Forward{ T(0), T(0), T(1) };

	template <typename T>
	const Vec3<T> Vec3<T>::Backward{ T(0), T(0), T(-1) };


	template <typename T>
	constexpr Vec3<T>::Vec3(T _x, T _y, T _z) noexcept :
		x{ _x },
		y{ _y },
		z{ _z }
	{
	}

	template <typename T>
	constexpr Vec3<T>::Vec3(T _scale) noexcept :
		x{ _scale },
		y{ _scale },
		z{ _scale }
	{
	}

	template <typename T>
	template <typename TIn>
	constexpr Vec3<T>::Vec3(const Vec3<TIn>& _other) noexcept :
		x{ static_cast<T>(_other.x) },
		y{ static_cast<T>(_other.y) },
		z{ static_cast<T>(_other.z) }
	{
	}

	template <typename T>
	template <typename TIn>
	constexpr Vec3<T>::Vec3(const Vec2<TIn>& _other, T _z) noexcept :
		x{ static_cast<T>(_other.x) },
		y{ static_cast<T>(_other.y) },
		z{ _z }
	{
	}

	template <typename T>
	template <typename TIn>
	constexpr Vec3<T>::Vec3(const Vec4<TIn>& _other) noexcept :
		x{ static_cast<T>(_other.x) },
		y{ static_cast<T>(_other.y) },
		z{ static_cast<T>(_other.z) }
	{
	}


	template <typename T>
	constexpr bool Vec3<T>::IsZero() const noexcept
	{
		return Sa::Equals0(x) && Sa::Equals0(y) && Sa::Equals0(z);
	}

	template <typename T>
	constexpr bool Vec3<T>::Equals(const Vec3& _other, T _epsilon) const noexcept
	{
		return Sa::Equals(x, _other.x, _epsilon) && Sa::Equals(y, _other.y, _epsilon) && Sa::Equals(z, _other.z, _epsilon);
	}

	template <typename T>
	constexpr T Vec3<T>::Length() const noexcept
	{
		return Maths::Sqrt(SqrLength());
	}

	template <typename T>
	constexpr T Vec3<T>::SqrLength() const noexcept
	{
		return x * x + y * y + z * z;
	}

	template <typename T>
	T* Vec3<T>::Data() noexcept
	{
		return &x;
	}

	template <typename T>
	const T* Vec3<T>::Data() const noexcept
	{
		return &x;
	}


	template <typename T>
	Vec3<T>& Vec3<T>::Normalize() noexcept
	{
		SA_WARN(!IsZero(), Maths, L"Normalize null vector!");

		const T norm = Length();

		x /= norm;
		y /= norm;
		z /= norm;

		return *this;
	}

	template <typename T>
	Vec3<T> Vec3<T>::GetNormalized() const noexcept
	{
		Vec3 res = *this;
		res.Normalize();

		return res;
	}

	template <typename T>
	constexpr bool Vec3<T>::IsNormalized() const noexcept
	{
		return Sa::Equals1(SqrLength());
	}

	template <typename T>
	Vec3<T> Vec3<T>::Reflect(const Vec3& _normal, float _elasticity) const noexcept
	{
		return *this - ProjectOnToNormal(_normal) * (1.0f + _elasticity);
	}

	template <typename T>
	Vec3<T> Vec3<T>::ProjectOnTo(const Vec3& _other) const noexcept
	{
		return Dot(*this, _other) / _other.SqrLength() * _other;
	}

	template <typename T>
	Vec3<T> Vec3<T>::ProjectOnToNormal(const Vec3& _normal) const noexcept
	{
		SA_WARN(_normal.IsNormalized(), Maths, L"Normal should be normalized or use ProjectOnTo() instead!");

		return Dot(*this, _normal) * _normal;
	}



	template <typename T>
	constexpr T Vec3<T>::Dot(const Vec3<T>& _lhs, const Vec3& _rhs) noexcept
	{
		return _lhs.x * _rhs.x +
			_lhs.y * _rhs.y +
			_lhs.z * _rhs.z;
	}

	template <typename T>
	constexpr Vec3<T> Vec3<T>::Cross(const Vec3<T>& _lhs, const Vec3& _rhs) noexcept
	{
		return Vec3(
			_lhs.y * _rhs.z - _lhs.z * _rhs.y,
			_lhs.z * _rhs.x - _lhs.x * _rhs.z,
			_lhs.x * _rhs.y - _lhs.y * _rhs.x
		);
	}

	template <typename T>
	Deg<T> Vec3<T>::Angle(const Vec3<T>& _start, const Vec3& _end, const Vec3& _normal) noexcept
	{
		T angle = static_cast<T>(AngleUnsigned(_start, _end));

		Vec3 cross = Cross(_start, _end);

		if (Dot(cross, _normal) < 0.0f)
			angle = -angle;

		return angle;
	}

	template <typename T>
	Deg<T> Vec3<T>::AngleUnsigned(const Vec3<T>& _start, const Vec3& _end) noexcept
	{
		return Maths::ACos(Dot(_start, _end));
	}

	template <typename T>
	constexpr T Vec3<T>::Dist(const Vec3& _start, const Vec3& _end) noexcept
	{
		return (_start - _end).Length();
	}

	template <typename T>
	constexpr T Vec3<T>::SqrDist(const Vec3& _start, const Vec3& _end) noexcept
	{
		return (_start - _end).SqrLength();
	}

	template <typename T>
	constexpr Vec3<T> Vec3<T>::Dir(const Vec3& _start, const Vec3& _end) noexcept
	{
		return _end - _start;
	}

	template <typename T>
	constexpr Vec3<T> Vec3<T>::DirN(const Vec3& _start, const Vec3& _end) noexcept
	{
		return Dir(_start, _end).GetNormalized();
	}

	template <typename T>
	Vec3<T> Vec3<T>::Lerp(const Vec3& _start, const Vec3& _end, float _alpha) noexcept
	{
		return Maths::Lerp(_start, _end, _alpha);
	}

	template <typename T>
	Vec3<T> Vec3<T>::LerpUnclamped(const Vec3& _start, const Vec3& _end, float _alpha) noexcept
	{
		return Maths::LerpUnclamped(_start, _end, _alpha);
	}

	template <typename T>
	Vec3<T> Vec3<T>::SLerp(const Vec3& _start, const Vec3& _end, float _alpha) noexcept
	{
		return Maths::SLerp(_start, _end, _alpha);
	}

	template <typename T>
	Vec3<T> Vec3<T>::SLerpUnclamped(const Vec3& _start, const Vec3& _end, float _alpha) noexcept
	{
		return Maths::SLerpUnclamped(_start, _end, _alpha);
	}


	template <typename T>
	constexpr Vec3<T> Vec3<T>::operator-() const noexcept
	{
		return Vec3(-x, -y, -z);
	}

	template <typename T>
	Vec3<T> Vec3<T>::operator*(T _scale) const noexcept
	{
		return Vec3(
			x * _scale,
			y * _scale,
			z * _scale
		);
	}

	template <typename T>
	Vec3<T> Vec3<T>::operator/(T _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale vector by 0 (division by 0).");

		return Vec3(
			x / _scale,
			y / _scale,
			z / _scale
		);
	}

	template <typename T>
	constexpr  Vec3<T> Vec3<T>::operator+(const Vec3& _rhs) const noexcept
	{
		return Vec3(
			x + _rhs.x,
			y + _rhs.y,
			z + _rhs.z
		);
	}

	template <typename T>
	constexpr  Vec3<T> Vec3<T>::operator-(const Vec3& _rhs) const noexcept
	{
		return Vec3(
			x - _rhs.x,
			y - _rhs.y,
			z - _rhs.z
		);
	}

	template <typename T>
	constexpr  Vec3<T> Vec3<T>::operator*(const Vec3& _rhs) const noexcept
	{
		return Vec3(
			x * _rhs.x,
			y * _rhs.y,
			z * _rhs.z
		);
	}

	template <typename T>
	constexpr  Vec3<T> Vec3<T>::operator/(const Vec3& _rhs) const noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.x), Maths, L"Divide X Axis value by 0!");
		SA_WARN(!Sa::Equals0(_rhs.y), Maths, L"Divide Y Axis value by 0!");
		SA_WARN(!Sa::Equals0(_rhs.z), Maths, L"Divide Z Axis value by 0!");

		return Vec3(
			x / _rhs.x,
			y / _rhs.y,
			z / _rhs.z
		);
	}

	template <typename T>
	constexpr T Vec3<T>::operator|(const Vec3& _rhs) const noexcept
	{
		return Dot(*this, _rhs);
	}

	template <typename T>
	constexpr Vec3<T> Vec3<T>::operator^(const Vec3& _rhs) const noexcept
	{
		return Cross(*this, _rhs);
	}


	template <typename T>
	Vec3<T>& Vec3<T>::operator*=(T _scale) noexcept
	{
		x *= _scale;
		y *= _scale;
		z *= _scale;

		return *this;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator/=(T _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale vector by 0 (division by 0).");

		x /= _scale;
		y /= _scale;
		z /= _scale;

		return *this;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator+=(const Vec3& _rhs) noexcept
	{
		x += _rhs.x;
		y += _rhs.y;
		z += _rhs.z;

		return *this;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator-=(const Vec3& _rhs) noexcept
	{
		x -= _rhs.x;
		y -= _rhs.y;
		z -= _rhs.z;

		return *this;
	}

	template <typename T>
	Vec3<T> Vec3<T>::operator*=(const Vec3& _rhs) noexcept
	{
		x *= _rhs.x;
		y *= _rhs.y;
		z *= _rhs.z;

		return *this;
	}

	template <typename T>
	Vec3<T> Vec3<T>::operator/=(const Vec3& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.x), Maths, L"Divide X Axis value by 0!");
		SA_WARN(!Sa::Equals0(_rhs.y), Maths, L"Divide Y Axis value by 0!");
		SA_WARN(!Sa::Equals0(_rhs.z), Maths, L"Divide Z Axis value by 0!");

		x /= _rhs.x;
		y /= _rhs.y;
		z /= _rhs.z;

		return *this;
	}


	template <typename T>
	constexpr bool Vec3<T>::operator==(const Vec3& _rhs) const noexcept
	{
		return Equals(_rhs);
	}

	template <typename T>
	constexpr bool Vec3<T>::operator!=(const Vec3& _rhs) const noexcept
	{
		return !(*this == _rhs);
	}


	template <typename T>
	T& Vec3<T>::operator[](uint32 _index)
	{
		SA_ASSERT(OutOfRange, Maths, _index, 0u, 2u);

		return Data()[_index];
	}

	template <typename T>
	const T& Vec3<T>::operator[](uint32 _index) const
	{
		SA_ASSERT(OutOfRange, Maths, _index, 0u, 2u);

		return Data()[_index];
	}


#if SA_LOGGING

	template <typename T>
	std::string Vec3<T>::ToString() const noexcept
	{
		return "X: " + Sa::ToString(x) +
			"\tY: " + Sa::ToString(y) +
			"\tZ: " + Sa::ToString(z);
	}

#endif


	template <typename T>
	constexpr Vec3<T> operator*(typename std::remove_cv<T>::type _lhs, const Vec3<T>& _rhs) noexcept
	{
		return _rhs * _lhs;
	}

	template <typename T>
	constexpr Vec3<T> operator/(typename std::remove_cv<T>::type _lhs, const Vec3<T>& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.x), Maths, L"Inverse scale X Axis by 0 (division by 0).");
		SA_WARN(!Sa::Equals0(_rhs.y), Maths, L"Inverse scale Y Axis by 0 (division by 0).");
		SA_WARN(!Sa::Equals0(_rhs.z), Maths, L"Inverse scale Z Axis by 0 (division by 0).");

		return Vec3<T>(_lhs / _rhs.x, _lhs / _rhs.y, _lhs / _rhs.z);
	}
}
