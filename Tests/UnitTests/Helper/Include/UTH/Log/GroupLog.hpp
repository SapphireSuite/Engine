// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_GROUP_LOG_GUARD
#define SAPPHIRE_UTH_GROUP_LOG_GUARD

#include <UTH/Group.hpp>
#include <UTH/Log/Log.hpp>

namespace Sa::UTH
{
	class GroupBeginLog : public Log
	{
	public:
		std::wstring name;

		GroupBeginLog(const std::wstring& _name);

		SA_UTH_API StringToken ToStringToken() const  override final;
	};


	class GroupEndLog : public Log
	{
	public:
		Group group;

		GroupEndLog(Group&& _group);

		SA_UTH_API StringToken ToStringToken() const  override final;
	};
}

#endif // GUARD
