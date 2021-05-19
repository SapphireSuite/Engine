// Copyright (c) 2021 Sapphire Development Team. All Rights Reserved.

#include <Maths/Space/Quaternion.hpp>

#include <Maths/Space/Vector3.hpp>

namespace Sa
{
#if SA_INTRISC_SSE // SIMD float.

	template <>
	float Quatf::SqrLength() const noexcept
	{
		__m128 pack = _mm_load_ps(&w);

		pack = _mm_mul_ps(pack, pack);
		const float* const fp = reinterpret_cast<float*>(&pack);

		return fp[0] + fp[1] + fp[2] + fp[3];
	}

	template <>
	Quatf& Quatf::Normalize() noexcept
	{
		SA_WARN(!IsZero(), Maths, L"Normalize null quaternion!");

		const __m128 lenP = _mm_set_ps1(Length());
		const __m128 pack = _mm_load_ps(&w);

		reinterpret_cast<__m128&>(*this) = _mm_div_ps(pack, lenP);

		return *this;
	}

	template <>
	Quatf Quatf::GetNormalized() const noexcept
	{
		SA_WARN(!IsZero(), Maths, L"Normalize null quaternion!");

		Quat res;

		const __m128 lenP = _mm_set_ps1(Length());
		const __m128 pack = _mm_load_ps(&w);

		reinterpret_cast<__m128&>(res) = _mm_div_ps(pack, lenP);

		return res;
	}


	template <>
	Quatf Quatf::Rotate(const Quatf& _other) const noexcept
	{
		SA_WARN(IsNormalized(), Maths, L"Quaternion should be normalized for multiplication. This quaternion is not normalized!");
		SA_WARN(_other.IsNormalized(), Maths, L"Quaternion should be normalized for multiplication. Other quaternion is not normalized!");

		Quat res;

		const __m128 wP = _mm_set_ps1(w);
		const __m128 xP = _mm_set_ps1(x);
		const __m128 yP = _mm_set_ps1(y);
		const __m128 zP = _mm_set_ps1(z);

		const __m128 qVP1 = _mm_load_ps(&_other.w);
		const __m128 qVP2 = _mm_set_ps(_other.y, -_other.z, _other.w, -_other.x);
		const __m128 qVP3 = _mm_set_ps(-_other.x, _other.w, _other.z, -_other.y);
		const __m128 qVP4 = _mm_set_ps(_other.w, _other.x, -_other.y, -_other.z);

		const __m128 wPmqVP1 = _mm_mul_ps(wP, qVP1);
		const __m128 xPmqVP2 = _mm_mul_ps(xP, qVP2);
		const __m128 yPmqVP3 = _mm_mul_ps(yP, qVP3);
		const __m128 zPmqVP4 = _mm_mul_ps(zP, qVP4);

		reinterpret_cast<__m128&>(res) = _mm_add_ps(_mm_add_ps(wPmqVP1, xPmqVP2), _mm_add_ps(yPmqVP3, zPmqVP4));

		return res;
	}


	template <>
	float Quatf::Dot(const Quatf& _lhs, const Quatf& _rhs) noexcept
	{
		const __m128 lPack = _mm_load_ps(&_lhs.w);
		const __m128 rPack = _mm_load_ps(&_rhs.w);

		const __m128 res = _mm_mul_ps(lPack, rPack);

		const float* const fp = reinterpret_cast<const float*>(&res);

		return fp[0] + fp[1] + fp[2] + fp[3];
	}


