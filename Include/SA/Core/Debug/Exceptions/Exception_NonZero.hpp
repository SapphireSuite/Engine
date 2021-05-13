// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_EXCEPTION_NON_ZERO_GUARD
#define SAPPHIRE_CORE_EXCEPTION_NON_ZERO_GUARD

#include <SA/Core/Debug/Exceptions/Exception.hpp>

/**
*	\file Exception_NonZero.hpp
*
*	\brief <b>NonZero Exception</b> type implementation.
*
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// NonZero Exception type.
	class Exception_NonZero : public Exception
	{
	public:
		/**
		*	\e Value Constructor.
		*
		*	\param[in] _infos		Base create infos.
		*	\param[in] _pred		Evaluated value predicate.
		*	\param[in] _details		Additional details to display on assertion.
		*/
		SA_ENGINE_API Exception_NonZero(
			const BaseInfos& _infos,
			bool _pred,
			const std::wstring& _details = L""
		) noexcept;
	};

#endif
}


/** \} */

#endif // GUARD
