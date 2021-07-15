// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_EXCEPTION_NULLPTR_GUARD
#define SAPPHIRE_CORE_EXCEPTION_NULLPTR_GUARD

#include <SA/Core/Debug/Exceptions/Exception.hpp>

/**
*	\file Exception_Nullptr.hpp
*
*	\brief <b>Nullptr Exception</b> type implementation.
*
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// Nullptr Exception type.
	class Exception_Nullptr : public Exception
	{
	public:
		/**
		*	\e Value move Constructor.
		* 
		*	\param[in] _infos		Base create infos.
		*	\param[in] _pred		Evaluated pointer predicate.
		*	\param[in] _details		Additional details to display on assertion.
		*/
		SA_ENGINE_API Exception_Nullptr(
			BaseInfos&& _infos,
			bool _pred,
			std::string&& _predStr,
			std::wstring&& _details = L""
		) noexcept;
	};

	#define __SA_CREATE_EXCEPTION_Nullptr(_baseInfos, _pred, ...) Sa::Exception_Nullptr(\
		_baseInfos,\
		_pred,\
		#_pred,\
		##__VA_ARGS__\
	)

#endif
}


/** \} */

#endif // GUARD
