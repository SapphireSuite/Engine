// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Space/Vector3.hpp>
#include <SA/Maths/Space/Vector4.hpp>
#include <SA/Maths/Space/Quaternion.hpp>
#include <SA/Maths/Matrix/Matrix3.hpp>
#include <SA/Maths/Matrix/Matrix4.hpp>
using namespace Sa;

namespace Sa::Matrix4_UT
{
	template <typename T, MatrixMajor major>
	Mat4<T, major> Generate()
	{
		return Mat4<T, major>(
			UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100),
			UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100),
			UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100),
			UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100), UTH::Rand<T>(-100, 100)
		);
	}

	void Constants()
	{
		// Zero.
		SA_UTH_EQ(Mat4f::Zero.e00, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e01, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e02, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e03, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e10, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e11, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e12, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e13, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e20, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e21, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e22, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e23, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e30, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e31, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e32, 0.0f);
		SA_UTH_EQ(Mat4f::Zero.e33, 0.0f);

		// Identity.
		SA_UTH_EQ(Mat4f::Identity.e00, 1.0f);
		SA_UTH_EQ(Mat4f::Identity.e01, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e02, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e03, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e10, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e11, 1.0f);
		SA_UTH_EQ(Mat4f::Identity.e12, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e13, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e20, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e21, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e22, 1.0f);
		SA_UTH_EQ(Mat4f::Identity.e23, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e30, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e31, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e32, 0.0f);
		SA_UTH_EQ(Mat4f::Identity.e33, 1.0f);
	}

	void Majors()
	{
		float e00 = UTH::Rand(-100.0f, 100.0f);
		float e01 = UTH::Rand(-100.0f, 100.0f);
		float e02 = UTH::Rand(-100.0f, 100.0f);
		float e03 = UTH::Rand(-100.0f, 100.0f);
		float e10 = UTH::Rand(-100.0f, 100.0f);
		float e11 = UTH::Rand(-100.0f, 100.0f);
		float e12 = UTH::Rand(-100.0f, 100.0f);
		float e13 = UTH::Rand(-100.0f, 100.0f);
		float e20 = UTH::Rand(-100.0f, 100.0f);
		float e21 = UTH::Rand(-100.0f, 100.0f);
		float e22 = UTH::Rand(-100.0f, 100.0f);
		float e23 = UTH::Rand(-100.0f, 100.0f);
		float e30 = UTH::Rand(-100.0f, 100.0f);
		float e31 = UTH::Rand(-100.0f, 100.0f);
		float e32 = UTH::Rand(-100.0f, 100.0f);
		float e33 = UTH::Rand(-100.0f, 100.0f);

		const Mat4<float, MatrixMajor::Row> m1(
			e00, e01, e02, e03,
			e10, e11, e12, e13,
			e20, e21, e22, e23,
			e30, e31, e32, e33
		);
		const Mat4<float, MatrixMajor::Column> m2(
			e00, e01, e02, e03,
			e10, e11, e12, e13,
			e20, e21, e22, e23,
			e30, e31, e32, e33
		);

		// Same value for same name.
		SA_UTH_EQ(m1.e00, m2.e00);
		SA_UTH_EQ(m1.e01, m2.e01);
		SA_UTH_EQ(m1.e02, m2.e02);
		SA_UTH_EQ(m1.e03, m2.e03);
		SA_UTH_EQ(m1.e10, m2.e10);
		SA_UTH_EQ(m1.e11, m2.e11);
		SA_UTH_EQ(m1.e12, m2.e12);
		SA_UTH_EQ(m1.e13, m2.e13);
		SA_UTH_EQ(m1.e20, m2.e20);
		SA_UTH_EQ(m1.e21, m2.e21);
		SA_UTH_EQ(m1.e22, m2.e22);
		SA_UTH_EQ(m1.e23, m2.e23);
		SA_UTH_EQ(m1.e30, m2.e30);
		SA_UTH_EQ(m1.e31, m2.e31);
		SA_UTH_EQ(m1.e32, m2.e32);
		SA_UTH_EQ(m1.e33, m2.e33);

		const float* const dm1 = m1.Data();
		const float* const dm2 = m2.Data();

		// Different memory.
		SA_UTH_EQ(dm1[0], dm2[0]);
		SA_UTH_EQ(dm1[1], dm2[4]);
		SA_UTH_EQ(dm1[2], dm2[8]);
		SA_UTH_EQ(dm1[3], dm2[12]);

		SA_UTH_EQ(dm1[4], dm2[1]);
		SA_UTH_EQ(dm1[5], dm2[5]);
		SA_UTH_EQ(dm1[6], dm2[9]);
		SA_UTH_EQ(dm1[7], dm2[13]);

		SA_UTH_EQ(dm1[8], dm2[2]);
		SA_UTH_EQ(dm1[9], dm2[6]);
		SA_UTH_EQ(dm1[10], dm2[10]);
		SA_UTH_EQ(dm1[11], dm2[14]);

		SA_UTH_EQ(dm1[12], dm2[3]);
		SA_UTH_EQ(dm1[13], dm2[7]);
		SA_UTH_EQ(dm1[14], dm2[11]);
		SA_UTH_EQ(dm1[15], dm2[15]);
	}


	template <MatrixMajor major>
	void Constructors()
	{
		// Default constructor.
		const Mat4<float, major> m0;
		SA_UTH_EQ(m0.e00, 0.0f);
		SA_UTH_EQ(m0.e01, 0.0f);
		SA_UTH_EQ(m0.e02, 0.0f);
		SA_UTH_EQ(m0.e03, 0.0f);
		SA_UTH_EQ(m0.e10, 0.0f);
		SA_UTH_EQ(m0.e11, 0.0f);
		SA_UTH_EQ(m0.e12, 0.0f);
		SA_UTH_EQ(m0.e13, 0.0f);
		SA_UTH_EQ(m0.e20, 0.0f);
		SA_UTH_EQ(m0.e21, 0.0f);
		SA_UTH_EQ(m0.e22, 0.0f);
		SA_UTH_EQ(m0.e23, 0.0f);
		SA_UTH_EQ(m0.e30, 0.0f);
		SA_UTH_EQ(m0.e31, 0.0f);
		SA_UTH_EQ(m0.e32, 0.0f);
		SA_UTH_EQ(m0.e33, 0.0f);


		// Value constructor.
		const float m1e00 = UTH::Rand(-100.0f, 100.0f);
		const float m1e01 = UTH::Rand(-100.0f, 100.0f);
		const float m1e02 = UTH::Rand(-100.0f, 100.0f);
		const float m1e03 = UTH::Rand(-100.0f, 100.0f);
		const float m1e10 = UTH::Rand(-100.0f, 100.0f);
		const float m1e11 = UTH::Rand(-100.0f, 100.0f);
		const float m1e12 = UTH::Rand(-100.0f, 100.0f);
		const float m1e13 = UTH::Rand(-100.0f, 100.0f);
		const float m1e20 = UTH::Rand(-100.0f, 100.0f);
		const float m1e21 = UTH::Rand(-100.0f, 100.0f);
		const float m1e22 = UTH::Rand(-100.0f, 100.0f);
		const float m1e23 = UTH::Rand(-100.0f, 100.0f);
		const float m1e30 = UTH::Rand(-100.0f, 100.0f);
		const float m1e31 = UTH::Rand(-100.0f, 100.0f);
		const float m1e32 = UTH::Rand(-100.0f, 100.0f);
		const float m1e33 = UTH::Rand(-100.0f, 100.0f);
		const Mat4<float, major> m1(
			m1e00, m1e01, m1e02, m1e03,
			m1e10, m1e11, m1e12, m1e13,
			m1e20, m1e21, m1e22, m1e23,
			m1e30, m1e31, m1e32, m1e33
		);

		SA_UTH_EQ(m1.e00, m1e00);
		SA_UTH_EQ(m1.e01, m1e01);
		SA_UTH_EQ(m1.e02, m1e02);
		SA_UTH_EQ(m1.e03, m1e03);
		SA_UTH_EQ(m1.e10, m1e10);
		SA_UTH_EQ(m1.e11, m1e11);
		SA_UTH_EQ(m1.e12, m1e12);
		SA_UTH_EQ(m1.e13, m1e13);
		SA_UTH_EQ(m1.e20, m1e20);
		SA_UTH_EQ(m1.e21, m1e21);
		SA_UTH_EQ(m1.e22, m1e22);
		SA_UTH_EQ(m1.e23, m1e23);
		SA_UTH_EQ(m1.e30, m1e30);
		SA_UTH_EQ(m1.e31, m1e31);
		SA_UTH_EQ(m1.e32, m1e32);
		SA_UTH_EQ(m1.e33, m1e33);


		// Value cast constructor.
		const int32 m2e00 = UTH::Rand(-100, 100);
		const int32 m2e01 = UTH::Rand(-100, 100);
		const int32 m2e02 = UTH::Rand(-100, 100);
		const int32 m2e03 = UTH::Rand(-100, 100);
		const int32 m2e10 = UTH::Rand(-100, 100);
		const int32 m2e11 = UTH::Rand(-100, 100);
		const int32 m2e12 = UTH::Rand(-100, 100);
		const int32 m2e13 = UTH::Rand(-100, 100);
		const int32 m2e20 = UTH::Rand(-100, 100);
		const int32 m2e21 = UTH::Rand(-100, 100);
		const int32 m2e22 = UTH::Rand(-100, 100);
		const int32 m2e23 = UTH::Rand(-100, 100);
		const int32 m2e30 = UTH::Rand(-100, 100);
		const int32 m2e31 = UTH::Rand(-100, 100);
		const int32 m2e32 = UTH::Rand(-100, 100);
		const int32 m2e33 = UTH::Rand(-100, 100);
		const Mat4<float, major> m2(Mat4<int32, major>(
			m2e00, m2e01, m2e02, m2e03,
			m2e10, m2e11, m2e12, m2e13,
			m2e20, m2e21, m2e22, m2e23,
			m2e30, m2e31, m2e32, m2e33
			));

		SA_UTH_EQ(m2.e00, static_cast<float>(m2e00));
		SA_UTH_EQ(m2.e01, static_cast<float>(m2e01));
		SA_UTH_EQ(m2.e02, static_cast<float>(m2e02));
		SA_UTH_EQ(m2.e03, static_cast<float>(m2e03));
		SA_UTH_EQ(m2.e10, static_cast<float>(m2e10));
		SA_UTH_EQ(m2.e11, static_cast<float>(m2e11));
		SA_UTH_EQ(m2.e12, static_cast<float>(m2e12));
		SA_UTH_EQ(m2.e13, static_cast<float>(m2e13));
		SA_UTH_EQ(m2.e20, static_cast<float>(m2e20));
		SA_UTH_EQ(m2.e21, static_cast<float>(m2e21));
		SA_UTH_EQ(m2.e22, static_cast<float>(m2e22));
		SA_UTH_EQ(m2.e23, static_cast<float>(m2e23));
		SA_UTH_EQ(m2.e30, static_cast<float>(m2e30));
		SA_UTH_EQ(m2.e31, static_cast<float>(m2e31));
		SA_UTH_EQ(m2.e32, static_cast<float>(m2e32));
		SA_UTH_EQ(m2.e33, static_cast<float>(m2e33));



		// Copy constructor.
		const Mat4<float, major> m3(m1);

		SA_UTH_EQ(m3.e00, m1.e00);
		SA_UTH_EQ(m3.e01, m1.e01);
		SA_UTH_EQ(m3.e02, m1.e02);
		SA_UTH_EQ(m3.e03, m1.e03);
		SA_UTH_EQ(m3.e10, m1.e10);
		SA_UTH_EQ(m3.e11, m1.e11);
		SA_UTH_EQ(m3.e12, m1.e12);
		SA_UTH_EQ(m3.e13, m1.e13);
		SA_UTH_EQ(m3.e20, m1.e20);
		SA_UTH_EQ(m3.e21, m1.e21);
		SA_UTH_EQ(m3.e22, m1.e22);
		SA_UTH_EQ(m3.e23, m1.e23);
		SA_UTH_EQ(m3.e30, m1.e30);
		SA_UTH_EQ(m3.e31, m1.e31);
		SA_UTH_EQ(m3.e32, m1.e32);
		SA_UTH_EQ(m3.e33, m1.e33);


		// From Mat3.
		const Mat3<float, major> m4(
			UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f),
			UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f),
			UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f)
		);

		const Mat4<float, major> m5(m4);

		SA_UTH_EQ(m5.e00, m4.e00);
		SA_UTH_EQ(m5.e01, m4.e01);
		SA_UTH_EQ(m5.e02, m4.e02);
		SA_UTH_EQ(m5.e03, 0.0f);
		SA_UTH_EQ(m5.e10, m4.e10);
		SA_UTH_EQ(m5.e11, m4.e11);
		SA_UTH_EQ(m5.e12, m4.e12);
		SA_UTH_EQ(m5.e13, 0.0f);
		SA_UTH_EQ(m5.e20, m4.e20);
		SA_UTH_EQ(m5.e21, m4.e21);
		SA_UTH_EQ(m5.e22, m4.e22);
		SA_UTH_EQ(m5.e23, 0.0f);
		SA_UTH_EQ(m5.e30, 0.0f);
		SA_UTH_EQ(m5.e31, 0.0f);
		SA_UTH_EQ(m5.e32, 0.0f);
		SA_UTH_EQ(m5.e33, 1.0f); // Default fill with identity.
	}

	template <MatrixMajor major>
	void Equals()
	{
		const Mat4f m1 = Generate<float, major>();
		const Mat4f m2 = Generate<float, major>();

		SA_UTH_RMF(false, m1, IsZero);
		SA_UTH_MF((Mat4<float, major>::Zero), IsZero);

		SA_UTH_MF(m1, Equals, m1);
		SA_UTH_RMF(false, m1, Equals, m2);

		SA_UTH_OP(m1, == , m1);
		SA_UTH_OP(m1, != , m2);
	}

	template <MatrixMajor major>
	void Transpose()
	{
		const Mat4<float, major> m1 = Generate<float, major>();
		const Mat4<float, major> m2 = m1.GetTransposed();

		SA_UTH_EQ(m2.e00, m1.e00);
		SA_UTH_EQ(m2.e10, m1.e01);
		SA_UTH_EQ(m2.e20, m1.e02);
		SA_UTH_EQ(m2.e30, m1.e03);
		SA_UTH_EQ(m2.e01, m1.e10);
		SA_UTH_EQ(m2.e11, m1.e11);
		SA_UTH_EQ(m2.e21, m1.e12);
		SA_UTH_EQ(m2.e31, m1.e13);
		SA_UTH_EQ(m2.e02, m1.e20);
		SA_UTH_EQ(m2.e12, m1.e21);
		SA_UTH_EQ(m2.e22, m1.e22);
		SA_UTH_EQ(m2.e32, m1.e23);
		SA_UTH_EQ(m2.e03, m1.e30);
		SA_UTH_EQ(m2.e13, m1.e31);
		SA_UTH_EQ(m2.e23, m1.e32);
		SA_UTH_EQ(m2.e33, m1.e33);


		// Self transpose.
		Mat4<float, major> m3 = m1;
		m3.Transpose();
		SA_UTH_EQ(m3, m2);
	}

