// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_FLAGS_GUARD
#define SAPPHIRE_CORE_FLAGS_GUARD

#include <SA/Core/Types/Int.hpp>

/**
*	\file Flags.hpp
*
*	\brief \b Definition of Sapphire Engine \b Flags type.
*
*	\ingroup Core_Types
*	\{
*/

namespace Sa
{
	/**
	*	\brief \e Template class for \b bit-flags enum management.
	*
	*	\tparam EnumT		EnumT type.
	*	\tparam BitsT		Bits type.
	*/
	template <typename EnumT, typename BitsT = UIntOfSize<sizeof(EnumT)>>
	class Flags
	{
		/// bit-flags value.
		BitsT mBits = 0;

	public:
		/// \b Default constructor.
		Flags() = default;

		/**
		*	\brief <b>EnumT value</b> constructor.
		*
		*	\param[in] _enum	Enum value to assign to the handle.
		*/
		constexpr Flags(EnumT _enum) noexcept;

		/**
		*	\brief <b>Bits value</b> constructor.
		*
		*	\param[in] _bits	Bits value to assign to the handle.
		*/
		constexpr Flags(BitsT _bits) noexcept;


		/**
		*	\brief Perform \b equal operation between bit flags and enum.
		*
		*	\param[in] _enum		Right operand.
		*
		*	\return result of equal operation.
		*/
		constexpr bool Equals(EnumT _enum) const noexcept;

		/**
		*	\brief Perform \b equal operation between Flags and type bits.
		*
		*	\param[in] _bits		Right operand.
		*
		*	\return result of equal operation.
		*/
		constexpr bool Equals(BitsT _bits) const noexcept;


		/**
		*	\brief \e Getter of bool if the <b>enum value</b> is currently set.
		*
		*	\param[in] _enum	Enum value to check with.
		*
		*	\return true if enum value is set, otherwise false.
		*/
		constexpr bool IsSet(EnumT _enum) const noexcept;

		/**
		*	\brief \e Getter of bool if <b>all bit values</b> are currently set.
		*
		*	\param[in] _bits	Bit values to check with.
		*
		*	\return true if bit values are set, otherwise false.
		*/
		constexpr bool AreSet(BitsT _bits) const noexcept;


		/**
		*	\brief Add enum value to the current bit flags.
		*
		*	\param[in] _enum	Enum value to add.
		* 
		*	\return this.
		*/
		Flags& Add(EnumT _enum) noexcept;

		/**
		*	\brief Add bits value to the current bit flags.
		*
		*	\param[in] _bits	Bits value to add.
		* 
		*	\return this.
		*/
		Flags& Add(BitsT _bits) noexcept;
		
		/**
		*	\brief Remove enum value to the current bit flags.
		*
		*	\param[in] _enum	Enum value to remove.
		* 
		*	\return this.
		*/
		Flags& Remove(EnumT _enum) noexcept;

		/**
		*	\brief Remove bits value to the current bit flags.
		*
		*	\param[in] _bits	Bits value to remove.
		* 
		*	\return this.
		*/
		Flags& Remove(BitsT _bits) noexcept;


		/**
		*	\brief Perform operator \b not on current bit flags.
		*
		*	\return result of not operation.
		*/
		constexpr Flags operator~() const noexcept;


		/**
		*	\brief Perform \b OR and \b assign operations with EnumT.
		*
		*	\param[in] _rhs		Right operand.
		*
		*	\return this instance.
		*/
		Flags& operator|=(EnumT _rhs) noexcept;

		/**
		*	\brief Perform \b OR and \b assign operations with BitsT.
		*
		*	\param[in] _rhs		Right operand.
		*
		*	\return this instance.
		*/
		Flags& operator|=(BitsT _rhs) noexcept;

		/**
		*	\brief Perform \b AND and \b assign operations with EnumT.
		*
		*	\param[in] _rhs		Right operand.
		*
		*	\return this instance.
		*/
		Flags& operator&=(EnumT _rhs) noexcept;

		/**
		*	\brief Perform \b AND and \b assign operations with BitsT.
		*
		*	\param[in] _rhs		Right operand.
		*
		*	\return this instance.
		*/
		Flags& operator&=(BitsT _rhs) noexcept;

