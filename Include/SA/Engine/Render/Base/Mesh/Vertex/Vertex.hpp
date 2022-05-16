// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VERTEX_GUARD
#define SAPPHIRE_ENGINE_VERTEX_GUARD

#include <cstdint>

namespace SA
{
	template <typename... Args>
	class Vertex : public Args...
	{
		template <typename FindT, typename FirstT, typename... PArgs>
		static uint32_t GetComponentOffsetPacked() noexcept;

	public:
		template <tpename T>
		static uint32_t GetComponentOffset() noexcept;
	};
}

#include <SA/Engine/Render/Base/Mesh/Vertex/Vertex.inl>

#endif // GUARD
