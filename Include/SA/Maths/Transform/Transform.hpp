// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_TRANSFORM_GUARD
#define SAPPHIRE_MATHS_TRANSFORM_GUARD

#include <SA/Maths/Matrix/Matrix4.hpp>
#include <SA/Maths/Transform/TransformBase.hpp>

namespace Sa
{
	template <typename T, TrComp Comps>
	struct Transf : public Intl::TransfBaseT<T, Comps>
	{
//{ Constructors

		// No defined constructors to keep default struct init constructor.
		// Use cast operator for Transform type conversion instead.
		
		/// \e Default constructor.
		Transf() = default;

		/// Default move constructor.
		Transf(Transf&&) = default;

		/// Default copy constructor.
		Transf(const Transf&) = default;
//}


//{ Equals

		/**
		*	\brief Whether this transform is a zero transform.
		*
		*	\return True if this is a zero transform.
		*/
		constexpr bool IsZero() const noexcept;

		/**
		*	\brief Whether this transform is an identity transform.
		*
		*	\return True if this is an identity transform.
		*/
		constexpr bool IsIdentity() const noexcept;

		/**
		*	\brief \e Compare 2 transform.
		*
		*	\param[in] _other		Other transform to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold comparison.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(const Transf& _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept;


		/**
		*	\brief \e Compare 2 transform equality.
		*
		*	\param[in] _rhs		Other transform to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(const Transf& _rhs) noexcept;

		/**
		*	\brief \e Compare 2 transform inequality.
		*
		*	\param[in] _rhs		Other transform to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(const Transf& _rhs) noexcept;
//}


//{ Transformation

		/**
		*	\brief \e Getter of \b right vector (X axis) of this transform.
		*
		*	\return transformed right vector normalized.
		*/
		Vec3<T> Right() const;

		/**
		*	\brief \e Getter of \b up vector (Y axis) of this transform.
		*
		*	\return transformed up vector normalized.
		*/
		Vec3<T> Up() const;

		/**
		*	\brief \e Getter of \b forward vector (Z axis) of this transform.
		*
		*	\return transformed forward vector normalized.
		*/
		Vec3<T> Forward() const;

		/**
		*	\brief \e Getter of Matrix
		*
		*	\return transformed forward vector normalized.
		*/
		Mat4<T> Matrix() const;

//}


//{ Lerp

		/**
		*	\brief <b> Clamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\param _start	Starting point of the lerp.
		*	\param _end		Ending point of the lerp.
		*	\param _alpha	Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		static Transf Lerp(const Transf& _start, const Transf& _end, float _alpha) noexcept;

		/**
		*	\brief <b> Unclamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\param _start	Starting point of the lerp.
		*	\param _end		Ending point of the lerp.
		*	\param _alpha	Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		static Transf LerpUnclamped(const Transf& _start, const Transf& _end, float _alpha) noexcept;

//}


//{ Operators

		/**
		*	\brief \e Default assignment move operator.
		*
		*	\return self transform assigned.
		*/
		Transf& operator=(Transf&&) = default;

		/**
		*	\brief \e Default assignment copy operator.
		*
		*	\return self transform assigned.
		*/
		Transf& operator=(const Transf&) = default;


		/**
		*	\brief \b Multiply transform to compute transformation.
		*
		*	\param[in] _rhs		Transform to multiply.
		*
		*	\return new transform result.
		*/
		template <TrComp CIn>
		Transf operator*(const Transf<T, CIn>& _other) const;

		/**
		*	\brief \b Divide transform to compute inverse-transformation.
		*
		*	\param[in] _rhs		Transform to divide.
		*
		*	\return new transform result.
		*/
		template <TrComp CIn>
		Transf operator/(const Transf<T, CIn>& _other) const;

		/**
		*	\brief \b Multiply transform to compute transformation.
		*
		*	\param[in] _rhs		Transform to multiply.
		*
		*	\return self transform result.
		*/
		template <TrComp CIn>
		Transf& operator*=(const Transf<T, CIn>& _other);

		/**
		*	\brief \b Divide transform to compute inverse-transformation.
		*
		*	\param[in] _rhs		Transform to divide.
		*
		*	\return self transform result.
		*/
		template <TrComp CIn>
		Transf& operator/=(const Transf<T, CIn>& _other);


		/**
		*	\brief \e Cast operator into other Transf type.
		*
		*	\tparam TIn		Type of the casted transform.
		*	\tparam CIn		Type of the casted TrComp.
		*
		*	\return \e Casted result.
		*/
		template <typename TIn, TrComp CIn>
		constexpr operator Transf<TIn, CIn>() const noexcept;
//}


#if SA_LOGGING

		/**
		*	\brief ToString implementation
		*
		*	Convert this Transform as a string.
		*
		*	\return this as a string.
		*/
		std::string ToString() const noexcept;

#endif
	};


//{ Aliases

		/// Alias for Position Transf.
	template <typename T>
	using TransfP = Transf<T, TrComp::Position>;

	/// Alias for Rotation Transf.
	template <typename T>
	using TransfR = Transf<T, TrComp::Rotation>;

	/// Alias for Scale Transf.
	template <typename T>
	using TransfS = Transf<T, TrComp::Scale>;

	/// Alias for Position Rotation Transf.
	template <typename T>
	using TransfPR = Transf<T, TrComp::PR>;

	/// Alias for Position Scale Transf.
	template <typename T>
	using TransfPS = Transf<T, TrComp::PS>;

	/// Alias for Rotation Scale Transf.
	template <typename T>
	using TransfRS = Transf<T, TrComp::RS>;

	/// Alias for Position Rotation Scale Transf.
	template <typename T>
	using TransfPRS = Transf<T, TrComp::PRS>;


	/// Alias for float Transf.
	template <TrComp TrComps>
	using Transff = Transf<float, TrComps>;

	/// Alias for float Position Transf.
	using TransffP = Transf<float, TrComp::Position>;

	/// Alias for float Rotation Transf.
	using TransffR = Transf<float, TrComp::Rotation>;

	/// Alias for float Scale Transf.
	using TransffS = Transf<float, TrComp::Scale>;

	/// Alias for float Position Rotation Transf.
	using TransffPR = Transf<float, TrComp::PR>;

	/// Alias for float Position Scale Transf.
	using TransffPS = Transf<float, TrComp::PS>;

	/// Alias for float Rotation Scale Transf.
	using TransffRS = Transf<float, TrComp::RS>;

	/// Alias for float Position Rotation Scale Transf.
	using TransffPRS = Transf<float, TrComp::PRS>;


	/// Template alias of Transform
	template <typename T, TrComp TrComps>
	using Transform = Transf<T, TrComps>;

	/// Alias for Position Transform.
	template <typename T>
	using TransformP = Transform<T, TrComp::Position>;

	/// Alias for Rotation Transform.
	template <typename T>
	using TransformR = Transform<T, TrComp::Rotation>;

	/// Alias for Scale Transform.
	template <typename T>
	using TransformS = Transform<T, TrComp::Scale>;

	/// Alias for Position Rotation Transform.
	template <typename T>
	using TransformPR = Transform<T, TrComp::PR>;

	/// Alias for Position Scale Transform.
	template <typename T>
	using TransformPS = Transform<T, TrComp::PS>;

	/// Alias for Rotation Scale Transform.
	template <typename T>
	using TransformRS = Transform<T, TrComp::RS>;

	/// Alias for Position Rotation Scale Transform.
	template <typename T>
	using TransformPRS = Transform<T, TrComp::PRS>;

//}
}

#include <SA/Maths/Transform/Transform.inl>

#endif // GUARD
