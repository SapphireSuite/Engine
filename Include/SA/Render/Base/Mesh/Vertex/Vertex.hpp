// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VERTEX_GUARD
#define SAPPHIRE_RENDER_VERTEX_GUARD

#include <SA/Render/Base/Mesh/Vertex/VertexBase.hpp>

namespace Sa
{
	template <VertexComp Comps>
	struct Vertex : public Intl::VertexBase<Comps>
	{
		using Intl::VertexBase<Comps>::VertexBase;
		using Base = Intl::VertexBase<Comps>;

		//template <VertexComp inComps>
		//Vertex(const Vertex<inComps>& _other) noexcept;

		//template <VertexComp inComps>
		//Vertex& operator=(const Vertex<inComps>& _rhs) noexcept;


		//bool operator==(const Vertex& _rhs) const noexcept;
		//bool operator!=(const Vertex& _rhs) const noexcept;
	};
}

#include <SA/Render/Base/Mesh/Vertex/Vertex.inl>

#endif // GUARD
