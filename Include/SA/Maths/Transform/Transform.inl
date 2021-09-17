// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
//{ Equals

	template <typename T, TrComp Comps>
	constexpr bool Transf<T, Comps>::IsZero() const noexcept
	{
		if constexpr (Comps & TrComp::Position)
		{
			if (!position.IsZero())
				return false;
		}

		if constexpr (Comps & TrComp::Rotation)
		{
			if (!rotation.IsZero())
				return false;
		}

		if constexpr (Comps & TrComp::Scale)
		{
			if (!scale.IsZero())
				return false;
		}

		if constexpr (Comps & TrComp::UScale)
		{
			if (uScale != T())
				return false;
		}

		return true;
	}

	template <typename T, TrComp Comps>
	constexpr bool Transf<T, Comps>::IsIdentity() const noexcept
	{
		if constexpr (Comps & TrComp::Position)
		{
			if (!position.IsZero())
				return false;
		}

		if constexpr (Comps & TrComp::Rotation)
		{
			if (!rotation.IsIdentity())
				return false;
		}

		if constexpr (Comps & TrComp::Scale)
		{
			if (scale != Vec3<T>::One)
				return false;
		}

		if constexpr (Comps & TrComp::UScale)
		{
			if (uScale != T(1))
				return false;
		}

		return true;
	}

	template <typename T, TrComp Comps>
	constexpr bool Transf<T, Comps>::Equals(const Transf& _other, T _epsilon) const noexcept
	{
		if constexpr (Comps & TrComp::Position)
		{
			if (position.Equals(_other.position, _epsilon))
				return false;
		}

		if constexpr (Comps & TrComp::Rotation)
		{
			if (rotation.Equals(_other.rotation, _epsilon))
				return false;
		}

		if constexpr (Comps & TrComp::Scale)
		{
			if (scale.Equals(_other.scale, _epsilon))
				return false;
		}

		if constexpr (Comps & TrComp::UScale)
		{
			if (uScale.Equals(_other.uScale, _epsilon))
				return false;
		}

		return true;
	}


	template <typename T, TrComp Comps>
	constexpr bool Transf<T, Comps>::operator==(const Transf& _rhs) noexcept
	{
		return Equals(_rhs);
	}

	template <typename T, TrComp Comps>
	constexpr bool Transf<T, Comps>::operator!=(const Transf& _rhs) noexcept
	{
		return !(*this == _rhs);
	}

//}


//{ Transformation

	template <typename T, TrComp Comps>
	Vec3<T> Transf<T, Comps>::Right() const
	{
		if constexpr (Comps & TrComp::Rotation)
			return rotation.RightVector();
		else
			return Vec3<T>::Right;
	}

	template <typename T, TrComp Comps>
	Vec3<T> Transf<T, Comps>::Up() const
	{
		if constexpr (Comps & TrComp::Rotation)
			return rotation.UpVector();
		else
			return Vec3<T>::Up;
	}

	template <typename T, TrComp Comps>
	Vec3<T> Transf<T, Comps>::Forward() const
	{
		if constexpr (Comps & TrComp::Rotation)
			return rotation.ForwardVector();
		else
			return Vec3<T>::Forward;
	}

	template <typename T, TrComp Comps>
	Mat4<T> Transf<T, Comps>::Matrix() const
	{
		if constexpr (Comps == TrComp::PRUS)
			return Mat4<T>::MakeTransform(position, rotation, Vec3<T>(uScale));
		else if constexpr (Comps == TrComp::PRS)
			return Mat4<T>::MakeTransform(position, rotation, scale);
		else if constexpr (Comps == TrComp::PR)
			return Mat4<T>::MakeTransform(position, rotation);
		else if constexpr (Comps == TrComp::PS)
			return Mat4<T>::MakeTransform(position, scale);
		else if constexpr (Comps == TrComp::PUS)
			return Mat4<T>::MakeTransform(position, Vec3<T>(uScale));
		else if constexpr (Comps == TrComp::RS)
			return Mat4<T>::MakeTransform(rotation, scale);
		else if constexpr (Comps == TrComp::RUS)
			return Mat4<T>::MakeTransform(rotation, Vec3<T>(uScale));
		else
			return Mat4<T>::Identity;
	}

//}


