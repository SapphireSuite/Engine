// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#include <Maths/Matrix/Matrix4.hpp>

#include <Maths/Space/Vector3.hpp>
#include <Maths/Space/Vector4.hpp>
#include <Maths/Space/Quaternion.hpp>

namespace Sa
{
#if SA_INTRISC_AVX // SIMD int32

//{ Row Major

	template <>
	RMat4i RMat4i::operator*(int32 _scale) const noexcept
	{
		Mat4 res;
		int32* const fres = res.Data();
		const int32* const data = Data();

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Mult row 0 and 1.
		reinterpret_cast<__m256i&>(fres[0]) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(data[0]), sPack);

		// Mult row 2 and 3.
		reinterpret_cast<__m256i&>(fres[8]) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(data[8]), sPack);

		return res;
	}

#if SA_INTRISC_SVML

	template <>
	RMat4i RMat4i::operator/(int32 _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		Mat4 res;
		int32* const fres = res.Data();
		const int32* const data = Data();

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Div row 0 and 1.
		reinterpret_cast<__m256i&>(fres[0]) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(data[0]), sPack);

		// Div row 2 and 3.
		reinterpret_cast<__m256i&>(fres[8]) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(data[8]), sPack);

		return res;
	}

#endif

	template <>
	RMat4i RMat4i::operator+(const RMat4i& _rhs) const noexcept
	{
		Mat4 res;
		int32* const fres = res.Data();
		const int32* const ldata = Data();
		const int32* const rdata = _rhs.Data();

		// Add row 0 and 1.
		reinterpret_cast<__m256i&>(fres[0]) = 
			_mm256_add_epi32(reinterpret_cast<const __m256i&>(ldata[0]), reinterpret_cast<const __m256i&>(rdata[0]));

		// Add row 2 and 3.
		reinterpret_cast<__m256i&>(fres[8]) = 
			_mm256_add_epi32(reinterpret_cast<const __m256i&>(ldata[8]), reinterpret_cast<const __m256i&>(rdata[8]));

		return res;
	}

	template <>
	RMat4i RMat4i::operator-(const RMat4i& _rhs) const noexcept
	{
		Mat4 res;
		int32* const fres = res.Data();
		const int32* const ldata = Data();
		const int32* const rdata = _rhs.Data();

		// Sub row 0 and 1.
		reinterpret_cast<__m256i&>(fres[0]) = 
			_mm256_sub_epi32(reinterpret_cast<const __m256i&>(ldata[0]), reinterpret_cast<const __m256i&>(rdata[0]));

		// Sub row 2 and 3.
		reinterpret_cast<__m256i&>(fres[8]) = 
			_mm256_sub_epi32(reinterpret_cast<const __m256i&>(ldata[8]), reinterpret_cast<const __m256i&>(rdata[8]));

		return res;
	}

	template <>
	RMat4i RMat4i::operator*(const RMat4i& _rhs) const noexcept
	{
		Mat4 res;
		int32* const data = res.Data();

		const __m256i lp00 = _mm256_set_epi32(e10, e10, e10, e10, e00, e00, e00, e00);
		const __m256i lp01 = _mm256_set_epi32(e30, e30, e30, e30, e20, e20, e20, e20);
		const __m256i lp10 = _mm256_set_epi32(e11, e11, e11, e11, e01, e01, e01, e01);
		const __m256i lp11 = _mm256_set_epi32(e31, e31, e31, e31, e21, e21, e21, e21);
		const __m256i lp20 = _mm256_set_epi32(e12, e12, e12, e12, e02, e02, e02, e02);
		const __m256i lp21 = _mm256_set_epi32(e32, e32, e32, e32, e22, e22, e22, e22);
		const __m256i lp30 = _mm256_set_epi32(e13, e13, e13, e13, e03, e03, e03, e03);
		const __m256i lp31 = _mm256_set_epi32(e33, e33, e33, e33, e23, e23, e23, e23);

		const __m256i rp0 = _mm256_set_epi32(_rhs.e03, _rhs.e02, _rhs.e01, _rhs.e00, _rhs.e03, _rhs.e02, _rhs.e01, _rhs.e00);
		const __m256i rp1 = _mm256_set_epi32(_rhs.e13, _rhs.e12, _rhs.e11, _rhs.e10, _rhs.e13, _rhs.e12, _rhs.e11, _rhs.e10);
		const __m256i rp2 = _mm256_set_epi32(_rhs.e23, _rhs.e22, _rhs.e21, _rhs.e20, _rhs.e23, _rhs.e22, _rhs.e21, _rhs.e20);
		const __m256i rp3 = _mm256_set_epi32(_rhs.e33, _rhs.e32, _rhs.e31, _rhs.e30, _rhs.e33, _rhs.e32, _rhs.e31, _rhs.e30);

		// Row 0 and 1.
		reinterpret_cast<__m256i&>(data[0]) = _mm256_add_epi32(
			_mm256_add_epi32(_mm256_mullo_epi32(lp00, rp0), _mm256_mullo_epi32(lp10, rp1)),
			_mm256_add_epi32(_mm256_mullo_epi32(lp20, rp2), _mm256_mullo_epi32(lp30, rp3))
		);

		// Row 2 and 3.
		reinterpret_cast<__m256i&>(data[8]) = _mm256_add_epi32(
			_mm256_add_epi32(_mm256_mullo_epi32(lp01, rp0), _mm256_mullo_epi32(lp11, rp1)),
			_mm256_add_epi32(_mm256_mullo_epi32(lp21, rp2), _mm256_mullo_epi32(lp31, rp3))
		);

		return res;
	}


	template <>
	Vec3<int32> RMat4i::operator*(const Vec3<int32>& _rhs) const noexcept
	{
		// Compute first 8 elems.
		const __m256i p0 = _mm256_set_epi32(e12, e02, e21, e11, e01, e20, e10, e00);
		const __m256i pScale = _mm256_set_epi32(_rhs.z, _rhs.z, _rhs.y, _rhs.y, _rhs.y, _rhs.x, _rhs.x, _rhs.x);

		const __m256i pTotal = _mm256_mullo_epi32(pScale, p0);
		const int32* const ires = reinterpret_cast<const int32*>(&pTotal);

		return Vec3i(
			ires[0] + ires[3] + ires[6],
			ires[1] + ires[4] + ires[7],
			ires[2] + ires[5] + e22 * _rhs.z
		);
	}

	template <>
	Vec4<int32> RMat4i::operator*(const Vec4<int32>& _rhs) const noexcept
	{
		const __m256i pScaleXY = _mm256_set_epi32(_rhs.y, _rhs.y, _rhs.y, _rhs.y, _rhs.x, _rhs.x, _rhs.x, _rhs.x);
		const __m256i pScaleZW = _mm256_set_epi32(_rhs.w, _rhs.w, _rhs.w, _rhs.w, _rhs.z, _rhs.z, _rhs.z, _rhs.z);

		const __m256i p01 = _mm256_mullo_epi32(_mm256_set_epi32(e31, e21, e11, e01, e30, e20, e10, e00), pScaleXY);
		const __m256i p23 = _mm256_mullo_epi32(_mm256_set_epi32(e33, e23, e13, e03, e32, e22, e12, e02), pScaleZW);

		const __m256i pTotal = _mm256_add_epi32(p01, p23);
		const __m128i* const p128Total = reinterpret_cast<const __m128i*>(&pTotal);

		Vec4i res;

		reinterpret_cast<__m128i&>(res) = _mm_add_epi32(p128Total[0], p128Total[1]);

		return res;
	}


	template <>
	RMat4i& RMat4i::operator*=(int32 _scale) noexcept
	{
		int32* const data = Data();

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Mult row 0 and 1.
		reinterpret_cast<__m256i&>(data[0]) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(data[0]), sPack);

		// Mult row 2 and 3.
		reinterpret_cast<__m256i&>(data[8]) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(data[8]), sPack);

		return *this;
	}

#if SA_INTRISC_SVML

	template <>
	RMat4i& RMat4i::operator/=(int32 _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		int32* const data = Data();

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Div row 0 and 1.
		reinterpret_cast<__m256i&>(data[0]) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(data[0]), sPack);

		// Div row 2 and 3.
		reinterpret_cast<__m256i&>(data[8]) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(data[8]), sPack);

		return *this;
	}

#endif

	template <>
	RMat4i& RMat4i::operator+=(const RMat4i& _rhs) noexcept
	{
		int32* const ldata = Data();
		const int32* const rdata = _rhs.Data();

		// Add row 0 and 1.
		reinterpret_cast<__m256i&>(ldata[0]) =
			_mm256_add_epi32(reinterpret_cast<const __m256i&>(ldata[0]), reinterpret_cast<const __m256i&>(rdata[0]));

		// Add row 2 and 3.
		reinterpret_cast<__m256i&>(ldata[8]) =
			_mm256_add_epi32(reinterpret_cast<const __m256i&>(ldata[8]), reinterpret_cast<const __m256i&>(rdata[8]));

		return *this;
	}

	template <>
	RMat4i& RMat4i::operator-=(const RMat4i& _rhs) noexcept
	{
		int32* const ldata = Data();
		const int32* const rdata = _rhs.Data();

		// Sub row 0 and 1.
		reinterpret_cast<__m256i&>(ldata[0]) =
			_mm256_sub_epi32(reinterpret_cast<const __m256i&>(ldata[0]), reinterpret_cast<const __m256i&>(rdata[0]));

		// Sub row 2 and 3.
		reinterpret_cast<__m256i&>(ldata[8]) =
			_mm256_sub_epi32(reinterpret_cast<const __m256i&>(ldata[8]), reinterpret_cast<const __m256i&>(rdata[8]));

		return *this;
	}
//}

//{ Column Major

	template <>
	CMat4i CMat4i::operator*(int32 _scale) const noexcept
	{
		Mat4 res;
		int32* const fres = res.Data();
		const int32* const data = Data();

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Mult row 0 and 1.
		reinterpret_cast<__m256i&>(fres[0]) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(data[0]), sPack);

		// Mult row 2 and 3.
		reinterpret_cast<__m256i&>(fres[8]) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(data[8]), sPack);

		return res;
	}

#if SA_INTRISC_SVML

	template <>
	CMat4i CMat4i::operator/(int32 _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		Mat4 res;
		int32* const fres = res.Data();
		const int32* const data = Data();

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Div row 0 and 1.
		reinterpret_cast<__m256i&>(fres[0]) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(data[0]), sPack);

		// Div row 2 and 3.
		reinterpret_cast<__m256i&>(fres[8]) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(data[8]), sPack);

		return res;
	}

#endif

	template <>
	CMat4i CMat4i::operator+(const CMat4i& _rhs) const noexcept
	{
		Mat4 res;
		int32* const fres = res.Data();
		const int32* const ldata = Data();
		const int32* const rdata = _rhs.Data();

		// Add row 0 and 1.
		reinterpret_cast<__m256i&>(fres[0]) =
			_mm256_add_epi32(reinterpret_cast<const __m256i&>(ldata[0]), reinterpret_cast<const __m256i&>(rdata[0]));

		// Add row 2 and 3.
		reinterpret_cast<__m256i&>(fres[8]) =
			_mm256_add_epi32(reinterpret_cast<const __m256i&>(ldata[8]), reinterpret_cast<const __m256i&>(rdata[8]));

		return res;
	}

	template <>
	CMat4i CMat4i::operator-(const CMat4i& _rhs) const noexcept
	{
		Mat4 res;
		int32* const fres = res.Data();
		const int32* const ldata = Data();
		const int32* const rdata = _rhs.Data();

		// Sub row 0 and 1.
		reinterpret_cast<__m256i&>(fres[0]) =
			_mm256_sub_epi32(reinterpret_cast<const __m256i&>(ldata[0]), reinterpret_cast<const __m256i&>(rdata[0]));

		// Sub row 2 and 3.
		reinterpret_cast<__m256i&>(fres[8]) =
			_mm256_sub_epi32(reinterpret_cast<const __m256i&>(ldata[8]), reinterpret_cast<const __m256i&>(rdata[8]));

		return res;
	}

	template <>
	CMat4i CMat4i::operator*(const CMat4i& _rhs) const noexcept
	{
		Mat4 res;
		int32* const data = res.Data();

		const __m256i rp00 = _mm256_set_epi32(_rhs.e01, _rhs.e01, _rhs.e01, _rhs.e01, _rhs.e00, _rhs.e00, _rhs.e00, _rhs.e00);
		const __m256i rp01 = _mm256_set_epi32(_rhs.e03, _rhs.e03, _rhs.e03, _rhs.e03, _rhs.e02, _rhs.e02, _rhs.e02, _rhs.e02);
		const __m256i rp10 = _mm256_set_epi32(_rhs.e11, _rhs.e11, _rhs.e11, _rhs.e11, _rhs.e10, _rhs.e10, _rhs.e10, _rhs.e10);
		const __m256i rp11 = _mm256_set_epi32(_rhs.e13, _rhs.e13, _rhs.e13, _rhs.e13, _rhs.e12, _rhs.e12, _rhs.e12, _rhs.e12);
		const __m256i rp20 = _mm256_set_epi32(_rhs.e21, _rhs.e21, _rhs.e21, _rhs.e21, _rhs.e20, _rhs.e20, _rhs.e20, _rhs.e20);
		const __m256i rp21 = _mm256_set_epi32(_rhs.e23, _rhs.e23, _rhs.e23, _rhs.e23, _rhs.e22, _rhs.e22, _rhs.e22, _rhs.e22);
		const __m256i rp30 = _mm256_set_epi32(_rhs.e31, _rhs.e31, _rhs.e31, _rhs.e31, _rhs.e30, _rhs.e30, _rhs.e30, _rhs.e30);
		const __m256i rp31 = _mm256_set_epi32(_rhs.e33, _rhs.e33, _rhs.e33, _rhs.e33, _rhs.e32, _rhs.e32, _rhs.e32, _rhs.e32);

		const __m256i lp0 = _mm256_set_epi32(e30, e20, e10, e00, e30, e20, e10, e00);
		const __m256i lp1 = _mm256_set_epi32(e31, e21, e11, e01, e31, e21, e11, e01);
		const __m256i lp2 = _mm256_set_epi32(e32, e22, e12, e02, e32, e22, e12, e02);
		const __m256i lp3 = _mm256_set_epi32(e33, e23, e13, e03, e33, e23, e13, e03);

		// Row 0 and 1.
		reinterpret_cast<__m256i&>(data[0]) = _mm256_add_epi32(
			_mm256_add_epi32(_mm256_mullo_epi32(rp00, lp0), _mm256_mullo_epi32(rp10, lp1)),
			_mm256_add_epi32(_mm256_mullo_epi32(rp20, lp2), _mm256_mullo_epi32(rp30, lp3))
		);

		// Row 2 and 3.
		reinterpret_cast<__m256i&>(data[8]) = _mm256_add_epi32(
			_mm256_add_epi32(_mm256_mullo_epi32(rp01, lp0), _mm256_mullo_epi32(rp11, lp1)),
			_mm256_add_epi32(_mm256_mullo_epi32(rp21, lp2), _mm256_mullo_epi32(rp31, lp3))
		);

		return res;
	}


	template <>
	Vec3<int32> CMat4i::operator*(const Vec3<int32>& _rhs) const noexcept
	{
		// Compute first 8 elems.
		const __m256i p0 = _mm256_set_epi32(e12, e02, e21, e11, e01, e20, e10, e00);
		const __m256i pScale = _mm256_set_epi32(_rhs.z, _rhs.z, _rhs.y, _rhs.y, _rhs.y, _rhs.x, _rhs.x, _rhs.x);

		const __m256i pTotal = _mm256_mullo_epi32(pScale, p0);
		const int32* const ires = reinterpret_cast<const int32*>(&pTotal);

		return Vec3i(
			ires[0] + ires[3] + ires[6],
			ires[1] + ires[4] + ires[7],
			ires[2] + ires[5] + e22 * _rhs.z
		);
	}

	template <>
	Vec4<int32> CMat4i::operator*(const Vec4<int32>& _rhs) const noexcept
	{
		const __m256i pScaleXY = _mm256_set_epi32(_rhs.y, _rhs.y, _rhs.y, _rhs.y, _rhs.x, _rhs.x, _rhs.x, _rhs.x);
		const __m256i pScaleZW = _mm256_set_epi32(_rhs.w, _rhs.w, _rhs.w, _rhs.w, _rhs.z, _rhs.z, _rhs.z, _rhs.z);

		const __m256i p01 = _mm256_mullo_epi32(_mm256_set_epi32(e31, e21, e11, e01, e30, e20, e10, e00), pScaleXY);
		const __m256i p23 = _mm256_mullo_epi32(_mm256_set_epi32(e33, e23, e13, e03, e32, e22, e12, e02), pScaleZW);

		const __m256i pTotal = _mm256_add_epi32(p01, p23);
		const __m128i* const p128Total = reinterpret_cast<const __m128i*>(&pTotal);

		Vec4i res;

		reinterpret_cast<__m128i&>(res) = _mm_add_epi32(p128Total[0], p128Total[1]);

		return res;
	}


	template <>
	CMat4i& CMat4i::operator*=(int32 _scale) noexcept
	{
		int32* const data = Data();

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Mult row 0 and 1.
		reinterpret_cast<__m256i&>(data[0]) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(data[0]), sPack);

		// Mult row 2 and 3.
		reinterpret_cast<__m256i&>(data[8]) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(data[8]), sPack);

		return *this;
	}

#if SA_INTRISC_SVML

	template <>
	CMat4i& CMat4i::operator/=(int32 _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		int32* const data = Data();

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Div row 0 and 1.
		reinterpret_cast<__m256i&>(data[0]) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(data[0]), sPack);

		// Div row 2 and 3.
		reinterpret_cast<__m256i&>(data[8]) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(data[8]), sPack);

		return *this;
	}

#endif

	template <>
	CMat4i& CMat4i::operator+=(const CMat4i& _rhs) noexcept
	{
		int32* const ldata = Data();
		const int32* const rdata = _rhs.Data();

		// Add row 0 and 1.
		reinterpret_cast<__m256i&>(ldata[0]) =
			_mm256_add_epi32(reinterpret_cast<const __m256i&>(ldata[0]), reinterpret_cast<const __m256i&>(rdata[0]));

		// Add row 2 and 3.
		reinterpret_cast<__m256i&>(ldata[8]) =
			_mm256_add_epi32(reinterpret_cast<const __m256i&>(ldata[8]), reinterpret_cast<const __m256i&>(rdata[8]));

		return *this;
	}

	template <>
	CMat4i& CMat4i::operator-=(const CMat4i& _rhs) noexcept
	{
		int32* const ldata = Data();
		const int32* const rdata = _rhs.Data();

		// Sub row 0 and 1.
		reinterpret_cast<__m256i&>(ldata[0]) =
			_mm256_sub_epi32(reinterpret_cast<const __m256i&>(ldata[0]), reinterpret_cast<const __m256i&>(rdata[0]));

		// Sub row 2 and 3.
		reinterpret_cast<__m256i&>(ldata[8]) =
			_mm256_sub_epi32(reinterpret_cast<const __m256i&>(ldata[8]), reinterpret_cast<const __m256i&>(rdata[8]));

		return *this;
	}

//}

#endif

#if SA_INTRISC_SSE // SIMD float

