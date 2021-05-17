// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Space/Vector3.hpp>
#include <SA/Maths/Space/Quaternion.hpp>
#include <SA/Maths/Matrix/Matrix3.hpp>
using namespace Sa;

namespace Sa::Matrix3_UT
{
	template <typename T, MatrixMajor major>
	Mat3<T, major> Generate()
	{
		return Mat3<T, major>(
			UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100),
			UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100),
			UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100)
		);
	}

	void Constants()
	{
		// Zero.
		SA_UTH_EQ(Mat3f::Zero.e00, 0.0f);
		SA_UTH_EQ(Mat3f::Zero.e01, 0.0f);
		SA_UTH_EQ(Mat3f::Zero.e02, 0.0f);
		SA_UTH_EQ(Mat3f::Zero.e10, 0.0f);
		SA_UTH_EQ(Mat3f::Zero.e11, 0.0f);
		SA_UTH_EQ(Mat3f::Zero.e12, 0.0f);
		SA_UTH_EQ(Mat3f::Zero.e20, 0.0f);
		SA_UTH_EQ(Mat3f::Zero.e21, 0.0f);
		SA_UTH_EQ(Mat3f::Zero.e22, 0.0f);

		// Identity.
		SA_UTH_EQ(Mat3f::Identity.e00, 1.0f);
		SA_UTH_EQ(Mat3f::Identity.e01, 0.0f);
		SA_UTH_EQ(Mat3f::Identity.e02, 0.0f);
		SA_UTH_EQ(Mat3f::Identity.e10, 0.0f);
		SA_UTH_EQ(Mat3f::Identity.e11, 1.0f);
		SA_UTH_EQ(Mat3f::Identity.e12, 0.0f);
		SA_UTH_EQ(Mat3f::Identity.e20, 0.0f);
		SA_UTH_EQ(Mat3f::Identity.e21, 0.0f);
		SA_UTH_EQ(Mat3f::Identity.e22, 1.0f);
	}

	void Majors()
	{
		float e00 = UTH::Rand(-100.0f, 100.0f);
		float e01 = UTH::Rand(-100.0f, 100.0f);
		float e02 = UTH::Rand(-100.0f, 100.0f);
		float e10 = UTH::Rand(-100.0f, 100.0f);
		float e11 = UTH::Rand(-100.0f, 100.0f);
		float e12 = UTH::Rand(-100.0f, 100.0f);
		float e20 = UTH::Rand(-100.0f, 100.0f);
		float e21 = UTH::Rand(-100.0f, 100.0f);
		float e22 = UTH::Rand(-100.0f, 100.0f);

		const Mat3<float, MatrixMajor::Row> m1(
			e00, e01, e02,
			e10, e11, e12,
			e20, e21, e22
		);
		const Mat3<float, MatrixMajor::Column> m2(
			e00, e01, e02,
			e10, e11, e12,
			e20, e21, e22
		);

		// Same value for same name.
		SA_UTH_EQ(m1.e00, m2.e00);
		SA_UTH_EQ(m1.e01, m2.e01);
		SA_UTH_EQ(m1.e02, m2.e02);
		SA_UTH_EQ(m1.e10, m2.e10);
		SA_UTH_EQ(m1.e11, m2.e11);
		SA_UTH_EQ(m1.e12, m2.e12);
		SA_UTH_EQ(m1.e20, m2.e20);
		SA_UTH_EQ(m1.e21, m2.e21);
		SA_UTH_EQ(m1.e22, m2.e22);

		const float* const dm1 = m1.Data();
		const float* const dm2 = m2.Data();

		// Different memory.
		SA_UTH_EQ(dm1[0], dm2[0]);
		SA_UTH_EQ(dm1[1], dm2[3]);
		SA_UTH_EQ(dm1[2], dm2[6]);

		SA_UTH_EQ(dm1[3], dm2[1]);
		SA_UTH_EQ(dm1[4], dm2[4]);
		SA_UTH_EQ(dm1[5], dm2[7]);

		SA_UTH_EQ(dm1[6], dm2[2]);
		SA_UTH_EQ(dm1[7], dm2[5]);
		SA_UTH_EQ(dm1[8], dm2[8]);
	}

	template <MatrixMajor major>
	void Constructors()
	{
		// Default constructor.
		const Mat3<float, major> m0;
		SA_UTH_EQ(m0.e00, 0.0f);
		SA_UTH_EQ(m0.e01, 0.0f);
		SA_UTH_EQ(m0.e02, 0.0f);
		SA_UTH_EQ(m0.e10, 0.0f);
		SA_UTH_EQ(m0.e11, 0.0f);
		SA_UTH_EQ(m0.e12, 0.0f);
		SA_UTH_EQ(m0.e20, 0.0f);
		SA_UTH_EQ(m0.e21, 0.0f);
		SA_UTH_EQ(m0.e22, 0.0f);


		// Value constructor.
		const float m1e00 = UTH::Rand(-100.0f, 100.0f);
		const float m1e01 = UTH::Rand(-100.0f, 100.0f);
		const float m1e02 = UTH::Rand(-100.0f, 100.0f);
		const float m1e10 = UTH::Rand(-100.0f, 100.0f);
		const float m1e11 = UTH::Rand(-100.0f, 100.0f);
		const float m1e12 = UTH::Rand(-100.0f, 100.0f);
		const float m1e20 = UTH::Rand(-100.0f, 100.0f);
		const float m1e21 = UTH::Rand(-100.0f, 100.0f);
		const float m1e22 = UTH::Rand(-100.0f, 100.0f);
		const Mat3<float, major> m1(
			m1e00, m1e01, m1e02,
			m1e10, m1e11, m1e12,
			m1e20, m1e21, m1e22
		);

		SA_UTH_EQ(m1.e00, m1e00);
		SA_UTH_EQ(m1.e01, m1e01);
		SA_UTH_EQ(m1.e02, m1e02);
		SA_UTH_EQ(m1.e10, m1e10);
		SA_UTH_EQ(m1.e11, m1e11);
		SA_UTH_EQ(m1.e12, m1e12);
		SA_UTH_EQ(m1.e20, m1e20);
		SA_UTH_EQ(m1.e21, m1e21);
		SA_UTH_EQ(m1.e22, m1e22);


		// Value cast constructor.
		const int32 m2e00 = UTH::Rand(-100, 100);
		const int32 m2e01 = UTH::Rand(-100, 100);
		const int32 m2e02 = UTH::Rand(-100, 100);
		const int32 m2e10 = UTH::Rand(-100, 100);
		const int32 m2e11 = UTH::Rand(-100, 100);
		const int32 m2e12 = UTH::Rand(-100, 100);
		const int32 m2e20 = UTH::Rand(-100, 100);
		const int32 m2e21 = UTH::Rand(-100, 100);
		const int32 m2e22 = UTH::Rand(-100, 100);
		const Mat3<float, major> m2(Mat3<int32, major>(
			m2e00, m2e01, m2e02,
			m2e10, m2e11, m2e12,
			m2e20, m2e21, m2e22
		));

		SA_UTH_EQ(m2.e00, static_cast<float>(m2e00));
		SA_UTH_EQ(m2.e01, static_cast<float>(m2e01));
		SA_UTH_EQ(m2.e02, static_cast<float>(m2e02));
		SA_UTH_EQ(m2.e10, static_cast<float>(m2e10));
		SA_UTH_EQ(m2.e11, static_cast<float>(m2e11));
		SA_UTH_EQ(m2.e12, static_cast<float>(m2e12));
		SA_UTH_EQ(m2.e20, static_cast<float>(m2e20));
		SA_UTH_EQ(m2.e21, static_cast<float>(m2e21));
		SA_UTH_EQ(m2.e22, static_cast<float>(m2e22));



		// Copy constructor.
		const Mat3<float, major> m3(m1);

		SA_UTH_EQ(m3.e00, m1.e00);
		SA_UTH_EQ(m3.e01, m1.e01);
		SA_UTH_EQ(m3.e02, m1.e02);
		SA_UTH_EQ(m3.e10, m1.e10);
		SA_UTH_EQ(m3.e11, m1.e11);
		SA_UTH_EQ(m3.e12, m1.e12);
		SA_UTH_EQ(m3.e20, m1.e20);
		SA_UTH_EQ(m3.e21, m1.e21);
		SA_UTH_EQ(m3.e22, m1.e22);


		//// From Mat4.
		//const Mat4<float, major> m4(
		//	UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f),
		//	UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f),
		//	UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f),
		//	UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f)
		//);

		//const Mat3<float, major> m5(m4);

		//SA_UTH_EQ(m5.e00, m4.e00);
		//SA_UTH_EQ(m5.e01, m4.e01);
		//SA_UTH_EQ(m5.e02, m4.e02);
		//SA_UTH_EQ(m5.e10, m4.e10);
		//SA_UTH_EQ(m5.e11, m4.e11);
		//SA_UTH_EQ(m5.e12, m4.e12);
		//SA_UTH_EQ(m5.e20, m4.e20);
		//SA_UTH_EQ(m5.e21, m4.e21);
		//SA_UTH_EQ(m5.e22, m4.e22);
	}

	template <MatrixMajor major>
	void Equals()
	{
		const Mat3<float, major> m1 = Generate<float, major>();
		const Mat3<float, major> m2 = Generate<float, major>();

		SA_UTH_RMF(false, m1, IsZero);
		SA_UTH_MF((Mat3<float, major>::Zero), IsZero);

		SA_UTH_MF(m1, Equals, m1);
		SA_UTH_RMF(false, m1, Equals, m2);

		SA_UTH_OP(m1, == , m1);
		SA_UTH_OP(m1, != , m2);
	}

	template <MatrixMajor major>
	void Transpose()
	{
		const Mat3<float, major> m1 = Generate<float, major>();
		const Mat3<float, major> m2 = m1.GetTransposed();

		SA_UTH_EQ(m2.e00, m1.e00);
		SA_UTH_EQ(m2.e10, m1.e01);
		SA_UTH_EQ(m2.e20, m1.e02);
		SA_UTH_EQ(m2.e01, m1.e10);
		SA_UTH_EQ(m2.e11, m1.e11);
		SA_UTH_EQ(m2.e21, m1.e12);
		SA_UTH_EQ(m2.e02, m1.e20);
		SA_UTH_EQ(m2.e12, m1.e21);
		SA_UTH_EQ(m2.e22, m1.e22);

		// Self transpose.
		Mat3<float, major> m3 = m1;
		m3.Transpose();
		SA_UTH_EQ(m3, m2);
	}

