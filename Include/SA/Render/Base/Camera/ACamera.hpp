// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ACAMERA_GUARD
#define SAPPHIRE_RENDER_ACAMERA_GUARD

#include <SA/Maths/Transform/Transform.hpp>
#include <SA/Render/Base/Camera/CameraUBO.hpp>

namespace Sa
{
	class ACamera
	{
	protected:
		CameraUBO mUBOData;

		bool bProjDirty = false;
		bool bTransformDirty = false;

	public:
		const CMat4f& GetProjection() const noexcept;
		void SetProjection(const CMat4f& _proj) noexcept;

		void SetTransform(const TransffPR& _tr);
	};
}

#endif // GUARD
