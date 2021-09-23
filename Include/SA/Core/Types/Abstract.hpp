// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_ABSTRACT_GUARD
#define SAPPHIRE_CORE_ABSTRACT_GUARD

#include <SA/Core/Debug.hpp>


/**
*	\file Abstract.hpp
* 
*	\brief \b Abstract type implementation.
* 
*	\ingroup Core_Types
*	\{
*/

namespace Sa
{
	/// Abstract class.
	class Abstract
	{
	public:
		/// Virtual destructor (ensure correct child deletion).
		virtual ~Abstract() = default;

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

#include <SA/Core/Types/Abstract.inl>


/** \} */

#endif // GUARD