//{ Row Major

	template <>
	float RMat4f::Determinant() const noexcept
	{
		/*
			return
				(+) e00 * 	e11 * (e22 * e33 - e23 * e32)
				(-) e00 * 	e21 * (e12 * e33 - e13 * e32)
				(+) e00 * 	e31 * (e12 * e23 - e13 * e22)
				(-) e10 * 	e01 * (e22 * e33 - e23 * e32)
				(+) e10 * 	e21 * (e02 * e33 - e03 * e32)
				(-) e10 * 	e31 * (e02 * e23 - e03 * e22)
				(+) e20 * 	e01 * (e12 * e33 - e13 * e32)
				(-) e20 * 	e11 * (e02 * e33 - e03 * e32)

				(+) e20 * 	e31 * (e02 * e13 - e03 * e12)
				(-) e30 * 	e01 * (e12 * e23 - e13 * e22)
				(+) e30 * 	e11 * (e02 * e23 - e03 * e22)
				(-) e30 * 	e21 * (e02 * e13 - e03 * e12);
		*/

		const __m256 p0 = _mm256_set_ps(-e20, e20, -e10, e10, -e10, e00, -e00, e00);
		const __m256 p1 = _mm256_set_ps(e11, e01, e31, e21, e01, e31, e21, e11);
		const __m256 p2 = _mm256_set_ps(e02, e12, e02, e02, e22, e12, e12, e22);
		const __m256 p3 = _mm256_set_ps(e33, e33, e23, e33, e33, e23, e33, e33);
		const __m256 p4 = _mm256_set_ps(e03, e13, e03, e03, e23, e13, e13, e23);
		const __m256 p5 = _mm256_set_ps(e32, e32, e22, e32, e32, e22, e32, e32);

		const __m256 p12345 = _mm256_mul_ps(p0, _mm256_mul_ps(p1, _mm256_sub_ps(_mm256_mul_ps(p2, p3), _mm256_mul_ps(p4, p5))));


		const __m256 p0_1 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, -e30, e30, -e30, e20);
		const __m256 p6 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, e21, e11, e01, e31);
		const __m256 p7 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, e02, e02, e12, e02);
		const __m256 p8 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, e13, e23, e23, e13);
		const __m256 p9 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, e03, e03, e13, e03);
		const __m256 p10 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, e12, e22, e22, e12);

		const __m256 p678910 = _mm256_mul_ps(p0_1, _mm256_mul_ps(p6, _mm256_sub_ps(_mm256_mul_ps(p7, p8), _mm256_mul_ps(p9, p10))));


		const __m256 pTotal = _mm256_add_ps(p12345, p678910);
		const float* const fres = reinterpret_cast<const float*>(&pTotal);

		return fres[0] + fres[1] + fres[2] + fres[3] + fres[4] + fres[5] + fres[6] + fres[7];
	}

	template <>
	RMat4f RMat4f::GetInversed() const noexcept
	{
		Mat4 res;
		float* const data = res.Data();
		const float det = Determinant();

		SA_WARN(!Sa::Equals0(det), Maths, L"Inverse matrix with determinant == 0");

		const float invDet = 1.0f / det;
		const __m256 invDetP = _mm256_set1_ps(invDet);


//{ Row 0
		/*
			e00 =
				(+) e11 * e22 * e33
				(-) e11 * e23 * e32
				(-) e21 * e12 * e33
				(+) e21 * e13 * e32
				(+) e31 * e12 * e23
				(-) e31 * e13 * e22

			e01 =
				(-) e01 * e22 * e33
				(+) e01 * e23 * e32
				(+) e21 * e02 * e33
				(-) e21 * e03 * e32
				(-) e31 * e02 * e23
				(+) e31 * e03 * e22

			e02 =
				(+) e01 * e12 * e33
				(-) e01 * e13 * e32
				(-) e11 * e02 * e33
				(+) e11 * e03 * e32
				(+) e31 * e02 * e13
				(-) e31 * e03 * e12

			e03 =
				(-) e01 * e12 * e23
				(+) e01 * e13 * e22
				(+) e11 * e02 * e23
				(-) e11 * e03 * e22
				(-) e21 * e02 * e13
				(+) e21 * e03 * e12

			4 (elems) * 6 (add/sub) = 24 = 3 (packs) * 8 (float).
		*/
		const __m256 r0p1 = _mm256_set_ps(e01, -e01, -e31, e31, e21, -e21, -e11, e11);
		const __m256 r0p2 = _mm256_set_ps(e23, e22, e13, e12, e13, e12, e23, e22);
		const __m256 r0p3 = _mm256_set_ps(e32, e33, e22, e23, e32, e33, e32, e33);
		const __m256 r0p123 = _mm256_mul_ps(_mm256_mul_ps(r0p1, r0p2), r0p3);
		const float* const r0f123 = reinterpret_cast<const float*>(&r0p123);

		const __m256 r0p4 = _mm256_set_ps(e11, -e11, -e01, e01, e31, -e31, -e21, e21);
		const __m256 r0p5 = _mm256_set_ps(e03, e02, e13, e12, e03, e02, e03, e02);
		const __m256 r0p6 = _mm256_set_ps(e32, e33, e32, e33, e22, e23, e32, e33);
		const __m256 r0p456 = _mm256_mul_ps(_mm256_mul_ps(r0p4, r0p5), r0p6);
		const float* const r0f456 = reinterpret_cast<const float*>(&r0p456);

		const __m256 r0p7 = _mm256_set_ps(e21, -e21, -e11, e11, e01, -e01, -e31, e31);
		const __m256 r0p8 = _mm256_set_ps(e03, e02, e03, e02, e13, e12, e03, e02);
		const __m256 r0p9 = _mm256_set_ps(e12, e13, e22, e23, e22, e23, e12, e13);
		const __m256 r0p789 = _mm256_mul_ps(_mm256_mul_ps(r0p7, r0p8), r0p9);
		const float* const r0f789 = reinterpret_cast<const float*>(&r0p789);


		// Fill elems.
		//res.e00 = r0f123[0] + r0f123[1] + r0f123[2] + r0f123[3] + r0f123[4] + r0f123[5];
		//res.e01 = r0f123[6] + r0f123[7] + r0f456[0] + r0f456[1] + r0f456[2] + r0f456[3];
		//res.e02 = r0f456[4] + r0f456[5] + r0f456[6] + r0f456[7] + r0f789[0] + r0f789[1];
		//res.e03 = r0f789[2] + r0f789[3] + r0f789[4] + r0f789[5] + r0f789[6] + r0f789[7];

		const __m128 r0rp1 = _mm_set_ps(r0f789[2], r0f456[4], r0f123[6], r0f123[0]);
		const __m128 r0rp2 = _mm_set_ps(r0f789[3], r0f456[5], r0f123[7], r0f123[1]);
		const __m128 r0rp3 = _mm_set_ps(r0f789[4], r0f456[6], r0f456[0], r0f123[2]);
		const __m128 r0rp4 = _mm_set_ps(r0f789[5], r0f456[7], r0f456[1], r0f123[3]);
		const __m128 r0rp5 = _mm_set_ps(r0f789[6], r0f789[0], r0f456[2], r0f123[4]);
		const __m128 r0rp6 = _mm_set_ps(r0f789[7], r0f789[1], r0f456[3], r0f123[5]);

		reinterpret_cast<__m128&>(data[0]) = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(r0rp1, r0rp2), r0rp3), r0rp4), r0rp5), r0rp6);
//}

//{ Row 1
		/*
			e10 =
				(-) e10 * e22 * e33
				(+) e10 * e23 * e32
				(+) e20 * e12 * e33
				(-) e20 * e13 * e32
				(-) e30 * e12 * e23
				(+) e30 * e13 * e22

			e11 =
				(+) e00 * e22 * e33
				(-) e00 * e23 * e32
				(-) e20 * e02 * e33
				(+) e20 * e03 * e32
				(+) e30 * e02 * e23
				(-) e30 * e03 * e22

			e12 =
				(-) e00 * e12 * e33
				(+) e00 * e13 * e32
				(+) e10 * e02 * e33
				(-) e10 * e03 * e32
				(-) e30 * e02 * e13
				(+) e30 * e03 * e12

			e13 =
				(+) e00 * e12 * e23
				(-) e00 * e13 * e22
				(-) e10 * e02 * e23
				(+) e10 * e03 * e22
				(+) e20 * e02 * e13
				(-) e20 * e03 * e12

			4 (elems) * 6 (add/sub) = 24 = 3 (packs) * 8 (float).
		*/
		const __m256 r1p1 = _mm256_set_ps(-e00, e00, e30, -e30, -e20, e20, e10, -e10);
		// r1p2 == r0p2
		// r1p3 == r0p3
		const __m256 r1p123 = _mm256_mul_ps(_mm256_mul_ps(r1p1, r0p2), r0p3);
		const float* const r1f123 = reinterpret_cast<const float*>(&r1p123);

		const __m256 r1p4 = _mm256_set_ps(-e10, e10, e00, -e00, -e30, e30, e20, -e20);
		// r1p5 == r0p5
		// r1p6 == r0p6
		const __m256 r1p456 = _mm256_mul_ps(_mm256_mul_ps(r1p4, r0p5), r0p6);
		const float* const r1f456 = reinterpret_cast<const float*>(&r1p456);

		const __m256 r1p7 = _mm256_set_ps(-e20, e20, e10, -e10, -e00, e00, e30, -e30);
		// r1p8 == r0p8
		// r1p9 == r0p9
		const __m256 r1p789 = _mm256_mul_ps(_mm256_mul_ps(r1p7, r0p8), r0p9);
		const float* const r1f789 = reinterpret_cast<const float*>(&r1p789);


		// Fill elems.
		//res.e10 = r1f123[0] + r1f123[1] + r1f123[2] + r1f123[3] + r1f123[4] + r1f123[5];
		//res.e11 = r1f123[6] + r1f123[7] + r1f456[0] + r1f456[1] + r1f456[2] + r1f456[3];
		//res.e12 = r1f456[4] + r1f456[5] + r1f456[6] + r1f456[7] + r1f789[0] + r1f789[1];
		//res.e13 = r1f789[2] + r1f789[3] + r1f789[4] + r1f789[5] + r1f789[6] + r1f789[7];

		const __m128 r1rp1 = _mm_set_ps(r1f789[2], r1f456[4], r1f123[6], r1f123[0]);
		const __m128 r1rp2 = _mm_set_ps(r1f789[3], r1f456[5], r1f123[7], r1f123[1]);
		const __m128 r1rp3 = _mm_set_ps(r1f789[4], r1f456[6], r1f456[0], r1f123[2]);
		const __m128 r1rp4 = _mm_set_ps(r1f789[5], r1f456[7], r1f456[1], r1f123[3]);
		const __m128 r1rp5 = _mm_set_ps(r1f789[6], r1f789[0], r1f456[2], r1f123[4]);
		const __m128 r1rp6 = _mm_set_ps(r1f789[7], r1f789[1], r1f456[3], r1f123[5]);

		reinterpret_cast<__m128&>(data[4]) = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(r1rp1, r1rp2), r1rp3), r1rp4), r1rp5), r1rp6);
//}

//{ Row 2
		/*
			e20 =
				(+) e10 * e21 * e33
				(-) e10 * e23 * e31
				(-) e20 * e11 * e33
				(+) e20 * e13 * e31
				(+) e30 * e11 * e23
				(-) e30 * e13 * e21

			e21 =
				(-) e00 * e21 * e33
				(+) e00 * e23 * e31
				(+) e20 * e01 * e33
				(-) e20 * e03 * e31
				(-) e30 * e01 * e23
				(+) e30 * e03 * e21

			e22 =
				(+) e00 * e11 * e33
				(-) e00 * e13 * e31
				(-) e10 * e01 * e33
				(+) e10 * e03 * e31
				(+) e30 * e01 * e13
				(-) e30 * e03 * e11

			e23 =
				(-) e00 * e11 * e23
				(+) e00 * e13 * e21
				(+) e10 * e01 * e23
				(-) e10 * e03 * e21
				(-) e20 * e01 * e13
				(+) e20 * e03 * e11

			4 (elems) * 6 (add/sub) = 24 = 3 (packs) * 8 (float).

			// Use row 1 pack and inverse all sign in second column (p2, p5, p8)
		*/
		// r2p1 = -r1p1
		const __m256 r2p2 = _mm256_set_ps(-e23, -e21, -e13, -e11, -e13, -e11, -e23, -e21);
		const __m256 r2p3 = _mm256_set_ps(e31, e33, e21, e23, e31, e33, e31, e33);
		const __m256 r2p123 = _mm256_mul_ps(_mm256_mul_ps(r1p1, r2p2), r2p3);
		const float* const r2f123 = reinterpret_cast<const float*>(&r2p123);

		// r2p4 = -r1p4
		const __m256 r2p5 = _mm256_set_ps(-e03, -e01, -e13, -e11, -e03, -e01, -e03, -e01);
		const __m256 r2p6 = _mm256_set_ps(e31, e33, e31, e33, e21, e23, e31, e33);
		const __m256 r2p456 = _mm256_mul_ps(_mm256_mul_ps(r1p4, r2p5), r2p6);
		const float* const r2f456 = reinterpret_cast<const float*>(&r2p456);

		// r2p7 = -r1p7
		const __m256 r2p8 = _mm256_set_ps(-e03, -e01, -e03, -e01, -e13, -e11, -e03, -e01);
		const __m256 r2p9 = _mm256_set_ps(e11, e13, e21, e23, e21, e23, e11, e13);
		const __m256 r2p789 = _mm256_mul_ps(_mm256_mul_ps(r1p7, r2p8), r2p9);
		const float* const r2f789 = reinterpret_cast<const float*>(&r2p789);


		// Fill elems.
		//res.e20 = r2f123[0] + r2f123[1] + r2f123[2] + r2f123[3] + r2f123[4] + r2f123[5];
		//res.e21 = r2f123[6] + r2f123[7] + r2f456[0] + r2f456[1] + r2f456[2] + r2f456[3];
		//res.e22 = r2f456[4] + r2f456[5] + r2f456[6] + r2f456[7] + r2f789[0] + r2f789[1];
		//res.e23 = r2f789[2] + r2f789[3] + r2f789[4] + r2f789[5] + r2f789[6] + r2f789[7];

		const __m128 r2rp1 = _mm_set_ps(r2f789[2], r2f456[4], r2f123[6], r2f123[0]);
		const __m128 r2rp2 = _mm_set_ps(r2f789[3], r2f456[5], r2f123[7], r2f123[1]);
		const __m128 r2rp3 = _mm_set_ps(r2f789[4], r2f456[6], r2f456[0], r2f123[2]);
		const __m128 r2rp4 = _mm_set_ps(r2f789[5], r2f456[7], r2f456[1], r2f123[3]);
		const __m128 r2rp5 = _mm_set_ps(r2f789[6], r2f789[0], r2f456[2], r2f123[4]);
		const __m128 r2rp6 = _mm_set_ps(r2f789[7], r2f789[1], r2f456[3], r2f123[5]);

		reinterpret_cast<__m128&>(data[8]) = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(r2rp1, r2rp2), r2rp3), r2rp4), r2rp5), r2rp6);
//}

//{ Row 3
		/*
			e30 =
				(-) e10 * e21 * e32
				(+) e10 * e22 * e31
				(+) e20 * e11 * e32
				(-) e20 * e12 * e31
				(-) e30 * e11 * e22
				(+) e30 * e12 * e21

			e31 =
				(+) e00 * e21 * e32
				(-) e00 * e22 * e31
				(-) e20 * e01 * e32
				(+) e20 * e02 * e31
				(+) e30 * e01 * e22
				(-) e30 * e02 * e21

			e32 =
				(-) e00 * e11 * e32
				(+) e00 * e12 * e31
				(+) e10 * e01 * e32
				(-) e10 * e02 * e31
				(-) e30 * e01 * e12
				(+) e30 * e02 * e11

			e33 =
				(+) e00 * e11 * e22
				(-) e00 * e12 * e21
				(-) e10 * e01 * e22
				(+) e10 * e02 * e21
				(+) e20 * e01 * e12
				(-) e20 * e02 * e11

			4 (elems) * 6 (add/sub) = 24 = 3 (packs) * 8 (float).
		*/
		// r3p1 = r1p1
		const __m256 r3p2 = _mm256_set_ps(e22, e21, e12, e11, e12, e11, e22, e21);
		const __m256 r3p3 = _mm256_set_ps(e31, e32, e21, e22, e31, e32, e31, e32);
		const __m256 r3p123 = _mm256_mul_ps(_mm256_mul_ps(r1p1, r3p2), r3p3);
		const float* const r3f123 = reinterpret_cast<const float*>(&r3p123);

		// r3p4 = r1p4
		const __m256 r3p5 = _mm256_set_ps(e02, e01, e12, e11, e02, e01, e02, e01);
		const __m256 r3p6 = _mm256_set_ps(e31, e32, e31, e32, e21, e22, e31, e32);
		const __m256 r3p456 = _mm256_mul_ps(_mm256_mul_ps(r1p4, r3p5), r3p6);
		const float* const r3f456 = reinterpret_cast<const float*>(&r3p456);

		// r3p7 = r1p7
		const __m256 r3p8 = _mm256_set_ps(e02, e01, e02, e01, e12, e11, e02, e01);
		const __m256 r3p9 = _mm256_set_ps(e11, e12, e21, e22, e21, e22, e11, e12);
		const __m256 r3p789 = _mm256_mul_ps(_mm256_mul_ps(r1p7, r3p8), r3p9);
		const float* const r3f789 = reinterpret_cast<const float*>(&r3p789);


		// Fill elems.
		//res.e20 = r3f123[0] + r3f123[1] + r3f123[2] + r3f123[3] + r3f123[4] + r3f123[5];
		//res.e21 = r3f123[6] + r3f123[7] + r3f456[0] + r3f456[1] + r3f456[2] + r3f456[3];
		//res.e22 = r3f456[4] + r3f456[5] + r3f456[6] + r3f456[7] + r3f789[0] + r3f789[1];
		//res.e23 = r3f789[2] + r3f789[3] + r3f789[4] + r3f789[5] + r3f789[6] + r3f789[7];

		const __m128 r3rp1 = _mm_set_ps(r3f789[2], r3f456[4], r3f123[6], r3f123[0]);
		const __m128 r3rp2 = _mm_set_ps(r3f789[3], r3f456[5], r3f123[7], r3f123[1]);
		const __m128 r3rp3 = _mm_set_ps(r3f789[4], r3f456[6], r3f456[0], r3f123[2]);
		const __m128 r3rp4 = _mm_set_ps(r3f789[5], r3f456[7], r3f456[1], r3f123[3]);
		const __m128 r3rp5 = _mm_set_ps(r3f789[6], r3f789[0], r3f456[2], r3f123[4]);
		const __m128 r3rp6 = _mm_set_ps(r3f789[7], r3f789[1], r3f456[3], r3f123[5]);

		reinterpret_cast<__m128&>(data[12]) = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(r3rp1, r3rp2), r3rp3), r3rp4), r3rp5), r3rp6);
