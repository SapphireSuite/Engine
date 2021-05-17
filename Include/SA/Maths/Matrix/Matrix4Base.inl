// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

namespace Sa::Intl
{
	/// \cond Internal

//{ Row Major

//{ Constructors

	template <typename T>
	constexpr Mat4_Base<T, MatrixMajor::Row>::Mat4_Base(
		T _e00, T _e01, T _e02, T _e03,
		T _e10, T _e11, T _e12, T _e13,
		T _e20, T _e21, T _e22, T _e23,
		T _e30, T _e31, T _e32, T _e33
	) noexcept :
		e00{ _e00 }, e01{ _e01 }, e02{ _e02 }, e03{ _e03 },
		e10{ _e10 }, e11{ _e11 }, e12{ _e12 }, e13{ _e13 },
		e20{ _e20 }, e21{ _e21 }, e22{ _e22 }, e23{ _e23 },
		e30{ _e30 }, e31{ _e31 }, e32{ _e32 }, e33{ _e33 }
	{
	}

	template <typename T>
	constexpr Mat4_Base<T, MatrixMajor::Row>::Mat4_Base(Mat4_Base<T, MatrixMajor::Column>&& _other) noexcept :
		e00{ std::move(_other.e00) }, e01{ std::move(_other.e01) }, e02{ std::move(_other.e02) }, e03{ std::move(_other.e03) },
		e10{ std::move(_other.e10) }, e11{ std::move(_other.e11) }, e12{ std::move(_other.e12) }, e13{ std::move(_other.e13) },
		e20{ std::move(_other.e20) }, e21{ std::move(_other.e21) }, e22{ std::move(_other.e22) }, e23{ std::move(_other.e23) },
		e30{ std::move(_other.e30) }, e31{ std::move(_other.e31) }, e32{ std::move(_other.e32) }, e33{ std::move(_other.e33) }
	{
	}

	template <typename T>
	constexpr Mat4_Base<T, MatrixMajor::Row>::Mat4_Base(const Mat4_Base<T, MatrixMajor::Column>& _other) noexcept :
		e00{ _other.e00 }, e01{ _other.e01 }, e02{ _other.e02 }, e03{ _other.e03 },
		e10{ _other.e10 }, e11{ _other.e11 }, e12{ _other.e12 }, e13{ _other.e13 },
		e20{ _other.e20 }, e21{ _other.e21 }, e22{ _other.e22 }, e23{ _other.e23 },
		e30{ _other.e30 }, e31{ _other.e31 }, e32{ _other.e32 }, e33{ _other.e33 }
	{
	}

//}

//{ Operators

	template <typename T>
	Mat4_Base<T, MatrixMajor::Row>& Mat4_Base<T, MatrixMajor::Row>::operator=(Mat4_Base<T, MatrixMajor::Column>&& _rhs) noexcept
	{
		e00 = std::move(_rhs.e00);
		e01 = std::move(_rhs.e01);
		e02 = std::move(_rhs.e02);
		e03 = std::move(_rhs.e03);

		e10 = std::move(_rhs.e10);
		e11 = std::move(_rhs.e11);
		e12 = std::move(_rhs.e12);
		e13 = std::move(_rhs.e13);

		e20 = std::move(_rhs.e20);
		e21 = std::move(_rhs.e21);
		e22 = std::move(_rhs.e22);
		e23 = std::move(_rhs.e23);

		e30 = std::move(_rhs.e30);
		e31 = std::move(_rhs.e31);
		e32 = std::move(_rhs.e32);
		e33 = std::move(_rhs.e33);

		return *this;
	}

	template <typename T>
	Mat4_Base<T, MatrixMajor::Row>& Mat4_Base<T, MatrixMajor::Row>::operator=(const Mat4_Base<T, MatrixMajor::Column>& _rhs) noexcept
	{
		e00 = _rhs.e00;
		e01 = _rhs.e01;
		e02 = _rhs.e02;
		e03 = _rhs.e03;

		e10 = _rhs.e10;
		e11 = _rhs.e11;
		e12 = _rhs.e12;
		e13 = _rhs.e13;

		e20 = _rhs.e20;
		e21 = _rhs.e21;
		e22 = _rhs.e22;
		e23 = _rhs.e23;

		e30 = _rhs.e30;
		e31 = _rhs.e31;
		e32 = _rhs.e32;
		e33 = _rhs.e33;

		return *this;
	}

//}

//}

//{ Column Major

