// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <UTH/Instance.hpp>
#include <UTH/Step.hpp>

#include <UTH/Log/GroupLog.hpp>
#include <UTH/Log/MessageLog.hpp>

#include <SA/Collections/Debug>

namespace Sa::UTH
{
	SA_UTH_API int32 exit = EXIT_SUCCESS;

	SA_UTH_API uint8 verbosity = static_cast<uint8>(Verbosity::Default);

	SA_UTH_API ConsoleTheme cslTheme;

	// Instantiate after.
	SA_UTH_API Instance Intl::instance;


	Instance::Instance()
	{
		MessageLog log;

		log.str.AppendToken(Step::Init);
		log.str.AppendString(L"[SA-UTH] Init ");


		// Init rand. TODO: Remove later, use engine Random impl.
		time_t currTime = time(NULL);
		srand(static_cast<unsigned int>(currTime));
		log.str.AppendString(L"Rand seed: " + ToWString(currTime));

		Debug::logger.Push(std::move(log));
	}
	
	Instance::~Instance()
	{
		Exit();
	}

	void Instance::Exit()
	{
		MessageLog log;

		log.str.AppendToken(Step::Exit);
		log.str.AppendString(L"[SA-UTH] Run: ");
		mCounter.AppendStr(log.str);


		// Output Group counter.
		if ((verbosity & Verbosity::GroupCount) && !mGroupCounter.IsEmpty())
		{
			log.str.AppendToken(Step::Exit);
			log.str.AppendString(L" in ");

			mGroupCounter.AppendStr(log.str);

			log.str.AppendToken(Step::Group);
			log.str.AppendString(L" groups");
		}


		// Output exit.
		log.str.AppendToken(Step::Exit);
		log.str.AppendString(L" and exit with code: ");

		if (exit == EXIT_SUCCESS)
		{
			log.str.AppendToken(Step::Success);
			log.str.AppendString(L"EXIT_SUCCESS (" + std::to_wstring(EXIT_SUCCESS) + L')');
		}
		else
		{
			log.str.AppendToken(Step::Failure);
			log.str.AppendString(L"EXIT_FAILURE (" + std::to_wstring(EXIT_FAILURE) + L')');
		}

		Debug::logger.Push(std::move(log));

		if (verbosity & Verbosity::Recap)
			Debug::logger.Push(std::move(mRecap));

#if SA_UTH_EXIT_PAUSE && !SA_CI

		{
			MessageLog msgLog;
			msgLog.str.AppendString(L"[SA-UTH] Press Enter to continue...\n");

			Debug::logger.Push(std::move(msgLog));

			std::cin.get();
		}

#endif

		::exit(exit);
	}


	void Instance::Process(TestLog&& _test)
	{
		mCounter.Increment(_test.bResult);

		UpdateGroups(_test.bResult);

		// Add to recap (copy) before move.
		if (!_test.bResult && (verbosity & Verbosity::Recap))
			AddRecapLog(_test);

		// Should log test.
		if (!_test.bResult || (verbosity & Verbosity::Success))
			Debug::logger.Push(std::move(_test));

		// Process exit after push
		if (!_test.bResult)
		{
			exit = EXIT_FAILURE;

#if SA_UTH_EXIT_ON_FAILURE

			Exit();

#endif
		}
	}

	uint32 Instance::GetGroupNum() const
	{
		return static_cast<uint32>(mGroups.size());
	}

	const std::vector<Group>& Instance::GetGroups() const
	{
		return mGroups;
	}

	void Instance::UpdateGroups(bool _pred)
	{
		if (!mGroups.empty())
		{
			// Update top group (last added).
			Group& gp = mGroups.back();

			gp.Update(_pred);
		}
	}

	void Instance::BeginGroup(const std::wstring& _name)
	{
		// Log before push for log indentation.
		if (verbosity & Verbosity::GroupStart)
			Debug::logger.Push(GroupBeginLog(_name));

		mGroups.push_back(Group{ _name });
	}

	void Instance::EndGroup()
	{
		Group group = mGroups.back();
		mGroups.erase(mGroups.end() - 1);

		// Spread values to parent.
		if (!mGroups.empty())
			group.Spread(mGroups.back());

		mGroupCounter.Increment(group.localExit == EXIT_SUCCESS);

		if ((verbosity & Verbosity::GroupExit) || group.localExit == EXIT_FAILURE)
			Debug::logger.Push(GroupEndLog(std::move(group)));
	}

	void Instance::AddRecapLog(const TestLog& _log)
	{
		TestLog copyLog = _log;
		copyLog.tabNum = 0u; // No indentation during Recap.

		mRecap.tests.push_back(std::move(copyLog));
	}
}