//}

		// Apply inv det
		reinterpret_cast<__m256&>(data[0]) = _mm256_mul_ps(invDetP, reinterpret_cast<const __m256&>(data[0]));
		reinterpret_cast<__m256&>(data[8]) = _mm256_mul_ps(invDetP, reinterpret_cast<const __m256&>(data[8]));

		return res;
	}

	
	template <>
	RMat4f& RMat4f::ApplyScale(const Vec3<float>& _scale) noexcept
	{
		float* const data = Data();

		// Compute row 01
		const __m256 pScaleXY = _mm256_set_ps(_scale.y, _scale.y, _scale.y, _scale.y, _scale.x, _scale.x, _scale.x, _scale.x);

		reinterpret_cast<__m256&>(data[0]) = _mm256_mul_ps(pScaleXY, _mm256_load_ps(&data[0]));


		// Compute row 2
		const __m128 pScaleZ = _mm_set1_ps(_scale.z);

		reinterpret_cast<__m128&>(data[8]) = _mm_mul_ps(pScaleZ, _mm_load_ps(&data[8]));

		return *this;
	}

	
	template <>
	RMat4f RMat4f::MakeRotation(const Quat<float>& _rot) noexcept
	{
		SA_WARN(_rot.IsNormalized(), Maths, L"Quaternion should be normalized!");

		/*
			return Mat3f(
				1.0f -	2.0f * (_rot.y * _rot.y + _rot.z * _rot.z),
						2.0f * (_rot.x * _rot.y - _rot.z * _rot.w),
						2.0f * (_rot.x * _rot.z + _rot.y * _rot.w),

						2.0f * (_rot.x * _rot.y + _rot.z * _rot.w),
				1.0f -	2.0f * (_rot.x * _rot.x + _rot.z * _rot.z),
						2.0f * (_rot.y * _rot.z - _rot.x * _rot.w),

						2.0f * (_rot.x * _rot.z - _rot.y * _rot.w),
						2.0f * (_rot.y * _rot.z + _rot.x * _rot.w),
				1.0f -	2.0f * (_rot.x * _rot.x + _rot.y * _rot.y)
			);
		*/

		const __m256 pDbl = _mm256_set1_ps(2.0);

		// 8 first elems.
		const __m256 p1 = _mm256_set_ps(_rot.y, _rot.x, _rot.y, _rot.x, _rot.x, _rot.x, _rot.x, _rot.y);
		const __m256 p2 = _mm256_set_ps(_rot.z, _rot.z, _rot.z, _rot.x, _rot.y, _rot.z, _rot.y, _rot.y);
		const __m256 p3 = _mm256_set_ps(_rot.x, -_rot.y, -_rot.x, _rot.z, _rot.z, _rot.y, -_rot.z, _rot.z);
		const __m256 p4 = _mm256_set_ps(_rot.w, _rot.w, _rot.w, _rot.z, _rot.w, _rot.w, _rot.w, _rot.z);

		__m256 p1234 = _mm256_mul_ps(pDbl, _mm256_add_ps(_mm256_mul_ps(p1, p2), _mm256_mul_ps(p3, p4)));
		float* const f1234 = reinterpret_cast<float*>(&p1234);

		// Apply 1.0f - value.
		f1234[0] = 1.0f - f1234[0];
		f1234[4] = 1.0f - f1234[4];


		// Last elem.
		float e22 = 1.0f - 2.0f * (_rot.x * _rot.x + _rot.y * _rot.y);


		return Mat4(
			f1234[0], f1234[1], f1234[2], 0.0f,
			f1234[3], f1234[4], f1234[5], 0.0f,
			f1234[6], f1234[7], e22, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	template <>
	RMat4f RMat4f::operator*(float _scale) const noexcept
	{
		Mat4 res;
		float* const fres = res.Data();
		const float* const data = Data();

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Mult row 0 and 1.
		reinterpret_cast<__m256&>(fres[0]) = _mm256_mul_ps(_mm256_load_ps(&data[0]), sPack);

		// Mult row 2 and 3.
		reinterpret_cast<__m256&>(fres[8]) = _mm256_mul_ps(_mm256_load_ps(&data[8]), sPack);

		return res;
	}

	template <>
	RMat4f RMat4f::operator/(float _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), L"Unscale matrix by 0 (division by 0)!");

		Mat4 res;
		float* const fres = res.Data();
		const float* const data = Data();

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Div row 0 and 1.
		reinterpret_cast<__m256&>(fres[0]) = _mm256_div_ps(_mm256_load_ps(&data[0]), sPack);

		// Div row 2 and 3.
		reinterpret_cast<__m256&>(fres[8]) = _mm256_div_ps(_mm256_load_ps(&data[8]), sPack);

		return res;
	}

	template <>
	RMat4f RMat4f::operator+(const RMat4f& _rhs) const noexcept
	{
		Mat4 res;
		float* const fres = res.Data();
		const float* const ldata = Data();
		const float* const rdata = _rhs.Data();

		// Add row 0 and 1.
		reinterpret_cast<__m256&>(fres[0]) = _mm256_add_ps(_mm256_load_ps(&ldata[0]), _mm256_load_ps(&rdata[0]));

		// Add row 2 and 3.
		reinterpret_cast<__m256&>(fres[8]) = _mm256_add_ps(_mm256_load_ps(&ldata[8]), _mm256_load_ps(&rdata[8]));

		return res;
	}

	template <>
	RMat4f RMat4f::operator-(const RMat4f& _rhs) const noexcept
	{
		Mat4 res;
		float* const fres = res.Data();
		const float* const ldata = Data();
		const float* const rdata = _rhs.Data();

		// Sub row 0 and 1.
		reinterpret_cast<__m256&>(fres[0]) = _mm256_sub_ps(_mm256_load_ps(&ldata[0]), _mm256_load_ps(&rdata[0]));

		// Sub row 2 and 3.
		reinterpret_cast<__m256&>(fres[8]) = _mm256_sub_ps(_mm256_load_ps(&ldata[8]), _mm256_load_ps(&rdata[8]));

		return res;
	}

	template <>
	RMat4f RMat4f::operator*(const RMat4f& _rhs) const noexcept
	{
		Mat4 res;
		float* const data = res.Data();

		const __m256 lp00 = _mm256_set_ps(e10, e10, e10, e10, e00, e00, e00, e00);
		const __m256 lp01 = _mm256_set_ps(e30, e30, e30, e30, e20, e20, e20, e20);
		const __m256 lp10 = _mm256_set_ps(e11, e11, e11, e11, e01, e01, e01, e01);
		const __m256 lp11 = _mm256_set_ps(e31, e31, e31, e31, e21, e21, e21, e21);
		const __m256 lp20 = _mm256_set_ps(e12, e12, e12, e12, e02, e02, e02, e02);
		const __m256 lp21 = _mm256_set_ps(e32, e32, e32, e32, e22, e22, e22, e22);
		const __m256 lp30 = _mm256_set_ps(e13, e13, e13, e13, e03, e03, e03, e03);
		const __m256 lp31 = _mm256_set_ps(e33, e33, e33, e33, e23, e23, e23, e23);

		const __m256 rp0 = _mm256_set_ps(_rhs.e03, _rhs.e02, _rhs.e01, _rhs.e00, _rhs.e03, _rhs.e02, _rhs.e01, _rhs.e00);
		const __m256 rp1 = _mm256_set_ps(_rhs.e13, _rhs.e12, _rhs.e11, _rhs.e10, _rhs.e13, _rhs.e12, _rhs.e11, _rhs.e10);
		const __m256 rp2 = _mm256_set_ps(_rhs.e23, _rhs.e22, _rhs.e21, _rhs.e20, _rhs.e23, _rhs.e22, _rhs.e21, _rhs.e20);
		const __m256 rp3 = _mm256_set_ps(_rhs.e33, _rhs.e32, _rhs.e31, _rhs.e30, _rhs.e33, _rhs.e32, _rhs.e31, _rhs.e30);

		// Row 0 and 1.
		reinterpret_cast<__m256&>(data[0]) = _mm256_add_ps(
			_mm256_add_ps(_mm256_mul_ps(lp00, rp0), _mm256_mul_ps(lp10, rp1)),
			_mm256_add_ps(_mm256_mul_ps(lp20, rp2), _mm256_mul_ps(lp30, rp3))
		);

		// Row 2 and 3.
		reinterpret_cast<__m256&>(data[8]) = _mm256_add_ps(
			_mm256_add_ps(_mm256_mul_ps(lp01, rp0), _mm256_mul_ps(lp11, rp1)),
			_mm256_add_ps(_mm256_mul_ps(lp21, rp2), _mm256_mul_ps(lp31, rp3))
		);

		return res;
	}


	template <>
	Vec3<float> RMat4f::operator*(const Vec3<float>& _rhs) const noexcept
	{
		// Compute first 8 elems.
		const __m256 p0 = _mm256_set_ps(e12, e02, e21, e11, e01, e20, e10, e00);
		const __m256 pScale = _mm256_set_ps(_rhs.z, _rhs.z, _rhs.y, _rhs.y, _rhs.y, _rhs.x, _rhs.x, _rhs.x);

		const __m256 pTotal = _mm256_mul_ps(pScale, p0);
		const float* const fres = reinterpret_cast<const float*>(&pTotal);

		return Vec3f(
			fres[0] + fres[3] + fres[6],
			fres[1] + fres[4] + fres[7],
			fres[2] + fres[5] + e22 * _rhs.z
		);
	}

	template <>
	Vec4<float> RMat4f::operator*(const Vec4<float>& _rhs) const noexcept
	{
		const __m256 pScaleXY = _mm256_set_ps(_rhs.y, _rhs.y, _rhs.y, _rhs.y, _rhs.x, _rhs.x, _rhs.x, _rhs.x);
		const __m256 pScaleZW = _mm256_set_ps(_rhs.w, _rhs.w, _rhs.w, _rhs.w, _rhs.z, _rhs.z, _rhs.z, _rhs.z);

		const __m256 p01 = _mm256_mul_ps(_mm256_set_ps(e31, e21, e11, e01, e30, e20, e10, e00), pScaleXY);
		const __m256 p23 = _mm256_mul_ps(_mm256_set_ps(e33, e23, e13, e03, e32, e22, e12, e02), pScaleZW);

		const __m256 pTotal = _mm256_add_ps(p01, p23);
		const __m128* const p128Total = reinterpret_cast<const __m128*>(&pTotal);

		Vec4f res;

		reinterpret_cast<__m128&>(res) = _mm_add_ps(p128Total[0], p128Total[1]);

		return res;
	}


	template <>
	RMat4f& RMat4f::operator*=(float _scale) noexcept
	{
		float* const data = Data();

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Mult row 0 and 1.
		reinterpret_cast<__m256&>(data[0]) = _mm256_mul_ps(_mm256_load_ps(&data[0]), sPack);

		// Mult row 2 and 3.
		reinterpret_cast<__m256&>(data[8]) = _mm256_mul_ps(_mm256_load_ps(&data[8]), sPack);

		return *this;
	}

	template <>
	RMat4f& RMat4f::operator/=(float _scale) noexcept
	{
		float* const data = Data();

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Div row 0 and 1.
		reinterpret_cast<__m256&>(data[0]) = _mm256_div_ps(_mm256_load_ps(&data[0]), sPack);

		// Div row 2 and 3.
		reinterpret_cast<__m256&>(data[8]) = _mm256_div_ps(_mm256_load_ps(&data[8]), sPack);

		return *this;
	}

	template <>
	RMat4f& RMat4f::operator+=(const RMat4f& _rhs) noexcept
	{
		float* const ldata = Data();
		const float* const rdata = _rhs.Data();
		
		// Add row 0 and 1.
		reinterpret_cast<__m256&>(ldata[0]) = _mm256_add_ps(_mm256_load_ps(&ldata[0]), _mm256_load_ps(&rdata[0]));

		// Add row 2 and 3.
		reinterpret_cast<__m256&>(ldata[8]) = _mm256_add_ps(_mm256_load_ps(&ldata[8]), _mm256_load_ps(&rdata[8]));

		return *this;
	}

	template <>
	RMat4f& RMat4f::operator-=(const RMat4f& _rhs) noexcept
	{
		float* const ldata = Data();
		const float* const rdata = _rhs.Data();

		// Sub row 0 and 1.
		reinterpret_cast<__m256&>(ldata[0]) = _mm256_sub_ps(_mm256_load_ps(&ldata[0]), _mm256_load_ps(&rdata[0]));

		// Sub row 2 and 3.
		reinterpret_cast<__m256&>(ldata[8]) = _mm256_sub_ps(_mm256_load_ps(&ldata[8]), _mm256_load_ps(&rdata[8]));

		return *this;
	}


	template <>
	RMat4f operator/(float _lhs, const RMat4f& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.e00), Maths, L"Inverse scale matrix e00 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e01), Maths, L"Inverse scale matrix e01 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e02), Maths, L"Inverse scale matrix e02 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e03), Maths, L"Inverse scale matrix e03 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e10), Maths, L"Inverse scale matrix e10 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e11), Maths, L"Inverse scale matrix e11 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e12), Maths, L"Inverse scale matrix e12 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e13), Maths, L"Inverse scale matrix e13 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e20), Maths, L"Inverse scale matrix e20 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e21), Maths, L"Inverse scale matrix e21 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e22), Maths, L"Inverse scale matrix e22 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e23), Maths, L"Inverse scale matrix e23 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e30), Maths, L"Inverse scale matrix e30 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e31), Maths, L"Inverse scale matrix e31 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e32), Maths, L"Inverse scale matrix e32 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e33), Maths, L"Inverse scale matrix e33 == 0!");


		RMat4f res;
		float* const fres = res.Data();
		const float* const rdata = _rhs.Data();

		const __m256 sPack = _mm256_set1_ps(_lhs);

		// Div row 0 and 1.
		reinterpret_cast<__m256&>(fres[0]) = _mm256_div_ps(sPack, _mm256_load_ps(&rdata[0]));

		// Div row 2 and 3.
		reinterpret_cast<__m256&>(fres[8]) = _mm256_div_ps(sPack, _mm256_load_ps(&rdata[8]));

		return res;
	}

//}

//{ Column Major

	template <>
	float CMat4f::Determinant() const noexcept
	{
		/*
			return
				(+) e00 * 	e11 * (e22 * e33 - e23 * e32)
				(-) e00 * 	e21 * (e12 * e33 - e13 * e32)
				(+) e00 * 	e31 * (e12 * e23 - e13 * e22)
				(-) e10 * 	e01 * (e22 * e33 - e23 * e32)
				(+) e10 * 	e21 * (e02 * e33 - e03 * e32)
				(-) e10 * 	e31 * (e02 * e23 - e03 * e22)
				(+) e20 * 	e01 * (e12 * e33 - e13 * e32)
				(-) e20 * 	e11 * (e02 * e33 - e03 * e32)

				(+) e20 * 	e31 * (e02 * e13 - e03 * e12)
				(-) e30 * 	e01 * (e12 * e23 - e13 * e22)
				(+) e30 * 	e11 * (e02 * e23 - e03 * e22)
				(-) e30 * 	e21 * (e02 * e13 - e03 * e12);
		*/

		const __m256 p0 = _mm256_set_ps(-e20, e20, -e10, e10, -e10, e00, -e00, e00);
		const __m256 p1 = _mm256_set_ps(e11, e01, e31, e21, e01, e31, e21, e11);
		const __m256 p2 = _mm256_set_ps(e02, e12, e02, e02, e22, e12, e12, e22);
		const __m256 p3 = _mm256_set_ps(e33, e33, e23, e33, e33, e23, e33, e33);
		const __m256 p4 = _mm256_set_ps(e03, e13, e03, e03, e23, e13, e13, e23);
		const __m256 p5 = _mm256_set_ps(e32, e32, e22, e32, e32, e22, e32, e32);

		const __m256 p12345 = _mm256_mul_ps(p0, _mm256_mul_ps(p1, _mm256_sub_ps(_mm256_mul_ps(p2, p3), _mm256_mul_ps(p4, p5))));


		const __m256 p0_1 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, -e30, e30, -e30, e20);
		const __m256 p6 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, e21, e11, e01, e31);
		const __m256 p7 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, e02, e02, e12, e02);
		const __m256 p8 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, e13, e23, e23, e13);
		const __m256 p9 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, e03, e03, e13, e03);
		const __m256 p10 = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, e12, e22, e22, e12);

		const __m256 p678910 = _mm256_mul_ps(p0_1, _mm256_mul_ps(p6, _mm256_sub_ps(_mm256_mul_ps(p7, p8), _mm256_mul_ps(p9, p10))));


		const __m256 pTotal = _mm256_add_ps(p12345, p678910);
		const float* const fres = reinterpret_cast<const float*>(&pTotal);

		return fres[0] + fres[1] + fres[2] + fres[3] + fres[4] + fres[5] + fres[6] + fres[7];
	}

	template <>
	CMat4f CMat4f::GetInversed() const noexcept
	{
		Mat4 res;
		float* const data = res.Data();
		const float det = Determinant();

		SA_WARN(!Sa::Equals0(det), Maths, L"Inverse matrix with determinant == 0");

		const float invDet = 1.0f / det;
		const __m256 invDetP = _mm256_set1_ps(invDet);


//{ Row 0
		/*
			e00 =
				(+) e11 * e22 * e33
				(-) e11 * e23 * e32
				(-) e21 * e12 * e33
				(+) e21 * e13 * e32
				(+) e31 * e12 * e23
				(-) e31 * e13 * e22

			e01 =
				(-) e01 * e22 * e33
				(+) e01 * e23 * e32
				(+) e21 * e02 * e33
				(-) e21 * e03 * e32
				(-) e31 * e02 * e23
				(+) e31 * e03 * e22

			e02 =
				(+) e01 * e12 * e33
				(-) e01 * e13 * e32
				(-) e11 * e02 * e33
				(+) e11 * e03 * e32
				(+) e31 * e02 * e13
				(-) e31 * e03 * e12

			e03 =
				(-) e01 * e12 * e23
				(+) e01 * e13 * e22
				(+) e11 * e02 * e23
				(-) e11 * e03 * e22
				(-) e21 * e02 * e13
				(+) e21 * e03 * e12

			4 (elems) * 6 (add/sub) = 24 = 3 (packs) * 8 (float).
		*/
		const __m256 r0p1 = _mm256_set_ps(e01, -e01, -e31, e31, e21, -e21, -e11, e11);
		const __m256 r0p2 = _mm256_set_ps(e23, e22, e13, e12, e13, e12, e23, e22);
		const __m256 r0p3 = _mm256_set_ps(e32, e33, e22, e23, e32, e33, e32, e33);
		const __m256 r0p123 = _mm256_mul_ps(_mm256_mul_ps(r0p1, r0p2), r0p3);
		const float* const r0f123 = reinterpret_cast<const float*>(&r0p123);

		const __m256 r0p4 = _mm256_set_ps(e11, -e11, -e01, e01, e31, -e31, -e21, e21);
		const __m256 r0p5 = _mm256_set_ps(e03, e02, e13, e12, e03, e02, e03, e02);
		const __m256 r0p6 = _mm256_set_ps(e32, e33, e32, e33, e22, e23, e32, e33);
		const __m256 r0p456 = _mm256_mul_ps(_mm256_mul_ps(r0p4, r0p5), r0p6);
		const float* const r0f456 = reinterpret_cast<const float*>(&r0p456);

		const __m256 r0p7 = _mm256_set_ps(e21, -e21, -e11, e11, e01, -e01, -e31, e31);
		const __m256 r0p8 = _mm256_set_ps(e03, e02, e03, e02, e13, e12, e03, e02);
		const __m256 r0p9 = _mm256_set_ps(e12, e13, e22, e23, e22, e23, e12, e13);
		const __m256 r0p789 = _mm256_mul_ps(_mm256_mul_ps(r0p7, r0p8), r0p9);
		const float* const r0f789 = reinterpret_cast<const float*>(&r0p789);


		// Fill elems.
		//res.e00 = r0f123[0] + r0f123[1] + r0f123[2] + r0f123[3] + r0f123[4] + r0f123[5];
		//res.e01 = r0f123[6] + r0f123[7] + r0f456[0] + r0f456[1] + r0f456[2] + r0f456[3];
		//res.e02 = r0f456[4] + r0f456[5] + r0f456[6] + r0f456[7] + r0f789[0] + r0f789[1];
		//res.e03 = r0f789[2] + r0f789[3] + r0f789[4] + r0f789[5] + r0f789[6] + r0f789[7];

		const __m128 r0rp1 = _mm_set_ps(r0f789[2], r0f456[4], r0f123[6], r0f123[0]);
		const __m128 r0rp2 = _mm_set_ps(r0f789[3], r0f456[5], r0f123[7], r0f123[1]);
		const __m128 r0rp3 = _mm_set_ps(r0f789[4], r0f456[6], r0f456[0], r0f123[2]);
		const __m128 r0rp4 = _mm_set_ps(r0f789[5], r0f456[7], r0f456[1], r0f123[3]);
		const __m128 r0rp5 = _mm_set_ps(r0f789[6], r0f789[0], r0f456[2], r0f123[4]);
		const __m128 r0rp6 = _mm_set_ps(r0f789[7], r0f789[1], r0f456[3], r0f123[5]);

		reinterpret_cast<__m128&>(data[0]) = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(r0rp1, r0rp2), r0rp3), r0rp4), r0rp5), r0rp6);
//}

//{ Row 1
		/*
			e10 =
				(-) e10 * e22 * e33
				(+) e10 * e23 * e32
				(+) e20 * e12 * e33
				(-) e20 * e13 * e32
				(-) e30 * e12 * e23
				(+) e30 * e13 * e22

			e11 =
				(+) e00 * e22 * e33
				(-) e00 * e23 * e32
				(-) e20 * e02 * e33
				(+) e20 * e03 * e32
				(+) e30 * e02 * e23
				(-) e30 * e03 * e22

			e12 =
				(-) e00 * e12 * e33
				(+) e00 * e13 * e32
				(+) e10 * e02 * e33
				(-) e10 * e03 * e32
				(-) e30 * e02 * e13
				(+) e30 * e03 * e12

			e13 =
				(+) e00 * e12 * e23
				(-) e00 * e13 * e22
				(-) e10 * e02 * e23
				(+) e10 * e03 * e22
				(+) e20 * e02 * e13
				(-) e20 * e03 * e12

			4 (elems) * 6 (add/sub) = 24 = 3 (packs) * 8 (float).
		*/
		const __m256 r1p1 = _mm256_set_ps(-e00, e00, e30, -e30, -e20, e20, e10, -e10);
		// r1p2 == r0p2
		// r1p3 == r0p3
		const __m256 r1p123 = _mm256_mul_ps(_mm256_mul_ps(r1p1, r0p2), r0p3);
		const float* const r1f123 = reinterpret_cast<const float*>(&r1p123);

		const __m256 r1p4 = _mm256_set_ps(-e10, e10, e00, -e00, -e30, e30, e20, -e20);
		// r1p5 == r0p5
		// r1p6 == r0p6
		const __m256 r1p456 = _mm256_mul_ps(_mm256_mul_ps(r1p4, r0p5), r0p6);
		const float* const r1f456 = reinterpret_cast<const float*>(&r1p456);

		const __m256 r1p7 = _mm256_set_ps(-e20, e20, e10, -e10, -e00, e00, e30, -e30);
		// r1p8 == r0p8
		// r1p9 == r0p9
		const __m256 r1p789 = _mm256_mul_ps(_mm256_mul_ps(r1p7, r0p8), r0p9);
		const float* const r1f789 = reinterpret_cast<const float*>(&r1p789);


		// Fill elems.
		//res.e10 = r1f123[0] + r1f123[1] + r1f123[2] + r1f123[3] + r1f123[4] + r1f123[5];
		//res.e11 = r1f123[6] + r1f123[7] + r1f456[0] + r1f456[1] + r1f456[2] + r1f456[3];
		//res.e12 = r1f456[4] + r1f456[5] + r1f456[6] + r1f456[7] + r1f789[0] + r1f789[1];
		//res.e13 = r1f789[2] + r1f789[3] + r1f789[4] + r1f789[5] + r1f789[6] + r1f789[7];

		const __m128 r1rp1 = _mm_set_ps(r1f789[2], r1f456[4], r1f123[6], r1f123[0]);
		const __m128 r1rp2 = _mm_set_ps(r1f789[3], r1f456[5], r1f123[7], r1f123[1]);
		const __m128 r1rp3 = _mm_set_ps(r1f789[4], r1f456[6], r1f456[0], r1f123[2]);
		const __m128 r1rp4 = _mm_set_ps(r1f789[5], r1f456[7], r1f456[1], r1f123[3]);
		const __m128 r1rp5 = _mm_set_ps(r1f789[6], r1f789[0], r1f456[2], r1f123[4]);
		const __m128 r1rp6 = _mm_set_ps(r1f789[7], r1f789[1], r1f456[3], r1f123[5]);

		reinterpret_cast<__m128&>(data[4]) = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(r1rp1, r1rp2), r1rp3), r1rp4), r1rp5), r1rp6);
