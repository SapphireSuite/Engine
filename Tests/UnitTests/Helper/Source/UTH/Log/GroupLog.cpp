// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Log/GroupLog.hpp>

#include <UTH/Step.hpp>

namespace Sa::UTH
{
	GroupBeginLog::GroupBeginLog(const std::wstring& _name) :
		Log(),
		name{ _name }
	{
	}

	StringToken GroupBeginLog::ToStringToken() const
	{
		StringToken str;

		str.AppendToken(Step::Group);
		str.AppendString(std::wstring(tabNum, '\t'));
		str.AppendString(L"[SA-UTH] Group:\t" + name);

		return str;
	}


	GroupEndLog::GroupEndLog(Group&& _group) : group{ std::move(_group) }
	{
	}

	StringToken GroupEndLog::ToStringToken() const
	{
		StringToken str;

		str.AppendToken(Step::Group);
		str.AppendString(std::wstring(tabNum, '\t'));
		str.AppendString(L"[SA-UTH] Group:\t" + group.name + L" run: ");

		group.count.AppendStr(str);

		str.AppendToken(Step::Group);
		str.AppendString(L" and exit with code: ");

		if (group.localExit == EXIT_SUCCESS)
		{
			str.AppendToken(Step::Success);
			str.AppendString(L"EXIT_SUCCESS (" + std::to_wstring(EXIT_SUCCESS) + L")");
		}
		else
		{
			str.AppendToken(Step::Failure);
			str.AppendString(L"EXIT_FAILURE (" + std::to_wstring(EXIT_FAILURE) + L")");
		}

		return str;
	}
}
