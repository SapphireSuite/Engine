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
		log.AddString(L"[SA-UTH] Init ");


		// Init rand. TODO: Remove later, use engine Random impl.
		time_t currTime = time(NULL);
		srand(static_cast<unsigned int>(currTime));
		log.AddString(L"Rand seed: " + ToWString(currTime));

		logger.Log(log);
	}
	
	int32 Instance::Exit(bool _bForce)
	{
		Log log = __SA_UTH_MAKE_LOG();

		log.AddToken(Step::Exit);
		log.AddString(L"[SA-UTH] Run: ");
		mCounter.AppendLog(log);


		// Output Group counter.
		if ((verbosity & Verbosity::GroupCount) && !mGroupCounter.IsEmpty())
		{
			log.AddToken(Step::Exit);
			log.AddString(L" in ");

			mGroupCounter.AppendLog(log);

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

		if (!mRecap.empty())
		{
			log.AddToken(Step::Exit);
			log.AddString(L"---------- Test Recap ----------");
		}

		logger.Log(log);


		// Print recap.
		for (auto it = mRecap.begin(); it != mRecap.end(); ++it)
			logger.Log(*it);


#if SA_UTH_EXIT_PAUSE && !SA_CI

		Log pauseLog = __SA_UTH_MAKE_LOG();
		pauseLog.AddString(L"[SA-UTH] Press Enter to continue...\n");

		logger.Log(pauseLog);

		std::cin.get();

#endif

		if(_bForce)
			::exit(exit);

		return exit;
	}


	void Instance::Process(const Test& _test)
	{
		mCounter.Increment(_test.bResult);

		UpdateGroups(_test.bResult);

		Log tLog = _test.MakeLog();

		if (!_test.bResult || (verbosity & Verbosity::Success)) // Should log test.
			logger.Log(tLog);

		if (!_test.bResult)
		{
			if (verbosity & Verbosity::Recap)
				AddRecapLog(tLog);

			exit = EXIT_FAILURE;

#if SA_UTH_EXIT_ON_FAILURE

			Exit(true);

#endif
		}
	}

	uint32 Instance::GetGroupNum() const
	{
		return static_cast<uint32>(mGroups.size());
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

		mGroups.push_back(Group{ _name });
	}

	void Instance::EndGroup()
	{
		Group group = mGroups.back();
		mGroups.erase(mGroups.end() - 1);

		// Spread values to parent.
		if (!mGroups.empty())
			group.Spread(mGroups.back());

		if ((verbosity & Verbosity::GroupExit) || group.localExit == EXIT_FAILURE)
		{
			Log log = __SA_UTH_MAKE_LOG();

			log.AddToken(Step::GroupEnd);
			log.AddString(L"[SA-UTH] Group:\t" + Sa::ToWString(group.name) + L" run: ");
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

		mGroupCounter.Increment(group.localExit == EXIT_SUCCESS);
	}

	void Instance::AddRecapLog(const Log& _log)
	{
		Log rLog(_log.file, _log.line, _log.function);

		rLog.msg.clear();
		std::wstring msg = _log.msg;

		// Remove all indentation.
		{
			size_t index = msg.find(L'\t');

			while (index != std::string::npos)
			{
				msg.erase(index, 1);
				index = msg.find(L'\t');
			}
		}

		// Add Title.
		const size_t titleIndex = msg.find_first_of(L'\n');
		rLog.AddString(msg.substr(0u, titleIndex));

		// Append group trace.
		if (!mGroups.empty())
		{
			rLog.AddToken(Step::Title);
			rLog.AddString(L"\tGroup: ");

			for (auto it = mGroups.begin(); it != mGroups.end(); ++it)
			{
				rLog.AddToken(Step::GroupBegin);

				rLog.AddString(Sa::ToWString(it->name));

				if (it + 1 != mGroups.end())
				{
					rLog.AddToken(Step::None);
					rLog.AddString(L"/");
				}
			}

			rLog.AddToken(Step::None);
		}


		// Add end.
		rLog.AddString(msg.substr(titleIndex) + L'\n');

		mRecap.push_back(rLog);
	}
}
