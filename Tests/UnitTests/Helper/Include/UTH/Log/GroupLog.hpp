// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_GROUP_LOG_GUARD
#define SAPPHIRE_UTH_GROUP_LOG_GUARD

#include <UTH/Group.hpp>
#include <UTH/Log/Log.hpp>

/**
*	\file GroupLog.hpp
* 
*	\brief UTH Group begin/end log implementation.
* 
*	\ingroup UTH
*	\{
*/

namespace Sa::UTH
{
	/// UTH Group begin log class.
	class GroupBeginLog : public Log
	{
	public:
		/// Group name.
		std::wstring name;

		/**
		*	\brief \e Value constructor.
		* 
		*	\param[in] _name	Group name.
		*/
		GroupBeginLog(const std::wstring& _name);

		SA_UTH_API StringToken ToStringToken() const  override final;
	};


	/// UTH Group End log class.
	class GroupEndLog : public Log
	{
	public:
		/// Handled group.
		Group group;

		/**
		*	\brief \e Value constructor.
		* 
		*	\param[in] _group	handled group.
		*/
		GroupEndLog(Group&& _group);

		SA_UTH_API StringToken ToStringToken() const  override final;
	};
}


/** \} */

#endif // GUARD