//}

//{ Row 2
		/*
			e20 =
				(+) e10 * e21 * e33
				(-) e10 * e23 * e31
				(-) e20 * e11 * e33
				(+) e20 * e13 * e31
				(+) e30 * e11 * e23
				(-) e30 * e13 * e21

			e21 =
				(-) e00 * e21 * e33
				(+) e00 * e23 * e31
				(+) e20 * e01 * e33
				(-) e20 * e03 * e31
				(-) e30 * e01 * e23
				(+) e30 * e03 * e21

			e22 =
				(+) e00 * e11 * e33
				(-) e00 * e13 * e31
				(-) e10 * e01 * e33
				(+) e10 * e03 * e31
				(+) e30 * e01 * e13
				(-) e30 * e03 * e11

			e23 =
				(-) e00 * e11 * e23
				(+) e00 * e13 * e21
				(+) e10 * e01 * e23
				(-) e10 * e03 * e21
				(-) e20 * e01 * e13
				(+) e20 * e03 * e11

			4 (elems) * 6 (add/sub) = 24 = 3 (packs) * 8 (float).

			// Use row 1 pack and inverse all sign in second column (p2, p5, p8)
		*/
		// r2p1 = -r1p1
		const __m256 r2p2 = _mm256_set_ps(-e23, -e21, -e13, -e11, -e13, -e11, -e23, -e21);
		const __m256 r2p3 = _mm256_set_ps(e31, e33, e21, e23, e31, e33, e31, e33);
		const __m256 r2p123 = _mm256_mul_ps(_mm256_mul_ps(r1p1, r2p2), r2p3);
		const float* const r2f123 = reinterpret_cast<const float*>(&r2p123);

		// r2p4 = -r1p4
		const __m256 r2p5 = _mm256_set_ps(-e03, -e01, -e13, -e11, -e03, -e01, -e03, -e01);
		const __m256 r2p6 = _mm256_set_ps(e31, e33, e31, e33, e21, e23, e31, e33);
		const __m256 r2p456 = _mm256_mul_ps(_mm256_mul_ps(r1p4, r2p5), r2p6);
		const float* const r2f456 = reinterpret_cast<const float*>(&r2p456);

		// r2p7 = -r1p7
		const __m256 r2p8 = _mm256_set_ps(-e03, -e01, -e03, -e01, -e13, -e11, -e03, -e01);
		const __m256 r2p9 = _mm256_set_ps(e11, e13, e21, e23, e21, e23, e11, e13);
		const __m256 r2p789 = _mm256_mul_ps(_mm256_mul_ps(r1p7, r2p8), r2p9);
		const float* const r2f789 = reinterpret_cast<const float*>(&r2p789);


		// Fill elems.
		//res.e20 = r2f123[0] + r2f123[1] + r2f123[2] + r2f123[3] + r2f123[4] + r2f123[5];
		//res.e21 = r2f123[6] + r2f123[7] + r2f456[0] + r2f456[1] + r2f456[2] + r2f456[3];
		//res.e22 = r2f456[4] + r2f456[5] + r2f456[6] + r2f456[7] + r2f789[0] + r2f789[1];
		//res.e23 = r2f789[2] + r2f789[3] + r2f789[4] + r2f789[5] + r2f789[6] + r2f789[7];

		const __m128 r2rp1 = _mm_set_ps(r2f789[2], r2f456[4], r2f123[6], r2f123[0]);
		const __m128 r2rp2 = _mm_set_ps(r2f789[3], r2f456[5], r2f123[7], r2f123[1]);
		const __m128 r2rp3 = _mm_set_ps(r2f789[4], r2f456[6], r2f456[0], r2f123[2]);
		const __m128 r2rp4 = _mm_set_ps(r2f789[5], r2f456[7], r2f456[1], r2f123[3]);
		const __m128 r2rp5 = _mm_set_ps(r2f789[6], r2f789[0], r2f456[2], r2f123[4]);
		const __m128 r2rp6 = _mm_set_ps(r2f789[7], r2f789[1], r2f456[3], r2f123[5]);

		reinterpret_cast<__m128&>(data[8]) = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(r2rp1, r2rp2), r2rp3), r2rp4), r2rp5), r2rp6);
//}

//{ Row 3
		/*
			e30 =
				(-) e10 * e21 * e32
				(+) e10 * e22 * e31
				(+) e20 * e11 * e32
				(-) e20 * e12 * e31
				(-) e30 * e11 * e22
				(+) e30 * e12 * e21

			e31 =
				(+) e00 * e21 * e32
				(-) e00 * e22 * e31
				(-) e20 * e01 * e32
				(+) e20 * e02 * e31
				(+) e30 * e01 * e22
				(-) e30 * e02 * e21

			e32 =
				(-) e00 * e11 * e32
				(+) e00 * e12 * e31
				(+) e10 * e01 * e32
				(-) e10 * e02 * e31
				(-) e30 * e01 * e12
				(+) e30 * e02 * e11

			e33 =
				(+) e00 * e11 * e22
				(-) e00 * e12 * e21
				(-) e10 * e01 * e22
				(+) e10 * e02 * e21
				(+) e20 * e01 * e12
				(-) e20 * e02 * e11

			4 (elems) * 6 (add/sub) = 24 = 3 (packs) * 8 (float).
		*/
		// r3p1 = r1p1
		const __m256 r3p2 = _mm256_set_ps(e22, e21, e12, e11, e12, e11, e22, e21);
		const __m256 r3p3 = _mm256_set_ps(e31, e32, e21, e22, e31, e32, e31, e32);
		const __m256 r3p123 = _mm256_mul_ps(_mm256_mul_ps(r1p1, r3p2), r3p3);
		const float* const r3f123 = reinterpret_cast<const float*>(&r3p123);

		// r3p4 = r1p4
		const __m256 r3p5 = _mm256_set_ps(e02, e01, e12, e11, e02, e01, e02, e01);
		const __m256 r3p6 = _mm256_set_ps(e31, e32, e31, e32, e21, e22, e31, e32);
		const __m256 r3p456 = _mm256_mul_ps(_mm256_mul_ps(r1p4, r3p5), r3p6);
		const float* const r3f456 = reinterpret_cast<const float*>(&r3p456);

		// r3p7 = r1p7
		const __m256 r3p8 = _mm256_set_ps(e02, e01, e02, e01, e12, e11, e02, e01);
		const __m256 r3p9 = _mm256_set_ps(e11, e12, e21, e22, e21, e22, e11, e12);
		const __m256 r3p789 = _mm256_mul_ps(_mm256_mul_ps(r1p7, r3p8), r3p9);
		const float* const r3f789 = reinterpret_cast<const float*>(&r3p789);


		// Fill elems.
		//res.e20 = r3f123[0] + r3f123[1] + r3f123[2] + r3f123[3] + r3f123[4] + r3f123[5];
		//res.e21 = r3f123[6] + r3f123[7] + r3f456[0] + r3f456[1] + r3f456[2] + r3f456[3];
		//res.e22 = r3f456[4] + r3f456[5] + r3f456[6] + r3f456[7] + r3f789[0] + r3f789[1];
		//res.e23 = r3f789[2] + r3f789[3] + r3f789[4] + r3f789[5] + r3f789[6] + r3f789[7];

		const __m128 r3rp1 = _mm_set_ps(r3f789[2], r3f456[4], r3f123[6], r3f123[0]);
		const __m128 r3rp2 = _mm_set_ps(r3f789[3], r3f456[5], r3f123[7], r3f123[1]);
		const __m128 r3rp3 = _mm_set_ps(r3f789[4], r3f456[6], r3f456[0], r3f123[2]);
		const __m128 r3rp4 = _mm_set_ps(r3f789[5], r3f456[7], r3f456[1], r3f123[3]);
		const __m128 r3rp5 = _mm_set_ps(r3f789[6], r3f789[0], r3f456[2], r3f123[4]);
		const __m128 r3rp6 = _mm_set_ps(r3f789[7], r3f789[1], r3f456[3], r3f123[5]);

		reinterpret_cast<__m128&>(data[12]) = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(r3rp1, r3rp2), r3rp3), r3rp4), r3rp5), r3rp6);
//}

		// Apply inv det
		reinterpret_cast<__m256&>(data[0]) = _mm256_mul_ps(invDetP, reinterpret_cast<const __m256&>(data[0]));
		reinterpret_cast<__m256&>(data[8]) = _mm256_mul_ps(invDetP, reinterpret_cast<const __m256&>(data[8]));

		// TODO: better column impl.
		res.Transpose();

		return res;
	}


	template <>
	CMat4f& CMat4f::ApplyScale(const Vec3<float>& _scale) noexcept
	{
		float* const data = Data();

		// Compute row 01
		const __m256 pScaleXY = _mm256_set_ps(1.0f, _scale.z, _scale.y, _scale.x, 1.0f, _scale.z, _scale.y, _scale.x);

		reinterpret_cast<__m256&>(data[0]) = _mm256_mul_ps(pScaleXY, _mm256_load_ps(&data[0]));


		// Compute row 2
		const __m128 pScaleZ = _mm_set_ps(1.0f, _scale.z, _scale.y, _scale.x);

		reinterpret_cast<__m128&>(data[8]) = _mm_mul_ps(pScaleZ, _mm_load_ps(&data[8]));

		return *this;
	}


	template <>
	CMat4f CMat4f::MakeRotation(const Quat<float>& _rot) noexcept
	{
		SA_WARN(_rot.IsNormalized(), Maths, L"Quaternion should be normalized!");

		/*
			return Mat3f(
				1.0f -	2.0f * (_rot.y * _rot.y + _rot.z * _rot.z),
						2.0f * (_rot.x * _rot.y - _rot.z * _rot.w),
						2.0f * (_rot.x * _rot.z + _rot.y * _rot.w),

						2.0f * (_rot.x * _rot.y + _rot.z * _rot.w),
				1.0f -	2.0f * (_rot.x * _rot.x + _rot.z * _rot.z),
						2.0f * (_rot.y * _rot.z - _rot.x * _rot.w),

						2.0f * (_rot.x * _rot.z - _rot.y * _rot.w),
						2.0f * (_rot.y * _rot.z + _rot.x * _rot.w),
				1.0f -	2.0f * (_rot.x * _rot.x + _rot.y * _rot.y)
			);
		*/

		const __m256 pDbl = _mm256_set1_ps(2.0);

		// 8 first elems.
		const __m256 p1 = _mm256_set_ps(_rot.y, _rot.x, _rot.y, _rot.x, _rot.x, _rot.x, _rot.x, _rot.y);
		const __m256 p2 = _mm256_set_ps(_rot.z, _rot.z, _rot.z, _rot.x, _rot.y, _rot.z, _rot.y, _rot.y);
		const __m256 p3 = _mm256_set_ps(_rot.x, -_rot.y, -_rot.x, _rot.z, _rot.z, _rot.y, -_rot.z, _rot.z);
		const __m256 p4 = _mm256_set_ps(_rot.w, _rot.w, _rot.w, _rot.z, _rot.w, _rot.w, _rot.w, _rot.z);

		__m256 p1234 = _mm256_mul_ps(pDbl, _mm256_add_ps(_mm256_mul_ps(p1, p2), _mm256_mul_ps(p3, p4)));
		float* const f1234 = reinterpret_cast<float*>(&p1234);

		// Apply 1.0f - value.
		f1234[0] = 1.0f - f1234[0];
		f1234[4] = 1.0f - f1234[4];


		// Last elem.
		float e22 = 1.0f - 2.0f * (_rot.x * _rot.x + _rot.y * _rot.y);


		return Mat4(
			f1234[0], f1234[1], f1234[2], 0.0f,
			f1234[3], f1234[4], f1234[5], 0.0f,
			f1234[6], f1234[7], e22, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	template <>
	CMat4f CMat4f::operator*(float _scale) const noexcept
	{
		Mat4 res;
		float* const fres = res.Data();
		const float* const data = Data();

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Mult row 0 and 1.
		reinterpret_cast<__m256&>(fres[0]) = _mm256_mul_ps(_mm256_load_ps(&data[0]), sPack);

		// Mult row 2 and 3.
		reinterpret_cast<__m256&>(fres[8]) = _mm256_mul_ps(_mm256_load_ps(&data[8]), sPack);

		return res;
	}

	template <>
	CMat4f CMat4f::operator/(float _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		Mat4 res;
		float* const fres = res.Data();
		const float* const data = Data();

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Div row 0 and 1.
		reinterpret_cast<__m256&>(fres[0]) = _mm256_div_ps(_mm256_load_ps(&data[0]), sPack);

		// Div row 2 and 3.
		reinterpret_cast<__m256&>(fres[8]) = _mm256_div_ps(_mm256_load_ps(&data[8]), sPack);

		return res;
	}

	template <>
	CMat4f CMat4f::operator+(const CMat4f& _rhs) const noexcept
	{
		Mat4 res;
		float* const fres = res.Data();
		const float* const ldata = Data();
		const float* const rdata = _rhs.Data();

		// Add row 0 and 1.
		reinterpret_cast<__m256&>(fres[0]) = _mm256_add_ps(_mm256_load_ps(&ldata[0]), _mm256_load_ps(&rdata[0]));

		// Add row 2 and 3.
		reinterpret_cast<__m256&>(fres[8]) = _mm256_add_ps(_mm256_load_ps(&ldata[8]), _mm256_load_ps(&rdata[8]));

		return res;
	}

	template <>
	CMat4f CMat4f::operator-(const CMat4f& _rhs) const noexcept
	{
		Mat4 res;
		float* const fres = res.Data();
		const float* const ldata = Data();
		const float* const rdata = _rhs.Data();

		// Sub row 0 and 1.
		reinterpret_cast<__m256&>(fres[0]) = _mm256_sub_ps(_mm256_load_ps(&ldata[0]), _mm256_load_ps(&rdata[0]));

		// Sub row 2 and 3.
		reinterpret_cast<__m256&>(fres[8]) = _mm256_sub_ps(_mm256_load_ps(&ldata[8]), _mm256_load_ps(&rdata[8]));

		return res;
	}

	template <>
	CMat4f CMat4f::operator*(const CMat4f& _rhs) const noexcept
	{
		Mat4 res;
		float* const data = res.Data();

		const __m256 rp00 = _mm256_set_ps(_rhs.e01, _rhs.e01, _rhs.e01, _rhs.e01, _rhs.e00, _rhs.e00, _rhs.e00, _rhs.e00);
		const __m256 rp01 = _mm256_set_ps(_rhs.e03, _rhs.e03, _rhs.e03, _rhs.e03, _rhs.e02, _rhs.e02, _rhs.e02, _rhs.e02);
		const __m256 rp10 = _mm256_set_ps(_rhs.e11, _rhs.e11, _rhs.e11, _rhs.e11, _rhs.e10, _rhs.e10, _rhs.e10, _rhs.e10);
		const __m256 rp11 = _mm256_set_ps(_rhs.e13, _rhs.e13, _rhs.e13, _rhs.e13, _rhs.e12, _rhs.e12, _rhs.e12, _rhs.e12);
		const __m256 rp20 = _mm256_set_ps(_rhs.e21, _rhs.e21, _rhs.e21, _rhs.e21, _rhs.e20, _rhs.e20, _rhs.e20, _rhs.e20);
		const __m256 rp21 = _mm256_set_ps(_rhs.e23, _rhs.e23, _rhs.e23, _rhs.e23, _rhs.e22, _rhs.e22, _rhs.e22, _rhs.e22);
		const __m256 rp30 = _mm256_set_ps(_rhs.e31, _rhs.e31, _rhs.e31, _rhs.e31, _rhs.e30, _rhs.e30, _rhs.e30, _rhs.e30);
		const __m256 rp31 = _mm256_set_ps(_rhs.e33, _rhs.e33, _rhs.e33, _rhs.e33, _rhs.e32, _rhs.e32, _rhs.e32, _rhs.e32);

		const __m256 lp0 = _mm256_set_ps(e30, e20, e10, e00, e30, e20, e10, e00);
		const __m256 lp1 = _mm256_set_ps(e31, e21, e11, e01, e31, e21, e11, e01);
		const __m256 lp2 = _mm256_set_ps(e32, e22, e12, e02, e32, e22, e12, e02);
		const __m256 lp3 = _mm256_set_ps(e33, e23, e13, e03, e33, e23, e13, e03);

		// Row 0 and 1.
		reinterpret_cast<__m256&>(data[0]) = _mm256_add_ps(
			_mm256_add_ps(_mm256_mul_ps(rp00, lp0), _mm256_mul_ps(rp10, lp1)),
			_mm256_add_ps(_mm256_mul_ps(rp20, lp2), _mm256_mul_ps(rp30, lp3))
		);

		// Row 2 and 3.
		reinterpret_cast<__m256&>(data[8]) = _mm256_add_ps(
			_mm256_add_ps(_mm256_mul_ps(rp01, lp0), _mm256_mul_ps(rp11, lp1)),
			_mm256_add_ps(_mm256_mul_ps(rp21, lp2), _mm256_mul_ps(rp31, lp3))
		);

		return res;
	}


	template <>
	Vec3<float> CMat4f::operator*(const Vec3<float>& _rhs) const noexcept
	{
		// Compute first 8 elems.
		const __m256 p0 = _mm256_set_ps(e12, e02, e21, e11, e01, e20, e10, e00);
		const __m256 pScale = _mm256_set_ps(_rhs.z, _rhs.z, _rhs.y, _rhs.y, _rhs.y, _rhs.x, _rhs.x, _rhs.x);

		const __m256 pTotal = _mm256_mul_ps(pScale, p0);
		const float* const fres = reinterpret_cast<const float*>(&pTotal);

		return Vec3f(
			fres[0] + fres[3] + fres[6],
			fres[1] + fres[4] + fres[7],
			fres[2] + fres[5] + e22 * _rhs.z
		);
	}

	template <>
	Vec4<float> CMat4f::operator*(const Vec4<float>& _rhs) const noexcept
	{
		const __m256 pScaleXY = _mm256_set_ps(_rhs.y, _rhs.y, _rhs.y, _rhs.y, _rhs.x, _rhs.x, _rhs.x, _rhs.x);
		const __m256 pScaleZW = _mm256_set_ps(_rhs.w, _rhs.w, _rhs.w, _rhs.w, _rhs.z, _rhs.z, _rhs.z, _rhs.z);

		const __m256 p01 = _mm256_mul_ps(_mm256_set_ps(e31, e21, e11, e01, e30, e20, e10, e00), pScaleXY);
		const __m256 p23 = _mm256_mul_ps(_mm256_set_ps(e33, e23, e13, e03, e32, e22, e12, e02), pScaleZW);

		const __m256 pTotal = _mm256_add_ps(p01, p23);
		const __m128* const p128Total = reinterpret_cast<const __m128*>(&pTotal);

		Vec4f res;

		reinterpret_cast<__m128&>(res) = _mm_add_ps(p128Total[0], p128Total[1]);

		return res;
	}


	template <>
	CMat4f& CMat4f::operator*=(float _scale) noexcept
	{
		float* const data = Data();

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Mult row 0 and 1.
		reinterpret_cast<__m256&>(data[0]) = _mm256_mul_ps(_mm256_load_ps(&data[0]), sPack);

		// Mult row 2 and 3.
		reinterpret_cast<__m256&>(data[8]) = _mm256_mul_ps(_mm256_load_ps(&data[8]), sPack);

		return *this;
	}

	template <>
	CMat4f& CMat4f::operator/=(float _scale) noexcept
	{
		float* const data = Data();

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Div row 0 and 1.
		reinterpret_cast<__m256&>(data[0]) = _mm256_div_ps(_mm256_load_ps(&data[0]), sPack);

		// Div row 2 and 3.
		reinterpret_cast<__m256&>(data[8]) = _mm256_div_ps(_mm256_load_ps(&data[8]), sPack);

		return *this;
	}

	template <>
	CMat4f& CMat4f::operator+=(const CMat4f& _rhs) noexcept
	{
		float* const ldata = Data();
		const float* const rdata = _rhs.Data();

		// Add row 0 and 1.
		reinterpret_cast<__m256&>(ldata[0]) = _mm256_add_ps(_mm256_load_ps(&ldata[0]), _mm256_load_ps(&rdata[0]));

		// Add row 2 and 3.
		reinterpret_cast<__m256&>(ldata[8]) = _mm256_add_ps(_mm256_load_ps(&ldata[8]), _mm256_load_ps(&rdata[8]));

		return *this;
	}

	template <>
	CMat4f& CMat4f::operator-=(const CMat4f& _rhs) noexcept
	{
		float* const ldata = Data();
		const float* const rdata = _rhs.Data();

		// Sub row 0 and 1.
		reinterpret_cast<__m256&>(ldata[0]) = _mm256_sub_ps(_mm256_load_ps(&ldata[0]), _mm256_load_ps(&rdata[0]));

		// Sub row 2 and 3.
		reinterpret_cast<__m256&>(ldata[8]) = _mm256_sub_ps(_mm256_load_ps(&ldata[8]), _mm256_load_ps(&rdata[8]));

		return *this;
	}


	template <>
	CMat4f operator/(float _lhs, const CMat4f& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.e00), Maths, L"Inverse scale matrix e00 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e01), Maths, L"Inverse scale matrix e01 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e02), Maths, L"Inverse scale matrix e02 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e03), Maths, L"Inverse scale matrix e03 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e10), Maths, L"Inverse scale matrix e10 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e11), Maths, L"Inverse scale matrix e11 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e12), Maths, L"Inverse scale matrix e12 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e13), Maths, L"Inverse scale matrix e13 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e20), Maths, L"Inverse scale matrix e20 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e21), Maths, L"Inverse scale matrix e21 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e22), Maths, L"Inverse scale matrix e22 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e23), Maths, L"Inverse scale matrix e23 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e30), Maths, L"Inverse scale matrix e30 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e31), Maths, L"Inverse scale matrix e31 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e32), Maths, L"Inverse scale matrix e32 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e33), Maths, L"Inverse scale matrix e33 == 0!");


		CMat4f res;
		float* const fres = res.Data();
		const float* const rdata = _rhs.Data();

		const __m256 sPack = _mm256_set1_ps(_lhs);

		// Div row 0 and 1.
		reinterpret_cast<__m256&>(fres[0]) = _mm256_div_ps(sPack, _mm256_load_ps(&rdata[0]));

		// Div row 2 and 3.
		reinterpret_cast<__m256&>(fres[8]) = _mm256_div_ps(sPack, _mm256_load_ps(&rdata[8]));

		return res;
	}

