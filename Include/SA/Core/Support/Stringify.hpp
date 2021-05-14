// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_STRINGIFY_GUARD
#define SAPPHIRE_CORE_STRINGIFY_GUARD

/**
*	\file Stringify.hpp
*
*	\brief \b Stringify support definition file.
*
*	Define stringify support preprocessors.
*
*	\ingroup Core
*	\{
*/


/// Convert any _param into a const char8* (Stringification).
#define SA_STR(_param) # _param

/// Convert a string _param into a const wchar*
#define SA_WIDE(_param) L"" _param

/// Convert any _param into a const wchar* (Wide Stringification)
#define SA_WSTR(_param) SA_WIDE(SA_STR(_param))


/** \} */

#endif // GUARD
