// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_MODULE_GUARD
#define SAPPHIRE_CORE_MODULE_GUARD

#include <SA/Core/Support/Platforms.hpp>

/**
*	\file ModuleAPI.hpp
*
*	\brief Sapphire Engine API Module config file.
*
*	Define API module import / export preprocessors.
*
*	\ingroup Core
*	\{
*/


#if SA_WIN

	/// Module export preprocessor.
	#define SA_MODUE_EXPORT __declspec(dllexport)

	/// Module import preprocessor.
	#define SA_MODUE_IMPORT __declspec(dllimport)

#elif SA_UNIX || SA_OSX || SA_ANDROID

	/// Module export preprocessor.
	#define SA_MODUE_EXPORT __attribute__((visibility("default")))

	/// Module import preprocessor.
	#define SA_MODUE_IMPORT

#endif


/** \} */


#endif // GUARD
