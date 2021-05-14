// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <UTH/Instance.hpp>
#include <UTH/LogStream.hpp>

#include <SA/Collections/Debug>

namespace Sa::UTH
{
	SA_UTH_API Instance Intl::instance;

	SA_UTH_API int32 exit = EXIT_SUCCESS;

	SA_UTH_API uint8 verbosity = static_cast<uint8>(Verbosity::Default);

	SA_UTH_API LogStream csl("log-UTH");

	Instance::Instance()
	{
		logger.Register(csl);
	}

	void Instance::Init()
	{
		Log log = __SA_UTH_MAKE_LOG();

		log.AddToken(Step::Init);
		log.AddString(L"[SA-UTH] Init");

		//SetConsoleColor(CslColor::Init);

		//// Init rand.
		//time_t currTime = time(NULL);
		//srand(static_cast<unsigned int>(currTime));
		//SA_UTH_LOG("[SA-UTH] Init Rand seed: " << currTime);

		//SetConsoleColor(CslColor::None);
	}
	
	int32 Instance::Exit(bool _bForce)
	{
		Log log = __SA_UTH_MAKE_LOG();

		log.AddToken(Step::Exit);
		log.AddString(L"[SA-UTH] Run: ");
		mCounter.AppendLog(log);


		// Output Group counter.
		if ((verbosity & Verbosity::GroupCount) && !Group::globalCount.IsEmpty())
		{
			log.AddToken(Step::Exit);
			log.AddString(L" in ");

			Group::globalCount.AppendLog(log);

			log.AddToken(Step::GroupEnd);
			log.AddString(L" groups");
		}


		// Output exit.
		log.AddToken(Step::Exit);
		log.AddString(L" and exit with code: ");

		if (exit == EXIT_SUCCESS)
		{
			log.AddToken(Step::Success);
			log.AddString(L"EXIT_SUCCESS (" + std::to_wstring(EXIT_SUCCESS) + L')');
		}
		else
		{
			log.AddToken(Step::Failure);
			log.AddString(L"EXIT_FAILURE (" + std::to_wstring(EXIT_FAILURE) + L')');
		}

		log.EndOfLine();
		log.AddToken(Step::None);


#if SA_UTH_EXIT_PAUSE && !SA_CI

		log.AddString(L"[SA-UTH] Press Enter to continue...\n");

		logger.Log(log);

		std::cin.get();

#else

		logger.Log(log);

#endif

		if(_bForce)
			::exit(exit);

		return exit;
	}


	void Instance::Process(const Test& _test)
	{
		mCounter.Increment(_test.bResult);
		
		UpdateGroups(_test.bResult);

		if (_test.bResult || (verbosity & Verbosity::Success)) // Should log test.
			logger.Log(_test.MakeLog());

		if(!_test.bResult)
			exit = EXIT_FAILURE;

#if SA_UTH_EXIT_ON_FAILURE

		Exit(true);

#endif
	}

	uint32 Instance::GetGroupNum() const
	{
		return mGroups.size();
	}

	void Instance::UpdateGroups(bool _pred)
	{
		if (!mGroups.empty())
		{
			// Update top group.
			Group& gp = mGroups.top();

			gp.Update(_pred);
		}
	}

	void Instance::BeginGroup(const std::string& _name)
	{
		// Log before push for log indentation.
		if (verbosity & Verbosity::GroupStart)
		{
			Log log = __SA_UTH_MAKE_LOG();

			log.AddToken(Step::GroupBegin);
			log.AddString(L"[SA-UTH] Group:\t" + Sa::ToWString(_name));

			logger.Log(log);
		}

		mGroups.push(Group{ _name });
	}

	void Instance::EndGroup()
	{
		Group group = mGroups.top();
		mGroups.pop();

		// Spread values to parent.
		if (!mGroups.empty())
			group.Spread(mGroups.top());

		if ((verbosity & Verbosity::GroupExit))
		{
			Log log = __SA_UTH_MAKE_LOG();

			log.AddToken(Step::GroupEnd);
			log.AddString(L"[SA-UTH] Group:\t" + Sa::ToWString(group.name) + L"run: ");
			group.count.AppendLog(log);

			log.AddToken(Step::GroupEnd);
			log.AddString(L" and exit with code: ");

			if (group.localExit == EXIT_SUCCESS)
			{
				log.AddToken(Step::Success);
				log.AddString(L"EXIT_SUCCESS (" + std::to_wstring(EXIT_SUCCESS) + L")");
			}
			else
			{
				log.AddToken(Step::Failure);
				log.AddString(L"EXIT_FAILURE (" + std::to_wstring(EXIT_FAILURE) + L")");
			}

			logger.Log(log);
		}

		mCounter.Increment(group.localExit == EXIT_SUCCESS);
	}
}
