// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename EnumT, typename IntlBitsT>
	constexpr Flags<EnumT, IntlBitsT>::Flags(EnumT _enum) noexcept : mBits{ static_cast<BitsT>(_enum) }
	{
	}

	template <typename EnumT, typename IntlBitsT>
	constexpr Flags<EnumT, IntlBitsT>::Flags(BitsT _bits) noexcept : mBits{ _bits }
	{
	}


	template <typename EnumT, typename IntlBitsT>
	constexpr bool Flags<EnumT, IntlBitsT>::Equals(BitsT _bits) const noexcept
	{
		return mBits == _bits;
	}


	template <typename EnumT, typename IntlBitsT>
	constexpr bool Flags<EnumT, IntlBitsT>::IsSet(EnumT _enum) const noexcept
	{
		return mBits & static_cast<BitsT>(_enum);
	}

	template <typename EnumT, typename IntlBitsT>
	constexpr bool Flags<EnumT, IntlBitsT>::AreSet(BitsT _bits) const noexcept
	{
		return (mBits & _bits) == _bits;
	}


	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>& Flags<EnumT, IntlBitsT>::Add(EnumT _enum) noexcept
	{
		return Add(static_cast<BitsT>(_enum));
	}

	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>& Flags<EnumT, IntlBitsT>::Add(BitsT _bits) noexcept
	{
		mBits |= _bits;

		return *this;
	}

	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>& Flags<EnumT, IntlBitsT>::Remove(EnumT _enum) noexcept
	{
		return Remove(static_cast<BitsT>(_enum));
	}

	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>& Flags<EnumT, IntlBitsT>::Remove(BitsT _bits) noexcept
	{
		mBits &= ~_bits;

		return *this;
	}


	template <typename EnumT, typename IntlBitsT>
	constexpr Flags<EnumT, IntlBitsT> Flags<EnumT, IntlBitsT>::operator~() const noexcept
	{
		return Flags(~mBits);
	}

	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>& Flags<EnumT, IntlBitsT>::operator|=(EnumT _rhs) noexcept
	{
		return *this |= static_cast<BitsT>(_rhs);
	}

	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>& Flags<EnumT, IntlBitsT>::operator|=(BitsT _rhs) noexcept
	{
		mBits |= _rhs;

		return *this;
	}

	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>& Flags<EnumT, IntlBitsT>::operator&=(EnumT _rhs) noexcept
	{
		return *this &= static_cast<BitsT>(_rhs);
	}

	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>& Flags<EnumT, IntlBitsT>::operator&=(BitsT _rhs) noexcept
	{
		mBits &= _rhs;

		return *this;
	}

	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>& Flags<EnumT, IntlBitsT>::operator^=(EnumT _rhs) noexcept
	{
		return *this ^= static_cast<BitsT>(_rhs);
	}

	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>& Flags<EnumT, IntlBitsT>::operator^=(BitsT _rhs) noexcept
	{
		mBits ^= _rhs;

		return *this;
	}


	template <typename EnumT, typename IntlBitsT>
	constexpr bool Flags<EnumT, IntlBitsT>::operator==(EnumT _rhs) const noexcept
	{
		return *this == static_cast<BitsT>(_rhs);
	}

	template <typename EnumT, typename IntlBitsT>
	constexpr bool Flags<EnumT, IntlBitsT>::operator==(BitsT _rhs) const noexcept
	{
		return Equals(_rhs);
	}

	template <typename EnumT, typename IntlBitsT>
	constexpr bool Flags<EnumT, IntlBitsT>::operator!=(EnumT _rhs) const noexcept
	{
		return *this != static_cast<BitsT>(_rhs);
	}

	template <typename EnumT, typename IntlBitsT>
	constexpr bool Flags<EnumT, IntlBitsT>::operator!=(BitsT _rhs) const noexcept
	{
		return !Equals(_rhs);
	}


	template <typename EnumT, typename IntlBitsT>
	Flags<EnumT, IntlBitsT>::operator BitsT() const noexcept
	{
		return mBits;
	}


#if SA_LOGGING

	template <typename EnumT, typename IntlBitsT>
	std::string Flags<EnumT, IntlBitsT>::ToString() const noexcept
	{
		std::string binaryStr;
		const uint32 bitCount = sizeof(EnumT) * 8;

		for (uint32 i = 1u; i <= bitCount; ++i)
		{
			// Parse bits
			if (mBits & (1 << (bitCount - i)))
				binaryStr.append("1");
			else
				binaryStr.append("0");

			// Add spaces every 4 bits (and not at the end.)
			if(i % 4 == 0 && i != bitCount)
				binaryStr.append(" ");
		}

		return std::to_string(mBits) + " {" + binaryStr + '}';
	}
#endif
}
