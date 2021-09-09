// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VERTEX_BASE_GUARD
#define SAPPHIRE_RENDER_VERTEX_BASE_GUARD

#include <SA/Maths/Space/Vector2.hpp>
#include <SA/Maths/Space/Vector3.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexComp.hpp>

namespace Sa
{
	namespace Intl
	{
		template <VertexComp Comps>
		struct VertexBase;

		template <>
		struct VertexBase<VertexComp::None>;


		template <>
		struct VertexBase<VertexComp::Position>
		{
			/// Position component of the Vertex.
			Vec3f position;
		};


		template <>
		struct VertexBase<VertexComp::PN>			// Position | Normal
		{
			/// Position component of the Vertex.
			Vec3f position;

			/// Normal component of the Vertex.
			Vec3f normal;

			static constexpr uint32 normalOffset = sizeof(Vec3f);
		};


		template <>
		struct VertexBase<VertexComp::PTex>			// Position | Texture
		{
			/// Position component of the Vertex.
			Vec3f position;

			/// Texture component of the Vertex.
			Vec2f texture;

			static constexpr uint32 textureOffset = sizeof(Vec3f);
		};


		template <>
		struct VertexBase<VertexComp::PC>			// Position | Color
		{
			/// Position component of the Vertex.
			Vec3f position;

			/// Color component of the Vertex.
			Vec3f color;

			static constexpr uint32 colorOffset = sizeof(Vec3f);
		};


		template <>
		struct VertexBase<VertexComp::PNTan>		// Position |Normal | Tangent
		{
			/// Position component of the Vertex.
			Vec3f position;

			/// Normal component of the Vertex.
			Vec3f normal;

			/// Tangent component of the Vertex.
			Vec3f tangent;

			static constexpr uint32 normalOffset = sizeof(Vec3f);
			static constexpr uint32 tangentOffset = 2u * sizeof(Vec3f);
		};


		template <>
		struct VertexBase<VertexComp::PNTex>		// Position | Normal | Texture
		{
			/// Position component of the Vertex.
			Vec3f position;

			/// Normal component of the Vertex.
			Vec3f normal;

			/// Texture component of the Vertex.
			Vec2f texture;

			static constexpr uint32 normalOffset = sizeof(Vec3f);
			static constexpr uint32 textureOffset = 2u * sizeof(Vec3f);
		};


		template <>
		struct VertexBase<VertexComp::PNC>			// Position | Normal | Color
		{
			/// Position component of the Vertex.
			Vec3f position;

			/// Normal component of the Vertex.
			Vec3f normal;

			/// Color component of the Vertex.
			Vec3f color;

			static constexpr uint32 normalOffset = sizeof(Vec3f);
			static constexpr uint32 colorOffset = 2u * sizeof(Vec3f);
		};


		template <>
		struct VertexBase<VertexComp::PNTanTex>		// Position | Normal | Tangent | Texture
		{
			/// Position component of the Vertex.
			Vec3f position;

			/// Normal component of the Vertex.
			Vec3f normal;

			/// Tangent component of the Vertex.
			Vec3f tangent;

			/// Texture component of the Vertex.
			Vec2f texture;

			static constexpr uint32 normalOffset = sizeof(Vec3f);
			static constexpr uint32 tangentOffset = 2u * sizeof(Vec3f);
			static constexpr uint32 textureOffset = 3u * sizeof(Vec3f);
		};


		template <>
		struct VertexBase<VertexComp::PNTanC>		 // Position | Normal | Tangent | Color
		{
			/// Position component of the Vertex.
			Vec3f position;

			/// Normal component of the Vertex.
			Vec3f normal;

			/// Tangent component of the Vertex.
			Vec3f tangent;

			/// Color component of the Vertex.
			Vec3f color;

			static constexpr uint32 normalOffset = sizeof(Vec3f);
			static constexpr uint32 tangentOffset = 2u * sizeof(Vec3f);
			static constexpr uint32 colorOffset = 3u * sizeof(Vec3f);
		};
	}
}

#endif // GUARD
