// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_MATRIX3_BASE_GUARD
#define SAPPHIRE_MATHS_MATRIX3_BASE_GUARD

#include <utility>

#include <SA/Maths/Matrix/MatrixMajor.hpp>

namespace Sa
{
	/// \cond Internal

	namespace Intl
	{
		template <typename T, MatrixMajor major>
		struct Mat3_Base;

//{ Row Major

		template <typename T>
		struct Mat3_Base<T, MatrixMajor::Row>
		{
			/// Matrix components.
			T e00{ T(0) }; T e01{ T(0) }; T e02{ T(0) };
			T e10{ T(0) }; T e11{ T(0) }; T e12{ T(0) };
			T e20{ T(0) }; T e21{ T(0) }; T e22{ T(0) };

//{ Constructors

			/// Default constructor.
			Mat3_Base() = default;

			/// Default value constructor.
			constexpr Mat3_Base(
				T _e00, T _e01, T _e02,
				T _e10, T _e11, T _e12,
				T _e20, T _e21, T _e22
			) noexcept;

			/// Default move constructor.
			Mat3_Base(Mat3_Base&&) = default;

			/// Default copy constructor.
			Mat3_Base(const Mat3_Base&) = default;

			/// Move constructor from column major.
			constexpr Mat3_Base(Mat3_Base<T, MatrixMajor::Column>&& _other) noexcept;

			/// Copy constructor from column major.
			constexpr Mat3_Base(const Mat3_Base<T, MatrixMajor::Column>&_other) noexcept;

//}

//{ Operators

			/// Default move assignment.
			Mat3_Base& operator=(Mat3_Base&&) = default;

			/// Default copy assignment.
			Mat3_Base& operator=(const Mat3_Base&) = default;

			/// Move assignment from column major.
			Mat3_Base& operator=(Mat3_Base<T, MatrixMajor::Column>&& _rhs) noexcept;

			/// Copy assignment from column major.
			Mat3_Base& operator=(const Mat3_Base<T, MatrixMajor::Column>& _rhs) noexcept;
//}
		};

//}

//{ Column Major

		template <typename T>
		struct Mat3_Base<T, MatrixMajor::Column>
		{
			/// Matrix components.
			T e00{ T(0) }; T e10{ T(0) }; T e20{ T(0) };
			T e01{ T(0) }; T e11{ T(0) }; T e21{ T(0) };
			T e02{ T(0) }; T e12{ T(0) }; T e22{ T(0) };

//{ Constructors

			/// Default constructor.
			Mat3_Base() = default;

			/// Default value constructor.
			constexpr Mat3_Base(
				T _e00, T _e01, T _e02,
				T _e10, T _e11, T _e12,
				T _e20, T _e21, T _e22
			) noexcept;

			/// Default move constructor.
			Mat3_Base(Mat3_Base&&) = default;

			/// Default copy constructor.
			Mat3_Base(const Mat3_Base&) = default;

			/// Move constructor from row major.
			constexpr Mat3_Base(Mat3_Base<T, MatrixMajor::Row>&& _other) noexcept;

			/// Copy constructor from row major.
			constexpr Mat3_Base(const Mat3_Base<T, MatrixMajor::Row>&_other) noexcept;

//}

//{ Operators

			/// Default move assignment.
			Mat3_Base& operator=(Mat3_Base&&) = default;

			/// Default copy assignment.
			Mat3_Base& operator=(const Mat3_Base&) = default;

			/// Move assignment from row major.
			Mat3_Base& operator=(Mat3_Base<T, MatrixMajor::Row> && _rhs) noexcept;

			/// Copy assignment from row major.
			Mat3_Base& operator=(const Mat3_Base<T, MatrixMajor::Row>&_rhs) noexcept;

//}
		};
	}

//}

	/// \endcond
}

#include <SA/Maths/Matrix/Matrix3Base.inl>

#endif // GUARD
