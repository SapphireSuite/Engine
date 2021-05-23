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

#include <SA/Core/Debug/Log/Logger.hpp>

namespace Sa::UTH
{
	class Instance
	{
		/// Total number of test run.
		Counter mCounter;

		/// Total number of group run.
		Counter mGroupCounter;

		std::vector<Group> mGroups;

		RecapLog mRecap;

		/// Update groups from predicate.
		void UpdateGroups(bool _pred);

		void AddRecapLog(const TestLog& _log);

	public:
		/**
		*	\brief Init function to be called at the start of main.
		*	Use SA_UTH_INIT() as helper macro.
		*/
		SA_UTH_API void Init();

		/**
		*	\brief Exit function to be called at the end of main.
		*	Use SA_UTH_EXIT() as helper macro.
		*
		*	\return exit code of all tests run.
		*/
		SA_UTH_API int32 Exit(bool _bForce = false);
		

		SA_UTH_API void Process(TestLog&& _test);

		uint32 GetGroupNum() const;
		const std::vector<Group>& GetGroups() const;

		/**
		*	\brief Begin a group of tests.
		* 
		*	param[in] _name	The name of the group that begins.
		*/
		SA_UTH_API void BeginGroup(const std::wstring& _name);

		/**
		*	\brief End current group of tests.
		* 
		*	param[in] _name	The name of the group that begins.
		*/
		SA_UTH_API void EndGroup();
	};

	namespace Intl
	{
		SA_UTH_API extern Instance instance;
	}

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

	///// Custom UTH console log stream.
	//SA_UTH_API extern LogStream csl;
}

#endif // GUARD
