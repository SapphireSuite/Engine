// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RAW_MESH_GUARD
#define SAPPHIRE_RENDER_RAW_MESH_GUARD

#include <SA/Core/Serialize/Serializer.hpp>

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


		void Reset();
	};


	namespace Serialize
	{
		void ToBinary(const RawMesh& _obj, std::string& _str);
		void FromBinary(RawMesh& _obj, Reader& _read);
	}
}

#include <SA/Render/Base/Mesh/RawMesh.inl>

#endif // GUARD
