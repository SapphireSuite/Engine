// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#include <Maths/Matrix/Matrix3.hpp>

#include <Maths/Space/Vector3.hpp>
#include <Maths/Space/Vector4.hpp>
#include <Maths/Space/Quaternion.hpp>

namespace Sa
{
#if SA_INTRISC_AVX // SIMD int32

//{ Row Major

	template <>
	RMat3i RMat3i::operator*(int32 _scale) const noexcept
	{
		Mat3 res;

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Mult 8 first elems.
		reinterpret_cast<__m256i&>(res.e00) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(e00), sPack);

		// Last elem.
		res.e22 = e22 * _scale;

		return res;
	}

#if SA_INTRISC_SVML

	template <>
	RMat3i RMat3i::operator/(int32 _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		Mat3 res;

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Div 8 first elems.
		reinterpret_cast<__m256i&>(res.e00) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(e00), sPack);

		// Last elem.
		res.e22 = e22 / _scale;

		return res;
	}

#endif

	template <>
	RMat3i RMat3i::operator+(const RMat3i& _rhs) const noexcept
	{
		Mat3 res;

		// Add 8 first elems.
		reinterpret_cast<__m256i&>(res.e00) = _mm256_add_epi32(reinterpret_cast<const __m256i&>(e00), reinterpret_cast<const __m256i&>(_rhs.e00));

		// Last elem.
		res.e22 = e22 + _rhs.e22;

		return res;
	}

	template <>
	RMat3i RMat3i::operator-(const RMat3i& _rhs) const noexcept
	{
		Mat3 res;

		// Sub 8 first elems.
		reinterpret_cast<__m256i&>(res.e00) = _mm256_sub_epi32(reinterpret_cast<const __m256i&>(e00), reinterpret_cast<const __m256i&>(_rhs.e00));

		// Last elem.
		res.e22 = e22 - _rhs.e22;

		return res;
	}

	template <>
	RMat3i RMat3i::operator*(const RMat3i& _rhs) const noexcept
	{
		Mat3 res;

		// Compute 8 first elems.
		const __m256i p1 = _mm256_set_epi32(e20, e20, e10, e10, e10, e00, e00, e00);
		const __m256i p2 = _mm256_set_epi32(_rhs.e01, _rhs.e00, _rhs.e02, _rhs.e01, _rhs.e00, _rhs.e02, _rhs.e01, _rhs.e00);
		const __m256i p12 = _mm256_mullo_epi32(p1, p2);


		const __m256i p3 = _mm256_set_epi32(e21, e21, e11, e11, e11, e01, e01, e01);
		const __m256i p4 = _mm256_set_epi32(_rhs.e11, _rhs.e10, _rhs.e12, _rhs.e11, _rhs.e10, _rhs.e12, _rhs.e11, _rhs.e10);
		const __m256i p34 = _mm256_mullo_epi32(p3, p4);


		const __m256i p5 = _mm256_set_epi32(e22, e22, e12, e12, e12, e02, e02, e02);
		const __m256i p6 = _mm256_set_epi32(_rhs.e21, _rhs.e20, _rhs.e22, _rhs.e21, _rhs.e20, _rhs.e22, _rhs.e21, _rhs.e20);
		const __m256i p56 = _mm256_mullo_epi32(p5, p6);


		reinterpret_cast<__m256i&>(res) = _mm256_add_epi32(_mm256_add_epi32(p12, p34), p56);

		// Last elem.
		res.e22 = e20 * _rhs.e02 + e21 * _rhs.e12 + e22 * _rhs.e22;

		return res;
	}


	template <>
	Vec3<int32> RMat3i::operator*(const Vec3<int32>& _rhs) const noexcept
	{
		// Compute first 8 elems.
		//const __m256i p0 = _mm256_load_epi32(&e00);
		const __m256i& p0 = reinterpret_cast<const __m256i&>(e00);

		const __m256i pScale = _mm256_set_epi32(_rhs.y, _rhs.x, _rhs.z, _rhs.y, _rhs.x, _rhs.z, _rhs.y, _rhs.x);

		const __m256i pTotal = _mm256_mullo_epi32(pScale, p0);
		const int32* const ires = reinterpret_cast<const int32*>(&pTotal);

		return Vec3i(
			ires[0] + ires[1] + ires[2],
			ires[3] + ires[4] + ires[5],
			ires[6] + ires[7] + e22 * _rhs.z
		);
	}


	template <>
	RMat3i& RMat3i::operator*=(int32 _scale) noexcept
	{
		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Mult 8 first elems.
		reinterpret_cast<__m256i&>(e00) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(e00), sPack);

		// Last elem.
		e22 *= _scale;

		return *this;
	}

#if SA_INTRISC_SVML

	template <>
	RMat3i& RMat3i::operator/=(int32 _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Div 8 first elems.
		reinterpret_cast<__m256i&>(e00) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(e00), sPack);

		// Last elem.
		e22 /= _scale;

		return *this;
	}

#endif

	template <>
	RMat3i& RMat3i::operator+=(const RMat3i& _rhs) noexcept
	{
		// Add 8 first elems.
		reinterpret_cast<__m256i&>(e00) = _mm256_add_epi32(reinterpret_cast<const __m256i&>(e00), reinterpret_cast<const __m256i&>(_rhs.e00));

		// Last elem.
		e22 += _rhs.e22;

		return *this;
	}

	template <>
	RMat3i& RMat3i::operator-=(const RMat3i& _rhs) noexcept
	{
		// Sub 8 first elems.
		reinterpret_cast<__m256i&>(e00) = _mm256_sub_epi32(reinterpret_cast<const __m256i&>(e00), reinterpret_cast<const __m256i&>(_rhs.e00));

		// Last elem.
		e22 -= _rhs.e22;

		return *this;
	}

//}

//{ Column Major

	template <>
	CMat3i CMat3i::operator*(int32 _scale) const noexcept
	{
		Mat3 res;

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Mult 8 first elems.
		reinterpret_cast<__m256i&>(res.e00) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(e00), sPack);

		// Last elem.
		res.e22 = e22 * _scale;

		return res;
	}

#if SA_INTRISC_SVML

	template <>
	CMat3i CMat3i::operator/(int32 _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		Mat3 res;

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Div 8 first elems.
		reinterpret_cast<__m256i&>(res.e00) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(e00), sPack);

		// Last elem.
		res.e22 = e22 / _scale;

		return res;
	}

