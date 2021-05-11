// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_VERSION_GUARD
#define SAPPHIRE_CORE_VERSION_GUARD

/**
*	\file Version.hpp
*
*	\brief Sapphire Engine version definition file.
*
*	Define version preprocessors.
*	Version follows the norm Major.Minor.Patch.
*
*	\ingroup Core
*	\{
*/


/**
*	\brief create version number from major, minor and patch.
*
*	\param[in] _major	Major version.
*	\param[in] _minor	Minor version.
*	\param[in] _patch	Patch version.
*/
#define SA_MAKE_VERSION(_major, _minor, _patch) (_major * 10000 + _minor * 100 + _patch)


/// Sapphire Engine \b major version.
#define SA_ENGINE_VERSION_MAJOR 0

/// Sapphire Engine \b minor version.
#define SA_ENGINE_VERSION_MINOR 1

/// Sapphire Engine \b patch version.
#define SA_ENGINE_VERSION_PATCH 0

/// Sapphire Engine \b full version.
#define SA_ENGINE_VERSION SA_MAKE_VERSION(SA_ENGINE_VERSION_MAJOR, SA_ENGINE_VERSION_MINOR, SA_ENGINE_VERSION_PATCH)


/** \} */

#endif // GUARD