//{ Inverse

	template <typename T, MatrixMajor major>
	void Inverse_Internal()
	{
		// Precomputed matrix.
		// https://www.wolframalpha.com/input/?i=%7B%7B5.26%2C+48.25%2C+12.36%7D%2C%7B148.2%2C+12.36%2C+68.2%7D%2C%7B9.25%2C+12.3%2C+46.27%7D%7D
		const Mat3<T, major> m1(
			5.26f, 48.25f, 12.36f,
			148.2f, 12.36f, 68.2f,
			9.25f, 12.3f, 46.27f
		);

		const T eps = T(0.01);

		SA_UTH_EQ(m1.Determinant(), T(-280708.85), eps);

		// Precomputed matrix.
		const Mat3<T, major> m1_resInv = Mat3<float, major>(
			0.0009510f, 0.0074115f, -0.0111784f,
			0.0221809f, -0.0004597f, -0.0052475f,
			-0.0060864f, -0.0013594f, 0.0252419f
			);

		SA_UTH_MF(m1.GetInversed(), Equals, m1_resInv, eps);

		// Self inverse.
		Mat3<T, major> m2 = m1;
		m2.Inverse();
		SA_UTH_MF(m2, Equals, m1_resInv, eps);
	}

	template <MatrixMajor major>
	void Inverse()
	{
#if SA_INTRISC
		SA_UTH_GPB(InverseF_SIMD);
		Inverse_Internal<float, major>();
		SA_UTH_GPE();

		SA_UTH_GPB(InverseD_SIMD);
		Inverse_Internal<double, major>();
		SA_UTH_GPE();
#else
		Inverse_Internal<float, major>();
#endif
	}

