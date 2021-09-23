// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	//template <VertexComp Comps>
	//template <VertexComp inComps>
	//Vertex<Comps>::Vertex(const Vertex<inComps>& _other) noexcept
	//{
	//	if constexpr (Comps & inComps & VertexComp::Position)
	//		Base::position = _other.position;

	//	if constexpr (Comps & inComps & VertexComp::Normal)
	//		Base::normal = _other.normal;

	//	if constexpr (Comps & inComps & VertexComp::Tangent)
	//		Base::tangent = _other.tangent;

	//	if constexpr (Comps & inComps & VertexComp::Texture)
	//		Base::texture = _other.texture;

	//	if constexpr (Comps & inComps & VertexComp::Color)
	//		Base::color = _other.color;
	//}

	//template <VertexComp Comps>
	//template <VertexComp inComps>
	//Vertex<Comps>& Vertex<Comps>::operator=(const Vertex<inComps>& _rhs) noexcept
	//{
	//	if constexpr (Comps & inComps & VertexComp::Position)
	//		Base::position = _other.position;

	//	if constexpr (Comps & inComps & VertexComp::Normal)
	//		Base::normal = _other.normal;

	//	if constexpr (Comps & inComps & VertexComp::Tangent)
	//		Base::tangent = _other.tangent;

	//	if constexpr (Comps & inComps & VertexComp::Texture)
	//		Base::texture = _other.texture;

	//	if constexpr (Comps & inComps & VertexComp::Color)
	//		Base::color = _other.color;
	//}


	//template <VertexComp Comps>
	//bool Vertex<Comps>::operator==(const Vertex& _rhs) const noexcept
	//{
	//	if constexpr (Comps & inComps & VertexComp::Position)
	//	{
	//		if (Base::position != _other.position)
	//			return false;
	//	}

	//	if constexpr (Comps & inComps & VertexComp::Normal)
	//	{
	//		if (Base::normal != _other.normal)
	//			return false;
	//	}

	//	if constexpr (Comps & inComps & VertexComp::Tangent)
	//	{
	//		if (Base::tangent != _other.tangent)
	//			return false;
	//	}

	//	if constexpr (Comps & inComps & VertexComp::Texture)
	//	{
	//		if (Base::texture != _other.texture)
	//			return false;
	//	}

	//	if constexpr (Comps & inComps & VertexComp::Color)
	//	{
	//		if (Base::color != _other.color)
	//			return false;
	//	}
	//}

	//template <VertexComp Comps>
	//bool Vertex<Comps>::operator!=(const Vertex& _rhs) const noexcept
	//{
	//	return !(*this == _rhs);
	//}
}