//}

#endif

#if SA_INTRISC_AVX // SIMD double

//{ Row Major

	template <>
	double RMat4d::Determinant() const noexcept
	{
		/*
			return
				e00 * (e11 * (e22 * e33 - e23 * e32) - e21 * (e12 * e33 - e13 * e32) + e31 * (e12 * e23 - e13 * e22)) -
				e10 * (e01 * (e22 * e33 - e23 * e32) - e21 * (e02 * e33 - e03 * e32) + e31 * (e02 * e23 - e03 * e22)) +
				e20 * (e01 * (e12 * e33 - e13 * e32) - e11 * (e02 * e33 - e03 * e32) + e31 * (e02 * e13 - e03 * e12)) -
				e30 * (e01 * (e12 * e23 - e13 * e22) - e11 * (e02 * e23 - e03 * e22) + e21 * (e02 * e13 - e03 * e12));
		*/

		const __m256d p0 = _mm256_set_pd(e01, e01, e01, e11);
		const __m256d p1 = _mm256_set_pd(e12, e12, e22, e22);
		const __m256d p2 = _mm256_set_pd(e23, e33, e33, e33);
		const __m256d p3 = _mm256_set_pd(e13, e13, e23, e23);
		const __m256d p4 = _mm256_set_pd(e22, e32, e32, e32);
		const __m256d p01234 = _mm256_mul_pd(p0, _mm256_sub_pd(_mm256_mul_pd(p1, p2), _mm256_mul_pd(p3, p4)));


		const __m256d p5 = _mm256_set_pd(e11, e11, e21, e21);
		const __m256d p6 = _mm256_set_pd(e02, e02, e02, e12);
		// p7 == p2.
		const __m256d p8 = _mm256_set_pd(e03, e03, e03, e13);
		// p9 == p4.
		const __m256d p56789 = _mm256_mul_pd(p5, _mm256_sub_pd(_mm256_mul_pd(p6, p2), _mm256_mul_pd(p8, p4)));


		const __m256d p10 = _mm256_set_pd(e21, e31, e31, e31);
		// p11 == p6
		// p12 == p3
		// p13 == p8
		// p14 == p1
		const __m256d p10_11_12_13_14 = _mm256_mul_pd(p10, _mm256_sub_pd(_mm256_mul_pd(p6, p3), _mm256_mul_pd(p8, p1)));

		const __m256d coefP = _mm256_set_pd(e30, e20, e10, e00);
		const __m256d total = _mm256_mul_pd(coefP, _mm256_add_pd(_mm256_sub_pd(p01234, p56789), p10_11_12_13_14));
		const double* const dTotal = reinterpret_cast<const double*>(&total);

		return dTotal[0] - dTotal[1] + dTotal[2] - dTotal[3];
	}

	template <>
	RMat4d RMat4d::GetInversed() const noexcept
	{
		Mat4 res;
		double* const data = res.Data();
		const double det = Determinant();

		SA_WARN(!Sa::Equals0(det), Maths, L"Inverse matrix with determinant == 0");

		const double invDet = 1.0f / det;
		const __m256d invDetP = _mm256_set1_pd(invDet);

//{ Row 0
		/*
			e00 =
				(+) e11 * e22 * e33
				(-) e11 * e23 * e32
				(-) e21 * e12 * e33
				(+) e21 * e13 * e32
				(+) e31 * e12 * e23
				(-) e31 * e13 * e22

			e01 =
				(-) e01 * e22 * e33
				(+) e01 * e23 * e32
				(+) e21 * e02 * e33
				(-) e21 * e03 * e32
				(-) e31 * e02 * e23
				(+) e31 * e03 * e22

			e02 =
				(+) e01 * e12 * e33
				(-) e01 * e13 * e32
				(-) e11 * e02 * e33
				(+) e11 * e03 * e32
				(+) e31 * e02 * e13
				(-) e31 * e03 * e12

			e03 =
				(-) e01 * e12 * e23
				(+) e01 * e13 * e22
				(+) e11 * e02 * e23
				(-) e11 * e03 * e22
				(-) e21 * e02 * e13
				(+) e21 * e03 * e12
		*/
		const __m256d r0p1 = _mm256_set_pd(e21, -e21, -e11, e11);
		const __m256d r0p2 = _mm256_set_pd(e13, e12, e23, e22);
		const __m256d r0p3 = _mm256_set_pd(e32, e33, e32, e33);
		const __m256d r0p123 = _mm256_mul_pd(_mm256_mul_pd(r0p1, r0p2), r0p3);
		const double* const r0f123 = reinterpret_cast<const double*>(&r0p123);

		const __m256d r0p4 = _mm256_set_pd(e01, -e01, -e31, e31);
		const __m256d r0p5 = _mm256_set_pd(e23, e22, e13, e12);
		const __m256d r0p6 = _mm256_set_pd(e32, e33, e22, e23);
		const __m256d r0p456 = _mm256_mul_pd(_mm256_mul_pd(r0p4, r0p5), r0p6);
		const double* const r0f456 = reinterpret_cast<const double*>(&r0p456);

		const __m256d r0p7 = _mm256_set_pd(e31, -e31, -e21, e21);
		const __m256d r0p8 = _mm256_set_pd(e03, e02, e03, e02);
		const __m256d r0p9 = _mm256_set_pd(e22, e23, e32, e33);
		const __m256d r0p789 = _mm256_mul_pd(_mm256_mul_pd(r0p7, r0p8), r0p9);
		const double* const r0f789 = reinterpret_cast<const double*>(&r0p789);

		const __m256d r0pA = _mm256_set_pd(e11, -e11, -e01, e01);
		const __m256d r0pB = _mm256_set_pd(e03, e02, e13, e12);
		const __m256d r0pC = _mm256_set_pd(e32, e33, e32, e33);
		const __m256d r0pABC = _mm256_mul_pd(_mm256_mul_pd(r0pA, r0pB), r0pC);
		const double* const r0fABC = reinterpret_cast<const double*>(&r0pABC);

		const __m256d r0pD = _mm256_set_pd(e01, -e01, -e31, e31);
		const __m256d r0pE = _mm256_set_pd(e13, e12, e03, e02);
		const __m256d r0pF = _mm256_set_pd(e22, e23, e12, e13);
		const __m256d r0pDEF = _mm256_mul_pd(_mm256_mul_pd(r0pD, r0pE), r0pF);
		const double* const r0fDEF = reinterpret_cast<const double*>(&r0pDEF);

		const __m256d r0pG = _mm256_set_pd(e21, -e21, -e11, e11);
		const __m256d r0pH = _mm256_set_pd(e03, e02, e03, e02);
		const __m256d r0pI = _mm256_set_pd(e12, e13, e22, e23);
		const __m256d r0pGHI = _mm256_mul_pd(_mm256_mul_pd(r0pG, r0pH), r0pI);
		const double* const r0fGHI = reinterpret_cast<const double*>(&r0pGHI);

		// Fill elems.
		//res.e00 = r0f123[0] + r0f123[1] + r0f123[2] + r0f123[3] + r0f456[0] + r0f456[1];
		//res.e01 = r0f456[2] + r0f456[3] + r0f789[0] + r0f789[1] + r0f789[2] + r0f789[3];
		//res.e02 = r0fABC[0] + r0fABC[1] + r0fABC[2] + r0fABC[3] + r0fDEF[0] + r0fDEF[1];
		//res.e03 = r0fDEF[2] + r0fDEF[3] + r0fGHI[0] + r0fGHI[1] + r0fGHI[2] + r0fGHI[3];

		const __m256d r0rp1 = _mm256_set_pd(r0fDEF[2], r0fABC[0], r0f456[2], r0f123[0]);
		const __m256d r0rp2 = _mm256_set_pd(r0fDEF[3], r0fABC[1], r0f456[3], r0f123[1]);
		const __m256d r0rp3 = _mm256_set_pd(r0fGHI[0], r0fABC[2], r0f789[0], r0f123[2]);
		const __m256d r0rp4 = _mm256_set_pd(r0fGHI[1], r0fABC[3], r0f789[1], r0f123[3]);
		const __m256d r0rp5 = _mm256_set_pd(r0fGHI[2], r0fDEF[0], r0f789[2], r0f456[0]);
		const __m256d r0rp6 = _mm256_set_pd(r0fGHI[3], r0fDEF[1], r0f789[3], r0f456[1]);

		reinterpret_cast<__m256d&>(data[0]) = _mm256_mul_pd(invDetP, _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(r0rp1, r0rp2), r0rp3), r0rp4), r0rp5), r0rp6));
//}

//{ Row 1
		/*
			e10 =
				(-) e10 * e22 * e33
				(+) e10 * e23 * e32
				(+) e20 * e12 * e33
				(-) e20 * e13 * e32
				(-) e30 * e12 * e23
				(+) e30 * e13 * e22

			e11 =
				(+) e00 * e22 * e33
				(-) e00 * e23 * e32
				(-) e20 * e02 * e33
				(+) e20 * e03 * e32
				(+) e30 * e02 * e23
				(-) e30 * e03 * e22

			e12 =
				(-) e00 * e12 * e33
				(+) e00 * e13 * e32
				(+) e10 * e02 * e33
				(-) e10 * e03 * e32
				(-) e30 * e02 * e13
				(+) e30 * e03 * e12

			e13 =
				(+) e00 * e12 * e23
				(-) e00 * e13 * e22
				(-) e10 * e02 * e23
				(+) e10 * e03 * e22
				(+) e20 * e02 * e13
				(-) e20 * e03 * e12
		*/
		const __m256d r1p1 = _mm256_set_pd(-e20, e20, e10, -e10);
		// r1p2 == r0p2
		// r1p3 == r0p3
		const __m256d r1p123 = _mm256_mul_pd(_mm256_mul_pd(r1p1, r0p2), r0p3);
		const double* const r1f123 = reinterpret_cast<const double*>(&r1p123);

		const __m256d r1p4 = _mm256_set_pd(-e00, e00, e30, -e30);
		// r1p5 == r0p5
		// r1p6 == r0p6
		const __m256d r1p456 = _mm256_mul_pd(_mm256_mul_pd(r1p4, r0p5), r0p6);
		const double* const r1f456 = reinterpret_cast<const double*>(&r1p456);

		const __m256d r1p7 = _mm256_set_pd(-e30, e30, e20, -e20);
		// r1p8 == r0p8
		// r1p9 == r0p9
		const __m256d r1p789 = _mm256_mul_pd(_mm256_mul_pd(r1p7, r0p8), r0p9);
		const double* const r1f789 = reinterpret_cast<const double*>(&r1p789);

		const __m256d r1pA = _mm256_set_pd(-e10, e10, e00, -e00);
		// r1pB == r0pB
		// r1pC == r0pC
		const __m256d r1pABC = _mm256_mul_pd(_mm256_mul_pd(r1pA, r0pB), r0pC);
		const double* const r1fABC = reinterpret_cast<const double*>(&r1pABC);

		const __m256d r1pD = _mm256_set_pd(-e00, e00, e30, -e30);
		// r1pE == r0pE
		// r1pF == r0pF
		const __m256d r1pDEF = _mm256_mul_pd(_mm256_mul_pd(r1pD, r0pE), r0pF);
		const double* const r1fDEF = reinterpret_cast<const double*>(&r1pDEF);

		const __m256d r1pG = _mm256_set_pd(-e20, e20, e10, -e10);
		// r1pH == r0pH
		// r1pI == r0pI
		const __m256d r1pGHI = _mm256_mul_pd(_mm256_mul_pd(r1pG, r0pH), r0pI);
		const double* const r1fGHI = reinterpret_cast<const double*>(&r1pGHI);

		// Fill elems.
		//res.e10 = r1f123[0] + r1f123[1] + r1f123[2] + r1f123[3] + r1f456[0] + r1f456[1];
		//res.e11 = r1f456[2] + r1f456[3] + r1f789[0] + r1f789[1] + r1f789[2] + r1f789[3];
		//res.e12 = r1fABC[0] + r1fABC[1] + r1fABC[2] + r1fABC[3] + r1fDEF[0] + r1fDEF[1];
		//res.e13 = r1fDEF[2] + r1fDEF[3] + r1fGHI[0] + r1fGHI[1] + r1fGHI[2] + r1fGHI[3];

		const __m256d r1rp1 = _mm256_set_pd(r1fDEF[2], r1fABC[0], r1f456[2], r1f123[0]);
		const __m256d r1rp2 = _mm256_set_pd(r1fDEF[3], r1fABC[1], r1f456[3], r1f123[1]);
		const __m256d r1rp3 = _mm256_set_pd(r1fGHI[0], r1fABC[2], r1f789[0], r1f123[2]);
		const __m256d r1rp4 = _mm256_set_pd(r1fGHI[1], r1fABC[3], r1f789[1], r1f123[3]);
		const __m256d r1rp5 = _mm256_set_pd(r1fGHI[2], r1fDEF[0], r1f789[2], r1f456[0]);
		const __m256d r1rp6 = _mm256_set_pd(r1fGHI[3], r1fDEF[1], r1f789[3], r1f456[1]);

		reinterpret_cast<__m256d&>(data[4]) = _mm256_mul_pd(invDetP, _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(r1rp1, r1rp2), r1rp3), r1rp4), r1rp5), r1rp6));

//}

//{ Row 2
		/*
			e20 =
				(+) e10 * e21 * e33
				(-) e10 * e23 * e31
				(-) e20 * e11 * e33
				(+) e20 * e13 * e31
				(+) e30 * e11 * e23
				(-) e30 * e13 * e21

			e21 =
				(-) e00 * e21 * e33
				(+) e00 * e23 * e31
				(+) e20 * e01 * e33
				(-) e20 * e03 * e31
				(-) e30 * e01 * e23
				(+) e30 * e03 * e21

			e22 =
				(+) e00 * e11 * e33
				(-) e00 * e13 * e31
				(-) e10 * e01 * e33
				(+) e10 * e03 * e31
				(+) e30 * e01 * e13
				(-) e30 * e03 * e11

			e23 =
				(-) e00 * e11 * e23
				(+) e00 * e13 * e21
				(+) e10 * e01 * e23
				(-) e10 * e03 * e21
				(-) e20 * e01 * e13
				(+) e20 * e03 * e11

			// Use row 1 pack and inverse all sign in second column (p2, p5, p8, B, E, H)
		*/
		// r2p1 == -r1p1
		const __m256d r2p2 = _mm256_set_pd(-e13, -e11, -e23, -e21);
		const __m256d r2p3 = _mm256_set_pd(e31, e33, e31, e33);
		const __m256d r2p123 = _mm256_mul_pd(_mm256_mul_pd(r1p1, r2p2), r2p3);
		const double* const r2f123 = reinterpret_cast<const double*>(&r2p123);

		// r2p4 == -r1p4
		const __m256d r2p5 = _mm256_set_pd(-e23, -e21, -e13, -e11);
		const __m256d r2p6 = _mm256_set_pd(e31, e33, e21, e23);
		const __m256d r2p456 = _mm256_mul_pd(_mm256_mul_pd(r1p4, r2p5), r2p6);
		const double* const r2f456 = reinterpret_cast<const double*>(&r2p456);

		// r2p7 == -r1p7
		const __m256d r2p8 = _mm256_set_pd(-e03, -e01, -e03, -e01);
		const __m256d r2p9 = _mm256_set_pd(e21, e23, e31, e33);
		const __m256d r2p789 = _mm256_mul_pd(_mm256_mul_pd(r1p7, r2p8), r2p9);
		const double* const r2f789 = reinterpret_cast<const double*>(&r2p789);

		// r2pA == -r1pA
		const __m256d r2pB = _mm256_set_pd(-e03, -e01, -e13, -e11);
		const __m256d r2pC = _mm256_set_pd(e31, e33, e31, e33);
		const __m256d r2pABC = _mm256_mul_pd(_mm256_mul_pd(r1pA, r2pB), r2pC);
		const double* const r2fABC = reinterpret_cast<const double*>(&r2pABC);

		// r2pD == -r1pD
		const __m256d r2pE = _mm256_set_pd(-e13, -e11, -e03, -e01);
		const __m256d r2pF = _mm256_set_pd(e21, e23, e11, e13);
		const __m256d r2pDEF = _mm256_mul_pd(_mm256_mul_pd(r1pD, r2pE), r2pF);
		const double* const r2fDEF = reinterpret_cast<const double*>(&r2pDEF);

		// r2pG == -r1pG
		const __m256d r2pH = _mm256_set_pd(-e03, -e01, -e03, -e01);
		const __m256d r2pI = _mm256_set_pd(e11, e13, e21, e23);
		const __m256d r2pGHI = _mm256_mul_pd(_mm256_mul_pd(r1pG, r2pH), r2pI);
		const double* const r2fGHI = reinterpret_cast<const double*>(&r2pGHI);

		// Fill elems.
		//res.e20 = r2f123[0] + r2f123[1] + r2f123[2] + r2f123[3] + r2f456[0] + r2f456[1];
		//res.e21 = r2f456[2] + r2f456[3] + r2f789[0] + r2f789[1] + r2f789[2] + r2f789[3];
		//res.e22 = r2fABC[0] + r2fABC[1] + r2fABC[2] + r2fABC[3] + r2fDEF[0] + r2fDEF[1];
		//res.e23 = r2fDEF[2] + r2fDEF[3] + r2fGHI[0] + r2fGHI[1] + r2fGHI[2] + r2fGHI[3];

		const __m256d r2rp1 = _mm256_set_pd(r2fDEF[2], r2fABC[0], r2f456[2], r2f123[0]);
		const __m256d r2rp2 = _mm256_set_pd(r2fDEF[3], r2fABC[1], r2f456[3], r2f123[1]);
		const __m256d r2rp3 = _mm256_set_pd(r2fGHI[0], r2fABC[2], r2f789[0], r2f123[2]);
		const __m256d r2rp4 = _mm256_set_pd(r2fGHI[1], r2fABC[3], r2f789[1], r2f123[3]);
		const __m256d r2rp5 = _mm256_set_pd(r2fGHI[2], r2fDEF[0], r2f789[2], r2f456[0]);
		const __m256d r2rp6 = _mm256_set_pd(r2fGHI[3], r2fDEF[1], r2f789[3], r2f456[1]);

		reinterpret_cast<__m256d&>(data[8]) = _mm256_mul_pd(invDetP, _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(r2rp1, r2rp2), r2rp3), r2rp4), r2rp5), r2rp6));

//}