//}

	template <MatrixMajor major>
	void Lerp()
	{
		const Mat3<float, major> m1(
			2.0f, 2.0f, 0.0f,
			6.0f, 10.0f, 16.0f,
			46.0f, 12.0f, 70.0f
		);

		const Mat3<float, major> m2(
			-2.0f, 4.0f, 8.0f,
			4.0f, -60.0f, 10.0f,
			1.0f, 8.0f, -10.0f
		);


		const Mat3<float, major> lerp_res05(
			0.0f, 3.0f, 4.0f,
			5.0f, -25.0f, 13.0f,
			23.5f, 10.0f, 30.0f
		);
		SA_UTH_RSF(lerp_res05, (Mat3<float, major>::Lerp), m1, m2, 0.5f);


#if SA_LOGGING
		Debug::logger.levelFlags.Remove(LogLevel::Warning);
#endif

		// Intended warning.
		SA_UTH_RSF(m2, (Mat3<float, major>::Lerp), m1, m2, 2.0f);

#if SA_LOGGING
		Debug::logger.levelFlags.Add(LogLevel::Warning);
#endif


		const Mat3<float, major> ulerp_res1(
			6.0f, 0.0f, -8.0f,
			8.0f, 80.0f, 22.0f,
			91.0f, 16.0f, 150.0f
		);
		SA_UTH_RSF(ulerp_res1, (Mat3<float, major>::LerpUnclamped), m1, m2, -1.0f);
	}

