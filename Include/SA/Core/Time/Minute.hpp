// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_MINUTE_GUARD
#define SAPPHIRE_CORE_MINUTE_GUARD

#include <SA/Config.hpp>

#include <SA/Core/Types/Int.hpp>

/**
*	\file Minute.hpp
*
*	\brief \b Definition of Sapphire Engine \b Minute type.
*
*	\ingroup Core_Time
*	\{
*/


namespace Sa
{
	class Tick;
	class MilliSecond;
	class Second;
	class Hour;

	/**
	*	\brief \e Time-relative class which provide \b conversions with other \e time-relative classes.
	*/
	class Minute
	{
		/// Handled time.
		float mTime = 0.0f;

	public:
		/// Constant to convert Minutes to Ticks.
		static constexpr float ToTicks = 60000000.0f;

		/// Constant to convert Minutes to MilliSeconds.
		static constexpr float ToMilliSeconds = 60000.0f;

		/// Constant to convert Minutes to Seconds.
		static constexpr float ToSeconds = 60.0f;

		/// Constant to convert Minutes to Hours.
		static constexpr float ToHours = 1.0f / 60.0f;

		/// \b Default contructor.
		Minute() = default;

		/**
		*	\brief \e Value contructor without conversion.
		*
		*	\param[in] _time	Time minutes as \c float.
		*/
		SA_ENGINE_API Minute(float _time) noexcept;

		/**
		*	\brief \e Value contructor without conversion.
		*
		*	\param[in] _time	Time minutes as \c uint64.
		*/
		SA_ENGINE_API Minute(uint64 _time) noexcept;


		/**
		*	\brief Access the handled value.
		*
		*	\return minutes as \c float without conversion.
		*/
		SA_ENGINE_API operator float() const noexcept;

		/**
		*	\brief \e Cast operator to \c Tick with proper conversion.
		*
		*	\return \c Tick converted from \c Minute.
		*/
		SA_ENGINE_API operator Tick() const noexcept;

		/**
		*	\brief \e Cast operator to \c MilliSecond with proper conversion.
		*
		*	\return \c MilliSecond converted from \c Minute.
		*/
		SA_ENGINE_API operator MilliSecond() const noexcept;

		/**
		*	\brief \e Cast operator to \c Second with proper conversion.
		*
		*	\return \c Second converted from \c Minute.
		*/
		SA_ENGINE_API operator Second() const noexcept;

		/**
		*	\brief \e Cast operator to \c Hour with proper conversion.
		*
		*	\return \c Hour converted from \c Minute.
		*/
		SA_ENGINE_API operator Hour() const noexcept;
	};

	/**
	*	\brief _min \b literal operator.
	*
	*	\param[in] _lit		Operand to convert as Minute.
	*
	*	\return \c Minute without time-conversion.
	*/
	SA_ENGINE_API Minute operator""_min(uint64 _lit) noexcept;

	/**
	*	\brief _ms \b literal operator.
	*
	*	\param[in] _lit		Operand to convert as Minute.
	*
	*	\return \c Minute without time-conversion.
	*/
	SA_ENGINE_API Minute operator""_min(long double _lit) noexcept;
}


/** \} */

#endif // GUARD
