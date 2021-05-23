// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CONFIG_GUARD
#define SAPPHIRE_CONFIG_GUARD

#include <SA/Core/Support/ModuleAPI.hpp>

/**
*	\file SA/Config.hpp
*
*	\brief Sapphire Engine config file.
*/


#if defined(SA_Engine_EXPORTS)

	/// Sapphire Engine API import/export preprocessor.
	#define SA_ENGINE_API SA_MODUE_EXPORT

#else

	/// Sapphire Engine API import/export preprocessor.
	#define SA_ENGINE_API SA_MODUE_IMPORT

#endif


/// Sapphire Engine global namespace
namespace Sa
{
	/// Sapphire Engine Maths algorithms implementations.
	namespace Maths
	{
	}

	/// Sapphire Engine Documentation classes implementations.
	namespace Doc
	{
	}

	/// \cond Internal

	/// Sapphire Engine Internal classes implementations.
	namespace Intl
	{
	}

	/// \endcond Internal
}


/**
*	\defgroup Debug Debug
*	Sapphire Engine Debug tools.
*/


#endif // GUARD