//{ Transform

	template <typename T, MatrixMajor major>
	void Transform_Internal()
	{
		const T esp = T(0.0001f);

		// Rotation.

		/**
		*	Precomputed values
		*	https://www.wolframalpha.com/input/?i=Quaternion%280.653799%2C+0.491984%2C+-0.573436%2C+-0.0408624%29
		*/
		const Quat<T> q1 = Quat<T>(
			static_cast<T>(0.65379899653308104),
			static_cast<T>(0.49198400950462062),
			static_cast<T>(-0.57343602152727124),
			static_cast<T>(-0.040862400064956901)
		);

		const Mat3<T, major> m1 = Mat3<T>::MakeRotation(q1);
		const Mat3<T, major> m1_res = Mat3<float, major>(
			0.339003f, -0.510811f, -0.790031f,
			-0.617674f, 0.512564f, -0.596453f,
			0.709616f, 0.690181f, -0.141754f
			);

		SA_UTH_MF(m1, Equals, m1_res, esp);


		// Scale.
		const Vec3<T> vScale(UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f));

		const Mat3<T, major> m2 = Mat3<T, major>::MakeScale(vScale);
		Mat3<T, major> m2_res = Mat3<T, major>::Identity;
		m2_res.e00 *= vScale.x;
		m2_res.e11 *= vScale.y;
		m2_res.e22 *= vScale.z;
		SA_UTH_EQ(m2, m2_res);


		// Rotation + Scale.
		const Mat3<T, major> m3 = Mat3<T, major>::MakeTransform(q1, vScale);
		Mat3<T, major> m3_res(
			m1_res.e00 * vScale.x, m1_res.e01 * vScale.x, m1_res.e02 * vScale.x,
			m1_res.e10 * vScale.y, m1_res.e11 * vScale.y, m1_res.e12 * vScale.y,
			m1_res.e20 * vScale.z, m1_res.e21 * vScale.z, m1_res.e22 * vScale.z
		);

		SA_UTH_MF(m3, Equals, m3_res, esp);
	}

	template <MatrixMajor major>
	void Transform()
	{
#if SA_INTRISC
		SA_UTH_GPB(TransformF_SIMD);
		Transform_Internal<float, major>();
		SA_UTH_GPE();

		SA_UTH_GPB(TransformD_SIMD);
		Transform_Internal<double, major>();
		SA_UTH_GPE();
#else
		Transform_Internal<float, major>();
#endif
	}

//}

