// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VERTEX_GUARD
#define SAPPHIRE_ENGINE_VERTEX_GUARD

#include <cstdint>

namespace SA
{
	template <typename... VertexComps>
	class Vertex : public VertexComps...
	{
	// public:
	// 	static constexpr uint32_t size = sizeof(Vertex);
	// 	static constexpr uint32_t attributeNum = sizeof...(VertexComps);
	};
}

#endif // GUARD
