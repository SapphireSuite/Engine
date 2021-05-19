// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_MATRIX4_BASE_GUARD
#define SAPPHIRE_MATHS_MATRIX4_BASE_GUARD

#include <utility>

#include <SA/Maths/Matrix/MatrixMajor.hpp>

namespace Sa
{
	/// \cond Internal

	namespace Intl
	{
		template <typename T, MatrixMajor major>
		struct Mat4_Base;

//{ Row Major

		template <typename T>
		struct Mat4_Base<T, MatrixMajor::Row>
		{
			/// Matrix components.
			T e00{ T(0) }; T e01{ T(0) }; T e02{ T(0) }; T e03{ T(0) };
			T e10{ T(0) }; T e11{ T(0) }; T e12{ T(0) }; T e13{ T(0) };
			T e20{ T(0) }; T e21{ T(0) }; T e22{ T(0) }; T e23{ T(0) };
			T e30{ T(0) }; T e31{ T(0) }; T e32{ T(0) }; T e33{ T(0) };


//{ Constructors

			/// Default constructor.
			Mat4_Base() = default;

			/// Default move constructor.
			Mat4_Base(Mat4_Base&&) = default;

			/// Default copy constructor.
			Mat4_Base(const Mat4_Base&) = default;

			/// Move constructor from column major.
			constexpr Mat4_Base(Mat4_Base<T, MatrixMajor::Column>&& _other) noexcept;

			/// Copy constructor from column major.
			constexpr Mat4_Base(const Mat4_Base<T, MatrixMajor::Column>&_other) noexcept;

			/// Default value constructor.
			constexpr Mat4_Base(
				T _e00, T _e01, T _e02, T _e03,
				T _e10, T _e11, T _e12, T _e13,
				T _e20, T _e21, T _e22, T _e23,
				T _e30, T _e31, T _e32, T _e33
			) noexcept;

//}

//{ Operators

			/// Default move assignment.
			Mat4_Base& operator=(Mat4_Base&&) = default;

			/// Move assignment from column major.
			Mat4_Base& operator=(Mat4_Base<T, MatrixMajor::Column>&& _rhs) noexcept;
			
			/// Default copy assignment.
			Mat4_Base& operator=(const Mat4_Base&) = default;

			/// Copy assignment from column major.
			Mat4_Base& operator=(const Mat4_Base<T, MatrixMajor::Column>& _rhs) noexcept;

//}
		};

//}

//{ Column Major

		template <typename T>
		struct Mat4_Base<T, MatrixMajor::Column>
		{
			/// Matrix components.
			T e00{ T(0) }; T e10{ T(0) }; T e20{ T(0) }; T e30{ T(0) };
			T e01{ T(0) }; T e11{ T(0) }; T e21{ T(0) }; T e31{ T(0) };
			T e02{ T(0) }; T e12{ T(0) }; T e22{ T(0) }; T e32{ T(0) };
			T e03{ T(0) }; T e13{ T(0) }; T e23{ T(0) }; T e33{ T(0) };

//{ Constructors

			/// Default constructor.
			Mat4_Base() = default;

			/// Default value constructor.
			constexpr Mat4_Base(
				T _e00, T _e01, T _e02, T _e03,
				T _e10, T _e11, T _e12, T _e13,
				T _e20, T _e21, T _e22, T _e23,
				T _e30, T _e31, T _e32, T _e33
			) noexcept;

			/// Default move constructor.
			Mat4_Base(Mat4_Base&&) = default;

			/// Default copy constructor.
			Mat4_Base(const Mat4_Base&) = default;

			/// Move constructor from row major.
			constexpr Mat4_Base(Mat4_Base<T, MatrixMajor::Row>&& _other) noexcept;

			/// Copy constructor from row major.
			constexpr Mat4_Base(const Mat4_Base<T, MatrixMajor::Row>&_other) noexcept;

//}

//{ Operators

			/// Default move assignment.
			Mat4_Base& operator=(Mat4_Base&&) = default;

			/// Default copy assignment.
			Mat4_Base& operator=(const Mat4_Base&) = default;

			/// Move assignment from row major.
			Mat4_Base& operator=(Mat4_Base<T, MatrixMajor::Row> && _rhs) noexcept;

			/// Copy assignment from row major.
			Mat4_Base& operator=(const Mat4_Base<T, MatrixMajor::Row>&_rhs) noexcept;

//}
		};
	}

//}

	/// \endcond
}

#include <SA/Maths/Matrix/Matrix4Base.inl>

#endif // GUARD
