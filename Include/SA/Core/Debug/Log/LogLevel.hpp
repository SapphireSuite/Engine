// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_LEVEL_GUARD
#define SAPPHIRE_CORE_LOG_LEVEL_GUARD

#include <SA/Config.hpp>

#include <SA/Core/Types/Char.hpp>
#include <SA/Core/Types/Variadics/Flags.hpp>

#include <SA/Core/Debug/Config.hpp>

/**
*	\file LogLevel.hpp
*
*	\brief Log level enum used by Sapphire Engine Debug class.
*
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// \brief All levels of logging.
	enum class LogLevel : uint8
	{
		/// Normal level
		Normal = (1 << 0),

		/// Info level
		Infos = (1 << 1),

		/// Warning level
		Warning = (1 << 2),

		/// Error level
		Error = (1 << 3),

		/// Assert Success level
		AssertSuccess = (1 << 4),

		/// Assert  Failed level
		AssertFailed = (1 << 5),

		/// Default log level (no assert success).
		Default = Normal | Infos | Warning | Error | AssertFailed,

		Max = uint8(-1)
	};

	/// \brief Alias.
	using LogLvl = LogLevel;

	SA_DEFINE_ENUM_FLAGS(LogLevel)


	/**
	*	\brief \e Getter of Log level name.
	*
	*	\param _lvl		Level to get the name.
	*
	*	\return			Name of the enum.
	*/
	SA_ENGINE_API const wchar* GetLogLevelName(LogLevel _lvl) noexcept;

#endif
}


/** \} */

#endif // GUARD