//{ Row 3
		/*
			e30 =
				(-) e10 * e21 * e32
				(+) e10 * e22 * e31
				(+) e20 * e11 * e32
				(-) e20 * e12 * e31
				(-) e30 * e11 * e22
				(+) e30 * e12 * e21

			e31 =
				(+) e00 * e21 * e32
				(-) e00 * e22 * e31
				(-) e20 * e01 * e32
				(+) e20 * e02 * e31
				(+) e30 * e01 * e22
				(-) e30 * e02 * e21

			e32 =
				(-) e00 * e11 * e32
				(+) e00 * e12 * e31
				(+) e10 * e01 * e32
				(-) e10 * e02 * e31
				(-) e30 * e01 * e12
				(+) e30 * e02 * e11

			e33 =
				(+) e00 * e11 * e22
				(-) e00 * e12 * e21
				(-) e10 * e01 * e22
				(+) e10 * e02 * e21
				(+) e20 * e01 * e12
				(-) e20 * e02 * e11
		*/
		// r3p1 = r1p1
		const __m256d r3p2 = _mm256_set_pd(e12, e11, e22, e21);
		const __m256d r3p3 = _mm256_set_pd(e31, e32, e31, e32);
		const __m256d r3p123 = _mm256_mul_pd(_mm256_mul_pd(r1p1, r3p2), r3p3);
		const double* const r3f123 = reinterpret_cast<const double*>(&r3p123);

		// r3p7 = r1p7
		const __m256d r3p5 = _mm256_set_pd(e22, e21, e12, e11);
		const __m256d r3p6 = _mm256_set_pd(e31, e32, e21, e22);
		const __m256d r3p456 = _mm256_mul_pd(_mm256_mul_pd(r1p4, r3p5), r3p6);
		const double* const r3f456 = reinterpret_cast<const double*>(&r3p456);

		// r3p7 = r1p7
		const __m256d r3p8 = _mm256_set_pd(e02, e01, e02, e01);
		const __m256d r3p9 = _mm256_set_pd(e21, e22, e31, e32);
		const __m256d r3p789 = _mm256_mul_pd(_mm256_mul_pd(r1p7, r3p8), r3p9);
		const double* const r3f789 = reinterpret_cast<const double*>(&r3p789);

		// r3pA = r1pA
		const __m256d r3pB = _mm256_set_pd(e02, e01, e12, e11);
		const __m256d r3pC = _mm256_set_pd(e31, e32, e31, e32);
		const __m256d r3pABC = _mm256_mul_pd(_mm256_mul_pd(r1pA, r3pB), r3pC);
		const double* const r3fABC = reinterpret_cast<const double*>(&r3pABC);

		// r3pD = r1pD
		const __m256d r3pE = _mm256_set_pd(e12, e11, e02, e01);
		const __m256d r3pF = _mm256_set_pd(e21, e22, e11, e12);
		const __m256d r3pDEF = _mm256_mul_pd(_mm256_mul_pd(r1pD, r3pE), r3pF);
		const double* const r3fDEF = reinterpret_cast<const double*>(&r3pDEF);

		// r3pG = r1pG
		const __m256d r3pH = _mm256_set_pd(e02, e01, e02, e01);
		const __m256d r3pI = _mm256_set_pd(e11, e12, e21, e22);
		const __m256d r3pGHI = _mm256_mul_pd(_mm256_mul_pd(r1pG, r3pH), r3pI);
		const double* const r3fGHI = reinterpret_cast<const double*>(&r3pGHI);

		// Fill elems.
		//res.e30 = r3f123[0] + r3f123[1] + r3f123[2] + r3f123[3] + r3f456[0] + r3f456[1];
		//res.e31 = r3f456[2] + r3f456[3] + r3f789[0] + r3f789[1] + r3f789[2] + r3f789[3];
		//res.e32 = r3fABC[0] + r3fABC[1] + r3fABC[2] + r3fABC[3] + r3fDEF[0] + r3fDEF[1];
		//res.e33 = r3fDEF[2] + r3fDEF[3] + r3fGHI[0] + r3fGHI[1] + r3fGHI[2] + r3fGHI[3];

		const __m256d r3rp1 = _mm256_set_pd(r3fDEF[2], r3fABC[0], r3f456[2], r3f123[0]);
		const __m256d r3rp2 = _mm256_set_pd(r3fDEF[3], r3fABC[1], r3f456[3], r3f123[1]);
		const __m256d r3rp3 = _mm256_set_pd(r3fGHI[0], r3fABC[2], r3f789[0], r3f123[2]);
		const __m256d r3rp4 = _mm256_set_pd(r3fGHI[1], r3fABC[3], r3f789[1], r3f123[3]);
		const __m256d r3rp5 = _mm256_set_pd(r3fGHI[2], r3fDEF[0], r3f789[2], r3f456[0]);
		const __m256d r3rp6 = _mm256_set_pd(r3fGHI[3], r3fDEF[1], r3f789[3], r3f456[1]);

		reinterpret_cast<__m256d&>(data[12]) = _mm256_mul_pd(invDetP, _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(r3rp1, r3rp2), r3rp3), r3rp4), r3rp5), r3rp6));

//}

		return res;
	}


	template <>
	RMat4d& RMat4d::ApplyScale(const Vec3<double>& _scale) noexcept
	{
		double* const data = Data();

		// Compute row 0
		const __m256d pScaleX = _mm256_set1_pd(_scale.x);
	
		reinterpret_cast<__m256d&>(data[0]) = _mm256_mul_pd(pScaleX, _mm256_load_pd(&data[0]));


		// Compute row 1
		const __m256d pScaleY = _mm256_set1_pd(_scale.y);

		reinterpret_cast<__m256d&>(data[4]) = _mm256_mul_pd(pScaleY, _mm256_load_pd(&data[4]));


		// Compute row 2
		const __m256d pScaleZ = _mm256_set1_pd(_scale.z);

		reinterpret_cast<__m256d&>(data[8]) = _mm256_mul_pd(pScaleZ, _mm256_load_pd(&data[8]));

		return *this;
	}


	template <>
	RMat4d RMat4d::MakeRotation(const Quat<double>& _rot) noexcept
	{
		SA_WARN(_rot.IsNormalized(), Maths, L"Quaternion should be normalized!");

		/*
			return Mat3f(
				1.0 -	2.0 * (_rot.y * _rot.y + _rot.z * _rot.z),
						2.0 * (_rot.x * _rot.y - _rot.z * _rot.w),
						2.0 * (_rot.x * _rot.z + _rot.y * _rot.w),

						2.0 * (_rot.x * _rot.y + _rot.z * _rot.w),
				1.0 -	2.0 * (_rot.x * _rot.x + _rot.z * _rot.z),
						2.0 * (_rot.y * _rot.z - _rot.x * _rot.w),

						2.0 * (_rot.x * _rot.z - _rot.y * _rot.w),
						2.0 * (_rot.y * _rot.z + _rot.x * _rot.w),
				1.0 -	2.0 * (_rot.x * _rot.x + _rot.y * _rot.y)
			);
		*/

		const __m256d pDbl = _mm256_set1_pd(2.0);

		// 4 first elems.
		const __m256d p1 = _mm256_set_pd(_rot.x, _rot.x, _rot.x, _rot.y);
		const __m256d p2 = _mm256_set_pd(_rot.y, _rot.z, _rot.y, _rot.y);
		const __m256d p3 = _mm256_set_pd(_rot.z, _rot.y, -_rot.z, _rot.z);
		const __m256d p4 = _mm256_set_pd(_rot.w, _rot.w, _rot.w, _rot.z);

		__m256d p1234 = _mm256_mul_pd(pDbl, _mm256_add_pd(_mm256_mul_pd(p1, p2), _mm256_mul_pd(p3, p4)));
		double* const d1234 = reinterpret_cast<double*>(&p1234);

		// Apply 1.0 - value.
		d1234[0] = 1.0 - d1234[0];


		// 4 next elems.
		const __m256d p5 = _mm256_set_pd(_rot.y, _rot.x, _rot.y, _rot.x);
		const __m256d p6 = _mm256_set_pd(_rot.z, _rot.z, _rot.z, _rot.x);
		const __m256d p7 = _mm256_set_pd(_rot.x, -_rot.y, -_rot.x, _rot.z);
		const __m256d p8 = _mm256_set_pd(_rot.w, _rot.w, _rot.w, _rot.z);

		__m256d p5678 = _mm256_mul_pd(pDbl, _mm256_add_pd(_mm256_mul_pd(p5, p6), _mm256_mul_pd(p7, p8)));
		double* const d5678 = reinterpret_cast<double*>(&p5678);

		// Apply 1.0 - value.
		d5678[0] = 1.0 - d5678[0];


		// Last elem.
		double e22 = 1.0 - 2.0 * (_rot.x * _rot.x + _rot.y * _rot.y);


		return Mat4(
			d1234[0], d1234[1], d1234[2], 0.0,
			d1234[3], d5678[0], d5678[1], 0.0,
			d5678[2], d5678[3], e22, 0.0,
			0.0, 0.0, 0.0, 1.0
		);
	}


	template <>
	RMat4d RMat4d::operator*(double _scale) const noexcept
	{
		Mat4 res;
		double* const fres = res.Data();
		const double* const data = Data();
		
		const __m256d sPack = _mm256_set1_pd(_scale);


		// Mult row 0.
		reinterpret_cast<__m256d&>(fres[0]) = _mm256_mul_pd(_mm256_load_pd(&data[0]), sPack);

		// Mult row 1.
		reinterpret_cast<__m256d&>(fres[4]) = _mm256_mul_pd(_mm256_load_pd(&data[4]), sPack);

		// Mult row 2.
		reinterpret_cast<__m256d&>(fres[8]) = _mm256_mul_pd(_mm256_load_pd(&data[8]), sPack);

		// Mult row 3.
		reinterpret_cast<__m256d&>(fres[12]) = _mm256_mul_pd(_mm256_load_pd(&data[12]), sPack);

		return res;
	}

	template <>
	RMat4d RMat4d::operator/(double _scale) const noexcept
	{
		Mat4 res;
		double* const fres = res.Data();
		const double* const data = Data();

		const __m256d sPack = _mm256_set1_pd(_scale);


		// Div row 0.
		reinterpret_cast<__m256d&>(fres[0]) = _mm256_div_pd(_mm256_load_pd(&data[0]), sPack);

		// Div row 1.
		reinterpret_cast<__m256d&>(fres[4]) = _mm256_div_pd(_mm256_load_pd(&data[4]), sPack);

		// Div row 2.
		reinterpret_cast<__m256d&>(fres[8]) = _mm256_div_pd(_mm256_load_pd(&data[8]), sPack);

		// Div row 3.
		reinterpret_cast<__m256d&>(fres[12]) = _mm256_div_pd(_mm256_load_pd(&data[12]), sPack);

		return res;
	}

	template <>
	RMat4d RMat4d::operator+(const RMat4d& _rhs) const noexcept
	{
		Mat4 res;
		double* const fres = res.Data();
		const double* const ldata = Data();
		const double* const rdata = _rhs.Data();


		// Add row 0.
		reinterpret_cast<__m256d&>(fres[0]) = _mm256_add_pd(_mm256_load_pd(&ldata[0]), _mm256_load_pd(&rdata[0]));

		// Add row 1.
		reinterpret_cast<__m256d&>(fres[4]) = _mm256_add_pd(_mm256_load_pd(&ldata[4]), _mm256_load_pd(&rdata[4]));

		// Add row 2.
		reinterpret_cast<__m256d&>(fres[8]) = _mm256_add_pd(_mm256_load_pd(&ldata[8]), _mm256_load_pd(&rdata[8]));

		// Add row 3.
		reinterpret_cast<__m256d&>(fres[12]) = _mm256_add_pd(_mm256_load_pd(&ldata[12]), _mm256_load_pd(&rdata[12]));

		return res;
	}

	template <>
	RMat4d RMat4d::operator-(const RMat4d& _rhs) const noexcept
	{
		Mat4 res;
		double* const fres = res.Data();
		const double* const ldata = Data();
		const double* const rdata = _rhs.Data();

		// Sub row 0.
		reinterpret_cast<__m256d&>(fres[0]) = _mm256_sub_pd(_mm256_load_pd(&ldata[0]), _mm256_load_pd(&rdata[0]));

		// Sub row 1.
		reinterpret_cast<__m256d&>(fres[4]) = _mm256_sub_pd(_mm256_load_pd(&ldata[4]), _mm256_load_pd(&rdata[4]));

		// Sub row 2.
		reinterpret_cast<__m256d&>(fres[8]) = _mm256_sub_pd(_mm256_load_pd(&ldata[8]), _mm256_load_pd(&rdata[8]));

		// Sub row 3.
		reinterpret_cast<__m256d&>(fres[12]) = _mm256_sub_pd(_mm256_load_pd(&ldata[12]), _mm256_load_pd(&rdata[12]));

		return res;
	}

	template <>
	RMat4d RMat4d::operator*(const RMat4d& _rhs) const noexcept
	{
		Mat4 res;
		double* const data = res.Data();

		const __m256d rRow0 = _mm256_set_pd(_rhs.e03, _rhs.e02, _rhs.e01, _rhs.e00);
		const __m256d rRow1 = _mm256_set_pd(_rhs.e13, _rhs.e12, _rhs.e11, _rhs.e10);
		const __m256d rRow2 = _mm256_set_pd(_rhs.e23, _rhs.e22, _rhs.e21, _rhs.e20);
		const __m256d rRow3 = _mm256_set_pd(_rhs.e33, _rhs.e32, _rhs.e31, _rhs.e30);

		// Row 0.
		reinterpret_cast<__m256d&>(data[0]) = _mm256_add_pd(
			_mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd(e00), rRow0), _mm256_mul_pd(_mm256_set1_pd(e01), rRow1)),
			_mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd(e02), rRow2), _mm256_mul_pd(_mm256_set1_pd(e03), rRow3))
		);

		// Row 1.
		reinterpret_cast<__m256d&>(data[4]) = _mm256_add_pd(
			_mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd(e10), rRow0), _mm256_mul_pd(_mm256_set1_pd(e11), rRow1)),
			_mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd(e12), rRow2), _mm256_mul_pd(_mm256_set1_pd(e13), rRow3))
		);

		// Row 2.
		reinterpret_cast<__m256d&>(data[8]) = _mm256_add_pd(
			_mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd(e20), rRow0), _mm256_mul_pd(_mm256_set1_pd(e21), rRow1)),
			_mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd(e22), rRow2), _mm256_mul_pd(_mm256_set1_pd(e23), rRow3))
		);

		// Row 3.
		reinterpret_cast<__m256d&>(data[12]) = _mm256_add_pd(
			_mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd(e30), rRow0), _mm256_mul_pd(_mm256_set1_pd(e31), rRow1)),
			_mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd(e32), rRow2), _mm256_mul_pd(_mm256_set1_pd(e33), rRow3))
		);

		return res;
	}


	template <>
	Vec3<double> RMat4d::operator*(const Vec3<double>& _rhs) const noexcept
	{
		const __m256d p0 = _mm256_mul_pd(_mm256_set1_pd(_rhs.x), _mm256_set_pd(0.0, e20, e10, e00));
		const __m256d p1 = _mm256_mul_pd(_mm256_set1_pd(_rhs.y), _mm256_set_pd(0.0, e21, e11, e01));
		const __m256d p2 = _mm256_mul_pd(_mm256_set1_pd(_rhs.z), _mm256_set_pd(0.0, e22, e12, e02));

		// Use Vec4 for padding.
		Vec4d res;

		reinterpret_cast<__m256d&>(res) = _mm256_add_pd(_mm256_add_pd(p0, p1), p2);

		return res;
	}

	template <>
	Vec4<double> RMat4d::operator*(const Vec4<double>& _rhs) const noexcept
	{
		const __m256d p0 = _mm256_mul_pd(_mm256_set1_pd(_rhs.x), _mm256_set_pd(e30, e20, e10, e00));
		const __m256d p1 = _mm256_mul_pd(_mm256_set1_pd(_rhs.y), _mm256_set_pd(e31, e21, e11, e01));
		const __m256d p2 = _mm256_mul_pd(_mm256_set1_pd(_rhs.z), _mm256_set_pd(e32, e22, e12, e02));
		const __m256d p3 = _mm256_mul_pd(_mm256_set1_pd(_rhs.w), _mm256_set_pd(e33, e23, e13, e03));

		Vec4d res;

		reinterpret_cast<__m256d&>(res) = _mm256_add_pd(_mm256_add_pd(p0, p1), _mm256_add_pd(p2, p3));

		return res;
	}


	template <>
	RMat4d& RMat4d::operator*=(double _scale) noexcept
	{
		double* const data = Data();
		const __m256d sPack = _mm256_set1_pd(_scale);

		// Mult row 0.
		reinterpret_cast<__m256d&>(data[0]) = _mm256_mul_pd(_mm256_load_pd(&data[0]), sPack);

		// Mult row 1.
		reinterpret_cast<__m256d&>(data[4]) = _mm256_mul_pd(_mm256_load_pd(&data[4]), sPack);

		// Mult row 2.
		reinterpret_cast<__m256d&>(data[8]) = _mm256_mul_pd(_mm256_load_pd(&data[8]), sPack);

		// Mult row 3.
		reinterpret_cast<__m256d&>(data[12]) = _mm256_mul_pd(_mm256_load_pd(&data[12]), sPack);

		return *this;
	}

	template <>
	RMat4d& RMat4d::operator/=(double _scale) noexcept
	{
		double* const data = Data();
		const __m256d sPack = _mm256_set1_pd(_scale);

		// Div row 0.
		reinterpret_cast<__m256d&>(data[0]) = _mm256_div_pd(_mm256_load_pd(&data[0]), sPack);

		// Div row 1.
		reinterpret_cast<__m256d&>(data[4]) = _mm256_div_pd(_mm256_load_pd(&data[4]), sPack);

		// Div row 2.
		reinterpret_cast<__m256d&>(data[8]) = _mm256_div_pd(_mm256_load_pd(&data[8]), sPack);

		// Div row 3.
		reinterpret_cast<__m256d&>(data[12]) = _mm256_div_pd(_mm256_load_pd(&data[12]), sPack);

		return *this;
	}

	template <>
	RMat4d& RMat4d::operator+=(const RMat4d& _rhs) noexcept
	{
		double* const ldata = Data();
		const double* const rdata = _rhs.Data();

		// Add row 0.
		reinterpret_cast<__m256d&>(ldata[0]) = _mm256_add_pd(_mm256_load_pd(&ldata[0]), _mm256_load_pd(&rdata[0]));

		// Add row 1.
		reinterpret_cast<__m256d&>(ldata[4]) = _mm256_add_pd(_mm256_load_pd(&ldata[4]), _mm256_load_pd(&rdata[4]));

		// Add row 2.
		reinterpret_cast<__m256d&>(ldata[8]) = _mm256_add_pd(_mm256_load_pd(&ldata[8]), _mm256_load_pd(&rdata[8]));

		// Add row 3.
		reinterpret_cast<__m256d&>(ldata[12]) = _mm256_add_pd(_mm256_load_pd(&ldata[12]), _mm256_load_pd(&rdata[12]));

		return *this;
	}

	template <>
	RMat4d& RMat4d::operator-=(const RMat4d& _rhs) noexcept
	{
		double* const ldata = Data();
		const double* const rdata = _rhs.Data();

		// Sub row 0.
		reinterpret_cast<__m256d&>(ldata[0]) = _mm256_sub_pd(_mm256_load_pd(&ldata[0]), _mm256_load_pd(&rdata[0]));

		// Sub row 1.
		reinterpret_cast<__m256d&>(ldata[4]) = _mm256_sub_pd(_mm256_load_pd(&ldata[4]), _mm256_load_pd(&rdata[4]));

		// Sub row 2.
		reinterpret_cast<__m256d&>(ldata[8]) = _mm256_sub_pd(_mm256_load_pd(&ldata[8]), _mm256_load_pd(&rdata[8]));

		// Sub row 3.
		reinterpret_cast<__m256d&>(ldata[12]) = _mm256_sub_pd(_mm256_load_pd(&ldata[12]), _mm256_load_pd(&rdata[12]));

		return *this;
	}


	template <>
	RMat4d operator/(double _lhs, const RMat4d& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.e00), Maths, L"Inverse scale matrix e00 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e01), Maths, L"Inverse scale matrix e01 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e02), Maths, L"Inverse scale matrix e02 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e03), Maths, L"Inverse scale matrix e03 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e10), Maths, L"Inverse scale matrix e10 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e11), Maths, L"Inverse scale matrix e11 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e12), Maths, L"Inverse scale matrix e12 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e13), Maths, L"Inverse scale matrix e13 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e20), Maths, L"Inverse scale matrix e20 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e21), Maths, L"Inverse scale matrix e21 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e22), Maths, L"Inverse scale matrix e22 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e23), Maths, L"Inverse scale matrix e23 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e30), Maths, L"Inverse scale matrix e30 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e31), Maths, L"Inverse scale matrix e31 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e32), Maths, L"Inverse scale matrix e32 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e33), Maths, L"Inverse scale matrix e33 == 0!");

		RMat4d res;
		double* const fres = res.Data();
		const double* const data = _rhs.Data();
		const __m256d sPack = _mm256_set1_pd(_lhs);


		// Div row 0.
		reinterpret_cast<__m256d&>(fres[0]) = _mm256_div_pd(sPack, _mm256_load_pd(&data[0]));

		// Div row 1.
		reinterpret_cast<__m256d&>(fres[4]) = _mm256_div_pd(sPack, _mm256_load_pd(&data[4]));

		// Div row 2.
		reinterpret_cast<__m256d&>(fres[8]) = _mm256_div_pd(sPack, _mm256_load_pd(&data[8]));

		// Div row 3.
		reinterpret_cast<__m256d&>(fres[12]) = _mm256_div_pd(sPack, _mm256_load_pd(&data[12]));

		return res;
	}

