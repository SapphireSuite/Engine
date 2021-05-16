// Copyright 2020 Sapphire development team.All Rights Reserved.

namespace Sa
{
	template <typename T>
	constexpr Deg<T>::Deg(T _deg) noexcept : mHandle{ _deg }
	{
	}
	
	template <typename T>
	template <typename TIn>
	constexpr Deg<T>::Deg(Deg<TIn> _other) noexcept : mHandle{ static_cast<T>(_other.operator TIn()) }
	{
	}

	template <typename T>
	template <typename TIn>
	constexpr Deg<T>::Deg(Rad<TIn> _rad) noexcept : mHandle{ static_cast<T>(_rad.operator TIn() * Maths::RadToDeg) }
	{
	}


	template <typename T>
	constexpr bool Deg<T>::Equals(Deg<T> _other, T _epsilon) const noexcept
	{
		return Sa::Equals(mHandle, _other.mHandle, _epsilon);
	}

	template <typename T>
	void Deg<T>::Clamp() noexcept
	{
		mHandle = std::fmod(mHandle, static_cast<T>(360));

		const T abs = std::abs(mHandle);

		if (abs > static_cast<T>(180))
			mHandle = (abs - static_cast<T>(360)) * Maths::Sign(mHandle);
	}


	template <typename T>
	Deg<T>& Deg<T>::operator+=(Deg _rhs) noexcept
	{
		mHandle += _rhs.mHandle;

		return *this;
	}

	template <typename T>
	Deg<T>& Deg<T>::operator-=(Deg _rhs) noexcept
	{
		mHandle -= _rhs.mHandle;

		return *this;
	}

	template <typename T>
	Deg<T>& Deg<T>::operator*=(T _scale) noexcept
	{
		mHandle *= _scale;

		return *this;
	}

	template <typename T>
	Deg<T>& Deg<T>::operator/=(T _scale)
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale Deg<" << typeid(T).name() << "> by 0 (division by 0).");

		mHandle /= _scale;

		return *this;
	}


	template <typename T>
	constexpr bool Deg<T>::operator==(Deg<T> _rhs) const noexcept
	{
		return Equals(_rhs);
	}

	template <typename T>
	constexpr bool Deg<T>::operator!=(Deg<T> _rhs) const noexcept
	{
		return !Equals(_rhs);
	}


	template <typename T>
	constexpr Deg<T>::operator T() const noexcept
	{
		return mHandle;
	}


#if SA_LOGGING

	template <typename T>
	std::string Deg<T>::ToString() const noexcept
	{
		return std::to_string(mHandle) + "_deg";
	}

#endif


	constexpr Degf operator""_deg(uint64 _lit) noexcept
	{
		return Degf(static_cast<float>(_lit));
	}

	constexpr Degf operator""_deg(long double _lit) noexcept
	{
		return Degf(static_cast<float>(_lit));
	}
}
