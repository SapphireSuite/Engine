// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_TICK_GUARD
#define SAPPHIRE_CORE_TICK_GUARD

#include <string>

#include <SA/Config.hpp>

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Debug/Config.hpp>

/**
*	\file Tick.hpp
*
*	\brief \b Definition of Sapphire Engine \b Tick type.
*
*	\ingroup Core_Time
*	\{
*/


namespace Sa
{
	class MilliSecond;
	class Second;
	class Minute;
	class Hour;

	/**
	*	\brief \e Time-relative class that provide \b conversions with other \e time-relative classes.
	*
	*	1 Tick is 1 MicroSecond (1e-6 second).
	*/
	class Tick
	{
		/// Handled time.
		float mTime = 0.0f;

	public:
		/// Constant to convert Ticks to MilliSeconds.
		static constexpr float ToMilliSeconds = 1.0f / 1000.0f;

		/// Constant to convert Ticks to Seconds.
		static constexpr float ToSeconds = 1.0f / 1000000.0f;

		/// Constant to convert Ticks to Minutes.
		static constexpr float ToMinutes = 1.0f / 60000000.0f;

		/// Constant to convert Ticks to Hours.
		static constexpr float ToHours = 1.0f / 3600000000.0f;

		/// \b Default contructor.
		Tick() = default;

		/**
		*	\brief \e Value contructor without conversion.
		*
		*	\param[in] _time	Time ticks as \c float.
		*/
		Tick(float _time) noexcept;

		/**
		*	\brief \e Value contructor without conversion.
		*
		*	\param[in] _time	Time ticks as \c uint64.
		*/
		Tick(uint64 _time) noexcept;


		/**
		*	\brief Access the handled value.
		*
		*	\return ticks as \c float without conversion.
		*/
		operator float() const noexcept;
		
		/**
		*	\brief \e Cast operator to \c MilliSecond with proper conversion.
		*
		*	\return \c MilliSecond converted from \c Tick.
		*/
		operator MilliSecond() const noexcept;

		/**
		*	\brief \e Cast operator to \c Second with proper conversion.
		*
		*	\return \c Second converted from \c Tick.
		*/
		operator Second() const noexcept;

		/**
		*	\brief \e Cast operator to \c Minute with proper conversion.
		*
		*	\return \c Minute converted from \c Tick.
		*/
		operator Minute() const noexcept;

		/**
		*	\brief \e Cast operator to \c Hour with proper conversion.
		*
		*	\return \c Hour converted from \c Tick.
		*/
		operator Hour() const noexcept;


#if SA_LOGGING

		/**
		*	\brief ToString implementation
		*
		*	Convert this tick as a string.
		*
		*	\return this as a string.
		*/
		std::string ToString() const noexcept;
#endif
	};

	/**
	*	\brief _tk \b literal operator.
	*
	*	\param[in] _lit		Operand to convert as Tick.
	*
	*	\return \c Tick without time-conversion.
	*/
	Tick operator""_tk(uint64 _lit) noexcept;

	/**
	*	\brief _sec \b literal operator.
	*
	*	\param[in] _lit		Operand to convert as Tick.
	*
	*	\return \c Tick without time-conversion.
	*/
	Tick operator""_tk(long double _lit) noexcept;
}


/** \} */

#endif // GUARD
