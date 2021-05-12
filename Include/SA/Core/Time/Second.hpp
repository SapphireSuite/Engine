// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_SECOND_GUARD
#define SAPPHIRE_CORE_SECOND_GUARD

#include <string>

#include <SA/Config.hpp>

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Debug/Config.hpp>

/**
*	\file Second.hpp
*
*	\brief \b Definition of Sapphire Engine \b Second type.
*
*	\ingroup Core_Time
*	\{
*/


namespace Sa
{
	class Tick;
	class MilliSecond;
	class Minute;
	class Hour;

	/**
	*	\brief \e Time-relative class which provide \b conversions with other \e time-relative classes.
	*/
	class Second
	{
		/// Handled time.
		float mTime = 0.0f;

	public:
		/// Constant to convert Seconds to Ticks.
		static constexpr float ToTicks = 1000000.0f;

		/// Constant to convert Seconds to MilliSeconds.
		static constexpr float ToMilliSeconds = 1000.0f;

		/// Constant to convert Seconds to Minutes.
		static constexpr float ToMinutes = 1.0f / 60.0f;

		/// Constant to convert Seconds to Hours.
		static constexpr float ToHours = 1.0f / 3600.0f;

		/// \b Default contructor.
		Second() = default;
		
		/**
		*	\brief \e Value contructor without conversion.
		*
		*	\param[in] _time	Time seconds as \c float.
		*/
		SA_ENGINE_API Second(float _time) noexcept;

		/**
		*	\brief \e Value contructor without conversion.
		*
		*	\param[in] _time	Time seconds as \c uint64.
		*/
		SA_ENGINE_API Second(uint64 _time) noexcept;


		/**
		*	\brief Access the handled value.
		*
		*	\return seconds as \c float without conversion.
		*/
		SA_ENGINE_API operator float() const noexcept;

		/**
		*	\brief \e Cast operator to \c Tick with proper conversion.
		*
		*	\return \c Tick converted from \c Second.
		*/
		SA_ENGINE_API operator Tick() const noexcept;

		/**
		*	\brief \e Cast operator to \c MilliSecond with proper conversion.
		*
		*	\return \c MilliSecond converted from \c Second.
		*/
		SA_ENGINE_API operator MilliSecond() const noexcept;

		/**
		*	\brief \e Cast operator to \c Minute with proper conversion.
		*
		*	\return \c Minute converted from \c Second.
		*/
		SA_ENGINE_API operator Minute() const noexcept;

		/**
		*	\brief \e Cast operator to \c Hour with proper conversion.
		*
		*	\return \c Hour converted from \c Second.
		*/
		SA_ENGINE_API operator Hour() const noexcept;


#if SA_LOGGING

		/// Convert ToString.
		SA_ENGINE_API std::string ToString() const noexcept;
#endif
	};

	/**
	*	\brief _sec \b literal operator.
	*
	*	\param[in] _lit		Operand to convert as Second.
	*
	*	\return \c Second without time-conversion.
	*/
	SA_ENGINE_API Second operator""_sec(uint64 _lit) noexcept;

	/**
	*	\brief _sec \b literal operator.
	*
	*	\param[in] _lit		Operand to convert as Second.
	*
	*	\return \c Second without time-conversion.
	*/
	SA_ENGINE_API Second operator""_sec(long double _lit) noexcept;
}


/** \} */

#endif // GUARD
