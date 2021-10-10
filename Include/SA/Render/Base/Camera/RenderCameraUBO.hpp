// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_CAMERA_UBO_GUARD
#define SAPPHIRE_RENDER_CAMERA_UBO_GUARD

#include <SA/Maths/Matrix/Matrix4.hpp>
#include <SA/Maths/Space/Vector3.hpp>

namespace Sa
{
	struct RenderCameraUBO
	{
		CMat4f proj = Mat4f::Identity;
		CMat4f viewInv = Mat4f::Identity;
		Vec3f viewPosition;
	};
}

#endif // GUARD
