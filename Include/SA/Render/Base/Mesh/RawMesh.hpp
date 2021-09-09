// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RAW_MESH_GUARD
#define SAPPHIRE_RENDER_RAW_MESH_GUARD

#include <vector>

#include <SA/Core/Algorithms/SizeOf.hpp>
#include <SA/Core/Algorithms/MemMove.hpp>
#include <SA/Core/Algorithms/Equals.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexLayoutSpec.hpp>

namespace Sa
{
	class RawMesh
	{
		std::shared_ptr<VertexLayout> mLayout = VertexLayout::Make<VertexComp::Default>();

	public:
		std::vector<char> vertices;
		std::vector<uint32> indices;

		std::shared_ptr<VertexLayout> GetLayout() const noexcept;
		void SetLayout(VertexComp _comps);
		template <VertexComp inComps>
		void SetLayout();

		void ComputeTangents();

		template <VertexComp Comps = VertexComp::Default>
		static RawMesh Triangle() noexcept;
		template <VertexComp Comps = VertexComp::Default>
		static RawMesh Square() noexcept;
		template <VertexComp Comps = VertexComp::Default>
		static RawMesh Cube() noexcept;
	};
}

#include <SA/Render/Base/Mesh/RawMesh.inl>

#endif // GUARD
