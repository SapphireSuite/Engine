// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_VERBOSITY_GUARD
#define SAPPHIRE_UTH_VERBOSITY_GUARD

#include <UTH/Config.hpp>

#include <SA/Core/Types/Variadics/Flags.hpp>

/**
*	\file Verbosity.hpp
* 
*	\brief UTH Verbosity enum implementation.
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
	/// Verbosity level enum.
	enum class Verbosity : uint8
	{
		/// No verbosity.
		None,

		/// Output success results.
		Success = 1 << 0,

		/// Output params' name.
		ParamsName = 1 << 1,

		/// Output params' value on failure.
		ParamsFailure = 1 << 2,

		/// Output params' value on success.
		ParamsSuccess = 1 << 3,

		/// Output group start.
		GroupStart = 1 << 4,

		/// Output group exit result.
		GroupExit = 1 << 5,

		/// Output group counter on exit.
		GroupCount = 1 << 6,

		/// Output recap of all failure test at the end.
		Recap = 1 << 7,


		/// Light verbosity value.
		Light = ParamsName | ParamsFailure | GroupCount | Recap,

#if SA_CI

		Default = Light,
#else

		/// Default verbosity value.
		Default = Success | ParamsName | ParamsFailure | GroupStart | GroupExit | GroupCount | Recap,

#endif

		/// Maximum verbosity level (all flags set).
		Max = 0xFF
	};

	/// Verbosity flags definition.
	SA_DEFINE_ENUM_FLAGS(Verbosity);
}


/** \} */

#endif // GUARD