#endif

	template <>
	CMat3i CMat3i::operator+(const CMat3i& _rhs) const noexcept
	{
		Mat3 res;

		// Add 8 first elems.
		reinterpret_cast<__m256i&>(res.e00) = _mm256_add_epi32(reinterpret_cast<const __m256i&>(e00), reinterpret_cast<const __m256i&>(_rhs.e00));

		// Last elem.
		res.e22 = e22 + _rhs.e22;

		return res;
	}

	template <>
	CMat3i CMat3i::operator-(const CMat3i& _rhs) const noexcept
	{
		Mat3 res;

		// Sub 8 first elems.
		reinterpret_cast<__m256i&>(res.e00) = _mm256_sub_epi32(reinterpret_cast<const __m256i&>(e00), reinterpret_cast<const __m256i&>(_rhs.e00));

		// Last elem.
		res.e22 = e22 - _rhs.e22;

		return res;
	}

	template <>
	CMat3i CMat3i::operator*(const CMat3i& _rhs) const noexcept
	{
		Mat3 res;

		// Compute 8 first elems.
		const __m256i p1 = _mm256_set_epi32(e10, e00, e20, e10, e00, e20, e10, e00);
		const __m256i p2 = _mm256_set_epi32(_rhs.e02, _rhs.e02, _rhs.e01, _rhs.e01, _rhs.e01, _rhs.e00, _rhs.e00, _rhs.e00);
		const __m256i p12 = _mm256_mullo_epi32(p1, p2);


		const __m256i p3 = _mm256_set_epi32(e11, e01, e21, e11, e01, e21, e11, e01);
		const __m256i p4 = _mm256_set_epi32(_rhs.e12, _rhs.e12, _rhs.e11, _rhs.e11, _rhs.e11, _rhs.e10, _rhs.e10, _rhs.e10);
		const __m256i p34 = _mm256_mullo_epi32(p3, p4);


		const __m256i p5 = _mm256_set_epi32(e12, e02, e22, e12, e02, e22, e12, e02);
		const __m256i p6 = _mm256_set_epi32(_rhs.e22, _rhs.e22, _rhs.e21, _rhs.e21, _rhs.e21, _rhs.e20, _rhs.e20, _rhs.e20);
		const __m256i p56 = _mm256_mullo_epi32(p5, p6);


		reinterpret_cast<__m256i&>(res) = _mm256_add_epi32(_mm256_add_epi32(p12, p34), p56);

		// Last elem.
		res.e22 = e20 * _rhs.e02 + e21 * _rhs.e12 + e22 * _rhs.e22;

		return res;
	}


	template <>
	Vec3<int32> CMat3i::operator*(const Vec3<int32>& _rhs) const noexcept
	{
		// Compute first 8 elems.
		const __m256i p0 = _mm256_set_epi32(e21, e20, e12, e11, e10, e02, e01, e00);

		const __m256i pScale = _mm256_set_epi32(_rhs.y, _rhs.x, _rhs.z, _rhs.y, _rhs.x, _rhs.z, _rhs.y, _rhs.x);

		const __m256i pTotal = _mm256_mullo_epi32(pScale, p0);
		const int32* const ires = reinterpret_cast<const int32*>(&pTotal);

		return Vec3i(
			ires[0] + ires[1] + ires[2],
			ires[3] + ires[4] + ires[5],
			ires[6] + ires[7] + e22 * _rhs.z
		);
	}


	template <>
	CMat3i& CMat3i::operator*=(int32 _scale) noexcept
	{
		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Mult 8 first elems.
		reinterpret_cast<__m256i&>(e00) = _mm256_mullo_epi32(reinterpret_cast<const __m256i&>(e00), sPack);

		// Last elem.
		e22 *= _scale;

		return *this;
	}

#if SA_INTRISC_SVML

	template <>
	CMat3i& CMat3i::operator/=(int32 _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		const __m256i sPack = _mm256_set1_epi32(_scale);

		// Div 8 first elems.
		reinterpret_cast<__m256i&>(e00) = _mm256_div_epi32(reinterpret_cast<const __m256i&>(e00), sPack);

		// Last elem.
		e22 /= _scale;

		return *this;
	}

#endif

	template <>
	CMat3i& CMat3i::operator+=(const CMat3i& _rhs) noexcept
	{
		// Add 8 first elems.
		reinterpret_cast<__m256i&>(e00) = _mm256_add_epi32(reinterpret_cast<const __m256i&>(e00), reinterpret_cast<const __m256i&>(_rhs.e00));

		// Last elem.
		e22 += _rhs.e22;

		return *this;
	}

	template <>
	CMat3i& CMat3i::operator-=(const CMat3i& _rhs) noexcept
	{
		// Sub 8 first elems.
		reinterpret_cast<__m256i&>(e00) = _mm256_sub_epi32(reinterpret_cast<const __m256i&>(e00), reinterpret_cast<const __m256i&>(_rhs.e00));

		// Last elem.
		e22 -= _rhs.e22;

		return *this;
	}

//}

#endif

#if SA_INTRISC_SSE // SIMD float

