// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_COUNTER_GUARD
#define SAPPHIRE_UTH_COUNTER_GUARD

#include <UTH/StringToken.hpp>

/**
*	\file Counter.hpp
* 
*	\brief Test counter implementation.
* 
*	\ingroup UTH
*	\{
*/

namespace Sa::UTH
{
	/// UTH test counter class.
	struct Counter
	{
		/// Counter of success.
		uint32 success = 0;

		/// Counter of failure.
		uint32 failure = 0;

		/**
		*	\brief Total test count (success + failure).
		* 
		*	\return Total count.
		*/
		uint32 Total() const;

		/**
		*	\brief Increment counter from predicate (either success or failure).
		* 
		*	\param[in] _pred	Predicate used for success or failure increment.
		*/
		void Increment(bool _pred);

		/**
		*	\return Whether this counter is empty.
		*/
		bool IsEmpty() const;

		/**
		*	\brief Append this counter as a StringToken.
		* 
		*	\param[out] _str	String token to append at.
		*/
		void AppendStr(StringToken& _str) const;

		/**
		*	\brief Increment this counter by _rhs.
		* 
		*	\param[in] _rhs		Counter used for incrementation.
		* 
		*	\return this counter.
		*/
		Counter& operator+=(const Counter& _rhs) noexcept;
	};
}


/** \} */

#endif // GUARD
