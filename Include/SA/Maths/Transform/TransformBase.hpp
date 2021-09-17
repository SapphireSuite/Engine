// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_TRANSFORM_BASE_GUARD
#define SAPPHIRE_MATHS_TRANSFORM_BASE_GUARD

#include <SA/Maths/Space/Vector3.hpp>
#include <SA/Maths/Space/Quaternion.hpp>

#include <SA/Maths/Transform/TransformComp.hpp>

namespace Sa::Intl
{
	template <typename T, TrComp Comps, bool b>
	struct TransfBaseComp;


	template <typename T, TrComp Comps>
	struct TransfBaseComp<T, Comps, false>
	{
	};


//{ Position

	template <typename T>
	struct TransfBaseComp<T, TrComp::Position, true>
	{
		Vec3<T> position;
	};

//}


//{ Rotation

	template <typename T>
	struct TransfBaseComp<T, TrComp::Rotation, true>
	{
		Quat<T> rotation = Quat<T>::Identity;
	};

//}


//{ UScale

	template <typename T>
	struct TransfBaseComp<T, TrComp::UScale, true>
	{
		T uScale = T(1);
	};

//}


//{ Scale

	template <typename T>
	struct TransfBaseComp<T, TrComp::Scale, true>
	{
		Vec3<T> scale = Vec3<T>::One;
	};

//}


	template <typename T, TrComp Comps, TrComp Flag>
	using TransfBaseFlagT = TransfBaseComp<T, Flag, bool(Comps & Flag)>;

	template <typename T, TrComp Comps>
	struct TransfBaseT :
		public TransfBaseFlagT<T, Comps, TrComp::Position>,
		public TransfBaseFlagT<T, Comps, TrComp::Rotation>,
		public TransfBaseFlagT<T, Comps, TrComp::Scale>,
		public TransfBaseFlagT<T, Comps, TrComp::UScale>
	{
	};
}

#endif // GUARD