//{ Operators

	template <typename T, MatrixMajor major>
	void Operators_Internal()
	{
		const T eps = T(0.01);
		Mat3<T, major> m1 = Generate<T, major>();

		// No 0 value for operator /.
		for (int i = 0; i < 9; ++i)
		{
			if (m1[i] == T(0))
				m1[i] = T(1);
		}


		const Mat3<T, major> mm1 = Mat3<T, major>(
			-m1.e00, -m1.e01, -m1.e02,
			-m1.e10, -m1.e11, -m1.e12,
			-m1.e20, -m1.e21, -m1.e22
			);
		SA_UTH_EQ(-m1, mm1);


		// Scalar Scale.
		T scale = T(UTH::Rand(-100.0f, 100.0f));

		// No 0 value for operator /.
		if (scale == T(0))
			scale = T(1);

		const Mat3<T, major> sm1(
			m1.e00 * scale, m1.e01 * scale, m1.e02 * scale,
			m1.e10 * scale, m1.e11 * scale, m1.e12 * scale,
			m1.e20 * scale, m1.e21 * scale, m1.e22 * scale
		);
		SA_UTH_EQ(m1 * scale, sm1);
		SA_UTH_EQ(scale * m1, sm1);

		const Mat3<T, major> usm1(
			m1.e00 / scale, m1.e01 / scale, m1.e02 / scale,
			m1.e10 / scale, m1.e11 / scale, m1.e12 / scale,
			m1.e20 / scale, m1.e21 / scale, m1.e22 / scale
		);
		const Mat3<T, major> susm1(
			scale / m1.e00, scale / m1.e01, scale / m1.e02,
			scale / m1.e10, scale / m1.e11, scale / m1.e12,
			scale / m1.e20, scale / m1.e21, scale / m1.e22
		);
		SA_UTH_EQ(m1 / scale, usm1);
		SA_UTH_EQ(scale / m1, susm1);


		// Vec3 transform operators.
		const Vec3<T> v1 = Vec3f(UTH::Rand(100.0f), UTH::Rand(100.0f), UTH::Rand(100.0f));
		Vec3<T> v1_res = Vec3<T>(
			m1.e00 * v1.x + m1.e01 * v1.y + m1.e02 * v1.z,
			m1.e10 * v1.x + m1.e11 * v1.y + m1.e12 * v1.z,
			m1.e20 * v1.x + m1.e21 * v1.y + m1.e22 * v1.z
			);
		SA_UTH_EQ(m1 * v1, v1_res);


		// Mat3f operators.
		const Mat3<T, major> m2 = Generate<T, major>();

		const Mat3<T, major> m1pm2(
			m1.e00 + m2.e00, m1.e01 + m2.e01, m1.e02 + m2.e02,
			m1.e10 + m2.e10, m1.e11 + m2.e11, m1.e12 + m2.e12,
			m1.e20 + m2.e20, m1.e21 + m2.e21, m1.e22 + m2.e22
		);
		SA_UTH_EQ(m1 + m2, m1pm2);

		const Mat3<T, major> m1mm2(
			m1.e00 - m2.e00, m1.e01 - m2.e01, m1.e02 - m2.e02,
			m1.e10 - m2.e10, m1.e11 - m2.e11, m1.e12 - m2.e12,
			m1.e20 - m2.e20, m1.e21 - m2.e21, m1.e22 - m2.e22
		);
		SA_UTH_EQ(m1 - m2, m1mm2);


		// Precomputed matrix.
		// https://www.wolframalpha.com/input/?i=%7B%7B5.26%2C+48.25%2C+12.36%7D%2C%7B148.2%2C+12.36%2C+68.2%7D%2C%7B9.25%2C+12.3%2C+46.27%7D%7D
		const Mat3<T, major> m3(
			T(5.26), T(48.25), T(12.36),
			T(148.2), T(12.36), T(68.2),
			T(9.25), T(12.3), T(46.27)
		);

		// Precomputed matrix.
		// https://www.wolframalpha.com/input/?i=%7B%7B98.0%2C+1324.0%2C+3.25%7D%2C+%7B63.25%2C+10.2%2C+1.25%7D%2C+%7B47.2%2C+6.21%2C+614.0%7D%7D
		const Mat3<T, major> m4(
			T(98.0), T(1324.0), T(3.25),
			T(63.25), T(10.2), T(1.25),
			T(47.2), T(6.21), T(614.0)
		);


		// Precomputed matrix.
		// https://www.wolframalpha.com/input/?i=%7B%7B5.26%2C+48.25%2C+12.36%7D%2C+%7B148.2%2C+12.36%2C+68.2%7D%2C+%7B9.25%2C+12.3%2C+46.27%7D%7D+*+%7B%7B98.0%2C+1324.0%2C+3.25%7D%2C+%7B63.25%2C+10.2%2C+1.25%7D%2C+%7B47.2%2C+6.21%2C+614.0%7D%7D
		Mat3<T, major> m3multm4;
		Mat3<T, major> m3divm4;

		if constexpr (std::is_integral<T>::value)
		{
			m3multm4 = Mat3<T, major>(
				4078, 7172, 7431,
				18456, 196480, 42208,
				3800, 12312, 28283
				);
		}
		else
		{
			m3multm4 = Mat3<float, major>(
				4150.684570f, 7533.145508f, 7666.447266f,
				18524.408203f, 196766.390625f, 42371.9f,
				3868.419189f, 12659.796875f, 28455.218750f
				);

			m3divm4 = Mat3<float, major>(
				0.0362558f, 0.0121266f, 0.0199137f,
				-0.0087067f, 2.277109f, 0.106485f,
				0.008343f, 0.0772336f, 0.0751569f
				);
		}

		SA_UTH_MF((m3 * m4), Equals, m3multm4, eps);

		if constexpr (std::is_floating_point<T>::value)
			SA_UTH_MF((m3 / m4), Equals, m3divm4, eps);


		// op *= scalar.
		Mat3<T, major> m5 = m1;
		m5 *= scale;
		SA_UTH_EQ(m5, sm1);


		// op /= scalar.
		Mat3<T, major> m6 = m1;
		m6 /= scale;
		SA_UTH_EQ(m6, usm1);


		// op += Mat.
		Mat3<T, major> m7 = m1;
		m7 += m2;
		SA_UTH_EQ(m7, m1pm2);

		// op -= Mat.
		Mat3<T, major> m8 = m1;
		m8 -= m2;
		SA_UTH_EQ(m8, m1mm2);


		// op *= Mat.
		Mat3<T, major> m9 = m3;
		m9 *= m4;
		SA_UTH_MF(m9, Equals, m3multm4, eps);


		// op /= Mat.
		if constexpr (std::is_floating_point<T>::value)
		{
			Mat3<T, major> m10 = m3;
			m10 /= m4;
			SA_UTH_MF(m10, Equals, m3divm4, eps);
		}
	}

	template <MatrixMajor major>
	void Operators()
	{
#if SA_INTRISC
		SA_UTH_GPB(OperatorsI_SIMD);
		Operators_Internal<int32, major>();
		SA_UTH_GPE();

		SA_UTH_GPB(OperatorsF_SIMD);
		Operators_Internal<float, major>();
		SA_UTH_GPE();

		SA_UTH_GPB(OperatorsD_SIMD);
		Operators_Internal<double, major>();
		SA_UTH_GPE();
#else
		Operators_Internal<float, major>();
#endif
	}