//{ Row Major

	template <>
	float RMat3f::Determinant() const noexcept
	{
		/*
			(+) e00 * e11 * e22
			(+) e01 * e12 * e20
			(+) e02 * e10 * e21
			(-) e20 * e11 * e02
			(-) e21 * e12 * e00
			(-) e22 * e10 * e01
		*/

		const __m256 p1 = _mm256_set_ps(0.0f, 0.0f, -e22, -e21, -e20, e02, e01, e00);
		const __m256 p2 = _mm256_set_ps(0.0f, 0.0f, e10, e12, e11, e10, e12, e11);
		const __m256 p3 = _mm256_set_ps(0.0f, 0.0f, e01, e00, e02, e21, e20, e22);

		float fres[8];
		_mm256_store_ps(fres, _mm256_mul_ps(_mm256_mul_ps(p1, p2), p3));

		return fres[0] + fres[1] + fres[2] + fres[3] + fres[4] + fres[5];
	}

	template <>
	RMat3f RMat3f::GetInversed() const noexcept
	{
		/*
			(1.0f / det) * (
				e11 * e22 - e21 * e12,
				e02 * e21 - e01 * e22,
				e01 * e12 - e11 * e02,
				e12 * e20 - e10 * e22,
				e00 * e22 - e20 * e02,
				e02 * e10 - e00 * e12,
				e10 * e21 - e20 * e11,
				e01 * e20 - e00 * e21,

				e00 * e11 - e10 * e01
			)
		*/

		Mat3 res;
		const float det = Determinant();

		SA_WARN(!Sa::Equals0(det), Maths, L"Inverse matrix with determinant == 0");

		const float invDet = 1.0f / det;
		const __m256 invDetP = _mm256_set1_ps(invDet);

		// Compute 8 first elems.
		const __m256 p1 = _mm256_set_ps(e01, e10, e02, e00, e12, e01, e02, e11);
		const __m256 p2 = _mm256_set_ps(e20, e21, e10, e22, e20, e12, e21, e22);
		const __m256 p3 = _mm256_set_ps(e00, e20, e00, e20, e10, e11, e01, e21);
		const __m256 p4 = _mm256_set_ps(e21, e11, e12, e02, e22, e02, e22, e12);

		_mm256_store_ps(&res.e00, _mm256_mul_ps(invDetP, _mm256_sub_ps(_mm256_mul_ps(p1, p2), _mm256_mul_ps(p3, p4))));

		// Last elem.
		res.e22 = invDet * (e00 * e11 - e10 * e01);

		return res;
	}

	template <>
	RMat3f& RMat3f::ApplyScale(const Vec3<float>& _scale) noexcept
	{
		// Compute 8 first elems.
		const __m256 pScale = _mm256_set_ps(_scale.z, _scale.z, _scale.y, _scale.y, _scale.y, _scale.x, _scale.x, _scale.x);

		const __m256 resP = _mm256_mul_ps(pScale, _mm256_load_ps(&e00));
		_mm256_store_ps(&e00, resP);

		// Last elem.
		e22 *= _scale.z;

		return *this;
	}


	template <>
	RMat3f RMat3f::MakeRotation(const Quat<float>& _rot) noexcept
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

		Mat3 res;

		// 8 first elems.
		const __m256 pDbl = _mm256_set1_ps(2.0f);

		const __m256 p1 = _mm256_set_ps(_rot.y, _rot.x, _rot.y, _rot.x, _rot.x, _rot.x, _rot.x, _rot.y);
		const __m256 p2 = _mm256_set_ps(_rot.z, _rot.z, _rot.z, _rot.x, _rot.y, _rot.z, _rot.y, _rot.y);
		const __m256 p3 = _mm256_set_ps(_rot.x, -_rot.y, -_rot.x, _rot.z, _rot.z, _rot.y, -_rot.z, _rot.z);
		const __m256 p4 = _mm256_set_ps(_rot.w, _rot.w, _rot.w, _rot.z, _rot.w, _rot.w, _rot.w, _rot.z);

		_mm256_store_ps(&res.e00, _mm256_mul_ps(pDbl, _mm256_add_ps(_mm256_mul_ps(p1, p2), _mm256_mul_ps(p3, p4))));

		// Apply 1.0f - value.
		res.e00 = 1.0f - res.e00;
		res.e11 = 1.0f - res.e11;

		// Last elem.
		res.e22 = 1.0f - 2.0f * (_rot.x * _rot.x + _rot.y * _rot.y);

		return res;
	}


	template <>
	RMat3f RMat3f::operator*(float _scale) const noexcept
	{
		Mat3 res;

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Mult 8 first elems.
		_mm256_store_ps(&res.e00, _mm256_mul_ps(_mm256_load_ps(&e00), sPack));

		// Last elem.
		res.e22 = e22 * _scale;

		return res;
	}

	template <>
	RMat3f RMat3f::operator/(float _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		Mat3 res;

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Div 8 first elems.
		_mm256_store_ps(&res.e00, _mm256_div_ps(_mm256_load_ps(&e00), sPack));

		// Last elem.
		res.e22 = e22 / _scale;

		return res;
	}

	template <>
	RMat3f RMat3f::operator+(const RMat3f& _rhs) const noexcept
	{
		Mat3 res;

		// Add 8 first elems.
		_mm256_store_ps(&res.e00, _mm256_add_ps(_mm256_load_ps(&e00), _mm256_load_ps(&_rhs.e00)));

		// Last elem.
		res.e22 = e22 + _rhs.e22;

		return res;
	}

	template <>
	RMat3f RMat3f::operator-(const RMat3f& _rhs) const noexcept
	{
		Mat3 res;

		// Sub 8 first elems.
		_mm256_store_ps(&res.e00, _mm256_sub_ps(_mm256_load_ps(&e00), _mm256_load_ps(&_rhs.e00)));

		// Last elem.
		res.e22 = e22 - _rhs.e22;

		return res;
	}

	template <>
	RMat3f RMat3f::operator*(const RMat3f& _rhs) const noexcept
	{
		Mat3 res;

		// Compute 8 first elems.
		const __m256 p1 = _mm256_set_ps(e20, e20, e10, e10, e10, e00, e00, e00);
		const __m256 p2 = _mm256_set_ps(_rhs.e01, _rhs.e00, _rhs.e02, _rhs.e01, _rhs.e00, _rhs.e02, _rhs.e01, _rhs.e00);
		const __m256 p12 = _mm256_mul_ps(p1, p2);


		const __m256 p3 = _mm256_set_ps(e21, e21, e11, e11, e11, e01, e01, e01);
		const __m256 p4 = _mm256_set_ps(_rhs.e11, _rhs.e10, _rhs.e12, _rhs.e11, _rhs.e10, _rhs.e12, _rhs.e11, _rhs.e10);
		const __m256 p34 = _mm256_mul_ps(p3, p4);


		const __m256 p5 = _mm256_set_ps(e22, e22, e12, e12, e12, e02, e02, e02);
		const __m256 p6 = _mm256_set_ps(_rhs.e21, _rhs.e20, _rhs.e22, _rhs.e21, _rhs.e20, _rhs.e22, _rhs.e21, _rhs.e20);
		const __m256 p56 = _mm256_mul_ps(p5, p6);

		_mm256_store_ps(&res.e00, _mm256_add_ps(_mm256_add_ps(p12, p34), p56));

		// Last elem.
		res.e22 = e20 * _rhs.e02 + e21 * _rhs.e12 + e22 * _rhs.e22;

		return res;
	}


	template <>
	Vec3<float> RMat3f::operator*(const Vec3<float>& _rhs) const noexcept
	{
		// Compute first 8 elems.
		const __m256 p0 = _mm256_load_ps(&e00);

		const __m256 pScale = _mm256_set_ps(_rhs.y, _rhs.x, _rhs.z, _rhs.y, _rhs.x, _rhs.z, _rhs.y, _rhs.x);

		float fres[8];
		_mm256_store_ps(fres, _mm256_mul_ps(pScale, p0));

		return Vec3f(
			fres[0] + fres[1] + fres[2],
			fres[3] + fres[4] + fres[5],
			fres[6] + fres[7] + e22 * _rhs.z
		);
	}


	template <>
	RMat3f& RMat3f::operator*=(float _scale) noexcept
	{
		const __m256 sPack = _mm256_set1_ps(_scale);

		// Mult 8 first elems.
		const __m256 resP = _mm256_mul_ps(_mm256_load_ps(&e00), sPack);
		_mm256_store_ps(&e00, resP);

		// Last elem.
		e22 *= _scale;

		return *this;
	}

	template <>
	RMat3f& RMat3f::operator/=(float _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Div 8 first elems.
		const __m256 resP = _mm256_div_ps(_mm256_load_ps(&e00), sPack);
		_mm256_store_ps(&e00, resP);

		// Last elem.
		e22 /= _scale;

		return *this;
	}

	template <>
	RMat3f& RMat3f::operator+=(const RMat3f& _rhs) noexcept
	{
		// Add 8 first elems.
		const __m256 resP = _mm256_add_ps(_mm256_load_ps(&e00), _mm256_load_ps(&_rhs.e00));
		_mm256_store_ps(&e00, resP);

		// Last elem.
		e22 += _rhs.e22;

		return *this;
	}

	template <>
	RMat3f& RMat3f::operator-=(const RMat3f& _rhs) noexcept
	{
		// Sub 8 first elems.
		const __m256 resP = _mm256_sub_ps(_mm256_load_ps(&e00), _mm256_load_ps(&_rhs.e00));
		_mm256_store_ps(&e00, resP);

		// Last elem.
		e22 -= _rhs.e22;

		return *this;
	}


	template <>
	RMat3f operator/(float _lhs, const RMat3f& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.e00), Maths, L"Inverse scale matrix e00 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e01), Maths, L"Inverse scale matrix e01 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e02), Maths, L"Inverse scale matrix e02 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e10), Maths, L"Inverse scale matrix e10 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e11), Maths, L"Inverse scale matrix e11 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e12), Maths, L"Inverse scale matrix e12 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e20), Maths, L"Inverse scale matrix e20 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e21), Maths, L"Inverse scale matrix e21 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e22), Maths, L"Inverse scale matrix e22 == 0!");

		RMat3f res;

		const __m256 sPack = _mm256_set1_ps(_lhs);

		// Div 8 first elems.
		_mm256_store_ps(&res.e00, _mm256_div_ps(sPack, _mm256_load_ps(&_rhs.e00)));

		// Last elem.
		res.e22 = _lhs / _rhs.e22;

		return res;
	}

//}

