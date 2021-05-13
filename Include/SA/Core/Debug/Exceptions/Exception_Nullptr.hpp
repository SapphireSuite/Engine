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
		*	\e Value Constructor.
		* 
		*	\param[in] _infos		Base create infos.
		*	\param[in] _pred		Evaluated pointer predicate.
		*	\param[in] _details		Additional details to display on assertion.
		*/
		SA_ENGINE_API Exception_Nullptr(
			const BaseInfos& _infos,
			bool _pred,
			const std::wstring& _details = L""
		) noexcept;
	};

#endif
}


/** \} */

#endif // GUARD
