// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Camera/ACamera.hpp>

namespace Sa
{
	const CMat4f& ACamera::GetProjection() const noexcept
	{
		return mUBOData.proj;
	}

	void ACamera::SetProjection(const CMat4f& _proj) noexcept
	{
		bProjDirty = true;
		mUBOData.proj = _proj;
	}


	void ACamera::SetTransform(const TransffPR& _tr)
	{
		bTransformDirty = true;

		mUBOData.viewInv = _tr.Matrix().GetInversed();
		mUBOData.viewPosition = _tr.position;
	}
}