//{ Column Major

	template <>
	float CMat3f::Determinant() const noexcept
	{
		/*
			(+) e00 * e11 * e22
			(+) e01 * e12 * e20
			(+) e02 * e10 * e21
			(-) e20 * e11 * e02
			(-) e21 * e12 * e00
			(-) e22 * e10 * e01
		*/

		const __m256 p1 = _mm256_set_ps(0.0f, 0.0f, -e22, -e21, -e20, e02, e01, e00);
		const __m256 p2 = _mm256_set_ps(0.0f, 0.0f, e10, e12, e11, e10, e12, e11);
		const __m256 p3 = _mm256_set_ps(0.0f, 0.0f, e01, e00, e02, e21, e20, e22);

		float fres[8];
		_mm256_store_ps(fres, _mm256_mul_ps(_mm256_mul_ps(p1, p2), p3));

		return fres[0] + fres[1] + fres[2] + fres[3] + fres[4] + fres[5];
	}

	template <>
	CMat3f CMat3f::GetInversed() const noexcept
	{
		/*
			(1.0f / det) * (
				e11 * e22 - e21 * e12,
				e02 * e21 - e01 * e22,
				e01 * e12 - e11 * e02,
				e12 * e20 - e10 * e22,
				e00 * e22 - e20 * e02,
				e02 * e10 - e00 * e12,
				e10 * e21 - e20 * e11,
				e01 * e20 - e00 * e21,

				e00 * e11 - e10 * e01
			)
		*/

		Mat3 res;
		const float det = Determinant();

		SA_WARN(!Sa::Equals0(det), Maths, L"Inverse matrix with determinant == 0");

		const float invDet = 1.0f / det;
		const __m256 invDetP = _mm256_set1_ps(invDet);

		// Compute 8 first elems.
		const __m256 p1 = _mm256_set_ps(e02, e01, e01, e00, e02, e10, e12, e11);
		const __m256 p2 = _mm256_set_ps(e10, e12, e20, e22, e21, e21, e20, e22);
		const __m256 p3 = _mm256_set_ps(e00, e11, e00, e20, e01, e20, e10, e21);
		const __m256 p4 = _mm256_set_ps(e12, e02, e21, e02, e22, e11, e22, e12);

		_mm256_store_ps(&res.e00, _mm256_mul_ps(invDetP, _mm256_sub_ps(_mm256_mul_ps(p1, p2), _mm256_mul_ps(p3, p4))));

		// Last elem.
		res.e22 = invDet * (e00 * e11 - e10 * e01);

		return res;
	}


	template <>
	CMat3f CMat3f::MakeRotation(const Quat<float>& _rot) noexcept
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

		Mat3 res;

		// 8 first elems.
		const __m256 pDbl = _mm256_set1_ps(2.0f);

		const __m256 p1 = _mm256_set_ps(_rot.y, _rot.x, _rot.y, _rot.x, _rot.x, _rot.x, _rot.x, _rot.y);
		const __m256 p2 = _mm256_set_ps(_rot.z, _rot.z, _rot.z, _rot.x, _rot.y, _rot.z, _rot.y, _rot.y);
		const __m256 p3 = _mm256_set_ps(-_rot.x, _rot.y, _rot.x, _rot.z, -_rot.z, -_rot.y, _rot.z, _rot.z);
		const __m256 p4 = _mm256_set_ps(_rot.w, _rot.w, _rot.w, _rot.z, _rot.w, _rot.w, _rot.w, _rot.z);

		_mm256_store_ps(&res.e00, _mm256_mul_ps(pDbl, _mm256_add_ps(_mm256_mul_ps(p1, p2), _mm256_mul_ps(p3, p4))));

		// Apply 1.0f - value.
		res.e00 = 1.0f - res.e00;
		res.e11 = 1.0f - res.e11;

		// Last elem.
		res.e22 = 1.0f - 2.0f * (_rot.x * _rot.x + _rot.y * _rot.y);

		return res;
	}

	template <>
	CMat3f& CMat3f::ApplyScale(const Vec3<float>& _scale) noexcept
	{
		// Compute 8 first elems.
		const __m256 pScale = _mm256_set_ps(_scale.y, _scale.x, _scale.z, _scale.y, _scale.x, _scale.z, _scale.y, _scale.x);

		const __m256 resP = _mm256_mul_ps(pScale, _mm256_load_ps(&e00));
		_mm256_store_ps(&e00, resP);

		// Last elem.
		e22 *= _scale.z;

		return *this;
	}


	template <>
	CMat3f CMat3f::operator*(float _scale) const noexcept
	{
		Mat3 res;

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Mult 8 first elems.
		_mm256_store_ps(&res.e00, _mm256_mul_ps(_mm256_load_ps(&e00), sPack));

		// Last elem.
		res.e22 = e22 * _scale;

		return res;
	}

	template <>
	CMat3f CMat3f::operator/(float _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0!");

		Mat3 res;

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Div 8 first elems.
		_mm256_store_ps(&res.e00, _mm256_div_ps(_mm256_load_ps(&e00), sPack));

		// Last elem.
		res.e22 = e22 / _scale;

		return res;
	}

	template <>
	CMat3f CMat3f::operator+(const CMat3f& _rhs) const noexcept
	{
		Mat3 res;

		// Add 8 first elems.
		_mm256_store_ps(&res.e00, _mm256_add_ps(_mm256_load_ps(&e00), _mm256_load_ps(&_rhs.e00)));

		// Last elem.
		res.e22 = e22 + _rhs.e22;

		return res;
	}

	template <>
	CMat3f CMat3f::operator-(const CMat3f& _rhs) const noexcept
	{
		Mat3 res;

		// Sub 8 first elems.
		_mm256_store_ps(&res.e00, _mm256_sub_ps(_mm256_load_ps(&e00), _mm256_load_ps(&_rhs.e00)));

		// Last elem.
		res.e22 = e22 - _rhs.e22;

		return res;
	}

	template <>
	CMat3f CMat3f::operator*(const CMat3f& _rhs) const noexcept
	{
		Mat3 res;

		// Compute 8 first elems.
		const __m256 p1 = _mm256_set_ps(e10, e00, e20, e10, e00, e20, e10, e00);
		const __m256 p2 = _mm256_set_ps(_rhs.e02, _rhs.e02, _rhs.e01, _rhs.e01, _rhs.e01, _rhs.e00, _rhs.e00, _rhs.e00);
		const __m256 p12 = _mm256_mul_ps(p1, p2);


		const __m256 p3 = _mm256_set_ps(e11, e01, e21, e11, e01, e21, e11, e01);
		const __m256 p4 = _mm256_set_ps(_rhs.e12, _rhs.e12, _rhs.e11, _rhs.e11, _rhs.e11, _rhs.e10, _rhs.e10, _rhs.e10);
		const __m256 p34 = _mm256_mul_ps(p3, p4);


		const __m256 p5 = _mm256_set_ps(e12, e02, e22, e12, e02, e22, e12, e02);
		const __m256 p6 = _mm256_set_ps(_rhs.e22, _rhs.e22, _rhs.e21, _rhs.e21, _rhs.e21, _rhs.e20, _rhs.e20, _rhs.e20);
		const __m256 p56 = _mm256_mul_ps(p5, p6);

		_mm256_store_ps(&res.e00, _mm256_add_ps(_mm256_add_ps(p12, p34), p56));

		// Last elem.
		res.e22 = e20 * _rhs.e02 + e21 * _rhs.e12 + e22 * _rhs.e22;

		return res;
	}


	template <>
	Vec3<float> CMat3f::operator*(const Vec3<float>& _rhs) const noexcept
	{
		// Compute first 8 elems.
		const __m256 p0 = _mm256_set_ps(e21, e20, e12, e11, e10, e02, e01, e00);

		const __m256 pScale = _mm256_set_ps(_rhs.y, _rhs.x, _rhs.z, _rhs.y, _rhs.x, _rhs.z, _rhs.y, _rhs.x);

		float fres[8];
		_mm256_store_ps(fres, _mm256_mul_ps(pScale, p0));

		return Vec3f(
			fres[0] + fres[1] + fres[2],
			fres[3] + fres[4] + fres[5],
			fres[6] + fres[7] + e22 * _rhs.z
		);
	}


	template <>
	CMat3f& CMat3f::operator*=(float _scale) noexcept
	{
		const __m256 sPack = _mm256_set1_ps(_scale);

		// Mult 8 first elems.
		const __m256 resP = _mm256_mul_ps(_mm256_load_ps(&e00), sPack);
		_mm256_store_ps(&e00, resP);

		// Last elem.
		e22 *= _scale;

		return *this;
	}

	template <>
	CMat3f& CMat3f::operator/=(float _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		const __m256 sPack = _mm256_set1_ps(_scale);

		// Div 8 first elems.
		const __m256 resP = _mm256_div_ps(_mm256_load_ps(&e00), sPack);
		_mm256_store_ps(&e00, resP);

		// Last elem.
		e22 /= _scale;

		return *this;
	}

	template <>
	CMat3f& CMat3f::operator+=(const CMat3f& _rhs) noexcept
	{
		// Add 8 first elems.
		const __m256 resP = _mm256_add_ps(_mm256_load_ps(&e00), _mm256_load_ps(&_rhs.e00));
		_mm256_store_ps(&e00, resP);

		// Last elem.
		e22 += _rhs.e22;

		return *this;
	}

	template <>
	CMat3f& CMat3f::operator-=(const CMat3f& _rhs) noexcept
	{
		// Sub 8 first elems.
		const __m256 resP = _mm256_sub_ps(_mm256_load_ps(&e00), _mm256_load_ps(&_rhs.e00));
		_mm256_store_ps(&e00, resP);

		// Last elem.
		e22 -= _rhs.e22;

		return *this;
	}


	template <>
	CMat3f operator/(float _lhs, const CMat3f& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.e00), Maths, L"Inverse scale matrix e00 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e01), Maths, L"Inverse scale matrix e01 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e02), Maths, L"Inverse scale matrix e02 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e10), Maths, L"Inverse scale matrix e10 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e11), Maths, L"Inverse scale matrix e11 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e12), Maths, L"Inverse scale matrix e12 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e20), Maths, L"Inverse scale matrix e20 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e21), Maths, L"Inverse scale matrix e21 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e22), Maths, L"Inverse scale matrix e22 == 0!");

		CMat3f res;

		const __m256 sPack = _mm256_set1_ps(_lhs);

		// Div 8 first elems.
		_mm256_store_ps(&res.e00, _mm256_div_ps(sPack, _mm256_load_ps(&_rhs.e00)));

		// Last elem.
		res.e22 = _lhs / _rhs.e22;

		return res;
	}