//}

//{ Column Major

	template <>
	double CMat4d::Determinant() const noexcept
	{
		/*
			return
				e00 * (e11 * (e22 * e33 - e23 * e32) - e21 * (e12 * e33 - e13 * e32) + e31 * (e12 * e23 - e13 * e22)) -
				e10 * (e01 * (e22 * e33 - e23 * e32) - e21 * (e02 * e33 - e03 * e32) + e31 * (e02 * e23 - e03 * e22)) +
				e20 * (e01 * (e12 * e33 - e13 * e32) - e11 * (e02 * e33 - e03 * e32) + e31 * (e02 * e13 - e03 * e12)) -
				e30 * (e01 * (e12 * e23 - e13 * e22) - e11 * (e02 * e23 - e03 * e22) + e21 * (e02 * e13 - e03 * e12));
		*/

		const __m256d p0 = _mm256_set_pd(e01, e01, e01, e11);
		const __m256d p1 = _mm256_set_pd(e12, e12, e22, e22);
		const __m256d p2 = _mm256_set_pd(e23, e33, e33, e33);
		const __m256d p3 = _mm256_set_pd(e13, e13, e23, e23);
		const __m256d p4 = _mm256_set_pd(e22, e32, e32, e32);
		const __m256d p01234 = _mm256_mul_pd(p0, _mm256_sub_pd(_mm256_mul_pd(p1, p2), _mm256_mul_pd(p3, p4)));


		const __m256d p5 = _mm256_set_pd(e11, e11, e21, e21);
		const __m256d p6 = _mm256_set_pd(e02, e02, e02, e12);
		// p7 == p2.
		const __m256d p8 = _mm256_set_pd(e03, e03, e03, e13);
		// p9 == p4.
		const __m256d p56789 = _mm256_mul_pd(p5, _mm256_sub_pd(_mm256_mul_pd(p6, p2), _mm256_mul_pd(p8, p4)));


		const __m256d p10 = _mm256_set_pd(e21, e31, e31, e31);
		// p11 == p6
		// p12 == p3
		// p13 == p8
		// p14 == p1
		const __m256d p10_11_12_13_14 = _mm256_mul_pd(p10, _mm256_sub_pd(_mm256_mul_pd(p6, p3), _mm256_mul_pd(p8, p1)));

		const __m256d coefP = _mm256_set_pd(e30, e20, e10, e00);
		const __m256d total = _mm256_mul_pd(coefP, _mm256_add_pd(_mm256_sub_pd(p01234, p56789), p10_11_12_13_14));
		const double* const dTotal = reinterpret_cast<const double*>(&total);

		return dTotal[0] - dTotal[1] + dTotal[2] - dTotal[3];
	}

	template <>
	CMat4d CMat4d::GetInversed() const noexcept
	{
		Mat4 res;
		double* const data = res.Data();
		const double det = Determinant();

		SA_WARN(!Sa::Equals0(det), Maths, L"Inverse matrix with determinant == 0");

		const double invDet = 1.0f / det;
		const __m256d invDetP = _mm256_set1_pd(invDet);

//{ Row 0
		/*
			e00 =
				(+) e11 * e22 * e33
				(-) e11 * e23 * e32
				(-) e21 * e12 * e33
				(+) e21 * e13 * e32
				(+) e31 * e12 * e23
				(-) e31 * e13 * e22

			e01 =
				(-) e01 * e22 * e33
				(+) e01 * e23 * e32
				(+) e21 * e02 * e33
				(-) e21 * e03 * e32
				(-) e31 * e02 * e23
				(+) e31 * e03 * e22

			e02 =
				(+) e01 * e12 * e33
				(-) e01 * e13 * e32
				(-) e11 * e02 * e33
				(+) e11 * e03 * e32
				(+) e31 * e02 * e13
				(-) e31 * e03 * e12

			e03 =
				(-) e01 * e12 * e23
				(+) e01 * e13 * e22
				(+) e11 * e02 * e23
				(-) e11 * e03 * e22
				(-) e21 * e02 * e13
				(+) e21 * e03 * e12
		*/
		const __m256d r0p1 = _mm256_set_pd(e21, -e21, -e11, e11);
		const __m256d r0p2 = _mm256_set_pd(e13, e12, e23, e22);
		const __m256d r0p3 = _mm256_set_pd(e32, e33, e32, e33);
		const __m256d r0p123 = _mm256_mul_pd(_mm256_mul_pd(r0p1, r0p2), r0p3);
		const double* const r0f123 = reinterpret_cast<const double*>(&r0p123);

		const __m256d r0p4 = _mm256_set_pd(e01, -e01, -e31, e31);
		const __m256d r0p5 = _mm256_set_pd(e23, e22, e13, e12);
		const __m256d r0p6 = _mm256_set_pd(e32, e33, e22, e23);
		const __m256d r0p456 = _mm256_mul_pd(_mm256_mul_pd(r0p4, r0p5), r0p6);
		const double* const r0f456 = reinterpret_cast<const double*>(&r0p456);

		const __m256d r0p7 = _mm256_set_pd(e31, -e31, -e21, e21);
		const __m256d r0p8 = _mm256_set_pd(e03, e02, e03, e02);
		const __m256d r0p9 = _mm256_set_pd(e22, e23, e32, e33);
		const __m256d r0p789 = _mm256_mul_pd(_mm256_mul_pd(r0p7, r0p8), r0p9);
		const double* const r0f789 = reinterpret_cast<const double*>(&r0p789);

		const __m256d r0pA = _mm256_set_pd(e11, -e11, -e01, e01);
		const __m256d r0pB = _mm256_set_pd(e03, e02, e13, e12);
		const __m256d r0pC = _mm256_set_pd(e32, e33, e32, e33);
		const __m256d r0pABC = _mm256_mul_pd(_mm256_mul_pd(r0pA, r0pB), r0pC);
		const double* const r0fABC = reinterpret_cast<const double*>(&r0pABC);

		const __m256d r0pD = _mm256_set_pd(e01, -e01, -e31, e31);
		const __m256d r0pE = _mm256_set_pd(e13, e12, e03, e02);
		const __m256d r0pF = _mm256_set_pd(e22, e23, e12, e13);
		const __m256d r0pDEF = _mm256_mul_pd(_mm256_mul_pd(r0pD, r0pE), r0pF);
		const double* const r0fDEF = reinterpret_cast<const double*>(&r0pDEF);

		const __m256d r0pG = _mm256_set_pd(e21, -e21, -e11, e11);
		const __m256d r0pH = _mm256_set_pd(e03, e02, e03, e02);
		const __m256d r0pI = _mm256_set_pd(e12, e13, e22, e23);
		const __m256d r0pGHI = _mm256_mul_pd(_mm256_mul_pd(r0pG, r0pH), r0pI);
		const double* const r0fGHI = reinterpret_cast<const double*>(&r0pGHI);

		// Fill elems.
		//res.e00 = r0f123[0] + r0f123[1] + r0f123[2] + r0f123[3] + r0f456[0] + r0f456[1];
		//res.e01 = r0f456[2] + r0f456[3] + r0f789[0] + r0f789[1] + r0f789[2] + r0f789[3];
		//res.e02 = r0fABC[0] + r0fABC[1] + r0fABC[2] + r0fABC[3] + r0fDEF[0] + r0fDEF[1];
		//res.e03 = r0fDEF[2] + r0fDEF[3] + r0fGHI[0] + r0fGHI[1] + r0fGHI[2] + r0fGHI[3];

		const __m256d r0rp1 = _mm256_set_pd(r0fDEF[2], r0fABC[0], r0f456[2], r0f123[0]);
		const __m256d r0rp2 = _mm256_set_pd(r0fDEF[3], r0fABC[1], r0f456[3], r0f123[1]);
		const __m256d r0rp3 = _mm256_set_pd(r0fGHI[0], r0fABC[2], r0f789[0], r0f123[2]);
		const __m256d r0rp4 = _mm256_set_pd(r0fGHI[1], r0fABC[3], r0f789[1], r0f123[3]);
		const __m256d r0rp5 = _mm256_set_pd(r0fGHI[2], r0fDEF[0], r0f789[2], r0f456[0]);
		const __m256d r0rp6 = _mm256_set_pd(r0fGHI[3], r0fDEF[1], r0f789[3], r0f456[1]);

		reinterpret_cast<__m256d&>(data[0]) = _mm256_mul_pd(invDetP, _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(r0rp1, r0rp2), r0rp3), r0rp4), r0rp5), r0rp6));
//}

//{ Row 1
		/*
			e10 =
				(-) e10 * e22 * e33
				(+) e10 * e23 * e32
				(+) e20 * e12 * e33
				(-) e20 * e13 * e32
				(-) e30 * e12 * e23
				(+) e30 * e13 * e22

			e11 =
				(+) e00 * e22 * e33
				(-) e00 * e23 * e32
				(-) e20 * e02 * e33
				(+) e20 * e03 * e32
				(+) e30 * e02 * e23
				(-) e30 * e03 * e22

			e12 =
				(-) e00 * e12 * e33
				(+) e00 * e13 * e32
				(+) e10 * e02 * e33
				(-) e10 * e03 * e32
				(-) e30 * e02 * e13
				(+) e30 * e03 * e12

			e13 =
				(+) e00 * e12 * e23
				(-) e00 * e13 * e22
				(-) e10 * e02 * e23
				(+) e10 * e03 * e22
				(+) e20 * e02 * e13
				(-) e20 * e03 * e12
		*/
		const __m256d r1p1 = _mm256_set_pd(-e20, e20, e10, -e10);
		// r1p2 == r0p2
		// r1p3 == r0p3
		const __m256d r1p123 = _mm256_mul_pd(_mm256_mul_pd(r1p1, r0p2), r0p3);
		const double* const r1f123 = reinterpret_cast<const double*>(&r1p123);

		const __m256d r1p4 = _mm256_set_pd(-e00, e00, e30, -e30);
		// r1p5 == r0p5
		// r1p6 == r0p6
		const __m256d r1p456 = _mm256_mul_pd(_mm256_mul_pd(r1p4, r0p5), r0p6);
		const double* const r1f456 = reinterpret_cast<const double*>(&r1p456);

		const __m256d r1p7 = _mm256_set_pd(-e30, e30, e20, -e20);
		// r1p8 == r0p8
		// r1p9 == r0p9
		const __m256d r1p789 = _mm256_mul_pd(_mm256_mul_pd(r1p7, r0p8), r0p9);
		const double* const r1f789 = reinterpret_cast<const double*>(&r1p789);

		const __m256d r1pA = _mm256_set_pd(-e10, e10, e00, -e00);
		// r1pB == r0pB
		// r1pC == r0pC
		const __m256d r1pABC = _mm256_mul_pd(_mm256_mul_pd(r1pA, r0pB), r0pC);
		const double* const r1fABC = reinterpret_cast<const double*>(&r1pABC);

		const __m256d r1pD = _mm256_set_pd(-e00, e00, e30, -e30);
		// r1pE == r0pE
		// r1pF == r0pF
		const __m256d r1pDEF = _mm256_mul_pd(_mm256_mul_pd(r1pD, r0pE), r0pF);
		const double* const r1fDEF = reinterpret_cast<const double*>(&r1pDEF);

		const __m256d r1pG = _mm256_set_pd(-e20, e20, e10, -e10);
		// r1pH == r0pH
		// r1pI == r0pI
		const __m256d r1pGHI = _mm256_mul_pd(_mm256_mul_pd(r1pG, r0pH), r0pI);
		const double* const r1fGHI = reinterpret_cast<const double*>(&r1pGHI);

		// Fill elems.
		//res.e10 = r1f123[0] + r1f123[1] + r1f123[2] + r1f123[3] + r1f456[0] + r1f456[1];
		//res.e11 = r1f456[2] + r1f456[3] + r1f789[0] + r1f789[1] + r1f789[2] + r1f789[3];
		//res.e12 = r1fABC[0] + r1fABC[1] + r1fABC[2] + r1fABC[3] + r1fDEF[0] + r1fDEF[1];
		//res.e13 = r1fDEF[2] + r1fDEF[3] + r1fGHI[0] + r1fGHI[1] + r1fGHI[2] + r1fGHI[3];

		const __m256d r1rp1 = _mm256_set_pd(r1fDEF[2], r1fABC[0], r1f456[2], r1f123[0]);
		const __m256d r1rp2 = _mm256_set_pd(r1fDEF[3], r1fABC[1], r1f456[3], r1f123[1]);
		const __m256d r1rp3 = _mm256_set_pd(r1fGHI[0], r1fABC[2], r1f789[0], r1f123[2]);
		const __m256d r1rp4 = _mm256_set_pd(r1fGHI[1], r1fABC[3], r1f789[1], r1f123[3]);
		const __m256d r1rp5 = _mm256_set_pd(r1fGHI[2], r1fDEF[0], r1f789[2], r1f456[0]);
		const __m256d r1rp6 = _mm256_set_pd(r1fGHI[3], r1fDEF[1], r1f789[3], r1f456[1]);

		reinterpret_cast<__m256d&>(data[4]) = _mm256_mul_pd(invDetP, _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(r1rp1, r1rp2), r1rp3), r1rp4), r1rp5), r1rp6));

//}

//{ Row 2
		/*
			e20 =
				(+) e10 * e21 * e33
				(-) e10 * e23 * e31
				(-) e20 * e11 * e33
				(+) e20 * e13 * e31
				(+) e30 * e11 * e23
				(-) e30 * e13 * e21

			e21 =
				(-) e00 * e21 * e33
				(+) e00 * e23 * e31
				(+) e20 * e01 * e33
				(-) e20 * e03 * e31
				(-) e30 * e01 * e23
				(+) e30 * e03 * e21

			e22 =
				(+) e00 * e11 * e33
				(-) e00 * e13 * e31
				(-) e10 * e01 * e33
				(+) e10 * e03 * e31
				(+) e30 * e01 * e13
				(-) e30 * e03 * e11

			e23 =
				(-) e00 * e11 * e23
				(+) e00 * e13 * e21
				(+) e10 * e01 * e23
				(-) e10 * e03 * e21
				(-) e20 * e01 * e13
				(+) e20 * e03 * e11

			// Use row 1 pack and inverse all sign in second column (p2, p5, p8, B, E, H)
		*/
		// r2p1 == -r1p1
		const __m256d r2p2 = _mm256_set_pd(-e13, -e11, -e23, -e21);
		const __m256d r2p3 = _mm256_set_pd(e31, e33, e31, e33);
		const __m256d r2p123 = _mm256_mul_pd(_mm256_mul_pd(r1p1, r2p2), r2p3);
		const double* const r2f123 = reinterpret_cast<const double*>(&r2p123);

		// r2p4 == -r1p4
		const __m256d r2p5 = _mm256_set_pd(-e23, -e21, -e13, -e11);
		const __m256d r2p6 = _mm256_set_pd(e31, e33, e21, e23);
		const __m256d r2p456 = _mm256_mul_pd(_mm256_mul_pd(r1p4, r2p5), r2p6);
		const double* const r2f456 = reinterpret_cast<const double*>(&r2p456);

		// r2p7 == -r1p7
		const __m256d r2p8 = _mm256_set_pd(-e03, -e01, -e03, -e01);
		const __m256d r2p9 = _mm256_set_pd(e21, e23, e31, e33);
		const __m256d r2p789 = _mm256_mul_pd(_mm256_mul_pd(r1p7, r2p8), r2p9);
		const double* const r2f789 = reinterpret_cast<const double*>(&r2p789);

		// r2pA == -r1pA
		const __m256d r2pB = _mm256_set_pd(-e03, -e01, -e13, -e11);
		const __m256d r2pC = _mm256_set_pd(e31, e33, e31, e33);
		const __m256d r2pABC = _mm256_mul_pd(_mm256_mul_pd(r1pA, r2pB), r2pC);
		const double* const r2fABC = reinterpret_cast<const double*>(&r2pABC);

		// r2pD == -r1pD
		const __m256d r2pE = _mm256_set_pd(-e13, -e11, -e03, -e01);
		const __m256d r2pF = _mm256_set_pd(e21, e23, e11, e13);
		const __m256d r2pDEF = _mm256_mul_pd(_mm256_mul_pd(r1pD, r2pE), r2pF);
		const double* const r2fDEF = reinterpret_cast<const double*>(&r2pDEF);

		// r2pG == -r1pG
		const __m256d r2pH = _mm256_set_pd(-e03, -e01, -e03, -e01);
		const __m256d r2pI = _mm256_set_pd(e11, e13, e21, e23);
		const __m256d r2pGHI = _mm256_mul_pd(_mm256_mul_pd(r1pG, r2pH), r2pI);
		const double* const r2fGHI = reinterpret_cast<const double*>(&r2pGHI);

		// Fill elems.
		//res.e20 = r2f123[0] + r2f123[1] + r2f123[2] + r2f123[3] + r2f456[0] + r2f456[1];
		//res.e21 = r2f456[2] + r2f456[3] + r2f789[0] + r2f789[1] + r2f789[2] + r2f789[3];
		//res.e22 = r2fABC[0] + r2fABC[1] + r2fABC[2] + r2fABC[3] + r2fDEF[0] + r2fDEF[1];
		//res.e23 = r2fDEF[2] + r2fDEF[3] + r2fGHI[0] + r2fGHI[1] + r2fGHI[2] + r2fGHI[3];

		const __m256d r2rp1 = _mm256_set_pd(r2fDEF[2], r2fABC[0], r2f456[2], r2f123[0]);
		const __m256d r2rp2 = _mm256_set_pd(r2fDEF[3], r2fABC[1], r2f456[3], r2f123[1]);
		const __m256d r2rp3 = _mm256_set_pd(r2fGHI[0], r2fABC[2], r2f789[0], r2f123[2]);
		const __m256d r2rp4 = _mm256_set_pd(r2fGHI[1], r2fABC[3], r2f789[1], r2f123[3]);
		const __m256d r2rp5 = _mm256_set_pd(r2fGHI[2], r2fDEF[0], r2f789[2], r2f456[0]);
		const __m256d r2rp6 = _mm256_set_pd(r2fGHI[3], r2fDEF[1], r2f789[3], r2f456[1]);

		reinterpret_cast<__m256d&>(data[8]) = _mm256_mul_pd(invDetP, _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(r2rp1, r2rp2), r2rp3), r2rp4), r2rp5), r2rp6));

//}

