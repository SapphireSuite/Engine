// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Group.hpp>

namespace Sa::UTH
{
	Counter Group::globalCount;

	void Group::Update(bool _pred)
	{
		count.Increment(_pred);

		if (!_pred)
			localExit = EXIT_FAILURE;
	}

	//void Group::Spread(Group& _parent)
	//{
	//	if (localExit == EXIT_FAILURE)
	//		_parent.localExit = EXIT_FAILURE;

	//	_parent.count += count;
	//}

	//void Group::Begin(const std::string& _name)
	//{
	//	//// Log before push for log indentation.
	//	//if ((verbosity & Verbosity::GroupStart) && Intl::ShouldLog())
	//	//	BeginLog(_name);

	//	//sGroups.push(Group{ _name });

	//	//if (GroupBeginCB)
	//	//	GroupBeginCB(_name);
	//}

	//Group Group::End()
	//{
	//	//Group group = sGroups.top();
	//	//sGroups.pop();

	//	//// Spread values to parent.
	//	//if (!sGroups.empty())
	//	//	group.Spread(sGroups.top());

	//	//if ((verbosity & Verbosity::GroupExit) && Intl::ShouldLog())
	//	//	EndLog(group);

	//	//if (GroupEndCB)
	//	//	GroupEndCB(group);

	//	//globalCount.Update(group.localExit == EXIT_SUCCESS);

	//	//return group;
	//}


	//void Group::BeginLog(const std::string& _name)
	//{
	//	//using namespace Intl;

	//	//SetConsoleColor(CslColor::GroupBegin);
	//	//SA_UTH_LOG("[SA-UTH] Group:\t" << _name);
	//	//SetConsoleColor(CslColor::None);
	//}

	//void Group::EndLog(const UTH::Group& _group)
	//{
	//	//using namespace Intl;

	//	//LogTabs();
	//	//SetConsoleColor(CslColor::GroupEnd);

	//	//__SA_UTH_LOG_IN("[SA-UTH] Group:\t" << _group.name << " run: ");

	//	//_group.count.Log();

	//	//SetConsoleColor(CslColor::GroupEnd);
	//	//__SA_UTH_LOG_IN(" and exit with code: ");

	//	//if (_group.localExit == EXIT_SUCCESS)
	//	//{
	//	//	SetConsoleColor(CslColor::Success);
	//	//	__SA_UTH_LOG_IN("EXIT_SUCCESS (" << EXIT_SUCCESS << ')');
	//	//}
	//	//else
	//	//{
	//	//	SetConsoleColor(CslColor::Failure);
	//	//	__SA_UTH_LOG_IN("EXIT_FAILURE (" << EXIT_FAILURE << ')');
	//	//}

	//	//__SA_UTH_LOG_ENDL();
	//	//SetConsoleColor(CslColor::None);
	//}


	//std::string Group::TabStr() noexcept
	//{
	//	//return std::string(sGroups.size(), '\t');
	//}

	//void Group::LogTabs() noexcept
	//{
	//	//if (sGroups.size())
	//	//	__SA_UTH_LOG_IN(TabStr());
	//}
}
