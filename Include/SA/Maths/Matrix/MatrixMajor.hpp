// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_MATRIX_MAJOR_GUARD
#define SAPPHIRE_MATHS_MATRIX_MAJOR_GUARD

#include <SA/Core/Types/Int.hpp>

/**
*	\file MatrixMajor.hpp
* 
*	\brief <b>Matrix Major</b> enum definitions
* 
*	\ingroup Maths
*	\{
*/


namespace Sa
{
	/// Matrix major enum.
	enum class MatrixMajor : uint8
	{
		/// Row major standard.
		Row = 1u,

		/// Column major standard.
		Column = 2u,


		/// Default standard.
		Default = Row
	};


	/// Shortcut alias.
	using MatMaj = MatrixMajor;
}


/** \} */

#endif // GUARD