//{ Row 3
		/*
			e30 =
				(-) e10 * e21 * e32
				(+) e10 * e22 * e31
				(+) e20 * e11 * e32
				(-) e20 * e12 * e31
				(-) e30 * e11 * e22
				(+) e30 * e12 * e21

			e31 =
				(+) e00 * e21 * e32
				(-) e00 * e22 * e31
				(-) e20 * e01 * e32
				(+) e20 * e02 * e31
				(+) e30 * e01 * e22
				(-) e30 * e02 * e21

			e32 =
				(-) e00 * e11 * e32
				(+) e00 * e12 * e31
				(+) e10 * e01 * e32
				(-) e10 * e02 * e31
				(-) e30 * e01 * e12
				(+) e30 * e02 * e11

			e33 =
				(+) e00 * e11 * e22
				(-) e00 * e12 * e21
				(-) e10 * e01 * e22
				(+) e10 * e02 * e21
				(+) e20 * e01 * e12
				(-) e20 * e02 * e11
		*/
		// r3p1 = r1p1
		const __m256d r3p2 = _mm256_set_pd(e12, e11, e22, e21);
		const __m256d r3p3 = _mm256_set_pd(e31, e32, e31, e32);
		const __m256d r3p123 = _mm256_mul_pd(_mm256_mul_pd(r1p1, r3p2), r3p3);
		const double* const r3f123 = reinterpret_cast<const double*>(&r3p123);

		// r3p7 = r1p7
		const __m256d r3p5 = _mm256_set_pd(e22, e21, e12, e11);
		const __m256d r3p6 = _mm256_set_pd(e31, e32, e21, e22);
		const __m256d r3p456 = _mm256_mul_pd(_mm256_mul_pd(r1p4, r3p5), r3p6);
		const double* const r3f456 = reinterpret_cast<const double*>(&r3p456);

		// r3p7 = r1p7
		const __m256d r3p8 = _mm256_set_pd(e02, e01, e02, e01);
		const __m256d r3p9 = _mm256_set_pd(e21, e22, e31, e32);
		const __m256d r3p789 = _mm256_mul_pd(_mm256_mul_pd(r1p7, r3p8), r3p9);
		const double* const r3f789 = reinterpret_cast<const double*>(&r3p789);

		// r3pA = r1pA
		const __m256d r3pB = _mm256_set_pd(e02, e01, e12, e11);
		const __m256d r3pC = _mm256_set_pd(e31, e32, e31, e32);
		const __m256d r3pABC = _mm256_mul_pd(_mm256_mul_pd(r1pA, r3pB), r3pC);
		const double* const r3fABC = reinterpret_cast<const double*>(&r3pABC);

		// r3pD = r1pD
		const __m256d r3pE = _mm256_set_pd(e12, e11, e02, e01);
		const __m256d r3pF = _mm256_set_pd(e21, e22, e11, e12);
		const __m256d r3pDEF = _mm256_mul_pd(_mm256_mul_pd(r1pD, r3pE), r3pF);
		const double* const r3fDEF = reinterpret_cast<const double*>(&r3pDEF);

		// r3pG = r1pG
		const __m256d r3pH = _mm256_set_pd(e02, e01, e02, e01);
		const __m256d r3pI = _mm256_set_pd(e11, e12, e21, e22);
		const __m256d r3pGHI = _mm256_mul_pd(_mm256_mul_pd(r1pG, r3pH), r3pI);
		const double* const r3fGHI = reinterpret_cast<const double*>(&r3pGHI);

		// Fill elems.
		//res.e30 = r3f123[0] + r3f123[1] + r3f123[2] + r3f123[3] + r3f456[0] + r3f456[1];
		//res.e31 = r3f456[2] + r3f456[3] + r3f789[0] + r3f789[1] + r3f789[2] + r3f789[3];
		//res.e32 = r3fABC[0] + r3fABC[1] + r3fABC[2] + r3fABC[3] + r3fDEF[0] + r3fDEF[1];
		//res.e33 = r3fDEF[2] + r3fDEF[3] + r3fGHI[0] + r3fGHI[1] + r3fGHI[2] + r3fGHI[3];

		const __m256d r3rp1 = _mm256_set_pd(r3fDEF[2], r3fABC[0], r3f456[2], r3f123[0]);
		const __m256d r3rp2 = _mm256_set_pd(r3fDEF[3], r3fABC[1], r3f456[3], r3f123[1]);
		const __m256d r3rp3 = _mm256_set_pd(r3fGHI[0], r3fABC[2], r3f789[0], r3f123[2]);
		const __m256d r3rp4 = _mm256_set_pd(r3fGHI[1], r3fABC[3], r3f789[1], r3f123[3]);
		const __m256d r3rp5 = _mm256_set_pd(r3fGHI[2], r3fDEF[0], r3f789[2], r3f456[0]);
		const __m256d r3rp6 = _mm256_set_pd(r3fGHI[3], r3fDEF[1], r3f789[3], r3f456[1]);

		reinterpret_cast<__m256d&>(data[12]) = _mm256_mul_pd(invDetP, _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(r3rp1, r3rp2), r3rp3), r3rp4), r3rp5), r3rp6));

//}

		// TODO: better column impl.
		res.Transpose();

		return res;
	}


	template <>
	CMat4d& CMat4d::ApplyScale(const Vec3<double>& _scale) noexcept
	{
		double* const data = Data();

		const __m256d pScale = _mm256_set_pd(1.0, _scale.z, _scale.y, _scale.x);

		// Compute row 0
		reinterpret_cast<__m256d&>(data[0]) = _mm256_mul_pd(pScale, _mm256_load_pd(&data[0]));

		// Compute row 1
		reinterpret_cast<__m256d&>(data[4]) = _mm256_mul_pd(pScale, _mm256_load_pd(&data[4]));

		// Compute row 2
		reinterpret_cast<__m256d&>(data[8]) = _mm256_mul_pd(pScale, _mm256_load_pd(&data[8]));

		return *this;
	}


	template <>
	CMat4d CMat4d::MakeRotation(const Quat<double>& _rot) noexcept
	{
		SA_WARN(_rot.IsNormalized(), Maths, L"Quaternion should be normalized!");

		/*
			return Mat3f(
				1.0 -	2.0 * (_rot.y * _rot.y + _rot.z * _rot.z),
						2.0 * (_rot.x * _rot.y - _rot.z * _rot.w),
						2.0 * (_rot.x * _rot.z + _rot.y * _rot.w),

						2.0 * (_rot.x * _rot.y + _rot.z * _rot.w),
				1.0 -	2.0 * (_rot.x * _rot.x + _rot.z * _rot.z),
						2.0 * (_rot.y * _rot.z - _rot.x * _rot.w),

						2.0 * (_rot.x * _rot.z - _rot.y * _rot.w),
						2.0 * (_rot.y * _rot.z + _rot.x * _rot.w),
				1.0 -	2.0 * (_rot.x * _rot.x + _rot.y * _rot.y)
			);
		*/

		const __m256d pDbl = _mm256_set1_pd(2.0);

		// 4 first elems.
		const __m256d p1 = _mm256_set_pd(_rot.x, _rot.x, _rot.x, _rot.y);
		const __m256d p2 = _mm256_set_pd(_rot.y, _rot.z, _rot.y, _rot.y);
		const __m256d p3 = _mm256_set_pd(_rot.z, _rot.y, -_rot.z, _rot.z);
		const __m256d p4 = _mm256_set_pd(_rot.w, _rot.w, _rot.w, _rot.z);

		__m256d p1234 = _mm256_mul_pd(pDbl, _mm256_add_pd(_mm256_mul_pd(p1, p2), _mm256_mul_pd(p3, p4)));
		double* const d1234 = reinterpret_cast<double*>(&p1234);

		// Apply 1.0 - value.
		d1234[0] = 1.0 - d1234[0];


		// 4 next elems.
		const __m256d p5 = _mm256_set_pd(_rot.y, _rot.x, _rot.y, _rot.x);
		const __m256d p6 = _mm256_set_pd(_rot.z, _rot.z, _rot.z, _rot.x);
		const __m256d p7 = _mm256_set_pd(_rot.x, -_rot.y, -_rot.x, _rot.z);
		const __m256d p8 = _mm256_set_pd(_rot.w, _rot.w, _rot.w, _rot.z);

		__m256d p5678 = _mm256_mul_pd(pDbl, _mm256_add_pd(_mm256_mul_pd(p5, p6), _mm256_mul_pd(p7, p8)));
		double* const d5678 = reinterpret_cast<double*>(&p5678);

		// Apply 1.0 - value.
		d5678[0] = 1.0 - d5678[0];


		// Last elem.
		double e22 = 1.0 - 2.0 * (_rot.x * _rot.x + _rot.y * _rot.y);


		return Mat4(
			d1234[0], d1234[1], d1234[2], 0.0,
			d1234[3], d5678[0], d5678[1], 0.0,
			d5678[2], d5678[3], e22, 0.0,
			0.0, 0.0, 0.0, 1.0
		);
	}


	template <>
	CMat4d CMat4d::operator*(double _scale) const noexcept
	{
		Mat4 res;
		double* const fres = res.Data();
		const double* const data = Data();

		const __m256d sPack = _mm256_set1_pd(_scale);


		// Mult row 0.
		reinterpret_cast<__m256d&>(fres[0]) = _mm256_mul_pd(_mm256_load_pd(&data[0]), sPack);

		// Mult row 1.
		reinterpret_cast<__m256d&>(fres[4]) = _mm256_mul_pd(_mm256_load_pd(&data[4]), sPack);

		// Mult row 2.
		reinterpret_cast<__m256d&>(fres[8]) = _mm256_mul_pd(_mm256_load_pd(&data[8]), sPack);

		// Mult row 3.
		reinterpret_cast<__m256d&>(fres[12]) = _mm256_mul_pd(_mm256_load_pd(&data[12]), sPack);

		return res;
	}

	template <>
	CMat4d CMat4d::operator/(double _scale) const noexcept
	{
		Mat4 res;
		double* const fres = res.Data();
		const double* const data = Data();

		const __m256d sPack = _mm256_set1_pd(_scale);


		// Div row 0.
		reinterpret_cast<__m256d&>(fres[0]) = _mm256_div_pd(_mm256_load_pd(&data[0]), sPack);

		// Div row 1.
		reinterpret_cast<__m256d&>(fres[4]) = _mm256_div_pd(_mm256_load_pd(&data[4]), sPack);

		// Div row 2.
		reinterpret_cast<__m256d&>(fres[8]) = _mm256_div_pd(_mm256_load_pd(&data[8]), sPack);

		// Div row 3.
		reinterpret_cast<__m256d&>(fres[12]) = _mm256_div_pd(_mm256_load_pd(&data[12]), sPack);

		return res;
	}

	template <>
	CMat4d CMat4d::operator+(const CMat4d& _rhs) const noexcept
	{
		Mat4 res;
		double* const fres = res.Data();
		const double* const ldata = Data();
		const double* const rdata = _rhs.Data();


		// Add row 0.
		reinterpret_cast<__m256d&>(fres[0]) = _mm256_add_pd(_mm256_load_pd(&ldata[0]), _mm256_load_pd(&rdata[0]));

		// Add row 1.
		reinterpret_cast<__m256d&>(fres[4]) = _mm256_add_pd(_mm256_load_pd(&ldata[4]), _mm256_load_pd(&rdata[4]));

		// Add row 2.
		reinterpret_cast<__m256d&>(fres[8]) = _mm256_add_pd(_mm256_load_pd(&ldata[8]), _mm256_load_pd(&rdata[8]));

		// Add row 3.
		reinterpret_cast<__m256d&>(fres[12]) = _mm256_add_pd(_mm256_load_pd(&ldata[12]), _mm256_load_pd(&rdata[12]));

		return res;
	}

	template <>
	CMat4d CMat4d::operator-(const CMat4d& _rhs) const noexcept
	{
		Mat4 res;
		double* const fres = res.Data();
		const double* const ldata = Data();
		const double* const rdata = _rhs.Data();

		// Sub row 0.
		reinterpret_cast<__m256d&>(fres[0]) = _mm256_sub_pd(_mm256_load_pd(&ldata[0]), _mm256_load_pd(&rdata[0]));

		// Sub row 1.
		reinterpret_cast<__m256d&>(fres[4]) = _mm256_sub_pd(_mm256_load_pd(&ldata[4]), _mm256_load_pd(&rdata[4]));

		// Sub row 2.
		reinterpret_cast<__m256d&>(fres[8]) = _mm256_sub_pd(_mm256_load_pd(&ldata[8]), _mm256_load_pd(&rdata[8]));

		// Sub row 3.
		reinterpret_cast<__m256d&>(fres[12]) = _mm256_sub_pd(_mm256_load_pd(&ldata[12]), _mm256_load_pd(&rdata[12]));

		return res;
	}

	template <>
	CMat4d CMat4d::operator*(const CMat4d& _rhs) const noexcept
	{
		Mat4 res;
		double* const data = res.Data();

		const __m256d lRow0 = _mm256_set_pd(e30, e20, e10, e00);
		const __m256d lRow1 = _mm256_set_pd(e31, e21, e11, e01);
		const __m256d lRow2 = _mm256_set_pd(e32, e22, e12, e02);
		const __m256d lRow3 = _mm256_set_pd(e33, e23, e13, e03);

		// Row 0.
		reinterpret_cast<__m256d&>(data[0]) = _mm256_add_pd(
			_mm256_add_pd(_mm256_mul_pd(lRow0, _mm256_set1_pd(_rhs.e00)), _mm256_mul_pd(lRow1, _mm256_set1_pd(_rhs.e10))),
			_mm256_add_pd(_mm256_mul_pd(lRow2, _mm256_set1_pd(_rhs.e20)), _mm256_mul_pd(lRow3, _mm256_set1_pd(_rhs.e30)))
		);

		// Row 1.
		reinterpret_cast<__m256d&>(data[4]) = _mm256_add_pd(
			_mm256_add_pd(_mm256_mul_pd(lRow0, _mm256_set1_pd(_rhs.e01)), _mm256_mul_pd(lRow1, _mm256_set1_pd(_rhs.e11))),
			_mm256_add_pd(_mm256_mul_pd(lRow2, _mm256_set1_pd(_rhs.e21)), _mm256_mul_pd(lRow3, _mm256_set1_pd(_rhs.e31)))
		);

		// Row 2.
		reinterpret_cast<__m256d&>(data[8]) = _mm256_add_pd(
			_mm256_add_pd(_mm256_mul_pd(lRow0, _mm256_set1_pd(_rhs.e02)), _mm256_mul_pd(lRow1, _mm256_set1_pd(_rhs.e12))),
			_mm256_add_pd(_mm256_mul_pd(lRow2, _mm256_set1_pd(_rhs.e22)), _mm256_mul_pd(lRow3, _mm256_set1_pd(_rhs.e32)))
		);

		// Row 3.
		reinterpret_cast<__m256d&>(data[12]) = _mm256_add_pd(
			_mm256_add_pd(_mm256_mul_pd(lRow0, _mm256_set1_pd(_rhs.e03)), _mm256_mul_pd(lRow1, _mm256_set1_pd(_rhs.e13))),
			_mm256_add_pd(_mm256_mul_pd(lRow2, _mm256_set1_pd(_rhs.e23)), _mm256_mul_pd(lRow3, _mm256_set1_pd(_rhs.e33)))
		);

		return res;
	}



	template <>
	Vec3<double> CMat4d::operator*(const Vec3<double>& _rhs) const noexcept
	{
		const __m256d p0 = _mm256_mul_pd(_mm256_set1_pd(_rhs.x), _mm256_set_pd(0.0, e20, e10, e00));
		const __m256d p1 = _mm256_mul_pd(_mm256_set1_pd(_rhs.y), _mm256_set_pd(0.0, e21, e11, e01));
		const __m256d p2 = _mm256_mul_pd(_mm256_set1_pd(_rhs.z), _mm256_set_pd(0.0, e22, e12, e02));

		// Use Vec4 for padding.
		Vec4d res;

		reinterpret_cast<__m256d&>(res) = _mm256_add_pd(_mm256_add_pd(p0, p1), p2);

		return res;
	}

	template <>
	Vec4<double> CMat4d::operator*(const Vec4<double>& _rhs) const noexcept
	{
		const __m256d p0 = _mm256_mul_pd(_mm256_set1_pd(_rhs.x), _mm256_set_pd(e30, e20, e10, e00));
		const __m256d p1 = _mm256_mul_pd(_mm256_set1_pd(_rhs.y), _mm256_set_pd(e31, e21, e11, e01));
		const __m256d p2 = _mm256_mul_pd(_mm256_set1_pd(_rhs.z), _mm256_set_pd(e32, e22, e12, e02));
		const __m256d p3 = _mm256_mul_pd(_mm256_set1_pd(_rhs.w), _mm256_set_pd(e33, e23, e13, e03));

		Vec4d res;

		reinterpret_cast<__m256d&>(res) = _mm256_add_pd(_mm256_add_pd(p0, p1), _mm256_add_pd(p2, p3));

		return res;
	}


	template <>
	CMat4d& CMat4d::operator*=(double _scale) noexcept
	{
		double* const data = Data();
		const __m256d sPack = _mm256_set1_pd(_scale);

		// Mult row 0.
		reinterpret_cast<__m256d&>(data[0]) = _mm256_mul_pd(_mm256_load_pd(&data[0]), sPack);

		// Mult row 1.
		reinterpret_cast<__m256d&>(data[4]) = _mm256_mul_pd(_mm256_load_pd(&data[4]), sPack);

		// Mult row 2.
		reinterpret_cast<__m256d&>(data[8]) = _mm256_mul_pd(_mm256_load_pd(&data[8]), sPack);

		// Mult row 3.
		reinterpret_cast<__m256d&>(data[12]) = _mm256_mul_pd(_mm256_load_pd(&data[12]), sPack);

		return *this;
	}

	template <>
	CMat4d& CMat4d::operator/=(double _scale) noexcept
	{
		double* const data = Data();
		const __m256d sPack = _mm256_set1_pd(_scale);

		// Div row 0.
		reinterpret_cast<__m256d&>(data[0]) = _mm256_div_pd(_mm256_load_pd(&data[0]), sPack);

		// Div row 1.
		reinterpret_cast<__m256d&>(data[4]) = _mm256_div_pd(_mm256_load_pd(&data[4]), sPack);

		// Div row 2.
		reinterpret_cast<__m256d&>(data[8]) = _mm256_div_pd(_mm256_load_pd(&data[8]), sPack);

		// Div row 3.
		reinterpret_cast<__m256d&>(data[12]) = _mm256_div_pd(_mm256_load_pd(&data[12]), sPack);

		return *this;
	}

	template <>
	CMat4d& CMat4d::operator+=(const CMat4d& _rhs) noexcept
	{
		double* const ldata = Data();
		const double* const rdata = _rhs.Data();

		// Add row 0.
		reinterpret_cast<__m256d&>(ldata[0]) = _mm256_add_pd(_mm256_load_pd(&ldata[0]), _mm256_load_pd(&rdata[0]));

		// Add row 1.
		reinterpret_cast<__m256d&>(ldata[4]) = _mm256_add_pd(_mm256_load_pd(&ldata[4]), _mm256_load_pd(&rdata[4]));

		// Add row 2.
		reinterpret_cast<__m256d&>(ldata[8]) = _mm256_add_pd(_mm256_load_pd(&ldata[8]), _mm256_load_pd(&rdata[8]));

		// Add row 3.
		reinterpret_cast<__m256d&>(ldata[12]) = _mm256_add_pd(_mm256_load_pd(&ldata[12]), _mm256_load_pd(&rdata[12]));

		return *this;
	}

	template <>
	CMat4d& CMat4d::operator-=(const CMat4d& _rhs) noexcept
	{
		double* const ldata = Data();
		const double* const rdata = _rhs.Data();

		// Sub row 0.
		reinterpret_cast<__m256d&>(ldata[0]) = _mm256_sub_pd(_mm256_load_pd(&ldata[0]), _mm256_load_pd(&rdata[0]));

		// Sub row 1.
		reinterpret_cast<__m256d&>(ldata[4]) = _mm256_sub_pd(_mm256_load_pd(&ldata[4]), _mm256_load_pd(&rdata[4]));

		// Sub row 2.
		reinterpret_cast<__m256d&>(ldata[8]) = _mm256_sub_pd(_mm256_load_pd(&ldata[8]), _mm256_load_pd(&rdata[8]));

		// Sub row 3.
		reinterpret_cast<__m256d&>(ldata[12]) = _mm256_sub_pd(_mm256_load_pd(&ldata[12]), _mm256_load_pd(&rdata[12]));

		return *this;
	}


	template <>
	CMat4d operator/(double _lhs, const CMat4d& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.e00), Maths, L"Inverse scale matrix e00 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e01), Maths, L"Inverse scale matrix e01 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e02), Maths, L"Inverse scale matrix e02 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e03), Maths, L"Inverse scale matrix e03 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e10), Maths, L"Inverse scale matrix e10 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e11), Maths, L"Inverse scale matrix e11 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e12), Maths, L"Inverse scale matrix e12 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e13), Maths, L"Inverse scale matrix e13 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e20), Maths, L"Inverse scale matrix e20 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e21), Maths, L"Inverse scale matrix e21 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e22), Maths, L"Inverse scale matrix e22 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e23), Maths, L"Inverse scale matrix e23 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e30), Maths, L"Inverse scale matrix e30 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e31), Maths, L"Inverse scale matrix e31 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e32), Maths, L"Inverse scale matrix e32 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e33), Maths, L"Inverse scale matrix e33 == 0!");

		CMat4d res;
		double* const fres = res.Data();
		const double* const data = _rhs.Data();
		const __m256d sPack = _mm256_set1_pd(_lhs);


		// Div row 0.
		reinterpret_cast<__m256d&>(fres[0]) = _mm256_div_pd(sPack, _mm256_load_pd(&data[0]));

		// Div row 1.
		reinterpret_cast<__m256d&>(fres[4]) = _mm256_div_pd(sPack, _mm256_load_pd(&data[4]));

		// Div row 2.
		reinterpret_cast<__m256d&>(fres[8]) = _mm256_div_pd(sPack, _mm256_load_pd(&data[8]));

		// Div row 3.
		reinterpret_cast<__m256d&>(fres[12]) = _mm256_div_pd(sPack, _mm256_load_pd(&data[12]));

		return res;
	}

//}

#endif
}