//}

#endif

#if SA_INTRISC_AVX // SIMD double

//{ Row Major

	template <>
	double RMat3d::Determinant() const noexcept
	{
		/*
			(+) e00 * e11 * e22
			(+) e01 * e12 * e20
			(+) e02 * e10 * e21
			(-) e20 * e11 * e02

			(-) e21 * e12 * e00
			(-) e22 * e10 * e01
		*/

		// 1st 4 pack.
		const __m256d p1 = _mm256_set_pd(-e20, e02, e01, e00);
		const __m256d p2 = _mm256_set_pd(e11, e10, e12, e11);
		const __m256d p3 = _mm256_set_pd(e02, e21, e20, e22);

		const __m256d p123 = _mm256_mul_pd(_mm256_mul_pd(p1, p2), p3);


		// 2nd 4 pack.
		const __m256d p4 = _mm256_set_pd(0.0, 0.0, -e22, -e21);
		const __m256d p5 = _mm256_set_pd(0.0, 0.0, e10, e12);
		const __m256d p6 = _mm256_set_pd(0.0, 0.0, e01, e00);

		const __m256d p456 = _mm256_mul_pd(_mm256_mul_pd(p4, p5), p6);

		double dres[4];
		_mm256_store_pd(dres, _mm256_add_pd(p123, p456));

		return dres[0] + dres[1] + dres[2] + dres[3];
	}

	template <>
	RMat3d RMat3d::GetInversed() const noexcept
	{
		/*
			(1.0 / det) * (
				e11 * e22 - e21 * e12,
				e02 * e21 - e01 * e22,
				e01 * e12 - e11 * e02,
				e12 * e20 - e10 * e22,

				e00 * e22 - e20 * e02,
				e02 * e10 - e00 * e12,
				e10 * e21 - e20 * e11,
				e01 * e20 - e00 * e21,

				e00 * e11 - e10 * e01
			)
		*/

		Mat3 res;
		const double det = Determinant();

		SA_WARN(!Sa::Equals0(det), Maths, L"Inverse matrix with determinant == 0");

		const double invDet = 1.0 / det;
		const __m256d invDetP = _mm256_set1_pd(invDet);

		// Compute 4 first elems.
		const __m256d p1 = _mm256_set_pd(e12, e01, e02, e11);
		const __m256d p2 = _mm256_set_pd(e20, e12, e21, e22);
		const __m256d p3 = _mm256_set_pd(e10, e11, e01, e21);
		const __m256d p4 = _mm256_set_pd(e22, e02, e22, e12);

		_mm256_store_pd(&res.e00, _mm256_mul_pd(invDetP, _mm256_sub_pd(_mm256_mul_pd(p1, p2), _mm256_mul_pd(p3, p4))));


		// Compute 4 next elems.
		const __m256d p5 = _mm256_set_pd(e01, e10, e02, e00);
		const __m256d p6 = _mm256_set_pd(e20, e21, e10, e22);
		const __m256d p7 = _mm256_set_pd(e00, e20, e00, e20);
		const __m256d p8 = _mm256_set_pd(e21, e11, e12, e02);

		_mm256_store_pd(&res.e11, _mm256_mul_pd(invDetP, _mm256_sub_pd(_mm256_mul_pd(p5, p6), _mm256_mul_pd(p7, p8))));


		// Last elem.
		res.e22 = invDet * (e00 * e11 - e10 * e01);

		return res;
	}


	template <>
	RMat3d RMat3d::MakeRotation(const Quat<double>& _rot) noexcept
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

		Mat3 res;

		const __m256d pDbl = _mm256_set1_pd(2.0);

		// 4 first elems.
		const __m256d p1 = _mm256_set_pd(_rot.x, _rot.x, _rot.x, _rot.y);
		const __m256d p2 = _mm256_set_pd(_rot.y, _rot.z, _rot.y, _rot.y);
		const __m256d p3 = _mm256_set_pd(_rot.z, _rot.y, -_rot.z, _rot.z);
		const __m256d p4 = _mm256_set_pd(_rot.w, _rot.w, _rot.w, _rot.z);

		_mm256_store_pd(&res.e00, _mm256_mul_pd(pDbl, _mm256_add_pd(_mm256_mul_pd(p1, p2), _mm256_mul_pd(p3, p4))));

		// Apply 1.0 - value.
		res.e00 = 1.0 - res.e00;


		// 4 next elems.
		const __m256d p5 = _mm256_set_pd(_rot.y, _rot.x, _rot.y, _rot.x);
		const __m256d p6 = _mm256_set_pd(_rot.z, _rot.z, _rot.z, _rot.x);
		const __m256d p7 = _mm256_set_pd(_rot.x, -_rot.y, -_rot.x, _rot.z);
		const __m256d p8 = _mm256_set_pd(_rot.w, _rot.w, _rot.w, _rot.z);

		const __m256d res5678 = _mm256_mul_pd(pDbl, _mm256_add_pd(_mm256_mul_pd(p5, p6), _mm256_mul_pd(p7, p8)));
		_mm256_store_pd(&res.e11, res5678);

		// Apply 1.0 - value.
		res.e11 = 1.0 - res.e11;


		// Last elem.
		res.e22 = 1.0 - 2.0 * (_rot.x * _rot.x + _rot.y * _rot.y);

		return res;
	}

	template <>
	RMat3d& RMat3d::ApplyScale(const Vec3<double>& _scale) noexcept
	{
		// Compute first 4 elems.
		const __m256d pScaleY3X = _mm256_set_pd(_scale.y, _scale.x, _scale.x, _scale.x);

		const __m256d res1234 = _mm256_mul_pd(pScaleY3X, _mm256_load_pd(&e00));
		_mm256_store_pd(&e00, res1234);

		// Compute next 4 elems.
		const __m256d pScale2Z2Y = _mm256_set_pd(_scale.z, _scale.z, _scale.y, _scale.y);

		const __m256d res5678 = _mm256_mul_pd(pScale2Z2Y, _mm256_load_pd(&e11));
		_mm256_store_pd(&e11, res5678);

		// Last elem.
		e22 *= _scale.z;

		return *this;
	}


	template <>
	RMat3d RMat3d::operator*(double _scale) const noexcept
	{
		Mat3 res;

		const __m256d sPack = _mm256_set1_pd(_scale);

		// Mult 4 first elems.
		_mm256_store_pd(&res.e00, _mm256_mul_pd(_mm256_load_pd(&e00), sPack));

		// Mult 4 next elems.
		_mm256_store_pd(&res.e11, _mm256_mul_pd(_mm256_load_pd(&e11), sPack));

		// Last elem.
		res.e22 = e22 * _scale;

		return res;
	}

	template <>
	RMat3d RMat3d::operator/(double _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0 (division by 0)!");

		Mat3 res;

		const __m256d sPack = _mm256_set1_pd(_scale);

		// Div 4 first elems.
		_mm256_store_pd(&res.e00, _mm256_div_pd(_mm256_load_pd(&e00), sPack));

		// Div 4 next elems.
		_mm256_store_pd(&res.e11, _mm256_div_pd(_mm256_load_pd(&e11), sPack));

		// Last elem.
		res.e22 = e22 / _scale;

		return res;
	}

	template <>
	RMat3d RMat3d::operator+(const RMat3d& _rhs) const noexcept
	{
		Mat3 res;

		// Add 4 first elems.
		_mm256_store_pd(&res.e00, _mm256_add_pd(_mm256_load_pd(&e00), _mm256_load_pd(&_rhs.e00)));

		// Add 4 next elems.
		_mm256_store_pd(&res.e11, _mm256_add_pd(_mm256_load_pd(&e11), _mm256_load_pd(&_rhs.e11)));

		// Last elem.
		res.e22 = e22 + _rhs.e22;

		return res;
	}

	template <>
	RMat3d RMat3d::operator-(const RMat3d& _rhs) const noexcept
	{
		Mat3 res;

		// Sub 4 first elems.
		_mm256_store_pd(&res.e00, _mm256_sub_pd(_mm256_load_pd(&e00), _mm256_load_pd(&_rhs.e00)));

		// Sub 4 next elems.
		_mm256_store_pd(&res.e11, _mm256_sub_pd(_mm256_load_pd(&e11), _mm256_load_pd(&_rhs.e11)));

		// Last elem.
		res.e22 = e22 - _rhs.e22;

		return res;
	}

	template <>
	RMat3d RMat3d::operator*(const RMat3d& _rhs) const noexcept
	{
		const __m256d rp0 = _mm256_set_pd(0.0f, _rhs.e02, _rhs.e01, _rhs.e00);
		const __m256d rp1 = _mm256_set_pd(0.0f, _rhs.e12, _rhs.e11, _rhs.e10);
		const __m256d rp2 = _mm256_set_pd(0.0f, _rhs.e22, _rhs.e21, _rhs.e20);


		const __m256d res012 = _mm256_add_pd(
			_mm256_add_pd(
				_mm256_mul_pd(_mm256_set1_pd(e00), rp0),
				_mm256_mul_pd(_mm256_set1_pd(e01), rp1)),
			_mm256_mul_pd(_mm256_set1_pd(e02), rp2)
		);

		double dres012[4];
		_mm256_store_pd(dres012, res012);


		const __m256d rese345 = _mm256_add_pd(
			_mm256_add_pd(
				_mm256_mul_pd(_mm256_set1_pd(e10), rp0),
				_mm256_mul_pd(_mm256_set1_pd(e11), rp1)),
			_mm256_mul_pd(_mm256_set1_pd(e12), rp2)
		);

		double dres345[4];
		_mm256_store_pd(dres345, rese345);


		const __m256d res678 = _mm256_add_pd(
			_mm256_add_pd(
				_mm256_mul_pd(_mm256_set1_pd(e20), rp0),
				_mm256_mul_pd(_mm256_set1_pd(e21), rp1)),
			_mm256_mul_pd(_mm256_set1_pd(e22), rp2)
		);
		double dres678[4];
		_mm256_store_pd(dres678, res678);

		return Mat3(
			dres012[0], dres012[1], dres012[2],
			dres345[0], dres345[1], dres345[2],
			dres678[0], dres678[1], dres678[2]
		);
	}


	template <>
	Vec3<double> RMat3d::operator*(const Vec3<double>& _rhs) const noexcept
	{
		const __m256d p0 = _mm256_mul_pd(_mm256_set1_pd(_rhs.x), _mm256_set_pd(0.0, e20, e10, e00));
		const __m256d p1 = _mm256_mul_pd(_mm256_set1_pd(_rhs.y), _mm256_set_pd(0.0, e21, e11, e01));
		const __m256d p2 = _mm256_mul_pd(_mm256_set1_pd(_rhs.z), _mm256_set_pd(0.0, e22, e12, e02));

		// Use Vec4 for padding.
		Vec4d res;

		_mm256_store_pd(res.Data(), _mm256_add_pd(_mm256_add_pd(p0, p1), p2));

		return res;
	}


	template <>
	RMat3d& RMat3d::operator*=(double _scale) noexcept
	{
		const __m256d sPack = _mm256_set1_pd(_scale);

		// Mult 4 first elems.
		const __m256d res1234 = _mm256_mul_pd(_mm256_load_pd(&e00), sPack);
		_mm256_store_pd(&e00, res1234);

		// Mult 4 next elems.
		const __m256d res5678 = _mm256_mul_pd(_mm256_load_pd(&e11), sPack);
		_mm256_store_pd(&e11, res5678);

		// Last elem.
		e22 *= _scale;

		return *this;
	}

	template <>
	RMat3d& RMat3d::operator/=(double _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), L"Unscale matrix by 0 (division by 0)!");

		const __m256d sPack = _mm256_set1_pd(_scale);

		// Div 4 first elems.
		const __m256d res1234 = _mm256_div_pd(_mm256_load_pd(&e00), sPack);
		_mm256_store_pd(&e00, res1234);

		// Div 4 next elems.
		const __m256d res5678 = _mm256_div_pd(_mm256_load_pd(&e11), sPack);
		_mm256_store_pd(&e11, res5678);

		// Last elem.
		e22 /= _scale;

		return *this;
	}

	template <>
	RMat3d& RMat3d::operator+=(const RMat3d& _rhs) noexcept
	{
		// Add 4 first elems.
		const __m256d res1234 = _mm256_add_pd(_mm256_load_pd(&e00), _mm256_load_pd(&_rhs.e00));
		_mm256_store_pd(&e00, res1234);

		// Add 4 next elems.
		const __m256d res5678 = _mm256_add_pd(_mm256_load_pd(&e11), _mm256_load_pd(&_rhs.e11));
		_mm256_store_pd(&e11, res5678);

		// Last elem.
		e22 += _rhs.e22;

		return *this;
	}

	template <>
	RMat3d& RMat3d::operator-=(const RMat3d& _rhs) noexcept
	{
		// Sub 4 first elems.
		const __m256d res1234 = _mm256_sub_pd(_mm256_load_pd(&e00), _mm256_load_pd(&_rhs.e00));
		_mm256_store_pd(&e00, res1234);

		// Sub 4 next elems.
		const __m256d res5678 = _mm256_sub_pd(_mm256_load_pd(&e11), _mm256_load_pd(&_rhs.e11));
		_mm256_store_pd(&e11, res5678);

		// Last elem.
		e22 -= _rhs.e22;

		return *this;
	}


	template <>
	RMat3d operator/(double _lhs, const RMat3d& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.e00), Maths, L"Inverse scale matrix e00 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e01), Maths, L"Inverse scale matrix e01 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e02), Maths, L"Inverse scale matrix e02 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e10), Maths, L"Inverse scale matrix e10 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e11), Maths, L"Inverse scale matrix e11 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e12), Maths, L"Inverse scale matrix e12 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e20), Maths, L"Inverse scale matrix e20 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e21), Maths, L"Inverse scale matrix e21 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e22), Maths, L"Inverse scale matrix e22 == 0!");

		RMat3d res;

		const __m256d sPack = _mm256_set1_pd(_lhs);

		// Div 4 first elems.
		_mm256_store_pd(&res.e00, _mm256_div_pd(sPack, _mm256_load_pd(&_rhs.e00)));

		// Div 4 next elems.
		_mm256_store_pd(&res.e11, _mm256_div_pd(sPack, _mm256_load_pd(&_rhs.e11)));

		// Last elem.
		res.e22 = _lhs / _rhs.e22;

		return res;
	}