	template <typename T>
	constexpr Mat4_Base<T, MatrixMajor::Column>::Mat4_Base(Mat4_Base<T, MatrixMajor::Row>&& _other) noexcept :
		e00{ std::move(_other.e00) }, e10{ std::move(_other.e10) }, e20{ std::move(_other.e20) }, e30{ std::move(_other.e30) },
		e01{ std::move(_other.e01) }, e11{ std::move(_other.e11) }, e21{ std::move(_other.e21) }, e31{ std::move(_other.e31) },
		e02{ std::move(_other.e02) }, e12{ std::move(_other.e12) }, e22{ std::move(_other.e22) }, e32{ std::move(_other.e32) },
		e03{ std::move(_other.e03) }, e13{ std::move(_other.e13) }, e23{ std::move(_other.e23) }, e33{ std::move(_other.e33) }
	{
	}

	template <typename T>
	constexpr Mat4_Base<T, MatrixMajor::Column>::Mat4_Base(const Mat4_Base<T, MatrixMajor::Row>& _other) noexcept :
		e00{ _other.e00 }, e10{ _other.e10 }, e20{ _other.e20 }, e30{ _other.e30 },
		e01{ _other.e01 }, e11{ _other.e11 }, e21{ _other.e21 }, e31{ _other.e31 },
		e02{ _other.e02 }, e12{ _other.e12 }, e22{ _other.e22 }, e32{ _other.e32 },
		e03{ _other.e03 }, e13{ _other.e13 }, e23{ _other.e23 }, e33{ _other.e33 }
	{
	}

	template <typename T>
	constexpr Mat4_Base<T, MatrixMajor::Column>::Mat4_Base(
		T _e00, T _e01, T _e02, T _e03,
		T _e10, T _e11, T _e12, T _e13,
		T _e20, T _e21, T _e22, T _e23,
		T _e30, T _e31, T _e32, T _e33
	) noexcept :
		e00{ _e00 }, e10{ _e10 }, e20{ _e20 }, e30{ _e30 },
		e01{ _e01 }, e11{ _e11 }, e21{ _e21 }, e31{ _e31 },
		e02{ _e02 }, e12{ _e12 }, e22{ _e22 }, e32{ _e32 },
		e03{ _e03 }, e13{ _e13 }, e23{ _e23 }, e33{ _e33 }
	{
	}


	template <typename T>
	Mat4_Base<T, MatrixMajor::Column>& Mat4_Base<T, MatrixMajor::Column>::operator=(Mat4_Base<T, MatrixMajor::Row>&& _rhs) noexcept
	{
		e00 = std::move(_rhs.e00);
		e10 = std::move(_rhs.e10);
		e20 = std::move(_rhs.e20);
		e30 = std::move(_rhs.e30);

		e01 = std::move(_rhs.e01);
		e11 = std::move(_rhs.e11);
		e21 = std::move(_rhs.e21);
		e31 = std::move(_rhs.e31);

		e02 = std::move(_rhs.e02);
		e12 = std::move(_rhs.e12);
		e22 = std::move(_rhs.e22);
		e32 = std::move(_rhs.e32);

		e03 = std::move(_rhs.e03);
		e13 = std::move(_rhs.e13);
		e23 = std::move(_rhs.e23);
		e33 = std::move(_rhs.e33);

		return *this;
	}

	template <typename T>
	Mat4_Base<T, MatrixMajor::Column>& Mat4_Base<T, MatrixMajor::Column>::operator=(const Mat4_Base<T, MatrixMajor::Row>& _rhs) noexcept
	{
		e00 = _rhs.e00;
		e10 = _rhs.e10;
		e20 = _rhs.e20;
		e30 = _rhs.e30;

		e01 = _rhs.e01;
		e11 = _rhs.e11;
		e12 = _rhs.e12;
		e31 = _rhs.e31;

		e02 = _rhs.e02;
		e21 = _rhs.e21;
		e22 = _rhs.e22;
		e32 = _rhs.e32;

		e03 = _rhs.e03;
		e13 = _rhs.e13;
		e23 = _rhs.e23;
		e33 = _rhs.e33;

		return *this;
	}

//}

	/// \endcond
}
