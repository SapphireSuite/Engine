// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename EnumT, typename BitsT>
	constexpr Flags<EnumT, BitsT>::Flags(EnumT _enum) noexcept : mBits{ static_cast<BitsT>(_enum) }
	{
	}

	template <typename EnumT, typename BitsT>
	constexpr Flags<EnumT, BitsT>::Flags(BitsT _bits) noexcept : mBits{ _bits }
	{
	}


	template <typename EnumT, typename BitsT>
	constexpr bool Flags<EnumT, BitsT>::Equals(BitsT _bits) const noexcept
	{
		return mBits == _bits;
	}


	template <typename EnumT, typename BitsT>
	constexpr bool Flags<EnumT, BitsT>::IsSet(EnumT _enum) const noexcept
	{
		return mBits & static_cast<BitsT>(_enum);
	}

	template <typename EnumT, typename BitsT>
	constexpr bool Flags<EnumT, BitsT>::AreSet(BitsT _bits) const noexcept
	{
		return (mBits & _bits) == _bits;
	}


	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>& Flags<EnumT, BitsT>::Add(EnumT _enum) noexcept
	{
		return Add(static_cast<BitsT>(_enum));
	}

	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>& Flags<EnumT, BitsT>::Add(BitsT _bits) noexcept
	{
		mBits |= _bits;

		return *this;
	}

	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>& Flags<EnumT, BitsT>::Remove(EnumT _enum) noexcept
	{
		return Remove(static_cast<BitsT>(_enum));
	}

	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>& Flags<EnumT, BitsT>::Remove(BitsT _bits) noexcept
	{
		mBits &= ~_bits;

		return *this;
	}


	template <typename EnumT, typename BitsT>
	constexpr Flags<EnumT, BitsT> Flags<EnumT, BitsT>::operator~() const noexcept
	{
		return Flags(~mBits);
	}

	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>& Flags<EnumT, BitsT>::operator|=(EnumT _rhs) noexcept
	{
		return *this |= static_cast<BitsT>(_rhs);
	}

	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>& Flags<EnumT, BitsT>::operator|=(BitsT _rhs) noexcept
	{
		mBits |= _rhs;

		return *this;
	}

	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>& Flags<EnumT, BitsT>::operator&=(EnumT _rhs) noexcept
	{
		return *this &= static_cast<BitsT>(_rhs);
	}

	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>& Flags<EnumT, BitsT>::operator&=(BitsT _rhs) noexcept
	{
		mBits &= _rhs;

		return *this;
	}

	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>& Flags<EnumT, BitsT>::operator^=(EnumT _rhs) noexcept
	{
		return *this ^= static_cast<BitsT>(_rhs);
	}

	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>& Flags<EnumT, BitsT>::operator^=(BitsT _rhs) noexcept
	{
		mBits ^= _rhs;

		return *this;
	}


	template <typename EnumT, typename BitsT>
	constexpr bool Flags<EnumT, BitsT>::operator==(EnumT _rhs) const noexcept
	{
		return *this == static_cast<BitsT>(_rhs);
	}

	template <typename EnumT, typename BitsT>
	constexpr bool Flags<EnumT, BitsT>::operator==(BitsT _rhs) const noexcept
	{
		return Equals(_rhs);
	}

	template <typename EnumT, typename BitsT>
	constexpr bool Flags<EnumT, BitsT>::operator!=(EnumT _rhs) const noexcept
	{
		return *this != static_cast<BitsT>(_rhs);
	}

	template <typename EnumT, typename BitsT>
	constexpr bool Flags<EnumT, BitsT>::operator!=(BitsT _rhs) const noexcept
	{
		return !Equals(_rhs);
	}


	template <typename EnumT, typename BitsT>
	Flags<EnumT, BitsT>::operator BitsT() const noexcept
	{
		return mBits;
	}


#if SA_LOGGING

	template <typename EnumT, typename BitsT>
	std::string Flags<EnumT, BitsT>::ToString() const noexcept
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
