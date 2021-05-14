// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_VERBOSITY_GUARD
#define SAPPHIRE_UTH_VERBOSITY_GUARD

#include <UTH/Config.hpp>

#include <SA/Core/Types/Variadics/Flags.hpp>

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


		/// Light verbosity value.
		Light = ParamsName | ParamsFailure | GroupExit,

		/// Default verbosity value.
		Default = Success | ParamsName | ParamsFailure | GroupStart | GroupExit | GroupCount,

		/// Maximum verbosity level (all flags set).
		Max = 0xFF
	};

	SA_DEFINE_ENUM_FLAGS(Verbosity);
}

#endif // GUARD
