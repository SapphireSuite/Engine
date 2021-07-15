// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_EXCEPTION_OUT_OF_RANGE_GUARD
#define SAPPHIRE_CORE_EXCEPTION_OUT_OF_RANGE_GUARD

#include <SA/Core/Debug/Exceptions/Exception.hpp>

/**
*	\file Exception_OutOfRange.hpp
*
*	\brief <b>OutOfRange Exception</b> type implementation.
*
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// OutOfRange Exception type.
	class Exception_OutOfRange : public Exception
	{
	public:
		/// Index used for access.
		uint32 currIndex = 0u;

		/// Minimum bound allowed.
		uint32 minBound = 0u;

		/// Maximum bound allowed.
		uint32 maxBound = 0u;

		/**
		*	\e Value move Constructor.
		* 
		*	\param[in] _infos		Base create infos.
		*	\param[in] _currIndex	Index used for access.
		*	\param[in] _minBound	Minimum bound allowed.
		*	\param[in] _maxBound	Maximum bound allowed.
		*	\param[in] _details		Additional details to display on assertion.
		*/
		SA_ENGINE_API Exception_OutOfRange(
			BaseInfos&& _infos,
			uint32 _currIndex,
			uint32 _minBound,
			uint32 _maxBound,
			std::wstring&& _details = L""
		) noexcept;
	};


	#define __SA_CREATE_EXCEPTION_OutOfRange(_baseInfos, _currIndex, _minBound, _maxBound, ...) Sa::Exception_OutOfRange(\
		_baseInfos,\
		_currIndex,\
		_minBound,\
		_maxBound,\
		##__VA_ARGS__\
	)

#endif
}


/** \} */

#endif // GUARD
