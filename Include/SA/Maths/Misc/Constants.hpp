// Copyright 2020 Sapphire development team.All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_CONSTANTS_GUARD
#define SAPPHIRE_MATHS_CONSTANTS_GUARD

namespace Sa
{
	namespace Maths
	{
		/// PI constant.
		static constexpr double Pi = 3.1415926535897932384;

		/// 2 * PI constant.
		static constexpr double PiX2 = 2.0 * Pi;

		/// PI / 2 constant.
		static constexpr double PiOv2 = Pi / 2.0;

		/// PI / 3 constant.
		static constexpr double PiOv3 = Pi / 3.0;

		/// PI / 4 constant.
		static constexpr double PiOv4 = Pi / 4.0;

		/// PI / 6 constant.
		static constexpr double PiOv6 = Pi / 6.0;

		/// Conversion constant to convert degree to radian.
		static constexpr double DegToRad = Pi / 180.0;

		/// Conversion constant to convert radian to degree.
		static constexpr double RadToDeg = 180.0 / Pi;
	}
}

#endif // GUARD
