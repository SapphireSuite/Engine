// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_CONFIG_GUARD
#define SAPPHIRE_RENDER_CONFIG_GUARD

/**
*	\file Render/Config.hpp
* 
*	\brief Render specific config file.
* 
*	\ingroup Render
*	\{
*/


#ifndef SA_VULKAN

	/// Sapphire Engine enable Vulkan preprocessor.
	#define SA_VULKAN 0

#endif

#ifndef SA_OPEN_GL

	/// Sapphire Engine enable OpenGL preprocessor.
	#define SA_OPEN_GL 0

#endif


/**
*	\defgroup Render Render
*	Sapphire Engine Render Module.
*/


/** \} */

#endif // GUARD
