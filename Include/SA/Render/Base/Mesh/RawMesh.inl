// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <VertexComp inComps>
	void RawMesh::SetLayout()
	{
		// No conversion to perform.
		if (mLayout->comps == VertexComp::None || mLayout->comps == inComps || vertices.empty())
		{
			mLayout = VertexLayout::Make<inComps>();
			return;
		}

		// TODO: Implement layout conversion.
		SA_ASSERT(Default, SA/Render, false, L"Method not implemented yet!");

		mLayout = VertexLayout::Make<inComps>();
	}
}
