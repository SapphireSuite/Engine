// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

#include <SA/Maths/Space/Vector3.hpp>
#include <SA/Maths/Space/Quaternion.hpp>
using namespace Sa;

namespace Sa::Quaternion_UT
{
	Quatf Generate()
	{
		return Quatf(UTH::Rand(-100.0f, 100.0f),
			UTH::Rand(-100.0f, 100.0f),
			UTH::Rand(-100.0f, 100.0f),
			UTH::Rand(-100.0f, 100.0f));
	}

	void Constants()
	{
		SA_UTH_EQ(Quatf::Zero.w, 0.0f);
		SA_UTH_EQ(Quatf::Zero.x, 0.0f);
		SA_UTH_EQ(Quatf::Zero.y, 0.0f);
		SA_UTH_EQ(Quatf::Zero.z, 0.0f);


		SA_UTH_EQ(Quatf::Identity.w, 1.0f);
		SA_UTH_EQ(Quatf::Identity.x, 0.0f);
		SA_UTH_EQ(Quatf::Identity.y, 0.0f);
		SA_UTH_EQ(Quatf::Identity.z, 0.0f);
	}

	void Constructors()
	{
		// Default constructor.
		const Quatf q0;
		SA_UTH_EQ(q0.w, 1.0f);
		SA_UTH_EQ(q0.x, 0.0f);
		SA_UTH_EQ(q0.y, 0.0f);
		SA_UTH_EQ(q0.z, 0.0f);


		// Value constructor.
		const float q1W = UTH::Rand(-100.0f, 100.0f);
		const float q1X = UTH::Rand(-100.0f, 100.0f);
		const float q1Y = UTH::Rand(-100.0f, 100.0f);
		const float q1Z = UTH::Rand(-100.0f, 100.0f);
		const Quatf q1(q1W, q1X, q1Y, q1Z);

		SA_UTH_EQ(q1.w, q1W);
		SA_UTH_EQ(q1.x, q1X);
		SA_UTH_EQ(q1.y, q1Y);
		SA_UTH_EQ(q1.z, q1Z);


		// Angle axis.
		const Degf q2An = UTH::Rand(-180.0f, 180.0f);
		const Radf q2HAn = q2An / 2.0f;

		const Vec3f q2Ax = Vec3f(UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f), UTH::Rand(-100.0f, 100.0f)).Normalize();
		const Vec3f res_q2Ax = q2Ax * std::sin(static_cast<float>(q2HAn));
		const Quatf q2(q2An, q2Ax);

		SA_UTH_EQ(q2.w, std::cos(static_cast<float>(q2HAn)));
		SA_UTH_EQ(q2.x, res_q2Ax.x);
		SA_UTH_EQ(q2.y, res_q2Ax.y);
		SA_UTH_EQ(q2.z, res_q2Ax.z);


		// Value cast constructor.
		const int32 q3W = UTH::Rand<int32>(-100, 100);
		const int32 q3X = UTH::Rand<int32>(-100, 100);
		const int32 q3Y = UTH::Rand<int32>(-100, 100);
		const int32 q3Z = UTH::Rand<int32>(-100, 100);
		const Quatf q3(Quat<int32>(q3W, q3X, q3Y, q3Z));

		SA_UTH_EQ(q3.w, static_cast<float>(q3W));
		SA_UTH_EQ(q3.x, static_cast<float>(q3X));
		SA_UTH_EQ(q3.y, static_cast<float>(q3Y));
		SA_UTH_EQ(q3.z, static_cast<float>(q3Z));


		// Copy constructor.
		const Quatf q4(q1);