//{ Inverse

	template <typename T, MatrixMajor major>
	void Inverse_Internal()
	{
		// Precomputed matrix.
		// https://www.wolframalpha.com/input/?i=%7B%7B5.26%2C+48.25%2C+12.36%2C+6.25%7D%2C%7B148.2%2C+12.36%2C+68.2%2C+17.36%7D%2C%7B9.25%2C+12.3%2C+46.27%2C+9.15%7D%2C%7B27.1%2C+7.4%2C+11.2%2C+4.23%7D%7D
		const Mat4<T, major> m1(
			T(5.26), T(48.25), T(12.36), T(6.25),
			T(148.2), T(12.36), T(68.2), T(17.36),
			T(9.25), T(12.3), T(46.27), T(9.15),
			T(27.1), T(7.4), T(11.2), T(4.23)
		);

		const T eps = T(0.1);

		SA_UTH_EQ(m1.Determinant(), T(-237488.906250), eps);

		// Precomputed matrix.
		const Mat4<T, major> m1_resInv = Mat4<float, major>(
			0.00560278f, 0.0143744f, -0.013435f, -0.0382097f,
			0.0340719f, 0.0173389f, -0.0110158f, -0.0976733f,
			0.0182788f, 0.0351108f, 0.0134225f, -0.200137f,
			-0.143898f, -0.215389f, 0.0698044f, 1.18199f
			);

		SA_UTH_MF(m1.GetInversed(), Equals, m1_resInv, eps);

		// Self inverse.
		Mat4<T, major> m2 = m1;
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

//{ Lerp

	template <MatrixMajor major>
	void Lerp()
	{
		const Mat4<float, major> m1(
			2.0f, 2.0f, 0.0f, 30.0f,
			6.0f, 10.0f, 16.0f, 26.0f,
			46.0f, 12.0f, 70.0f, 2.0f,
			9.0f, 18.0f, 0.0f, 31.0f
		);

		const Mat4<float, major> m2(
			-2.0f, 4.0f, 8.0f, 94.0f,
			4.0f, -60.0f, 10.0f, 32.0f,
			1.0f, 8.0f, -10.0f, 41.0f,
			20.0f, 1.0, 4.0, 13.0f
		);


		const Mat4<float, major> lerp_res05(
			0.0f, 3.0f, 4.0f, 62.0f,
			5.0f, -25.0f, 13.0f, 29.0f,
			23.5f, 10.0f, 30.0f, 21.5f,
			14.5f, 9.5f, 2.0f, 22.0f
		);
		SA_UTH_RSF(lerp_res05, (Mat4<float, major>::Lerp), m1, m2, 0.5f);


		SA_LOGLVL_DIS_SECTB(Warning)

			// Intended warning.
			SA_UTH_RSF(m2, (Mat4<float, major>::Lerp), m1, m2, 2.0f);
		
		SA_LOGLVL_DIS_SECTE()


		const Mat4<float, major> ulerp_res1(
			6.0f, 0.0f, -8.0f, -34.0f,
			8.0f, 80.0f, 22.0f, 20.0f,
			91.0f, 16.0f, 150.0f, -37.0f,
			-2.0f, 35.0f, -4.0f, 49.0f
		);
		SA_UTH_RSF(ulerp_res1, (Mat4<float, major>::LerpUnclamped), m1, m2, -1.0f);
	}

//}

//{ Transform

	template <typename T, MatrixMajor major>
	void Transform_Internal()
	{
		const T eps = T(0.0001);

		// Translation.
		const Vec3<T> vTr = Vec3f(10.0412f, 2.361f, 12.35f);
		const Mat4<T, major> mTr = Mat4<float, major>(
			1.0f, 0.0f, 0.0f, static_cast<float>(vTr.x),
			0.0f, 1.0f, 0.0f, static_cast<float>(vTr.y),
			0.0f, 0.0f, 1.0f, static_cast<float>(vTr.z),
			0.0f, 0.0f, 0.0f, 1.0f
		);
		SA_UTH_EQ((Mat4<T, major>::MakeTranslation(vTr)), mTr);

		Mat4<T, major> mTr2 = Mat4<T, major>::Identity;
		mTr2.ApplyTranslation(vTr);
		SA_UTH_EQ(mTr2, mTr);


		// Rotation.

		/**
		*	Precomputed values
		*	https://www.wolframalpha.com/input/?i=Quaternion%280.653799%2C+0.491984%2C+-0.573436%2C+-0.0408624%29
		*/
		const Quat<T> q1 = Quatd(
			0.65379899684951437,
			0.49198400932684733,
			-0.57343602132006610,
			-0.040862400050191698
		);

		const Mat4<T, major> mRot = Mat4<float, major>(
			0.339003f, -0.510811f, -0.790031f, 0.0f,
			-0.617674f, 0.512564f, -0.596453f, 0.0f,
			0.709616f, 0.690181f, -0.141754f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);

		SA_UTH_MF((Mat4<T, major>::MakeRotation(q1)), Equals, mRot, eps);


		// Scale.
		const Vec3<T> vScale = Vec3f(UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f));

		Mat4<T, major> mScale = Mat4<T, major>::Identity;
		mScale.e00 *= vScale.x;
		mScale.e11 *= vScale.y;
		mScale.e22 *= vScale.z;
		SA_UTH_EQ((Mat4<T, major>::MakeScale(vScale)), mScale);


		// Translation + Rotation.
		Mat4<T, major> mTrRot = mRot;
		mTrRot.e03 = vTr.x;
		mTrRot.e13 = vTr.y;
		mTrRot.e23 = vTr.z;

		const Mat4<T, major> mmTrRot = Mat4<T, major>::MakeTransform(vTr, q1);
		SA_UTH_MF(mmTrRot, Equals, mTrRot, eps);


		// Translation + Scale.
		Mat4<T, major> mTrScale = mScale;
		mTrScale.e03 = vTr.x;
		mTrScale.e13 = vTr.y;
		mTrScale.e23 = vTr.z;

		const Mat4<T, major> mmTrScale = Mat4<T, major>::MakeTransform(vTr, vScale);
		SA_UTH_EQ(mmTrScale, mTrScale);


		// Rotation + Scale.
		const Mat4<T, major> mRotScale = mScale * mRot;

		const Mat4<T, major> mmRotScale = Mat4<T, major>::MakeTransform(q1, vScale);
		SA_UTH_MF(mmRotScale, Equals, mRotScale, eps);


		// Translation + Rotation + Scale.
		Mat4<T, major> mTrRotScale = mRotScale;
		mTrRotScale.e03 = vTr.x;
		mTrRotScale.e13 = vTr.y;
		mTrRotScale.e23 = vTr.z;

		const Mat4<T, major> mmTrRotScale = Mat4<T, major>::MakeTransform(vTr, q1, vScale);
		SA_UTH_MF(mmTrRotScale, Equals, mTrRotScale, eps);
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

	template <typename T, MatrixMajor major>
	void Operators_Internal()
	{
		const T eps = T(0.01);
		Mat4<T, major> m1 = Generate<T, major>();

		// No 0 value for operator /.
		for (int i = 0; i < 16; ++i)
		{
			if (m1[i] == T(0))
				m1[i] = T(1);
		}


		const Mat4<T, major> mm1 = Mat4<T, major>(
			-m1.e00, -m1.e01, -m1.e02, -m1.e03,
			-m1.e10, -m1.e11, -m1.e12, -m1.e13,
			-m1.e20, -m1.e21, -m1.e22, -m1.e23,
			-m1.e30, -m1.e31, -m1.e32, -m1.e33
			);
		SA_UTH_EQ(-m1, mm1);


		// Scalar Scale.
		T scale = T(UTH::Rand(-100.0f, 100.0f));

		// No 0 value for operator /.
		if (scale == T(0))
			scale = T(1);

		const Mat4<T, major> sm1(
			m1.e00 * scale, m1.e01 * scale, m1.e02 * scale, m1.e03 * scale,
			m1.e10 * scale, m1.e11 * scale, m1.e12 * scale, m1.e13 * scale,
			m1.e20 * scale, m1.e21 * scale, m1.e22 * scale, m1.e23 * scale,
			m1.e30 * scale, m1.e31 * scale, m1.e32 * scale, m1.e33 * scale
		);
		SA_UTH_EQ(m1 * scale, sm1);
		SA_UTH_EQ(scale * m1, sm1);

		const Mat4<T, major> usm1(
			m1.e00 / scale, m1.e01 / scale, m1.e02 / scale, m1.e03 / scale,
			m1.e10 / scale, m1.e11 / scale, m1.e12 / scale, m1.e13 / scale,
			m1.e20 / scale, m1.e21 / scale, m1.e22 / scale, m1.e23 / scale,
			m1.e30 / scale, m1.e31 / scale, m1.e32 / scale, m1.e33 / scale
		);
		const Mat4<T, major> susm1(
			scale / m1.e00, scale / m1.e01, scale / m1.e02, scale / m1.e03,
			scale / m1.e10, scale / m1.e11, scale / m1.e12, scale / m1.e13,
			scale / m1.e20, scale / m1.e21, scale / m1.e22, scale / m1.e23,
			scale / m1.e30, scale / m1.e31, scale / m1.e32, scale / m1.e33
		);
		SA_UTH_EQ(m1 / scale, usm1);
		SA_UTH_EQ(scale / m1, susm1);

		// Vec transform operators.
		const Vec3<T> v1 = Vec3f(UTH::Rand(100.0f), UTH::Rand(100.0f), UTH::Rand(100.0f));
		Vec3<T> v1_res = Vec3<T>(
			m1.e00 * v1.x + m1.e01 * v1.y + m1.e02 * v1.z,
			m1.e10 * v1.x + m1.e11 * v1.y + m1.e12 * v1.z,
			m1.e20 * v1.x + m1.e21 * v1.y + m1.e22 * v1.z
			);
		SA_UTH_MF(m1 * v1, Equals, v1_res, T(0.01));

		const Vec4<T> v2 = Vec4f(UTH::Rand(100.0f), UTH::Rand(100.0f), UTH::Rand(100.0f), UTH::Rand(100.0f));
		Vec4<T> v2_res = Vec4<T>(
			m1.e00 * v2.x + m1.e01 * v2.y + m1.e02 * v2.z + m1.e03 * v2.w,
			m1.e10 * v2.x + m1.e11 * v2.y + m1.e12 * v2.z + m1.e13 * v2.w,
			m1.e20 * v2.x + m1.e21 * v2.y + m1.e22 * v2.z + m1.e23 * v2.w,
			m1.e30 * v2.x + m1.e31 * v2.y + m1.e32 * v2.z + m1.e33 * v2.w
			);
		SA_UTH_MF(m1 * v2, Equals, v2_res, T(0.01));


		// Mat4f operators.
		const Mat4<T, major> m2 = Generate<T, major>();

		const Mat4<T, major> m1pm2(
			m1.e00 + m2.e00, m1.e01 + m2.e01, m1.e02 + m2.e02, m1.e03 + m2.e03,
			m1.e10 + m2.e10, m1.e11 + m2.e11, m1.e12 + m2.e12, m1.e13 + m2.e13,
			m1.e20 + m2.e20, m1.e21 + m2.e21, m1.e22 + m2.e22, m1.e23 + m2.e23,
			m1.e30 + m2.e30, m1.e31 + m2.e31, m1.e32 + m2.e32, m1.e33 + m2.e33
		);
		SA_UTH_EQ(m1 + m2, m1pm2);

		const Mat4<T, major> m1mm2(
			m1.e00 - m2.e00, m1.e01 - m2.e01, m1.e02 - m2.e02, m1.e03 - m2.e03,
			m1.e10 - m2.e10, m1.e11 - m2.e11, m1.e12 - m2.e12, m1.e13 - m2.e13,
			m1.e20 - m2.e20, m1.e21 - m2.e21, m1.e22 - m2.e22, m1.e23 - m2.e23,
			m1.e30 - m2.e30, m1.e31 - m2.e31, m1.e32 - m2.e32, m1.e33 - m2.e33
		);
		SA_UTH_EQ(m1 - m2, m1mm2);


		// Precomputed matrix.
		// https://www.wolframalpha.com/input/?i=%7B%7B5.26%2C+48.25%2C+12.36%2C+6.25%7D%2C%7B148.2%2C+12.36%2C+68.2%2C+17.36%7D%2C%7B9.25%2C+12.3%2C+46.27%2C+9.15%7D%2C%7B27.1%2C+7.4%2C+11.2%2C+4.23%7D%7D
		const Mat4<T, major> m3(
			T(5.26), T(48.25), T(12.36), T(6.25),
			T(148.2), T(12.36), T(68.2), T(17.36),
			T(9.25), T(12.3), T(46.27), T(9.15),
			T(27.1), T(7.4), T(11.2), T(4.23)
		);

		// Precomputed matrix.
		// https://www.wolframalpha.com/input/?i=%7B%7B98.0%2C+1324.0%2C+3.25%2C+6.21%7D%2C%7B63.25%2C+10.2%2C+1.25%2C+8.12%7D%2C%7B47.2%2C+6.21%2C+614.0%2C+45.31%7D%2C%7B5.36%2C+14.2%2C+3.22%2C+7.25%7D%7D
		const Mat4<T, major> m4(
			T(98.0), T(1324.0), T(3.25), T(6.21),
			T(63.25), T(10.2), T(1.25), T(8.12),
			T(47.2), T(6.21), T(614.0), T(45.31),
			T(5.36), T(14.2), T(3.22), T(7.25)
		);


		// Precomputed matrix.
		// https://www.wolframalpha.com/input/?i=matrix%28%7B5.26%2C+48.25%2C+12.36%7D%2C+%7B148.2%2C+12.36%2C+68.2%7D%2C+%7B9.25%2C+12.3%2C+46.27%7D%29+*+matrix%28%7B98.0%2C+1324.0%2C+3.25%7D%2C+%7B63.25%2C+10.2%2C+1.25%7D%2C+%7B47.2%2C+6.21%2C+614.0%7D%29
		Mat4<T, major> m3multm4;
		Mat4<T, major> m3divm4;

		if constexpr (std::is_integral<T>::value)
		{
			m3multm4 = Mat4<T, major>(
				4108, 7256, 7449, 996,
				18541, 196718, 42259, 4163,
				3845, 12438, 28310, 2283,
				3624, 35940, 6854, 741
				);
		}
		else
		{
			m3multm4 = Mat4<float, major>(
				4184.1845f, 7621.8956f, 7686.5725f, 1029.7987f,
				18617.457031f, 197012.906250f, 42427.796875f, 4236.687012f,
				3917.463135f, 12789.726562f, 28484.681641f, 2320.149902f,
				3675.163086f, 36085.500000f, 6987.745605f, 766.518494f
				);

			m3divm4 = Mat4<float, major>(
				0.028285f, -0.038804f, 0.015961f, 0.781553f,
				0.000656f, 2.336921f, 0.111128f, -0.917945f,
				0.000305f, 0.025881f, 0.071171f, 0.788025f,
				0.002203f, 0.411019f, 0.017325f, 0.012946f
				);
		}

		SA_UTH_MF((m3 * m4), Equals, m3multm4, eps);


		if constexpr (std::is_floating_point<T>::value)
			SA_UTH_MF((m3 / m4), Equals, m3divm4, eps);


		// op *= scalar.
		Mat4<T, major> m5 = m1;
		m5 *= scale;
		SA_UTH_EQ(m5, sm1);


		// op /= scalar.
		Mat4<T, major> m6 = m1;
		m6 /= scale;
		SA_UTH_EQ(m6, usm1);


		// op += Mat.
		Mat4<T, major> m7 = m1;
		m7 += m2;
		SA_UTH_EQ(m7, m1pm2);

		// op -= Mat.
		Mat4<T, major> m8 = m1;
		m8 -= m2;
		SA_UTH_EQ(m8, m1mm2);


		// op *= Mat.
		Mat4<T, major> m9 = m3;
		m9 *= m4;
		SA_UTH_MF(m9, Equals, m3multm4, eps);


		// op /= Mat.
		if constexpr (std::is_floating_point<T>::value)
		{
			Mat4<T, major> m10 = m3;
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
		Operators_Internal<int32, major>();
		Operators_Internal<float, major>();
#endif
	}

//{ Accessors

	template <MatrixMajor major>
	void Accessors();

	template <>
	void Accessors<MatMaj::Row>()
	{
		Mat4<float, MatMaj::Row> m1 = Generate<float, MatMaj::Row>();

		SA_UTH_EQ(m1[0], m1.e00);
		SA_UTH_EQ(m1[1], m1.e01);
		SA_UTH_EQ(m1[2], m1.e02);
		SA_UTH_EQ(m1[3], m1.e03);
		SA_UTH_EQ(m1[4], m1.e10);
		SA_UTH_EQ(m1[5], m1.e11);
		SA_UTH_EQ(m1[6], m1.e12);
		SA_UTH_EQ(m1[7], m1.e13);
		SA_UTH_EQ(m1[8], m1.e20);
		SA_UTH_EQ(m1[9], m1.e21);
		SA_UTH_EQ(m1[10], m1.e22);
		SA_UTH_EQ(m1[11], m1.e23);
		SA_UTH_EQ(m1[12], m1.e30);
		SA_UTH_EQ(m1[13], m1.e31);
		SA_UTH_EQ(m1[14], m1.e32);
		SA_UTH_EQ(m1[15], m1.e33);

		SA_UTH_EQ(m1.At(0), m1.e00);
		SA_UTH_EQ(m1.At(1), m1.e01);
		SA_UTH_EQ(m1.At(2), m1.e02);
		SA_UTH_EQ(m1.At(3), m1.e03);
		SA_UTH_EQ(m1.At(4), m1.e10);
		SA_UTH_EQ(m1.At(5), m1.e11);
		SA_UTH_EQ(m1.At(6), m1.e12);
		SA_UTH_EQ(m1.At(7), m1.e13);
		SA_UTH_EQ(m1.At(8), m1.e20);
		SA_UTH_EQ(m1.At(9), m1.e21);
		SA_UTH_EQ(m1.At(10), m1.e22);
		SA_UTH_EQ(m1.At(11), m1.e23);
		SA_UTH_EQ(m1.At(12), m1.e30);
		SA_UTH_EQ(m1.At(13), m1.e31);
		SA_UTH_EQ(m1.At(14), m1.e32);
		SA_UTH_EQ(m1.At(15), m1.e33);

		SA_UTH_EQ(m1.At(0, 0), m1.e00);
		SA_UTH_EQ(m1.At(0, 1), m1.e01);
		SA_UTH_EQ(m1.At(0, 2), m1.e02);
		SA_UTH_EQ(m1.At(0, 3), m1.e03);
		SA_UTH_EQ(m1.At(1, 0), m1.e10);
		SA_UTH_EQ(m1.At(1, 1), m1.e11);
		SA_UTH_EQ(m1.At(1, 2), m1.e12);
		SA_UTH_EQ(m1.At(1, 3), m1.e13);
		SA_UTH_EQ(m1.At(2, 0), m1.e20);
		SA_UTH_EQ(m1.At(2, 1), m1.e21);
		SA_UTH_EQ(m1.At(2, 2), m1.e22);
		SA_UTH_EQ(m1.At(2, 3), m1.e23);
		SA_UTH_EQ(m1.At(3, 0), m1.e30);
		SA_UTH_EQ(m1.At(3, 1), m1.e31);
		SA_UTH_EQ(m1.At(3, 2), m1.e32);
		SA_UTH_EQ(m1.At(3, 3), m1.e33);

		SA_UTH_EQ(m1.Data(), &m1.e00);

		const Mat4<float, MatMaj::Row>& cm1 = m1;

		SA_UTH_EQ(cm1[0], cm1.e00);
		SA_UTH_EQ(cm1[1], cm1.e01);
		SA_UTH_EQ(cm1[2], cm1.e02);
		SA_UTH_EQ(cm1[3], cm1.e03);
		SA_UTH_EQ(cm1[4], cm1.e10);
		SA_UTH_EQ(cm1[5], cm1.e11);
		SA_UTH_EQ(cm1[6], cm1.e12);
		SA_UTH_EQ(cm1[7], cm1.e13);
		SA_UTH_EQ(cm1[8], cm1.e20);
		SA_UTH_EQ(cm1[9], cm1.e21);
		SA_UTH_EQ(cm1[10], cm1.e22);
		SA_UTH_EQ(cm1[11], cm1.e23);
		SA_UTH_EQ(cm1[12], cm1.e30);
		SA_UTH_EQ(cm1[13], cm1.e31);
		SA_UTH_EQ(cm1[14], cm1.e32);
		SA_UTH_EQ(cm1[15], cm1.e33);

		SA_UTH_EQ(cm1.At(0), cm1.e00);
		SA_UTH_EQ(cm1.At(1), cm1.e01);
		SA_UTH_EQ(cm1.At(2), cm1.e02);
		SA_UTH_EQ(cm1.At(3), cm1.e03);
		SA_UTH_EQ(cm1.At(4), cm1.e10);
		SA_UTH_EQ(cm1.At(5), cm1.e11);
		SA_UTH_EQ(cm1.At(6), cm1.e12);
		SA_UTH_EQ(cm1.At(7), cm1.e13);
		SA_UTH_EQ(cm1.At(8), cm1.e20);
		SA_UTH_EQ(cm1.At(9), cm1.e21);
		SA_UTH_EQ(cm1.At(10), cm1.e22);
		SA_UTH_EQ(cm1.At(11), cm1.e23);
		SA_UTH_EQ(cm1.At(12), cm1.e30);
		SA_UTH_EQ(cm1.At(13), cm1.e31);
		SA_UTH_EQ(cm1.At(14), cm1.e32);
		SA_UTH_EQ(cm1.At(15), cm1.e33);

		SA_UTH_EQ(cm1.At(0, 0), cm1.e00);
		SA_UTH_EQ(cm1.At(0, 1), cm1.e01);
		SA_UTH_EQ(cm1.At(0, 2), cm1.e02);
		SA_UTH_EQ(cm1.At(0, 3), cm1.e03);
		SA_UTH_EQ(cm1.At(1, 0), cm1.e10);
		SA_UTH_EQ(cm1.At(1, 1), cm1.e11);
		SA_UTH_EQ(cm1.At(1, 2), cm1.e12);
		SA_UTH_EQ(cm1.At(1, 3), cm1.e13);
		SA_UTH_EQ(cm1.At(2, 0), cm1.e20);
		SA_UTH_EQ(cm1.At(2, 1), cm1.e21);
		SA_UTH_EQ(cm1.At(2, 2), cm1.e22);
		SA_UTH_EQ(cm1.At(2, 3), cm1.e23);
		SA_UTH_EQ(cm1.At(3, 0), cm1.e30);
		SA_UTH_EQ(cm1.At(3, 1), cm1.e31);
		SA_UTH_EQ(cm1.At(3, 2), cm1.e32);
		SA_UTH_EQ(cm1.At(3, 3), cm1.e33);

		SA_UTH_EQ(cm1.Data(), &cm1.e00);
	}

	template <>
	void Accessors<MatMaj::Column>()
	{
		Mat4<float, MatMaj::Column> m1 = Generate<float, MatMaj::Column>();

		SA_UTH_EQ(m1[0], m1.e00);
		SA_UTH_EQ(m1[1], m1.e10);
		SA_UTH_EQ(m1[2], m1.e20);
		SA_UTH_EQ(m1[3], m1.e30);
		SA_UTH_EQ(m1[4], m1.e01);
		SA_UTH_EQ(m1[5], m1.e11);
		SA_UTH_EQ(m1[6], m1.e21);
		SA_UTH_EQ(m1[7], m1.e31);
		SA_UTH_EQ(m1[8], m1.e02);
		SA_UTH_EQ(m1[9], m1.e12);
		SA_UTH_EQ(m1[10], m1.e22);
		SA_UTH_EQ(m1[11], m1.e32);
		SA_UTH_EQ(m1[12], m1.e03);
		SA_UTH_EQ(m1[13], m1.e13);
		SA_UTH_EQ(m1[14], m1.e23);
		SA_UTH_EQ(m1[15], m1.e33);

		SA_UTH_EQ(m1.At(0), m1.e00);
		SA_UTH_EQ(m1.At(1), m1.e10);
		SA_UTH_EQ(m1.At(2), m1.e20);
		SA_UTH_EQ(m1.At(3), m1.e30);
		SA_UTH_EQ(m1.At(4), m1.e01);
		SA_UTH_EQ(m1.At(5), m1.e11);
		SA_UTH_EQ(m1.At(6), m1.e21);
		SA_UTH_EQ(m1.At(7), m1.e31);
		SA_UTH_EQ(m1.At(8), m1.e02);
		SA_UTH_EQ(m1.At(9), m1.e12);
		SA_UTH_EQ(m1.At(10), m1.e22);
		SA_UTH_EQ(m1.At(11), m1.e32);
		SA_UTH_EQ(m1.At(12), m1.e03);
		SA_UTH_EQ(m1.At(13), m1.e13);
		SA_UTH_EQ(m1.At(14), m1.e23);
		SA_UTH_EQ(m1.At(15), m1.e33);

		SA_UTH_EQ(m1.At(0, 0), m1.e00);
		SA_UTH_EQ(m1.At(0, 1), m1.e10);
		SA_UTH_EQ(m1.At(0, 2), m1.e20);
		SA_UTH_EQ(m1.At(0, 3), m1.e30);
		SA_UTH_EQ(m1.At(1, 0), m1.e01);
		SA_UTH_EQ(m1.At(1, 1), m1.e11);
		SA_UTH_EQ(m1.At(1, 2), m1.e21);
		SA_UTH_EQ(m1.At(1, 3), m1.e31);
		SA_UTH_EQ(m1.At(2, 0), m1.e02);
		SA_UTH_EQ(m1.At(2, 1), m1.e12);
		SA_UTH_EQ(m1.At(2, 2), m1.e22);
		SA_UTH_EQ(m1.At(2, 3), m1.e32);
		SA_UTH_EQ(m1.At(3, 0), m1.e03);
		SA_UTH_EQ(m1.At(3, 1), m1.e13);
		SA_UTH_EQ(m1.At(3, 2), m1.e23);
		SA_UTH_EQ(m1.At(3, 3), m1.e33);

		SA_UTH_EQ(m1.Data(), &m1.e00);


		const Mat4<float, MatMaj::Column>& cm1 = m1;

		SA_UTH_EQ(cm1[0], cm1.e00);
		SA_UTH_EQ(cm1[1], cm1.e10);
		SA_UTH_EQ(cm1[2], cm1.e20);
		SA_UTH_EQ(cm1[3], cm1.e30);
		SA_UTH_EQ(cm1[4], cm1.e01);
		SA_UTH_EQ(cm1[5], cm1.e11);
		SA_UTH_EQ(cm1[6], cm1.e21);
		SA_UTH_EQ(cm1[7], cm1.e31);
		SA_UTH_EQ(cm1[8], cm1.e02);
		SA_UTH_EQ(cm1[9], cm1.e12);
		SA_UTH_EQ(cm1[10], cm1.e22);
		SA_UTH_EQ(cm1[11], cm1.e32);
		SA_UTH_EQ(cm1[12], cm1.e03);
		SA_UTH_EQ(cm1[13], cm1.e13);
		SA_UTH_EQ(cm1[14], cm1.e23);
		SA_UTH_EQ(cm1[15], cm1.e33);

		SA_UTH_EQ(cm1.At(0), cm1.e00);
		SA_UTH_EQ(cm1.At(1), cm1.e10);
		SA_UTH_EQ(cm1.At(2), cm1.e20);
		SA_UTH_EQ(cm1.At(3), cm1.e30);
		SA_UTH_EQ(cm1.At(4), cm1.e01);
		SA_UTH_EQ(cm1.At(5), cm1.e11);
		SA_UTH_EQ(cm1.At(6), cm1.e21);
		SA_UTH_EQ(cm1.At(7), cm1.e31);
		SA_UTH_EQ(cm1.At(8), cm1.e02);
		SA_UTH_EQ(cm1.At(9), cm1.e12);
		SA_UTH_EQ(cm1.At(10), cm1.e22);
		SA_UTH_EQ(cm1.At(11), cm1.e32);
		SA_UTH_EQ(cm1.At(12), cm1.e03);
		SA_UTH_EQ(cm1.At(13), cm1.e13);
		SA_UTH_EQ(cm1.At(14), cm1.e23);
		SA_UTH_EQ(cm1.At(15), cm1.e33);

		SA_UTH_EQ(cm1.At(0, 0), cm1.e00);
		SA_UTH_EQ(cm1.At(0, 1), cm1.e10);
		SA_UTH_EQ(cm1.At(0, 2), cm1.e20);
		SA_UTH_EQ(cm1.At(0, 3), cm1.e30);
		SA_UTH_EQ(cm1.At(1, 0), cm1.e01);
		SA_UTH_EQ(cm1.At(1, 1), cm1.e11);
		SA_UTH_EQ(cm1.At(1, 2), cm1.e21);
		SA_UTH_EQ(cm1.At(1, 3), cm1.e31);
		SA_UTH_EQ(cm1.At(2, 0), cm1.e02);
		SA_UTH_EQ(cm1.At(2, 1), cm1.e12);
		SA_UTH_EQ(cm1.At(2, 2), cm1.e22);
		SA_UTH_EQ(cm1.At(2, 3), cm1.e32);
		SA_UTH_EQ(cm1.At(3, 0), cm1.e03);
		SA_UTH_EQ(cm1.At(3, 1), cm1.e13);
		SA_UTH_EQ(cm1.At(3, 2), cm1.e23);
		SA_UTH_EQ(cm1.At(3, 3), cm1.e33);

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

void Matrix4Tests()
{
	using namespace Matrix4_UT;

	SA_UTH_GP(Main<MatMaj::Row>());
	SA_UTH_GP(Main<MatMaj::Column>());
}
