// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_TIME_GUARD
#define SAPPHIRE_CORE_TIME_GUARD

#include <SA/Core/Time/Tick.hpp>
#include <SA/Core/Time/Second.hpp>
#include <SA/Core/Time/DateTime.hpp>

/**
*	\file Time.hpp
*
*	\brief \b Definition of Sapphire Engine \b Time static accessors.
*
*	\ingroup Core_Time
*	\{
*/


namespace Sa
{
	/**
	*	\brief Static class which provide <b>time service</b> access.
	*/
	class Time
	{
	public:
		/// \b Deleted destructor.
		~Time() = delete;

		/**
		*	\brief Get the time in \c seconds since the beginning of the program.
		*
		*	\return time in seconds.
		*/
		SA_ENGINE_API static Second Now();

		/**
		*	\brief Get the time in \c ticks since the beginning of the program.
		*
		*	\return time in ticks.
		*/
		SA_ENGINE_API static Tick Ticks();

		/**
		*	\brief Get the current local date time.
		*
		*	\return time in seconds.
		*/
		SA_ENGINE_API static DateTime Date() noexcept;

		/**
		*	\brief Get the current date time at Greenwich.
		*
		*	\return time in seconds.
		*/
		SA_ENGINE_API static DateTime GMDate() noexcept;

		/**
		*	\brief Generate a \b seed based on the time.
		*
		*	Return the time since the Epoch (00:00:00 UTC, January 1st, 1970).
		*	This value is usually used for seed generation.
		*
		*	\return Seed based on time.
		*/
		SA_ENGINE_API static uint64 Seed() noexcept;

		/**
		*	\brief Sleep the program for an amount of time (in millisecond).
		*
		*	\param[in] _ms		Amount of time to sleep in millisecond.
		*/
		SA_ENGINE_API static void Sleep(MilliSecond _ms) noexcept;
	};


	/** \} */
}

#endif // GUARD
