// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDER_BUFFER_TYPE_GUARD
#define SAPPHIRE_RENDER_RENDER_BUFFER_TYPE_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	enum class RenderBufferType
	{
		Uniform,
		Storage,

		Vertex,
		Index,

		TransferSRC,
		TransferDST
	};

#if SA_VULKAN

	namespace Vk
	{
		VkBufferUsageFlagBits API_GetBufferUsage(RenderBufferType _type);
	}

#endif
}

#endif // GUARD