//{ Lerp

	template <typename T, TrComp Comps>
	Transf<T, Comps> Transf<T, Comps>::Lerp(const Transf& _start, const Transf& _end, float _alpha) noexcept
	{
		Transf res;

		if constexpr (Comps & TrComp::Position)
			res.position = Vec3<T>::Lerp(_start.position, _end.position, _alpha);

		if constexpr (Comps & TrComp::Rotation)
			res.rotation = Quat<T>::SLerp(_start.rotation, _end.rotation, _alpha);

		if constexpr (Comps & TrComp::Scale)
			res.scale = Vec3<T>::Lerp(_start.scale, _end.scale, _alpha);

		if constexpr (Comps & TrComp::UScale)
			res.uScale = Maths::Lerp(_start.uScale, _end.uScale, _alpha);

		return res;
	}

	template <typename T, TrComp Comps>
	Transf<T, Comps> Transf<T, Comps>::LerpUnclamped(const Transf& _start, const Transf& _end, float _alpha) noexcept
	{
		Transf res;

		if constexpr (Comps & TrComp::Position)
			res.position = Vec3<T>::LerpUnclamped(_start.position, _end.position, _alpha);

		if constexpr (Comps & TrComp::Rotation)
			res.rotation = Quat<T>::SLerpUnclamped(_start.rotation, _end.rotation, _alpha);

		if constexpr (Comps & TrComp::Scale)
			res.scale = Vec3<T>::LerpUnclamped(_start.scale, _end.scale, _alpha);

		if constexpr (Comps & TrComp::UScale)
			res.uScale = Maths::LerpUnclamped(_start.uScale, _end.uScale, _alpha);

		return res;
	}

//}


//{ Operators

	template <typename T, TrComp Comps>
	template <TrComp CIn>
	Transf<T, Comps> Transf<T, Comps>::operator*(const Transf<T, CIn>& _other) const
	{
		/**
		*	Transf(
		*		position + rotation.Rotate(_other.position),
		*		rotation * _other.rotation,
		*		scale * _other.scale);
		*/

		Transf res = *this;

		if constexpr (Comps & TrComp::Rotation)
		{
			if constexpr (Comps & CIn & TrComp::Position)
				res.position += rotation.Rotate(_other.position);

			if constexpr (CIn & TrComp::Rotaion)
				res.rotation *= _other.rotation;
		}

		if constexpr (Comps & CIn & TrComp::UScale)
				res.uScale *= _other.uScale;

		if constexpr (Comps & TrComp::Scale)
		{
			if constexpr (CIn & TrComp::Scale)
				res.scale *= _other.scale;
			else if constexpr (CIn & TrComp::UScale && (Comps & TrComp::UScale) == 0)
				res.scale *= Vec3<T>{ _other.uScale };
		}

		return res;
	}


	template <typename T, TrComp Comps>
	template <TrComp CIn>
	Transf<T, Comps> Transf<T, Comps>::operator/(const Transf<T, CIn>& _other) const
	{
		/**
		*	return Transf(
		*		position - rotation.Rotate(_other.position),
		*		rotation / _other.rotation,
		*		scale / _other.scale
		*	);
		*/

		Transf res = *this;

		if constexpr (Comps & TrComp::Rotation)
		{
			if constexpr (Comps & CIn & TrComp::Position)
				res.position -= rotation.Rotate(_other.position);

			if constexpr (CIn & TrComp::Rotaion)
				res.rotation /= _other.rotation;
		}

		if constexpr (Comps & CIn & TrComp::UScale)
			res.uScale /= _other.uScale;

		if constexpr (Comps & TrComp::Scale)
		{
			if constexpr (CIn & TrComp::Scale)
				res.scale /= _other.scale;
			else if constexpr (CIn & TrComp::UScale && (Comps & TrComp::UScale) == 0)
				res.scale /= Vec3<T>{ _other.uScale };
		}

		return res;
	}


	template <typename T, TrComp Comps>
	template <TrComp CIn>
	Transf<T, Comps>& Transf<T, Comps>::operator*=(const Transf<T, CIn>& _other)
	{
		*this = *this * _other;

		return *this;
	}


	template <typename T, TrComp Comps>
	template <TrComp CIn>
	Transf<T, Comps>& Transf<T, Comps>::operator/=(const Transf<T, CIn>& _other)
	{
		*this = *this / _other;

		return *this;
	}


	template <typename T, TrComp Comps>
	template <typename TIn, TrComp CIn>
	constexpr Transf<T, Comps>::operator Transf<TIn, CIn>() const noexcept
	{
		Transf<TIn, CIn> res;

		if constexpr (Comps & CIn & TrComp::Position)
			res.position = position;

		if constexpr (Comps & CIn & TrComp::Rotation)
			res.rotation = rotation;

		if constexpr (Comps & CIn & TrComp::Scale)
			res.scale = scale;

		if constexpr (Comps & CIn & TrComp::UScale)
			res.uScale = uScale;

		return res;
	}

//}


#if SA_LOGGING

	template <typename T, TrComp Comps>
	std::string Transf<T, Comps>::ToString() const noexcept
	{
		std::string res;

		if constexpr (Comps & TrComp::Position)
			res += "Pos: " + position.ToString() + "\n\t";

		if constexpr (Comps & TrComp::Rotation)
			res += "Rot: " + rotation.ToString() + "\n\t";

		if constexpr (Comps & TrComp::Scale)
			res += "Scale: " + scale.ToString() + "\n\t";

		if constexpr (Comps & TrComp::UScale)
			res += "UScale: " + Sa::ToString(uScale);

		return res;
	}

#endif
}
