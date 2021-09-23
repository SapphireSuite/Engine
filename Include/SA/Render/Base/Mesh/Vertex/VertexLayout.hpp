// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VERTEX_LAYOUT_GUARD
#define SAPPHIRE_RENDER_VERTEX_LAYOUT_GUARD

#include <memory>

#include <SA/Maths/Space/Vector2.hpp>
#include <SA/Maths/Space/Vector3.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexComp.hpp>

namespace Sa
{
	class VertexLayout
	{
	protected:
		VertexLayout(VertexComp _comps, uint32 _vertexSize) noexcept;

	public:
		const VertexComp comps = VertexComp::None;

		const uint32 vertexSize = 0u;


		virtual ~VertexLayout() = default;


		virtual Vec3f* Position(char* _data, uint32 _index = 0u) const = 0;
		virtual Vec3f* Normal(char* _data, uint32 _index = 0u) const = 0;
		virtual Vec3f* Tangent(char* _data, uint32 _index = 0u) const = 0;
		virtual Vec2f* Texture(char* _data, uint32 _index = 0u) const = 0;
		virtual Vec3f* Color(char* _data, uint32 _index = 0u) const = 0;

		virtual uint32 GetPositionOffet() const noexcept = 0;
		virtual uint32 GetNormalOffet() const noexcept = 0;
		virtual uint32 GetTangentOffet() const noexcept = 0;
		virtual uint32 GetTextureOffet() const noexcept = 0;
		virtual uint32 GetColorOffet() const noexcept = 0;

		template <VertexComp Comps>
		static std::shared_ptr<VertexLayout> Make() noexcept;
		static std::shared_ptr<VertexLayout> Make(VertexComp _comps) noexcept;
	};
}

// Included in VertexLayoutSpec.hpp to allow Make<> compilation.
//#include <SA/Render/Base/Mesh/Vertex/VertexLayout.inl>

#endif // GUARD
