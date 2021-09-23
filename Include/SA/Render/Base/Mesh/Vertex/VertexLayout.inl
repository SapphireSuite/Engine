// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <VertexComp Comps>
	std::shared_ptr<VertexLayout> VertexLayout::Make() noexcept
	{
		return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<Comps>);
	}
}