	template <>
	Vec3<Degf> Quatf::ToEuler() const noexcept
	{
		/*
			cosPitch =	1.0 -	2.0f * (x * x + y * y);
			sinPitch =			2.0f * (w * x + y * z);

			sinYaw =			2.0f * (w * y - z * x);

			cosRoll =	1.0 -	2.0f * (y * y + z * z);
			sinRoll =			2.0f * (w * z + x * y);
		*/

		Vec3<Degf> result;

		// Compute pitch and roll pack.
		const __m256 pDbl = _mm256_set1_ps(2.0f);

		const __m256 p1 = _mm256_set_ps(0.0f, 0.0f, 0.0f, w, y, w, w, x);
		const __m256 p2 = _mm256_set_ps(0.0f, 0.0f, 0.0f, z, y, y, x, x);
		const __m256 p3 = _mm256_set_ps(0.0f, 0.0f, 0.0f, x, z, -z, y, y);
		const __m256 p4 = _mm256_set_ps(0.0f, 0.0f, 0.0f, y, z, x, z, y);

		const __m256 pTotal = _mm256_mul_ps(pDbl, _mm256_add_ps(_mm256_mul_ps(p1, p2), _mm256_mul_ps(p3, p4)));
		const float* const fTotal = reinterpret_cast<const float*>(&pTotal);

		// Pitch - X axis.
		result.x = Maths::ATan2(fTotal[1], 1.0f - fTotal[0]); // atan2(sinPitch, cosPitch).


		// Yaw - Y axis.
		if (std::abs(fTotal[2]) > 1.0f) // 90 degrees if out of range.
			result.y = static_cast<float>(Maths::Sign(fTotal[2]) * Maths::PiOv4 * Maths::RadToDeg);
		else
			result.y = Maths::ASin(fTotal[2]);


		// Roll - Z axis.
		result.z = Maths::ATan2(fTotal[4], 1.0f - fTotal[3]); // atan2(sinRoll, cosRoll).

		return result;
	}

	template <>
	Quatf Quatf::FromEuler(const Vec3<Degf>& _angles) noexcept
	{
		Quat res;

		Vec3<Radf> halfRadAngles = Vec3f(_angles) * 0.5f * static_cast<float>(Maths::DegToRad);

		const float cosPitch = Maths::Cos(halfRadAngles.x);
		const float sinPitch = Maths::Sin(halfRadAngles.x);

		const float cosYaw = Maths::Cos(halfRadAngles.y);
		const float sinYaw = Maths::Sin(halfRadAngles.y);

		const float cosRoll = Maths::Cos(halfRadAngles.z);
		const float sinRoll = Maths::Sin(halfRadAngles.z);


		__m128 pitchP1 = _mm_set_ps(cosPitch, cosPitch, sinPitch, cosPitch);
		__m128 yawP1 = _mm_set_ps(cosYaw, sinYaw, cosYaw, cosYaw);
		__m128 rollP1 = _mm_set_ps(sinRoll, cosRoll, cosRoll, cosRoll);

		__m128 lhs = _mm_mul_ps(_mm_mul_ps(pitchP1, yawP1), rollP1);


		__m128 pitchP2 = _mm_set_ps(-sinPitch, sinPitch, -cosPitch, sinPitch);
		__m128 yawP2 = _mm_set_ps(sinYaw, cosYaw, sinYaw, sinYaw);
		__m128 rollP2 = _mm_set_ps(cosRoll, sinRoll, sinRoll, sinRoll);

		__m128 rhs = _mm_mul_ps(_mm_mul_ps(pitchP2, yawP2), rollP2);

		reinterpret_cast<__m128&>(res) = _mm_add_ps(lhs, rhs);

		return res;
	}


	template <>
	Quatf Quatf::operator*(float _scale) const noexcept
	{
		Quatf res;

		const __m128 scP = _mm_set_ps1(_scale);
		const __m128 pack = _mm_load_ps(&w);

		reinterpret_cast<__m128&>(res) = _mm_mul_ps(pack, scP);

		return res;
	}

	template <>
	Quatf Quatf::operator/(float _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale quaternion by 0 (division by 0)!");

		Quatf res;

		const __m128 scP = _mm_set_ps1(_scale);
		const __m128 pack = _mm_load_ps(&w);

		reinterpret_cast<__m128&>(res) = _mm_div_ps(pack, scP);

		return res;
	}

	template <>
	Quatf Quatf::operator+(const Quatf& _rhs) const noexcept
	{
		Quat res;

		const __m128 lPack = _mm_load_ps(&w);
		const __m128 rPack = _mm_load_ps(&_rhs.w);

		reinterpret_cast<__m128&>(res) = _mm_add_ps(lPack, rPack);

		return res;
	}

	template <>
	Quatf Quatf::operator-(const Quatf& _rhs) const noexcept
	{
		Quat res;

		const __m128 lPack = _mm_load_ps(&w);
		const __m128 rPack = _mm_load_ps(&_rhs.w);

		reinterpret_cast<__m128&>(res) = _mm_sub_ps(lPack, rPack);

		return res;
	}


