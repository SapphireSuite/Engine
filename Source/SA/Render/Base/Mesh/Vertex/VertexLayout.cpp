// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Mesh/Vertex/VertexLayout.hpp>

#include <Collections/Debug>

#include <Render/Base/Mesh/Vertex/VertexLayoutSpec.hpp>

namespace Sa
{
	VertexLayout::VertexLayout(VertexComp _comps, uint32 _vertexSize) noexcept :
		comps{ _comps },
		vertexSize{ _vertexSize }
	{
	}

	std::shared_ptr<VertexLayout> VertexLayout::Make(VertexComp _comps) noexcept
	{
		switch (_comps)
		{
			case Sa::VertexComp::Position:
				return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<VertexComp::Position>);
			case Sa::VertexComp::PN:
				return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<VertexComp::PN>);
			case Sa::VertexComp::PTex:
				return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<VertexComp::PTex>);
			case Sa::VertexComp::PC:
				return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<VertexComp::PC>);
			case Sa::VertexComp::PNTan:
				return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<VertexComp::PNTan>);
			case Sa::VertexComp::PNTex:
				return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<VertexComp::PNTex>);
			case Sa::VertexComp::PNC:
				return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<VertexComp::PNC>);
			case Sa::VertexComp::PNTanTex:
				return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<VertexComp::PNTanTex>);
			case Sa::VertexComp::PNTanC:
				return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<VertexComp::PNTanC>);
			default:
				SA_LOG(L"Vertex Layout with components [" << _comps << "L] is not supported yet!", Error, SA/Render);
				return std::shared_ptr<VertexLayout>(new VertexLayoutSpec<VertexComp::Position>);
		}
	}
}
