// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_INTERFACE_GUARD
#define SAPPHIRE_CORE_INTERFACE_GUARD

#include <SA/Collections/Debug>


/**
*	\file Interface.hpp
* 
*	\brief \b Interface type implementation.
* 
*	\ingroup Core_Types
*	\{
*/

namespace Sa
{
	/// Interface class.
	class Interface
	{
	public:
#if SA_DEBUG || 1 // TODO: Remove Later.

		/**
		*	\brief \b Virtual destructor (<b>DEBUG ONLY</b>).
		* 
		*	Allow type check on debug.
		*/
		virtual ~Interface() = default;

#endif

		/**
		*	\brief Cast this as T&
		* 
		*	\tparam T	Type to cast in.
		* 
		*	\return this casted as T&.
		*/
		template <typename T>
		T& As();

		/**
		*	\brief Cast this as const T&
		* 
		*	\tparam T	Type to cast in.
		* 
		*	\return this casted as const T&.
		*/
		template <typename T>
		const T& As() const;


		/**
		*	\brief Cast this as T*
		* 
		*	\tparam T	Type to cast in.
		* 
		*	\return this casted as T*.
		*/
		template <typename T>
		T* AsPtr();

		/**
		*	\brief Cast this as const T*
		* 
		*	\tparam T	Type to cast in.
		* 
		*	\return this casted as const T*.
		*/
		template <typename T>
		const T* AsPtr() const;
	};
}

#include <SA/Core/Types/Interface.inl>


/** \} */

#endif // GUARD
