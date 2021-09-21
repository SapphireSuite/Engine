// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Mesh/RawMesh.hpp>

namespace Sa
{
	std::shared_ptr<VertexLayout> RawMesh::GetLayout() const noexcept
	{
		return mLayout;
	}

	void RawMesh::SetLayout(VertexComp _comps)
	{
		// No conversion to perform.
		if (mLayout->comps == VertexComp::None || mLayout->comps == _comps || vertices.empty())
		{
			mLayout = VertexLayout::Make(_comps);
			return;
		}

		// TODO: Implement layout conversion.
		SA_ASSERT(Default, SA/Render, false, L"Method not implemented yet!");

		mLayout = VertexLayout::Make(_comps);
	}


	void RawMesh::Reset()
	{
		vertices.clear();
		indices.clear();
	}
}