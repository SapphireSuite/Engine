// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VERTEX_GUARD
#define SAPPHIRE_ENGINE_VERTEX_GUARD

#include <cstdint>

#include <SA/Engine/Render/Base/Mesh/Vertex/Components/VertexPosition.hpp>
#include <SA/Engine/Render/Base/Mesh/Vertex/Components/VertexNormal.hpp>
#include <SA/Engine/Render/Base/Mesh/Vertex/Components/VertexTangent.hpp>
#include <SA/Engine/Render/Base/Mesh/Vertex/Components/VertexBitangent.hpp>
#include <SA/Engine/Render/Base/Mesh/Vertex/Components/VertexTexture.hpp>
#include <SA/Engine/Render/Base/Mesh/Vertex/Components/VertexColor.hpp>

namespace SA
{
	template <typename... Args>
	class Vertex : public Args...
	{
		template <typename FindT, typename FirstT, typename... PArgs>
		static uint32_t GetComponentOffsetPacked() noexcept;

	public:
		template <typename T>
		static uint32_t GetComponentOffset() noexcept;
	};

	using VertexPC = Vertex<VertexPosition, VertexColor>;
	using VertexPT = Vertex<VertexPosition, VertexTexture>;
	using VertexPNTT = Vertex<VertexPosition, VertexNormal, VertexTangent, VertexTexture>;
	using VertexPNTBT = Vertex<VertexPosition, VertexNormal, VertexTangent, VertexBitangent, VertexTexture>;
}

#include <SA/Engine/Render/Base/Mesh/Vertex/Vertex.inl>

#endif // GUARD