//}

//{ Column Major

	template <>
	double CMat3d::Determinant() const noexcept
	{
		/*
			(+) e00 * e11 * e22
			(+) e01 * e12 * e20
			(+) e02 * e10 * e21
			(-) e20 * e11 * e02

			(-) e21 * e12 * e00
			(-) e22 * e10 * e01
		*/

		// 1st 4 pack.
		const __m256d p1 = _mm256_set_pd(-e20, e02, e01, e00);
		const __m256d p2 = _mm256_set_pd(e11, e10, e12, e11);
		const __m256d p3 = _mm256_set_pd(e02, e21, e20, e22);

		const __m256d p123 = _mm256_mul_pd(_mm256_mul_pd(p1, p2), p3);


		// 2nd 4 pack.
		const __m256d p4 = _mm256_set_pd(0.0, 0.0, -e22, -e21);
		const __m256d p5 = _mm256_set_pd(0.0, 0.0, e10, e12);
		const __m256d p6 = _mm256_set_pd(0.0, 0.0, e01, e00);

		const __m256d p456 = _mm256_mul_pd(_mm256_mul_pd(p4, p5), p6);

		double dres[4];
		_mm256_store_pd(dres, _mm256_add_pd(p123, p456));

		return dres[0] + dres[1] + dres[2] + dres[3];
	}

	template <>
	CMat3d CMat3d::GetInversed() const noexcept
	{
		/*
			(1.0 / det) * (
				e11 * e22 - e21 * e12,
				e02 * e21 - e01 * e22,
				e01 * e12 - e11 * e02,
				e12 * e20 - e10 * e22,

				e00 * e22 - e20 * e02,
				e02 * e10 - e00 * e12,
				e10 * e21 - e20 * e11,
				e01 * e20 - e00 * e21,

				e00 * e11 - e10 * e01
			)
		*/

		Mat3 res;
		const double det = Determinant();

		SA_WARN(!Sa::Equals0(det), Maths, L"Inverse matrix with determinant == 0");

		const double invDet = 1.0 / det;
		const __m256d invDetP = _mm256_set1_pd(invDet);

		// Compute 4 first elems.
		const __m256d p1 = _mm256_set_pd(e02, e10, e12, e11);
		const __m256d p2 = _mm256_set_pd(e21, e21, e20, e22);
		const __m256d p3 = _mm256_set_pd(e01, e20, e10, e21);
		const __m256d p4 = _mm256_set_pd(e22, e11, e22, e12);

		_mm256_store_pd(&res.e00, _mm256_mul_pd(invDetP, _mm256_sub_pd(_mm256_mul_pd(p1, p2), _mm256_mul_pd(p3, p4))));


		// Compute 4 next elems.
		const __m256d p5 = _mm256_set_pd(e02, e01, e01, e00);
		const __m256d p6 = _mm256_set_pd(e10, e12, e20, e22);
		const __m256d p7 = _mm256_set_pd(e00, e11, e00, e20);
		const __m256d p8 = _mm256_set_pd(e12, e02, e21, e02);

		_mm256_store_pd(&res.e11, _mm256_mul_pd(invDetP, _mm256_sub_pd(_mm256_mul_pd(p5, p6), _mm256_mul_pd(p7, p8))));


		// Last elem.
		res.e22 = invDet * (e00 * e11 - e10 * e01);

		return res;
	}


	template <>
	CMat3d CMat3d::MakeRotation(const Quat<double>& _rot) noexcept
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

		Mat3 res;

		const __m256d pDbl = _mm256_set1_pd(2.0);

		// 4 first elems.
		const __m256d p1 = _mm256_set_pd(_rot.x, _rot.x, _rot.x, _rot.y);
		const __m256d p2 = _mm256_set_pd(_rot.y, _rot.z, _rot.y, _rot.y);
		const __m256d p3 = _mm256_set_pd(-_rot.z, -_rot.y, _rot.z, _rot.z);
		const __m256d p4 = _mm256_set_pd(_rot.w, _rot.w, _rot.w, _rot.z);

		_mm256_store_pd(&res.e00, _mm256_mul_pd(pDbl, _mm256_add_pd(_mm256_mul_pd(p1, p2), _mm256_mul_pd(p3, p4))));

		// Apply 1.0 - value.
		res.e00 = 1.0 - res.e00;


		// 4 next elems.
		const __m256d p5 = _mm256_set_pd(_rot.y, _rot.x, _rot.y, _rot.x);
		const __m256d p6 = _mm256_set_pd(_rot.z, _rot.z, _rot.z, _rot.x);
		const __m256d p7 = _mm256_set_pd(-_rot.x, _rot.y, _rot.x, _rot.z);
		const __m256d p8 = _mm256_set_pd(_rot.w, _rot.w, _rot.w, _rot.z);

		_mm256_store_pd(&res.e11, _mm256_mul_pd(pDbl, _mm256_add_pd(_mm256_mul_pd(p5, p6), _mm256_mul_pd(p7, p8))));

		// Apply 1.0 - value.
		res.e11 = 1.0 - res.e11;


		// Last elem.
		res.e22 = 1.0 - 2.0 * (_rot.x * _rot.x + _rot.y * _rot.y);

		return res;
	}

	template <>
	CMat3d& CMat3d::ApplyScale(const Vec3<double>& _scale) noexcept
	{
		// Compute first 4 elems.
		const __m256d pScale01 = _mm256_set_pd(_scale.x, _scale.z, _scale.y, _scale.x);

		const __m256d res1234 = _mm256_mul_pd(pScale01, _mm256_load_pd(&e00));
		_mm256_store_pd(&e00, res1234);


		// Compute next 4 elems.
		const __m256d pScale23 = _mm256_set_pd(_scale.y, _scale.x, _scale.z, _scale.y);

		const __m256d res5678 = _mm256_mul_pd(pScale23, _mm256_load_pd(&e11));
		_mm256_store_pd(&e11, res5678);

		// Last elem.
		e22 *= _scale.z;

		return *this;
	}


	template <>
	CMat3d CMat3d::operator*(double _scale) const noexcept
	{
		Mat3 res;

		const __m256d sPack = _mm256_set1_pd(_scale);

		// Mult 4 first elems.
		_mm256_store_pd(&res.e00, _mm256_mul_pd(_mm256_load_pd(&e00), sPack));

		// Mult 4 next elems.
		_mm256_store_pd(&res.e11, _mm256_mul_pd(_mm256_load_pd(&e11), sPack));

		// Last elem.
		res.e22 = e22 * _scale;

		return res;
	}

	template <>
	CMat3d CMat3d::operator/(double _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0!");

		Mat3 res;

		const __m256d sPack = _mm256_set1_pd(_scale);

		// Div 4 first elems.
		_mm256_store_pd(&res.e00, _mm256_div_pd(_mm256_load_pd(&e00), sPack));

		// Div 4 next elems.
		_mm256_store_pd(&res.e11, _mm256_div_pd(_mm256_load_pd(&e11), sPack));

		// Last elem.
		res.e22 = e22 / _scale;

		return res;
	}

	template <>
	CMat3d CMat3d::operator+(const CMat3d& _rhs) const noexcept
	{
		Mat3 res;

		// Add 4 first elems.
		_mm256_store_pd(&res.e00, _mm256_add_pd(_mm256_load_pd(&e00), _mm256_load_pd(&_rhs.e00)));

		// Add 4 next elems.
		_mm256_store_pd(&res.e11, _mm256_add_pd(_mm256_load_pd(&e11), _mm256_load_pd(&_rhs.e11)));

		// Last elem.
		res.e22 = e22 + _rhs.e22;

		return res;
	}

	template <>
	CMat3d CMat3d::operator-(const CMat3d& _rhs) const noexcept
	{
		Mat3 res;

		// Sub 4 first elems.
		_mm256_store_pd(&res.e00, _mm256_sub_pd(_mm256_load_pd(&e00), _mm256_load_pd(&_rhs.e00)));

		// Sub 4 next elems.
		_mm256_store_pd(&res.e11, _mm256_sub_pd(_mm256_load_pd(&e11), _mm256_load_pd(&_rhs.e11)));

		// Last elem.
		res.e22 = e22 - _rhs.e22;

		return res;
	}

	template <>
	CMat3d CMat3d::operator*(const CMat3d& _rhs) const noexcept
	{
		const __m256d lp0 = _mm256_set_pd(0.0f, e20, e10, e00);
		const __m256d lp1 = _mm256_set_pd(0.0f, e21, e11, e01);
		const __m256d lp2 = _mm256_set_pd(0.0f, e22, e12, e02);


		const __m256d res012 = _mm256_add_pd(
			_mm256_add_pd(
				_mm256_mul_pd(_mm256_set1_pd(_rhs.e00), lp0),
				_mm256_mul_pd(_mm256_set1_pd(_rhs.e10), lp1)),
			_mm256_mul_pd(_mm256_set1_pd(_rhs.e20), lp2)
		);

		double dres012[4];
		_mm256_store_pd(dres012, res012);


		const __m256d rese345 = _mm256_add_pd(
			_mm256_add_pd(
				_mm256_mul_pd(_mm256_set1_pd(_rhs.e01), lp0),
				_mm256_mul_pd(_mm256_set1_pd(_rhs.e11), lp1)),
			_mm256_mul_pd(_mm256_set1_pd(_rhs.e21), lp2)
		);

		double dres345[4];
		_mm256_store_pd(dres345, rese345);


		const __m256d res678 = _mm256_add_pd(
			_mm256_add_pd(
				_mm256_mul_pd(_mm256_set1_pd(_rhs.e02), lp0),
				_mm256_mul_pd(_mm256_set1_pd(_rhs.e12), lp1)),
			_mm256_mul_pd(_mm256_set1_pd(_rhs.e22), lp2)
		);

		double dres678[4];
		_mm256_store_pd(dres678, res678);

		return Mat3(
			dres012[0], dres345[0], dres678[0],
			dres012[1], dres345[1], dres678[1],
			dres012[2], dres345[2], dres678[2]
		);
	}


	template <>
	Vec3<double> CMat3d::operator*(const Vec3<double>& _rhs) const noexcept
	{
		const __m256d p0 = _mm256_mul_pd(_mm256_set1_pd(_rhs.x), _mm256_set_pd(0.0, e20, e10, e00));
		const __m256d p1 = _mm256_mul_pd(_mm256_set1_pd(_rhs.y), _mm256_set_pd(0.0, e21, e11, e01));
		const __m256d p2 = _mm256_mul_pd(_mm256_set1_pd(_rhs.z), _mm256_set_pd(0.0, e22, e12, e02));

		// Use Vec4 for padding.
		Vec4d res;

		_mm256_store_pd(res.Data(), _mm256_add_pd(_mm256_add_pd(p0, p1), p2));

		return res;
	}


	template <>
	CMat3d& CMat3d::operator*=(double _scale) noexcept
	{
		const __m256d sPack = _mm256_set1_pd(_scale);

		// Mult 4 first elems.
		const __m256d res1234 = _mm256_mul_pd(_mm256_load_pd(&e00), sPack);
		_mm256_store_pd(&e00, res1234);

		// Mult 4 next elems.
		const __m256d res5678 = _mm256_mul_pd(_mm256_load_pd(&e11), sPack);
		_mm256_store_pd(&e11, res5678);

		// Last elem.
		e22 *= _scale;

		return *this;
	}

	template <>
	CMat3d& CMat3d::operator/=(double _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale matrix by 0!");

		const __m256d sPack = _mm256_set1_pd(_scale);

		// Div 4 first elems.
		const __m256d res1234 = _mm256_div_pd(_mm256_load_pd(&e00), sPack);
		_mm256_store_pd(&e00, res1234);

		// Div 4 next elems.
		const __m256d res5678 = _mm256_div_pd(_mm256_load_pd(&e11), sPack);
		_mm256_store_pd(&e11, res5678);

		// Last elem.
		e22 /= _scale;

		return *this;
	}

	template <>
	CMat3d& CMat3d::operator+=(const CMat3d& _rhs) noexcept
	{
		// Add 4 first elems.
		const __m256d res1234 = _mm256_add_pd(_mm256_load_pd(&e00), _mm256_load_pd(&_rhs.e00));
		_mm256_store_pd(&e00, res1234);

		// Add 4 next elems.
		const __m256d res5678 = _mm256_add_pd(_mm256_load_pd(&e11), _mm256_load_pd(&_rhs.e11));
		_mm256_store_pd(&e11, res5678);

		// Last elem.
		e22 += _rhs.e22;

		return *this;
	}

	template <>
	CMat3d& CMat3d::operator-=(const CMat3d& _rhs) noexcept
	{
		// Sub 4 first elems.
		const __m256d res1234 = _mm256_sub_pd(_mm256_load_pd(&e00), _mm256_load_pd(&_rhs.e00));
		_mm256_store_pd(&e00, res1234);

		// Sub 4 next elems.
		const __m256d res5678 = _mm256_sub_pd(_mm256_load_pd(&e11), _mm256_load_pd(&_rhs.e11));
		_mm256_store_pd(&e11, res5678);

		// Last elem.
		e22 -= _rhs.e22;

		return *this;
	}


	template <>
	CMat3d operator/(double _lhs, const CMat3d& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.e00), Maths, L"Inverse scale matrix e00 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e01), Maths, L"Inverse scale matrix e01 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e02), Maths, L"Inverse scale matrix e02 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e10), Maths, L"Inverse scale matrix e10 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e11), Maths, L"Inverse scale matrix e11 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e12), Maths, L"Inverse scale matrix e12 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e20), Maths, L"Inverse scale matrix e20 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e21), Maths, L"Inverse scale matrix e21 == 0!");
		SA_WARN(!Sa::Equals0(_rhs.e22), Maths, L"Inverse scale matrix e22 == 0!");

		CMat3d res;

		const __m256d sPack = _mm256_set1_pd(_lhs);

		// Div 4 first elems.
		_mm256_store_pd(&res.e00, _mm256_div_pd(sPack, _mm256_load_pd(&_rhs.e00)));

		// Div 4 next elems.
		_mm256_store_pd(&res.e11, _mm256_div_pd(sPack, _mm256_load_pd(&_rhs.e11)));

		// Last elem.
		res.e22 = _lhs / _rhs.e22;

		return res;
	}

//}

#endif
}
