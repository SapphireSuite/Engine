// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Mesh/AMesh.hpp>

namespace Sa
{
	std::shared_ptr<VertexLayout> AMesh::GetLayout() const noexcept
	{
		return mLayout;
	}
}
