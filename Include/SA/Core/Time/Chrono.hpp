// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_CHRONO_GUARD
#define SAPPHIRE_CORE_CHRONO_GUARD

#include <SA/Core/Time/Tick.hpp>

/**
*	\file Chrono.hpp
*
*	\brief \b Definition of Sapphire Engine \b Chrono type.
*
*	\ingroup Core_Time
*	\{
*/


namespace Sa
{
	/**
	*	\brief Chronometer class to measure a <b>period of time</b>.
	*/
	class Chrono
	{
		/// Handled start time.
		Tick mStart;

	public:

		/// \b Start the chronometer.
		void Start() noexcept;

		/**
		*	\brief \b End the chronometer.
		*
		*	\return The mesured time since the \b Start() call.
		*/
		Tick End() noexcept;

		/**
		*	\brief \b End the chronometer and instantly call \b Start() again.
		*
		*	\return The mesured time since the previous \b Start() call.
		*/
		Tick Restart() noexcept;
	};
}


/** \} */

#endif // GUARD