//}

//{ Accessors

	template <MatrixMajor major>
	void Accessors();

	template <>
	void Accessors<MatMaj::Row>()
	{
		Mat3<float, MatMaj::Row> m1 = Generate<float, MatMaj::Row>();

		SA_UTH_EQ(m1[0], m1.e00);
		SA_UTH_EQ(m1[1], m1.e01);
		SA_UTH_EQ(m1[2], m1.e02);
		SA_UTH_EQ(m1[3], m1.e10);
		SA_UTH_EQ(m1[4], m1.e11);
		SA_UTH_EQ(m1[5], m1.e12);
		SA_UTH_EQ(m1[6], m1.e20);
		SA_UTH_EQ(m1[7], m1.e21);
		SA_UTH_EQ(m1[8], m1.e22);

		SA_UTH_EQ(m1.At(0), m1.e00);
		SA_UTH_EQ(m1.At(1), m1.e01);
		SA_UTH_EQ(m1.At(2), m1.e02);
		SA_UTH_EQ(m1.At(3), m1.e10);
		SA_UTH_EQ(m1.At(4), m1.e11);
		SA_UTH_EQ(m1.At(5), m1.e12);
		SA_UTH_EQ(m1.At(6), m1.e20);
		SA_UTH_EQ(m1.At(7), m1.e21);
		SA_UTH_EQ(m1.At(8), m1.e22);

		SA_UTH_EQ(m1.At(0, 0), m1.e00);
		SA_UTH_EQ(m1.At(0, 1), m1.e01);
		SA_UTH_EQ(m1.At(0, 2), m1.e02);
		SA_UTH_EQ(m1.At(1, 0), m1.e10);
		SA_UTH_EQ(m1.At(1, 1), m1.e11);
		SA_UTH_EQ(m1.At(1, 2), m1.e12);
		SA_UTH_EQ(m1.At(2, 0), m1.e20);
		SA_UTH_EQ(m1.At(2, 1), m1.e21);
		SA_UTH_EQ(m1.At(2, 2), m1.e22);

		SA_UTH_EQ(m1.Data(), &m1.e00);

		const Mat3<float, MatMaj::Row>& cm1 = m1;

		SA_UTH_EQ(cm1[0], cm1.e00);
		SA_UTH_EQ(cm1[1], cm1.e01);
		SA_UTH_EQ(cm1[2], cm1.e02);
		SA_UTH_EQ(cm1[3], cm1.e10);
		SA_UTH_EQ(cm1[4], cm1.e11);
		SA_UTH_EQ(cm1[5], cm1.e12);
		SA_UTH_EQ(cm1[6], cm1.e20);
		SA_UTH_EQ(cm1[7], cm1.e21);
		SA_UTH_EQ(cm1[8], cm1.e22);

		SA_UTH_EQ(cm1.At(0), cm1.e00);
		SA_UTH_EQ(cm1.At(1), cm1.e01);
		SA_UTH_EQ(cm1.At(2), cm1.e02);
		SA_UTH_EQ(cm1.At(3), cm1.e10);
		SA_UTH_EQ(cm1.At(4), cm1.e11);
		SA_UTH_EQ(cm1.At(5), cm1.e12);
		SA_UTH_EQ(cm1.At(6), cm1.e20);
		SA_UTH_EQ(cm1.At(7), cm1.e21);
		SA_UTH_EQ(cm1.At(8), cm1.e22);

		SA_UTH_EQ(cm1.At(0, 0), cm1.e00);
		SA_UTH_EQ(cm1.At(0, 1), cm1.e01);
		SA_UTH_EQ(cm1.At(0, 2), cm1.e02);
		SA_UTH_EQ(cm1.At(1, 0), cm1.e10);
		SA_UTH_EQ(cm1.At(1, 1), cm1.e11);
		SA_UTH_EQ(cm1.At(1, 2), cm1.e12);
		SA_UTH_EQ(cm1.At(2, 0), cm1.e20);
		SA_UTH_EQ(cm1.At(2, 1), cm1.e21);
		SA_UTH_EQ(cm1.At(2, 2), cm1.e22);

		SA_UTH_EQ(cm1.Data(), &cm1.e00);
	}

	template <>
	void Accessors<MatMaj::Column>()
	{
		Mat3<float, MatMaj::Column> m1 = Generate<float, MatMaj::Column>();

		SA_UTH_EQ(m1[0], m1.e00);
		SA_UTH_EQ(m1[1], m1.e10);
		SA_UTH_EQ(m1[2], m1.e20);
		SA_UTH_EQ(m1[3], m1.e01);
		SA_UTH_EQ(m1[4], m1.e11);
		SA_UTH_EQ(m1[5], m1.e21);
		SA_UTH_EQ(m1[6], m1.e02);
		SA_UTH_EQ(m1[7], m1.e12);
		SA_UTH_EQ(m1[8], m1.e22);

		SA_UTH_EQ(m1.At(0), m1.e00);
		SA_UTH_EQ(m1.At(1), m1.e10);
		SA_UTH_EQ(m1.At(2), m1.e20);
		SA_UTH_EQ(m1.At(3), m1.e01);
		SA_UTH_EQ(m1.At(4), m1.e11);
		SA_UTH_EQ(m1.At(5), m1.e21);
		SA_UTH_EQ(m1.At(6), m1.e02);
		SA_UTH_EQ(m1.At(7), m1.e12);
		SA_UTH_EQ(m1.At(8), m1.e22);

		SA_UTH_EQ(m1.At(0, 0), m1.e00);
		SA_UTH_EQ(m1.At(0, 1), m1.e10);
		SA_UTH_EQ(m1.At(0, 2), m1.e20);
		SA_UTH_EQ(m1.At(1, 0), m1.e01);
		SA_UTH_EQ(m1.At(1, 1), m1.e11);
		SA_UTH_EQ(m1.At(1, 2), m1.e21);
		SA_UTH_EQ(m1.At(2, 0), m1.e02);
		SA_UTH_EQ(m1.At(2, 1), m1.e12);
		SA_UTH_EQ(m1.At(2, 2), m1.e22);

		SA_UTH_EQ(m1.Data(), &m1.e00);

		const Mat3<float, MatMaj::Column>& cm1 = m1;

		SA_UTH_EQ(cm1[0], cm1.e00);
		SA_UTH_EQ(cm1[1], cm1.e10);
		SA_UTH_EQ(cm1[2], cm1.e20);
		SA_UTH_EQ(cm1[3], cm1.e01);
		SA_UTH_EQ(cm1[4], cm1.e11);
		SA_UTH_EQ(cm1[5], cm1.e21);
		SA_UTH_EQ(cm1[6], cm1.e02);
		SA_UTH_EQ(cm1[7], cm1.e12);
		SA_UTH_EQ(cm1[8], cm1.e22);

		SA_UTH_EQ(cm1.At(0), cm1.e00);
		SA_UTH_EQ(cm1.At(1), cm1.e10);
		SA_UTH_EQ(cm1.At(2), cm1.e20);
		SA_UTH_EQ(cm1.At(3), cm1.e01);
		SA_UTH_EQ(cm1.At(4), cm1.e11);
		SA_UTH_EQ(cm1.At(5), cm1.e21);
		SA_UTH_EQ(cm1.At(6), cm1.e02);
		SA_UTH_EQ(cm1.At(7), cm1.e12);
		SA_UTH_EQ(cm1.At(8), cm1.e22);

		SA_UTH_EQ(cm1.At(0, 0), cm1.e00);
		SA_UTH_EQ(cm1.At(0, 1), cm1.e10);
		SA_UTH_EQ(cm1.At(0, 2), cm1.e20);
		SA_UTH_EQ(cm1.At(1, 0), cm1.e01);
		SA_UTH_EQ(cm1.At(1, 1), cm1.e11);
		SA_UTH_EQ(cm1.At(1, 2), cm1.e21);
		SA_UTH_EQ(cm1.At(2, 0), cm1.e02);
		SA_UTH_EQ(cm1.At(2, 1), cm1.e12);
		SA_UTH_EQ(cm1.At(2, 2), cm1.e22);

		SA_UTH_EQ(cm1.Data(), &cm1.e00);
	}

//}

	template <MatMaj major>
	void Main()
	{
		SA_UTH_GP(Constants());
		SA_UTH_GP(Majors());
		SA_UTH_GP(Constructors<major>());
		SA_UTH_GP(Equals<major>());
		SA_UTH_GP(Transpose<major>());
		SA_UTH_GP(Inverse<major>());
		SA_UTH_GP(Lerp<major>());
		SA_UTH_GP(Transform<major>());
		SA_UTH_GP(Operators<major>());
		SA_UTH_GP(Accessors<major>());
	}
}

void Matrix3Tests()
{
	using namespace Matrix3_UT;

	SA_UTH_GP(Main<MatMaj::Row>());
	SA_UTH_GP(Main<MatMaj::Column>());
}
