// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_STATIC_CONSTANT_GUARD
#define SAPPHIRE_CORE_STATIC_CONSTANT_GUARD

namespace Sa
{
	/**
	*	\file StaticConstant.hpp
	*
	*	\brief \b Definition of Sapphire Engine \b static constant type.
	*
	*	\ingroup Core_Types
	*	\{
	*/


	/**
	*	\brief Static constexpr template variable.
	*
	*	Define a static constant of type \c T and value val.
	*
	*	\tparam T		Type of the constant.
	*	\tparam val		Value of the constant.
	*/
	template <typename T, T val>
	struct StaticConstant
	{
		/// Value of the constant.
		static constexpr T value = val;
	};


	/** \} */
}

#endif // GUARD
