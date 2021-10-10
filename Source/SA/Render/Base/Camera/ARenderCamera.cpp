// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Camera/ARenderCamera.hpp>

namespace Sa
{
	const CMat4f& ARenderCamera::GetProjection() const noexcept
	{
		return mUBOData.proj;
	}

	void ARenderCamera::SetProjection(const CMat4f& _proj) noexcept
	{
		bProjDirty = true;
		mUBOData.proj = _proj;
	}


	void ARenderCamera::SetTransform(const TransffPR& _tr)
	{
		bTransformDirty = true;

		mUBOData.viewInv = _tr.Matrix().GetInversed();
		mUBOData.viewPosition = _tr.position;
	}
}
