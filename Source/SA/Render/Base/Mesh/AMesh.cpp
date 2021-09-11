// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Mesh/AMesh.hpp>

namespace Sa
{
	std::shared_ptr<VertexLayout> AMesh::GetLayout() const noexcept
	{
		return mLayout;
	}

	void AMesh::Create(const RawMesh& _rawMesh)
	{
		mLayout = _rawMesh.GetLayout();
	}
}