	template <>
	Quatf& Quatf::operator*=(float _scale) noexcept
	{
		const __m128 scP = _mm_set_ps1(_scale);
		const __m128 pack = _mm_load_ps(&w);

		reinterpret_cast<__m128&>(*this) = _mm_mul_ps(pack, scP);

		return *this;
	}

	template <>
	Quatf& Quatf::operator/=(float _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale quaternion by 0 (division by 0)!");

		const __m128 scP = _mm_set_ps1(_scale);
		const __m128 pack = _mm_load_ps(&w);

		reinterpret_cast<__m128&>(*this) = _mm_div_ps(pack, scP);

		return *this;
	}

	template <>
	Quatf& Quatf::operator+=(const Quatf& _rhs) noexcept
	{
		const __m128 lPack = _mm_load_ps(&w);
		const __m128 rPack = _mm_load_ps(&_rhs.w);

		reinterpret_cast<__m128&>(*this) = _mm_add_ps(lPack, rPack);

		return *this;
	}

	template <>
	Quatf& Quatf::operator-=(const Quatf& _rhs) noexcept
	{
		const __m128 lPack = _mm_load_ps(&w);
		const __m128 rPack = _mm_load_ps(&_rhs.w);

		reinterpret_cast<__m128&>(*this) = _mm_sub_ps(lPack, rPack);

		return *this;
	}


	template <>
	Quatf operator/(float _lhs, const Quatf& _rhs) noexcept
	{
		Quatf res;

		SA_WARN(!Sa::Equals0(_rhs.w), Maths, L"Inverse scale W by 0!");
		SA_WARN(!Sa::Equals0(_rhs.x), Maths, L"Inverse scale X Axis by 0!");
		SA_WARN(!Sa::Equals0(_rhs.y), Maths, L"Inverse scale Y Axis by 0!");
		SA_WARN(!Sa::Equals0(_rhs.z), Maths, L"Inverse scale Z Axis by 0!");

		const __m128 lPack = _mm_set_ps1(_lhs);
		const __m128 rPack = _mm_load_ps(&_rhs.w);

		reinterpret_cast<__m128&>(res) = _mm_div_ps(lPack, rPack);

		return res;
	}

#endif

#if SA_INTRISC_AVX // SIMD double

	template <>
	double Quatd::SqrLength() const noexcept
	{
		__m256d pack = _mm256_load_pd(&w);

		pack = _mm256_mul_pd(pack, pack);
		const double* const dp = reinterpret_cast<double*>(&pack);

		return dp[0] + dp[1] + dp[2] + dp[3];
	}

	template <>
	Quatd& Quatd::Normalize() noexcept
	{
		SA_WARN(!IsZero(), Maths, L"Normalize null quaternion!");

		const __m256d lenP = _mm256_set1_pd(Length());
		const __m256d pack = _mm256_load_pd(&w);

		reinterpret_cast<__m256d&>(*this) = _mm256_div_pd(pack, lenP);

		return *this;
	}

	template <>
	Quatd Quatd::GetNormalized() const noexcept
	{
		SA_WARN(!IsZero(), Maths, L"Normalize null quaternion!");

		Quat res;

		const __m256d lenP = _mm256_set1_pd(Length());
		const __m256d pack = _mm256_load_pd(&w);

		reinterpret_cast<__m256d&>(res) = _mm256_div_pd(pack, lenP);

		return res;
	}


	template <>
	Quatd Quatd::Rotate(const Quatd& _other) const noexcept
	{
		SA_WARN(IsNormalized(), Maths, L"Quaternion should be normalized for multiplication. This quaternion is not normalized!");
		SA_WARN(_other.IsNormalized(), Maths, L"Quaternion should be normalized for multiplication. Other quaternion is not normalized!");

		Quat res;

		const __m256d wP = _mm256_set1_pd(w);
		const __m256d xP = _mm256_set1_pd(x);
		const __m256d yP = _mm256_set1_pd(y);
		const __m256d zP = _mm256_set1_pd(z);

		const __m256d qVP1 = _mm256_load_pd(&_other.w);
		const __m256d qVP2 = _mm256_set_pd(_other.y, -_other.z, _other.w, -_other.x);
		const __m256d qVP3 = _mm256_set_pd(-_other.x, _other.w, _other.z, -_other.y);
		const __m256d qVP4 = _mm256_set_pd(_other.w, _other.x, -_other.y, -_other.z);

		const __m256d wPmqVP1 = _mm256_mul_pd(wP, qVP1);
		const __m256d xPmqVP2 = _mm256_mul_pd(xP, qVP2);
		const __m256d yPmqVP3 = _mm256_mul_pd(yP, qVP3);
		const __m256d zPmqVP4 = _mm256_mul_pd(zP, qVP4);

		reinterpret_cast<__m256d&>(res) = _mm256_add_pd(_mm256_add_pd(wPmqVP1, xPmqVP2), _mm256_add_pd(yPmqVP3, zPmqVP4));

		return res;
	}


