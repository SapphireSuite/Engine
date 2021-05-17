// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

namespace Sa::Intl
{
	/// \cond Internal

//{ Row Major

//{ Construcors

	template <typename T>
	constexpr Mat3_Base<T, MatrixMajor::Row>::Mat3_Base(
		T _e00, T _e01, T _e02,
		T _e10, T _e11, T _e12,
		T _e20, T _e21, T _e22
	) noexcept :
		e00{ _e00 }, e01{ _e01 }, e02{ _e02 },
		e10{ _e10 }, e11{ _e11 }, e12{ _e12 },
		e20{ _e20 }, e21{ _e21 }, e22{ _e22 }
	{
	}

	template <typename T>
	constexpr Mat3_Base<T, MatrixMajor::Row>::Mat3_Base(Mat3_Base<T, MatrixMajor::Column>&& _other) noexcept :
		e00{ std::move(_other.e00) }, e01{ std::move(_other.e01) }, e02{ std::move(_other.e02) },
		e10{ std::move(_other.e10) }, e11{ std::move(_other.e11) }, e12{ std::move(_other.e12) },
		e20{ std::move(_other.e20) }, e21{ std::move(_other.e21) }, e22{ std::move(_other.e22) }
	{
	}

	template <typename T>
	constexpr Mat3_Base<T, MatrixMajor::Row>::Mat3_Base(const Mat3_Base<T, MatrixMajor::Column>& _other) noexcept :
		e00{ _other.e00 }, e01{ _other.e01 }, e02{ _other.e02 },
		e10{ _other.e10 }, e11{ _other.e11 }, e12{ _other.e12 },
		e20{ _other.e20 }, e21{ _other.e21 }, e22{ _other.e22 }
	{
	}

//}

//{ Operators

	template <typename T>
	Mat3_Base<T, MatrixMajor::Row>& Mat3_Base<T, MatrixMajor::Row>::operator=(Mat3_Base<T, MatrixMajor::Column>&& _rhs) noexcept
	{
		e00 = std::move(_rhs.e00);
		e01 = std::move(_rhs.e01);
		e02 = std::move(_rhs.e02);

		e10 = std::move(_rhs.e10);
		e11 = std::move(_rhs.e11);
		e12 = std::move(_rhs.e12);

		e20 = std::move(_rhs.e20);
		e21 = std::move(_rhs.e21);
		e22 = std::move(_rhs.e22);

		return *this;
	}

	template <typename T>
	Mat3_Base<T, MatrixMajor::Row>& Mat3_Base<T, MatrixMajor::Row>::operator=(const Mat3_Base<T, MatrixMajor::Column>& _rhs) noexcept
	{
		e00 = _rhs.e00;
		e01 = _rhs.e01;
		e02 = _rhs.e02;

		e10 = _rhs.e10;
		e11 = _rhs.e11;
		e12 = _rhs.e12;

		e20 = _rhs.e20;
		e21 = _rhs.e21;
		e22 = _rhs.e22;

		return *this;
	}

//}

//}

//{ Column Major

	template <typename T>
	constexpr Mat3_Base<T, MatrixMajor::Column>::Mat3_Base(
		T _e00, T _e01, T _e02,
		T _e10, T _e11, T _e12,
		T _e20, T _e21, T _e22
	) noexcept :
		e00{ _e00 }, e10{ _e10 }, e20{ _e20 },
		e01{ _e01 }, e11{ _e11 }, e21{ _e21 },
		e02{ _e02 }, e12{ _e12 }, e22{ _e22 }
	{
	}

	template <typename T>
	constexpr Mat3_Base<T, MatrixMajor::Column>::Mat3_Base(Mat3_Base<T, MatrixMajor::Row>&& _other) noexcept :
		e00{ std::move(_other.e00) }, e10{ std::move(_other.e10) }, e20{ std::move(_other.e20) },
		e01{ std::move(_other.e01) }, e11{ std::move(_other.e11) }, e21{ std::move(_other.e21) },
		e02{ std::move(_other.e02) }, e12{ std::move(_other.e12) }, e22{ std::move(_other.e22) }
	{
	}

	template <typename T>
	constexpr Mat3_Base<T, MatrixMajor::Column>::Mat3_Base(const Mat3_Base<T, MatrixMajor::Row>& _other) noexcept :
		e00{ _other.e00 }, e10{ _other.e10 }, e20{ _other.e20 },
		e01{ _other.e01 }, e11{ _other.e11 }, e21{ _other.e21 },
		e02{ _other.e02 }, e12{ _other.e12 }, e22{ _other.e22 }
	{
	}

//}

//{ Operators

	template <typename T>
	Mat3_Base<T, MatrixMajor::Column>& Mat3_Base<T, MatrixMajor::Column>::operator=(Mat3_Base<T, MatrixMajor::Row>&& _rhs) noexcept
	{
		e00 = std::move(_rhs.e00);
		e10 = std::move(_rhs.e10);
		e20 = std::move(_rhs.e20);

		e01 = std::move(_rhs.e01);
		e11 = std::move(_rhs.e11);
		e21 = std::move(_rhs.e21);

		e02 = std::move(_rhs.e02);
		e12 = std::move(_rhs.e12);
		e22 = std::move(_rhs.e22);

		return *this;
	}

	template <typename T>
	Mat3_Base<T, MatrixMajor::Column>& Mat3_Base<T, MatrixMajor::Column>::operator=(const Mat3_Base<T, MatrixMajor::Row>& _rhs) noexcept
	{
		e00 = _rhs.e00;
		e10 = _rhs.e10;
		e20 = _rhs.e20;

		e01 = _rhs.e01;
		e11 = _rhs.e11;
		e12 = _rhs.e12;

		e02 = _rhs.e02;
		e21 = _rhs.e21;
		e22 = _rhs.e22;

		return *this;
	}

//}

//}

	///\endcond
}
