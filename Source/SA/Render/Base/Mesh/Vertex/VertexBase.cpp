// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Mesh/Vertex/VertexBase.hpp>

namespace Sa::Intl
{
	VertexBase<VertexComp::Position>::VertexBase(const Vec3f& _pos) noexcept : position{ _pos }
	{
	}


	VertexBase<VertexComp::PN>::VertexBase(const Vec3f& _pos, const Vec3f& _normal) noexcept :
		position{ _pos },
		normal{ _normal }
	{
	}


	VertexBase<VertexComp::PTex>::VertexBase(const Vec3f& _pos, const Vec2f& _texture) noexcept :
		position{ _pos },
		texture{ _texture }
	{
	}


	VertexBase<VertexComp::PC>::VertexBase(const Vec3f& _pos, const Vec3f& _color) noexcept :
		position{ _pos },
		color{ _color }
	{
	}


	VertexBase<VertexComp::PNTan>::VertexBase(const Vec3f& _pos, const Vec3f& _normal, const Vec3f& _tangent) noexcept :
		position{ _pos },
		normal{ _normal },
		tangent{ _tangent }
	{
	}


	VertexBase<VertexComp::PNTex>::VertexBase(const Vec3f& _pos, const Vec3f& _normal, const Vec2f& _texture) noexcept :
		position{ _pos },
		normal{ _normal },
		texture{ _texture }
	{
	}


	VertexBase<VertexComp::PNC>::VertexBase(const Vec3f& _pos, const Vec3f& _normal, const Vec3f& _color) noexcept :
		position{ _pos },
		normal{ _normal },
		color{ _color }
	{
	}


	VertexBase<VertexComp::PNTanTex>::VertexBase(const Vec3f& _pos, const Vec3f& _normal, const Vec3f& _tangent, const Vec2f& _texture) noexcept :
		position{ _pos },
		normal{ _normal },
		tangent{ _tangent },
		texture{ _texture }
	{
	}


	VertexBase<VertexComp::PNTanC>::VertexBase(const Vec3f& _pos, const Vec3f& _normal, const Vec3f& _tangent, const Vec3f& _color) noexcept :
		position{ _pos },
		normal{ _normal },
		tangent{ _tangent },
		color{ _color }
	{
	}
}
