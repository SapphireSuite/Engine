// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VERTEX_LAYOUT_SPEC_GUARD
#define SAPPHIRE_RENDER_VERTEX_LAYOUT_SPEC_GUARD

#include <SA/Render/Base/Mesh/Vertex/Vertex.hpp>
#include <SA/Render/Base/Mesh/Vertex/VertexLayout.hpp>

namespace Sa
{
	template <VertexComp Comps>
	class VertexLayoutSpec : public VertexLayout
	{
	public:
		VertexLayoutSpec() noexcept;

		Vec3f* Position(char* _data, uint32 _index) const override final;
		Vec3f* Normal(char* _data, uint32 _index) const override final;
		Vec3f* Tangent(char* _data, uint32 _index) const override final;
		Vec2f* Texture(char* _data, uint32 _index) const override final;
		Vec3f* Color(char* _data, uint32 _index) const override final;

		uint32 GetPositionOffet() const noexcept override final;
		uint32 GetNormalOffet() const noexcept override final;
		uint32 GetTangentOffet() const noexcept override final;
		uint32 GetTextureOffet() const noexcept override final;
		uint32 GetColorOffet() const noexcept override final;
	};
}

#include <SA/Render/Base/Mesh/Vertex/VertexLayout.inl>
#include <SA/Render/Base/Mesh/Vertex/VertexLayoutSpec.inl>

#endif // GUARD
