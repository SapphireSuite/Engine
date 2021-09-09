// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <VertexComp Comps>
	VertexLayoutSpec<Comps>::VertexLayoutSpec() noexcept :
		VertexLayout{ Comps, sizeof(Vertex<Comps>) }
	{
	}


	template <VertexComp Comps>
	Vec3f* VertexLayoutSpec<Comps>::Position(char* _data, uint32 _index) const
	{
		return reinterpret_cast<Vec3f*>(_data + _index * vertexSize);
	}
	
	template <VertexComp Comps>
	Vec3f* VertexLayoutSpec<Comps>::Normal(char* _data, uint32 _index) const
	{
		if constexpr (Comps & VertexComp::Normal)
			return reinterpret_cast<Vec3f*>(_data + _index * vertexSize + Vertex<Comps>::normalOffset);
		else
			return nullptr;
	}
	
	template <VertexComp Comps>
	Vec3f* VertexLayoutSpec<Comps>::Tangent(char* _data, uint32 _index) const
	{
		if constexpr (Comps & VertexComp::Tangent)
			return reinterpret_cast<Vec3f*>(_data + _index * vertexSize + Vertex<Comps>::tangentOffset);
		else
			return nullptr;
	}
	
	template <VertexComp Comps>
	Vec2f* VertexLayoutSpec<Comps>::Texture(char* _data, uint32 _index) const
	{
		if constexpr (Comps & VertexComp::Texture)
			return reinterpret_cast<Vec2f*>(_data + _index * vertexSize + Vertex<Comps>::textureOffset);
		else
			return nullptr;
	}
	
	template <VertexComp Comps>
	Vec3f* VertexLayoutSpec<Comps>::Color(char* _data, uint32 _index) const
	{
		if constexpr (Comps & VertexComp::Color)
			return reinterpret_cast<Vec3f*>(_data + _index * vertexSize + Vertex<Comps>::colorOffset);
		else
			return nullptr;
	}

		
	template <VertexComp Comps>
	uint32 VertexLayoutSpec<Comps>::GetPositionOffet() const noexcept
	{
		return 0u;
	}
	
	template <VertexComp Comps>
	uint32 VertexLayoutSpec<Comps>::GetNormalOffet() const noexcept
	{
		if constexpr (Comps & VertexComp::Normal)
			return Vertex<Comps>::normalOffset;
		else
			return ~uint32();
	}
	
	template <VertexComp Comps>
	uint32 VertexLayoutSpec<Comps>::GetTangentOffet() const noexcept
	{
		if constexpr (Comps & VertexComp::Tangent)
			return Vertex<Comps>::tangentOffset;
		else
			return ~uint32();
	}
	
	template <VertexComp Comps>
	uint32 VertexLayoutSpec<Comps>::GetTextureOffet() const noexcept
	{
		if constexpr (Comps & VertexComp::Texture)
			return Vertex<Comps>::textureOffset;
		else
			return ~uint32();
	}
	
	template <VertexComp Comps>
	uint32 VertexLayoutSpec<Comps>::GetColorOffet() const noexcept
	{
		if constexpr (Comps & VertexComp::Color)
			return Vertex<Comps>::colorOffset;
		else
			return ~uint32();
	}
}
	