		/**
		*	\brief Perform \b XOR and \b assign operations with EnumT.
		*
		*	\param[in] _rhs		Right operand.
		*
		*	\return this instance.
		*/
		Flags& operator^=(EnumT _rhs) noexcept;

		/**
		*	\brief Perform \b XOR and \b assign operations with BitsT.
		*
		*	\param[in] _rhs		Right operand.
		*
		*	\return this instance.
		*/
		Flags& operator^=(BitsT _rhs) noexcept;


		/**
		*	\brief Perform \b equal operation between bit flags and enum.
		*
		*	\param[in] _rhs		Right operand.
		*
		*	\return result of equal operation.
		*/
		constexpr bool operator==(EnumT _rhs) const noexcept;

		/**
		*	\brief Perform \b equal operation between Flags and type bits.
		*
		*	\param[in] _rhs		Right operand.
		*
		*	\return result of equal operation.
		*/
		constexpr bool operator==(BitsT _rhs) const noexcept;

		/**
		*	\brief Perform <b>not equal</b> operation between bit flags and enum.
		*
		*	\param[in] _rhs		Right operand.
		*
		*	\return result of not equal operation.
		*/
		constexpr bool operator!=(EnumT _rhs) const noexcept;

		/**
		*	\brief Perform <b>not equal</b> operation between Flags and type bits.
		*
		*	\param[in] _rhs		Right operand.
		*
		*	\return result of not equal operation.
		*/
		constexpr bool operator!=(BitsT _rhs) const noexcept;


		/**
		*	\brief \e Cast operator to BitsT to get bit flags.
		*
		*	\return bit flags.
		*/
		operator BitsT() const noexcept;
	};


	/**
	*	\brief Define flag operators for enum type.
	* 
	*	\param[in] _enumType	Type of enum.
	*/
	#define SA_DEFINE_ENUM_FLAGS(_enumType)\
	inline Sa::UIntOfSize<sizeof(_enumType)> operator|(_enumType _lhs, _enumType _rhs) noexcept\
	{\
		return static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_lhs) | static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_rhs);\
	}\
	\
	inline Sa::UIntOfSize<sizeof(_enumType)> operator|(Sa::UIntOfSize<sizeof(_enumType)> _lhs, _enumType _rhs) noexcept\
	{\
		return _lhs | static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_rhs);\
	}\
	\
	inline Sa::UIntOfSize<sizeof(_enumType)>& operator|=(Sa::UIntOfSize<sizeof(_enumType)>& _lhs, _enumType _rhs) noexcept\
	{\
		return _lhs |= static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_rhs);\
	}\
	\
	\
	inline Sa::UIntOfSize<sizeof(_enumType)> operator&(_enumType _lhs, _enumType _rhs) noexcept\
	{\
		return static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_lhs) & static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_rhs);\
	}\
	\
	inline Sa::UIntOfSize<sizeof(_enumType)> operator&(Sa::UIntOfSize<sizeof(_enumType)> _lhs, _enumType _rhs) noexcept\
	{\
		return _lhs & static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_rhs);\
	}\
	\
	inline Sa::UIntOfSize<sizeof(_enumType)>& operator&=(Sa::UIntOfSize<sizeof(_enumType)>& _lhs, _enumType _rhs) noexcept\
	{\
		return _lhs &= static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_rhs);\
	}\
	\
	\
	inline Sa::UIntOfSize<sizeof(_enumType)> operator^(_enumType _lhs, _enumType _rhs) noexcept\
	{\
		return static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_lhs) ^ static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_rhs);\
	}\
	\
	inline Sa::UIntOfSize<sizeof(_enumType)> operator^(Sa::UIntOfSize<sizeof(_enumType)> _lhs, _enumType _rhs) noexcept\
	{\
		return _lhs ^ static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_rhs);\
	}\
	\
	inline Sa::UIntOfSize<sizeof(_enumType)>& operator^=(Sa::UIntOfSize<sizeof(_enumType)>& _lhs, _enumType _rhs) noexcept\
	{\
		return _lhs ^= static_cast<Sa::UIntOfSize<sizeof(_enumType)>>(_rhs);\
	}\
	\
	\
	inline Sa::UIntOfSize<sizeof(_enumType)> operator~(_enumType _enum) noexcept\
	{\
		return ~static_cast<uint8>(_enum);\
	}
}


/** \} */

#include <SA/Core/Types/Variadics/Flags.inl>

#endif // GUARD