		SA_UTH_EQ(q4.w, q1.w);
		SA_UTH_EQ(q4.x, q1.x);
		SA_UTH_EQ(q4.y, q1.y);
		SA_UTH_EQ(q4.z, q1.z);
	}

	void Equals()
	{
		const Quatf q1 = Generate();
		const Quatf q2 = Generate();

		SA_UTH_RMF(false, q1, IsZero);
		SA_UTH_MF(Quatf::Zero, IsZero);

		SA_UTH_MF(q1, Equals, q1);
		SA_UTH_RMF(false, q1, Equals, q2);

		SA_UTH_OP(q1, == , q1);
		SA_UTH_OP(q1, != , q2);
	}

	template <typename T>
	void Lenght_Internal()
	{
		Quat<T> q1 = Generate();

		const T qLenSqr = q1.w * q1.w + q1.x * q1.x + q1.y * q1.y + q1.z * q1.z;
		const T qLen = Maths::Sqrt(qLenSqr);
		SA_UTH_RMF(qLen, q1, Length);
		SA_UTH_RMF(qLenSqr, q1, SqrLength);

		const Quat<T> nQ1 = q1.GetNormalized();
		SA_UTH_EQ(nQ1.x, q1.x / qLen);
		SA_UTH_EQ(nQ1.y, q1.y / qLen);

		SA_UTH_MF(nQ1, IsNormalized);
		SA_UTH_EQ(nQ1.Length(), T(1.0), std::numeric_limits<T>::epsilon());
		SA_UTH_RMF(false, q1, IsNormalized);

		q1.Normalize();
		SA_UTH_OP(q1, == , nQ1);
	}

	void Lenght()
	{
#if SA_INTRISC
		SA_UTH_GPB(LenghtF_SIMD);
		Lenght_Internal<float>();
		SA_UTH_GPE();

		SA_UTH_GPB(LenghtD_SIMD);
		Lenght_Internal<double>();
		SA_UTH_GPE();
#else
		Lenght_Internal<float>();
#endif
	}

	void Inverse()
	{
		Quatf q1 = Generate().GetNormalized();
		const Quatf q2 = q1.GetInversed();

		SA_UTH_EQ(q2.w, q1.w);
		SA_UTH_EQ(q2.x, -q1.x);
		SA_UTH_EQ(q2.y, -q1.y);
		SA_UTH_EQ(q2.z, -q1.z);

		q1.Inverse();
		SA_UTH_MF(q1, Equals, q2);
	}

	template <typename T>
	void Rotate_Internal()
	{
		const T eps = T(0.0000001);

		/**
		*	Random values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=Quaternion%2848%2B36.12i-42.1j-3k%29
		*/
		const Quat<T> q1(
			static_cast<T>(0.65379899684951437),
			static_cast<T>(0.49198400932684733),
			static_cast<T>(-0.57343602132006610),
			static_cast<T>(-0.040862400050191698)
		);

		/**
		*	Random values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=Quaternion%287%2B1.36i-4j-23.2k%29
		*/
		const Quat<T> q2(
			static_cast<T>(0.28456911695921927),
			static_cast<T>(0.055287819843885436),
			static_cast<T>(-0.16261099422502870),
			static_cast<T>(-0.94314438937370981)
		);

		/**
		*	Computed values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=Quaternion%2848%2B36.12i-42.1j-3k%29*Quaternion%287%2B1.36i-4j-23.2k%29
		*/
		const Quat<T> q1mltq2(
			static_cast<T>(0.027064135033571496),
			static_cast<T>(0.71033886691834713),
			static_cast<T>(0.19225567792515003),
			static_cast<T>(-0.67655301421661274)
		);
		SA_UTH_MF(q1.Rotate(q2), Equals, q1mltq2, eps);

		/**
		*	Computed values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=Quaternion%2848-36.12i42.1j3k%29*Quaternion%287%2B1.36i-4j-23.2k%29
		*/
		const Quat<T> q1dq2(
			static_cast<T>(0.34503787137100783),
			static_cast<T>(-0.63804462461448919),
			static_cast<T>(-0.40488548772720184),
			static_cast<T>(-0.55670069709694570)
		);
		SA_UTH_MF(q1.UnRotate(q2), Equals, q1dq2, eps);

		/**
		*	Random values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=vector+%7B2%2C+-5%2C+4%7D
		*/
		const Vec3<T> axis(
			static_cast<T>(0.29814198175425533),
			static_cast<T>(-0.74535601236806759),
			static_cast<T>(0.59628497678745696)
		);

		/// Precomputed values.
		const Vec3<T> q1RAxis(
			static_cast<T>(0.010723429430577691),
			static_cast<T>(-0.92185348802304057),
			static_cast<T>(-0.38739022428794517)
		);
		SA_UTH_MF(q1.Rotate(axis), Equals, q1RAxis, eps);

		/// Precomputed values.
		const Vec3<T> q1URAxis(
			static_cast<T>(0.98459188616666193),
			static_cast<T>(-0.12279218649081475),
			static_cast<T>(0.12450272215675917)
		);
		SA_UTH_MF(q1.UnRotate(axis), Equals, q1URAxis, eps);

		/// Precomputed values.
		const Vec3<T> q1RightAxis(
			static_cast<T>(0.33900278631197822),
			static_cast<T>(-0.61767429909059990),
			static_cast<T>(0.70961649737777233)
		);
		SA_UTH_MF(q1.RightVector(), Equals, q1RightAxis, eps);

		/// Precomputed values.
		const Vec3<T> q1UpAxis(
			static_cast<T>(-0.51081111426321479),
			static_cast<T>(0.51256399683354759),
			static_cast<T>(0.69018124890739507)
		);
		SA_UTH_MF(q1.UpVector(), Equals, q1UpAxis, eps);

		/// Precomputed values.
		const Vec3<T> q1ForwardAxis(
			static_cast<T>(-0.79003108714336978),
			static_cast<T>(-0.59645336032344964),
			static_cast<T>(-0.14175427389173478)
		);
		SA_UTH_MF(q1.ForwardVector(), Equals, q1ForwardAxis, eps);
	}

	void Rotate()
	{
#if SA_INTRISC
		SA_UTH_GPB(RotateF_SIMD);
		Rotate_Internal<float>();
		SA_UTH_GPE();

		SA_UTH_GPB(RotateD_SIMD);
		Rotate_Internal<double>();
		SA_UTH_GPE();
#else
		Rotate_Internal<float>();
#endif
	}

	template <typename T>
	void Euler_Internal()
	{
		// Pi/2 angle on X Axis.
		const Quat<T> q1(90.0_deg, Vec3<T>(1.0f, 0.0f, 0.0f));
		const Vec3<T> res_eul1 = Vec3<T>(90.0f, 0.0f, 0.0f);
		const Vec3<Deg<T>> eul1 = Vec3<T>(q1.ToEuler());
		SA_UTH_MF(Vec3<T>(eul1), Equals, res_eul1, 0.1f);
		SA_UTH_MF(Quat<T>::FromEuler(eul1), Equals, q1);

		// Pi/2 angle on Y Axis.
		const Quat<T> q2(90.0_deg, Vec3<T>(0.0f, 1.0f, 0.0f));
		const Vec3<T> res_eul2 = Vec3<T>(0.0f, 90.0f, 0.0f);
		const Vec3<Deg<T>> eul2 = Vec3<T>(q2.ToEuler());
		SA_UTH_MF(Vec3<T>(eul2), Equals, res_eul2, 0.1f);
		SA_UTH_MF(Quat<T>::FromEuler(eul2), Equals, q2, 0.001f);

		// Pi/2 angle on Z Axis.
		const Quat<T> q3(90.0_deg, Vec3<T>(0.0f, 0.0f, 1.0f));
		const Vec3<T> res_eul3 = Vec3<T>(0.0f, 0.0f, 90.0f);
		const Vec3<Deg<T>> eul3 = Vec3<T>(q3.ToEuler());
		SA_UTH_MF(Vec3<T>(eul3), Equals, res_eul3, 0.1f);
		SA_UTH_MF(Quat<T>::FromEuler(eul3), Equals, q3);


		// Pi/2 angle on XY Axis.
		const Quat<T> q4(90.0_deg, Vec3<T>(1.0f, 1.0f, 0.0f).Normalize());
		const Vec3<T> res_eul4 = Vec3<T>(90.0f, 45.0f, 45.0f);
		const Vec3<Deg<T>> eul4 = Vec3<T>(q4.ToEuler());
		SA_UTH_MF(Vec3<T>(eul4), Equals, res_eul4, 0.1f);
		SA_UTH_MF(Quat<T>::FromEuler(eul4), Equals, q4, 0.00001f);

		// Pi/2 angle on XZ Axis.
		const Quat<T> q5(90.0_deg, Vec3<T>(1.0f, 0.0f, 1.0f).Normalize());
		const Vec3<T> res_eul5 = Vec3<T>(54.75f, -30.0f, 54.75f);
		const Vec3<Deg<T>> eul5 = Vec3<T>(q5.ToEuler());
		SA_UTH_MF(Vec3<T>(eul5), Equals, res_eul5, 0.1f);
		SA_UTH_MF(Quat<T>::FromEuler(eul5), Equals, q5);

		// Pi/2 angle on YZ Axis.
		const Quat<T> q6(90.0_deg, Vec3<T>(0.0f, 1.0f, 1.0f).Normalize());
		const Vec3<T> res_eul6 = Vec3<T>(45.0f, 45.0f, 90.0f);
		const Vec3<Deg<T>> eul6 = Vec3<T>(q6.ToEuler());
		SA_UTH_MF(Vec3<T>(eul6), Equals, res_eul6, 0.1f);
		SA_UTH_MF(Quat<T>::FromEuler(eul6), Equals, q6);


		// Pi/2 angle on XYZ Axis.
		const Quat<T> q7(90.0_deg, Vec3<T>(1.0f, 1.0f, 1.0f).Normalize());
		const Vec3<T> res_eul7 = Vec3<T>(70.0f, 14.0f, 70.0f);
		const Vec3<Deg<T>> eul7 = Vec3<T>(q7.ToEuler());
		SA_UTH_MF(Vec3<T>(eul7), Equals, res_eul7, 1.0f);
		SA_UTH_MF(Quat<T>::FromEuler(eul7), Equals, q7, 0.00001f);


		// random angle on random axis.
		const Quat<T> q8(145.264_deg, Vec3<T>(3.656f, 1.15f, 7.36f).Normalize());
		const Vec3<T> res_eul8 = Vec3<T>(37.84f, -39.26f, 127.20f);
		const Vec3<Deg<T>> eul8 = Vec3<T>(q8.ToEuler());
		SA_UTH_MF(Vec3<T>(eul8), Equals, res_eul8, 0.1f);
		SA_UTH_MF(Quat<T>::FromEuler(eul8), Equals, q8, 0.00001f);
	}

	void Euler()
	{
#if SA_INTRISC
		SA_UTH_GPB(EulerF_SIMD);
		Euler_Internal<float>();
		SA_UTH_GPE();

		SA_UTH_GPB(EulerD_SIMD);
		Euler_Internal<double>();
		SA_UTH_GPE();
#else
		Euler_Internal<float>();
#endif
	}

	template <typename T>
	void Dot_Internal()
	{
		const Quat<T> q1 = Generate();
		const Quat<T> q2 = Generate();

		T dot = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
		SA_UTH_RSF(dot, Quat<T>::Dot, q1, q2);
		SA_UTH_ROP(dot, q1, | , q2);
	}

	void Dot()
	{
#if SA_INTRISC
		SA_UTH_GPB(DotF_SIMD);
		Dot_Internal<float>();
		SA_UTH_GPE();

		SA_UTH_GPB(DotD_SIMD);
		Dot_Internal<double>();
		SA_UTH_GPE();
#else
		Dot_Internal<float>();
#endif
	}

	void Lerp()
	{
		/**
		*	Random values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=Quaternion%2848%2C36.12%2C-42.1%2C-3%29
		*/
		const Quatf q1(0.653799f, 0.491984f, -0.573436f, -0.0408624f);

		/**
		*	Random values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=Quaternion%287%2B1.36i-4j-23.2k%29
		*/
		const Quatf q2(0.2845691f, 0.05528782f, -0.162611f, -0.9431444f);

		// Precomputed value.
		const Quatf lerp_res05 = Quatf(0.5721251f, 0.3336728f, -0.4487695f, -0.5999511f);
		SA_UTH_RSF(lerp_res05, Quatf::Lerp, q1, q2, 0.5f);

		// Intended warning.
		SA_UTH_RSF(q2, Quatf::Lerp, q1, q2, 2.0f);

		// Precomputed value.
		const Quatf ulerp_res1 = Quatf(0.5377033f, 0.4881137f, -0.517327f, 0.4527616f);
		SA_UTH_RSF(ulerp_res1, Quatf::LerpUnclamped, q1, q2, -1.0f);

		// Precomputed value.
		const Quatf slerp_res05 = Quatf(0.5721251f, 0.3336728f, -0.4487695f, -0.5999511f);
		SA_UTH_RSF(slerp_res05, Quatf::SLerp, q1, q2, 0.5f)
	}

	template <typename T>
	void Operators_Internal()
	{
		const T eps = T(0.000001);
		const Quat<T> q1 = Generate();

		const Quat<T> mq1 = Quat<T>(-q1.w, -q1.x, -q1.y, -q1.z);
		SA_UTH_EQ(-q1, mq1);

		// Scalar Scale.
		T scale = UTH::Rand(-100.0f, 100.0f);
		const Quat<T> sq1 = Quat<T>(q1.w * scale, q1.x * scale, q1.y * scale, q1.z * scale);
		SA_UTH_EQ(q1 * scale, sq1);
		SA_UTH_EQ(scale * q1, sq1);

		const Quat<T> usq1 = Quat<T>(q1.w / scale, q1.x / scale, q1.y / scale, q1.z / scale);
		const Quat<T> susq1 = Quat<T>(scale / q1.w, scale / q1.x, scale / q1.y, scale / q1.z);
		SA_UTH_EQ(q1 / scale, usq1);
		SA_UTH_EQ(scale / q1, susq1);


		// Quat operators.
		const Quat<T> q2 = Generate();

		const Quat<T> q1pq2 = Quat<T>(q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z);
		SA_UTH_EQ(q1 + q2, q1pq2);

		const Quat<T> q1mq2 = Quat<T>(q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z);
		SA_UTH_EQ(q1 - q2, q1mq2);


		/**
		*	Random values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=Quaternion%2848%2C36.12%2C-42.1%2C-3%29
		*/
		const Quat<T> qmlt1(0.65379899684951437, 0.49198400932684733, -0.57343602132006610, -0.040862400050191698);

		/**
		*	Random values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=Quaternion%287%2B1.36i-4j-23.2k%29
		*/
		const Quat<T> qmlt2(0.28456911695921927, 0.055287819843885436, -0.16261099422502870, -0.94314438937370981);

		/**
		*	Computed values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=Quaternion%2848%2B36.12i-42.1j-3k%29*Quaternion%287%2B1.36i-4j-23.2k%29
		*/
		const Quat<T> q1mltq2(0.027064122703847494, 0.71033883189067515, 0.19225561767425950, -0.67655306860818476);
		SA_UTH_MF((qmlt1 * qmlt2), Equals, q1mltq2, eps);

		/**
		*	Computed values from Wolfram Alpha.
		*	https://www.wolframalpha.com/input/?i=Quaternion%280.653799+%2B+0.491984i+-+0.573436j+-+0.0408624k%29+*+Quaternion%280.0115685+-+0.0022476i+%2B+0.00661059j+%2B+0.0383414k%29
		*/
		const Quat<T> q1dq2(0.34503790147878188, -0.43033188617788687, -0.51861987096184237, 0.65329682666091582);
		SA_UTH_MF((qmlt1 / qmlt2), Equals, q1dq2, eps);

		// op *= scalar.
		Quat<T> q3 = q1;
		q3 *= scale;
		SA_UTH_EQ(q3, sq1);


		// op /= scalar.
		Quat<T> q4 = q1;
		q4 /= scale;
		SA_UTH_EQ(q4, usq1);


		// op += Quat.
		Quat<T> q5 = q1;
		q5 += q2;
		SA_UTH_EQ(q5, q1pq2);

		// op -= Quat.
		Quat<T> q6 = q1;
		q6 -= q2;
		SA_UTH_EQ(q6, q1mq2);


		// op *= Quat.
		Quat<T> q7 = qmlt1;
		q7 *= qmlt2;
		SA_UTH_MF(q7, Equals, q1mltq2, eps);


		// op /= Quat.
		Quat<T> q8 = qmlt1;
		q8 /= qmlt2;
		SA_UTH_MF(q8, Equals, q1dq2, eps);
	}

	void Operators()
	{
#if SA_INTRISC
		SA_UTH_GPB(OperatorsF_SIMD);
		Operators_Internal<float>();
		SA_UTH_GPE();

		SA_UTH_GPB(OperatorsD_SIMD);
		Operators_Internal<double>();
		SA_UTH_GPE();
#else
		Operators_Internal<float>();
#endif
	}

	void Accessors()
	{
		const Quatf q1 = Generate();

		SA_UTH_EQ(q1[0], q1.w);
		SA_UTH_EQ(q1[1], q1.x);
		SA_UTH_EQ(q1[2], q1.y);
		SA_UTH_EQ(q1[3], q1.z);

		SA_UTH_EQ(q1.Data(), &q1.w);
		SA_UTH_EQ(const_cast<Quatf&>(q1).Data(), &const_cast<Quatf&>(q1).w);

		SA_UTH_EQ(&q1.ImgAxis().x, &q1.x);
		SA_UTH_EQ(&const_cast<Quatf&>(q1).ImgAxis().x, &const_cast<Quatf&>(q1).x);
	}
}

void QuaternionTests()
{
	using namespace Quaternion_UT;

	SA_UTH_GP(Constants());
	SA_UTH_GP(Constructors());
	SA_UTH_GP(Equals());
	SA_UTH_GP(Lenght());
	SA_UTH_GP(Inverse());
	SA_UTH_GP(Rotate());
	SA_UTH_GP(Euler());
	SA_UTH_GP(Dot());
	SA_UTH_GP(Lerp());
	SA_UTH_GP(Operators());
	SA_UTH_GP(Accessors());
}
