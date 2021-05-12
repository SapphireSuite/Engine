// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_HOUR_GUARD
#define SAPPHIRE_CORE_HOUR_GUARD

#include <string>

#include <SA/Config.hpp>

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Debug/Config.hpp>

/**
*	\file Hour.hpp
*
*	\brief \b Definition of Sapphire Engine \b Hour type.
*
*	\ingroup Core_Time
*	\{
*/


namespace Sa
{
	class Tick;
	class MilliSecond;
	class Second;
	class Minute;

	/**
	*	\brief \e Time-relative class which provide \b conversions with other \e time-relative classes.
	*/
	class Hour
	{
		/// Handled time.
		float mTime = 0.0f;

	public:
		/// Constant to convert Hours to Ticks.
		static constexpr float ToTicks = 3600000000.0f;

		/// Constant to convert Hours to MilliSeconds.
		static constexpr float ToMilliSeconds = 3600000.0f;

		/// Constant to convert Hours to Seconds.
		static constexpr float ToSeconds = 3600.0f;

		/// Constant to convert Hours to Minutes.
		static constexpr float ToMinutes = 60.0f;

		/// \b Default contructor.
		Hour() = default;

		/**
		*	\brief \e Value contructor without conversion.
		*
		*	\param[in] _time	Time hours as \c float.
		*/
		SA_ENGINE_API Hour(float _time) noexcept;

		/**
		*	\brief \e Value contructor without conversion.
		*
		*	\param[in] _time	Time hours as \c float.
		*/
		SA_ENGINE_API Hour(uint64 _time) noexcept;


		/**
		*	\brief Access the handled value.
		*
		*	\return hours as \c float without conversion.
		*/
		SA_ENGINE_API operator float() const noexcept;

		/**
		*	\brief \e Cast operator to \c Tick with proper conversion.
		*
		*	\return \c Tick converted from \c Hour.
		*/
		SA_ENGINE_API operator Tick() const noexcept;

		/**
		*	\brief \e Cast operator to \c MilliSecond with proper conversion.
		*
		*	\return \c MilliSecond converted from \c Hour.
		*/
		SA_ENGINE_API operator MilliSecond() const noexcept;

		/**
		*	\brief \e Cast operator to \c Second with proper conversion.
		*
		*	\return \c Second converted from \c Hour.
		*/
		SA_ENGINE_API operator Second() const noexcept;

		/**
		*	\brief \e Cast operator to \c Minute with proper conversion.
		*
		*	\return \c Minute converted from \c Hour.
		*/
		SA_ENGINE_API operator Minute() const noexcept;


#if SA_LOGGING

		/// Convert ToString.
		SA_ENGINE_API std::string ToString() const noexcept;
#endif
	};

	/**
	*	\brief _hr \b literal operator.
	*
	*	\param[in] _lit		Operand to convert as Hour.
	*
	*	\return \c Hour without time-conversion.
	*/
	SA_ENGINE_API Hour operator""_hr(uint64 _lit) noexcept;

	/**
	*	\brief _hr \b literal operator.
	*
	*	\param[in] _lit		Operand to convert as Hour.
	*
	*	\return \c Hour without time-conversion.
	*/
	SA_ENGINE_API Hour operator""_hr(long double _lit) noexcept;
}


	/** \} */

#endif // GUARD
