// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_INSTANCE_GUARD
#define SAPPHIRE_UTH_INSTANCE_GUARD

#include <vector>

#include <UTH/Config.hpp>

#include <UTH/Group.hpp>
#include <UTH/Verbosity.hpp>
#include <UTH/Log/TestLog.hpp>
#include <UTH/Log/RecapLog.hpp>
#include <UTH/Log/ConsoleTheme.hpp>

#include <SA/Core/Debug/Log/Logger.hpp>

/**
*	\file Instance.hpp
* 
*	\brief UTH Instance implementation.
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
	/// UTH instance class.
	class Instance
	{
		/// Total number of test run.
		Counter mCounter;

		/// Total number of group run.
		Counter mGroupCounter;
		
		/// Current active groups.
		std::vector<Group> mGroups;

		/// Recap of failed tests log.
		RecapLog mRecap;

		/// Update groups from predicate.
		void UpdateGroups(bool _pred);

		/**
		*	\brief Add a test log to RecapLog.
		* 
		*	\param[in] _log		Log to add.
		*/
		void AddRecapLog(const TestLog& _log);

	public:
		/// \e Default constructor. Initialize UTH instance.
		Instance();

		/// Destructor, call exit main function.
		~Instance();


		/// Exit main function.
		void Exit();
		

		/**
		*	\brief Process a test.
		*	Use SA_UTH_ test macros as helper.
		* 
		*	\param[in] _test	Test to process.
		*/
		SA_UTH_API void Process(TestLog&& _test);

		/// \return Current number of groups.
		uint32 GetGroupNum() const;

		/// \return Current active group list.
		const std::vector<Group>& GetGroups() const;

		/**
		*	\brief Begin a group of tests.
		* 
		*	\param[in] _name	The name of the group that begins.
		*/
		SA_UTH_API void BeginGroup(const std::wstring& _name);

		/**
		*	\brief End current group of tests.
		*/
		SA_UTH_API void EndGroup();
	};

	// Easy User Access variables.

	/**
	*	\brief Exit result from unit testing.
	*
	*	UTH::exit will be equal to EXIT_FAILURE (1) if at least one test has failed.
	*
	*	exit 0 == success.
	*	exit 1 == failure.
	*/
	SA_UTH_API extern int32 exit;

	/// Current verbosity level.
	SA_UTH_API extern uint8 verbosity;

	/// Console theme.
	SA_UTH_API extern ConsoleTheme cslTheme;


	/// \cond Internal

	namespace Intl
	{
		/**
		*	Internal instance object.
		*	Use SA_UTH_ test macros as helper use.
		*/
		SA_UTH_API extern Instance instance;
	}

	/// \endcond
}


/** \} */

#endif // GUARD