	template <>
	double Quatd::Dot(const Quatd& _lhs, const Quatd& _rhs) noexcept
	{
		const __m256d lPack = _mm256_load_pd(&_lhs.w);
		const __m256d rPack = _mm256_load_pd(&_rhs.w);

		const __m256d res = _mm256_mul_pd(lPack, rPack);

		const double* const dp = reinterpret_cast<const double*>(&res);

		return dp[0] + dp[1] + dp[2] + dp[3];
	}


	template <>
	Vec3<Degd> Quatd::ToEuler() const noexcept
	{
		/*
			cosPitch =	1.0 -	2.0 * (x * x + y * y);
			sinPitch =			2.0 * (w * x + y * z);
			cosRoll =	1.0 -	2.0 * (y * y + z * z);
			sinRoll =			2.0 * (w * z + x * y);
			
			sinYaw =			2.0 * (w * y - z * x);
		*/

		Vec3<Degd> result;


		// Compute pitch and roll pack.
		const __m256d pDbl = _mm256_set1_pd(2.0);

		const __m256d p1 = _mm256_set_pd(w, y, w, x);
		const __m256d p2 = _mm256_set_pd(z, y, x, x);
		const __m256d p3 = _mm256_set_pd(x, z, y, y);
		const __m256d p4 = _mm256_set_pd(y, z, z, y);

		const __m256d pTotal = _mm256_mul_pd(pDbl, _mm256_add_pd(_mm256_mul_pd(p1, p2), _mm256_mul_pd(p3, p4)));
		const double* const dTotal = reinterpret_cast<const double*>(&pTotal);


		double cosPitch = 1.0 - dTotal[0];

		// Handle double precision.
		if (Sa::Equals0(cosPitch))
			cosPitch = 0.0f;

		double cosRoll = 1.0 - dTotal[2];

		// Handle double precision.
		if (Sa::Equals0(cosRoll))
			cosRoll = 0.0f;

		
		// Pitch - X axis.
		result.x = Maths::ATan2(dTotal[1], cosPitch); // atan2(sinPitch, cosPitch).


		// Yaw - Y axis.
		{
			double sinYaw = 2.0 * (w * y - z * x);

			// Handle double precision.
			if (Sa::Equals1(sinYaw))
				sinYaw = 1.0;

			if (std::abs(sinYaw) > 1.0) // 90 degrees if out of range.
				result.y = Maths::Sign(sinYaw) * Maths::PiOv4 * Maths::RadToDeg;
			else
				result.y = Maths::ASin(sinYaw);
		}


		// Roll - Z axis.
		result.z = Maths::ATan2(dTotal[3], cosRoll); // atan2(sinRoll, cosRoll).

		return result;
	}

	template <>
	Quatd Quatd::FromEuler(const Vec3<Degd>& _angles) noexcept
	{
		Quat res;

		Vec3<Radd> halfRadAngles = Vec3d(_angles) * 0.5 * Maths::DegToRad;

		const double cosPitch = Maths::Cos(halfRadAngles.x);
		const double sinPitch = Maths::Sin(halfRadAngles.x);

		const double cosYaw = Maths::Cos(halfRadAngles.y);
		const double sinYaw = Maths::Sin(halfRadAngles.y);

		const double cosRoll = Maths::Cos(halfRadAngles.z);
		const double sinRoll = Maths::Sin(halfRadAngles.z);


		__m256d pitchP1 = _mm256_set_pd(cosPitch, cosPitch, sinPitch, cosPitch);
		__m256d yawP1 = _mm256_set_pd(cosYaw, sinYaw, cosYaw, cosYaw);
		__m256d rollP1 = _mm256_set_pd(sinRoll, cosRoll, cosRoll, cosRoll);

		__m256d lhs = _mm256_mul_pd(_mm256_mul_pd(pitchP1, yawP1), rollP1);


		__m256d pitchP2 = _mm256_set_pd(-sinPitch, sinPitch, -cosPitch, sinPitch);
		__m256d yawP2 = _mm256_set_pd(sinYaw, cosYaw, sinYaw, sinYaw);
		__m256d rollP2 = _mm256_set_pd(cosRoll, sinRoll, sinRoll, sinRoll);

		__m256d rhs = _mm256_mul_pd(_mm256_mul_pd(pitchP2, yawP2), rollP2);

		reinterpret_cast<__m256d&>(res) = _mm256_add_pd(lhs, rhs);
		return res;
	}


