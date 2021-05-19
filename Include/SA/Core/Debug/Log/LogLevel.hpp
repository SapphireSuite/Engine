// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_LEVEL_GUARD
#define SAPPHIRE_CORE_LOG_LEVEL_GUARD

#include <SA/Config.hpp>

#include <SA/Core/Types/Char.hpp>
#include <SA/Core/Types/Variadics/RAII.hpp>
#include <SA/Core/Types/Variadics/Flags.hpp>

#include <SA/Core/Debug/Config.hpp>

/**
*	\file LogLevel.hpp
*
*	\brief <b>Log level</b> enum implementation.
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

	/// Shortcut alias.
	using LogLvl = LogLevel;

	SA_DEFINE_ENUM_FLAGS(LogLevel)


	/**
	*	\brief \e Getter of Log level name.
	*
	*	\param[in] _lvl		Level to get the name.
	*
	*	\return			Name of the enum.
	*/
	SA_ENGINE_API const wchar* GetLogLevelName(LogLevel _lvl) noexcept;


	/**
	*	\brief RAII specialization for LogLvl.
	* 
	*	Disable input Loglevel on construction, re-enable on destruction.
	* 
	*	Use //TODO:
	*
	*	\implements RAII
	*/
	template<>
	class RAII<LogLvl>
	{
		/// Handled level.
		LogLvl mHandle = LogLvl::Normal;

	public:
		/**
		*	\brief \e Value constructor
		*
		*	\param[in] _lvl		LogLevel to disable.
		*/
		SA_ENGINE_API RAII(LogLvl _lvl) noexcept;

		/// Re-enable log level.
		SA_ENGINE_API ~RAII() noexcept;
	};

	/// \brief Start disable log level section.
	#define SA_LOGLVL_DIS_SECTB(_lvl) { RAII<LogLvl> __r(LogLevel::_lvl);

	/// \brief End disable log level section.
	#define SA_LOGLVL_DIS_SECTE() }

#else

	#define SA_LOGLVL_DIS_SECTB(...) {}

	#define SA_LOGLVL_DIS_SECTE(...) {}

#endif
}


/** \} */

#endif // GUARD
