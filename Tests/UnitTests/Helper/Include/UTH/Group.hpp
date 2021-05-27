// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_GROUP_GUARD
#define SAPPHIRE_UTH_GROUP_GUARD

#include <string>

#include <UTH/Counter.hpp>

/**
*	\file Group.hpp
* 
*	\brief UTH Group test implementation.
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
//{ Group

	/// Infos generated from a group of tests.
	class Group
	{
	public:
		/// Name of the group.
		std::wstring name;

		/**
		*	\brief Local exit from tests of the group.
		*
		*	UTH::localExit will be equal to EXIT_FAILURE (1) if at least one test of the group failed.
		*
		*	localExit 0 == success.
		*	localExit 1 == failure.
		*/
		bool localExit = EXIT_SUCCESS;

		/// Counter of test run in this group.
		Counter count{};

		/**
		*	\brief Update group from predicate
		* 
		*	\param[in] _pred	Predicate.
		*/
		void Update(bool _pred);

		/**
		*	\brief Spreads values to parent group.
		*
		*	\param[in] _parent	parent to spread values to.
		*/
		void Spread(Group& _parent);
	};

//}
}


/** \} */

#endif // GUARD