	template <>
	Quatd Quatd::operator*(double _scale) const noexcept
	{
		Quat res;
		
		const __m256d scP = _mm256_set1_pd(_scale);
		const __m256d pack = _mm256_load_pd(&w);

		reinterpret_cast<__m256d&>(res) = _mm256_mul_pd(pack, scP);

		return res;
	}

	template <>
	Quatd Quatd::operator/(double _scale) const noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale quaternion by 0 (division by 0)!");
		
		Quat res;

		const __m256d scP = _mm256_set1_pd(_scale);
		const __m256d pack = _mm256_load_pd(&w);

		reinterpret_cast<__m256d&>(res) = _mm256_div_pd(pack, scP);

		return res;
	}

	template <>
	Quatd Quatd::operator+(const Quatd& _rhs) const noexcept
	{
		Quat res;

		const __m256d lPack = _mm256_load_pd(&w);
		const __m256d rPack = _mm256_load_pd(&_rhs.w);

		reinterpret_cast<__m256d&>(res) = _mm256_add_pd(lPack, rPack);

		return res;
	}

	template <>
	Quatd Quatd::operator-(const Quatd& _rhs) const noexcept
	{
		Quat res;

		const __m256d lPack = _mm256_load_pd(&w);
		const __m256d rPack = _mm256_load_pd(&_rhs.w);

		reinterpret_cast<__m256d&>(res) = _mm256_sub_pd(lPack, rPack);

		return res;
	}


	template <>
	Quatd& Quatd::operator*=(double _scale) noexcept
	{
		const __m256d scP = _mm256_set1_pd(_scale);
		const __m256d pack = _mm256_load_pd(&w);

		reinterpret_cast<__m256d&>(*this) = _mm256_mul_pd(pack, scP);

		return *this;
	}

	template <>
	Quatd& Quatd::operator/=(double _scale) noexcept
	{
		SA_WARN(!Sa::Equals0(_scale), Maths, L"Unscale quaternion by 0 (division by 0)!");

		const __m256d scP = _mm256_set1_pd(_scale);
		const __m256d pack = _mm256_load_pd(&w);

		reinterpret_cast<__m256d&>(*this) = _mm256_div_pd(pack, scP);

		return *this;
	}

	template <>
	Quatd& Quatd::operator+=(const Quatd& _rhs) noexcept
	{
		const __m256d lPack = _mm256_load_pd(&w);
		const __m256d rPack = _mm256_load_pd(&_rhs.w);

		reinterpret_cast<__m256d&>(*this) = _mm256_add_pd(lPack, rPack);

		return *this;
	}

	template <>
	Quatd& Quatd::operator-=(const Quatd& _rhs) noexcept
	{
		const __m256d lPack = _mm256_load_pd(&w);
		const __m256d rPack = _mm256_load_pd(&_rhs.w);

		reinterpret_cast<__m256d&>(*this) = _mm256_sub_pd(lPack, rPack);

		return *this;
	}


	template <>
	Quatd operator/(double _lhs, const Quatd& _rhs) noexcept
	{
		SA_WARN(!Sa::Equals0(_rhs.w), Maths, L"Inverse scale W by 0!");
		SA_WARN(!Sa::Equals0(_rhs.x), Maths, L"Inverse scale X Axis by 0!");
		SA_WARN(!Sa::Equals0(_rhs.y), Maths, L"Inverse scale Y Axis by 0!");
		SA_WARN(!Sa::Equals0(_rhs.z), Maths, L"Inverse scale Z Axis by 0!");

		Quatd res;

		const __m256d lPack = _mm256_set1_pd(_lhs);
		const __m256d rPack = _mm256_load_pd(&_rhs.w);

		reinterpret_cast<__m256d&>(res) = _mm256_div_pd(lPack, rPack);

		return res;
	}

#endif
}
