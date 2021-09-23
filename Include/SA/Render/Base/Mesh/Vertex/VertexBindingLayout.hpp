// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VERTEX_BINDING_LAYOUT_GUARD
#define SAPPHIRE_RENDER_VERTEX_BINDING_LAYOUT_GUARD

#include <SA/Render/Base/Mesh/Vertex/VertexLayout.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	struct VertexBindingLayout
	{
		std::shared_ptr<const VertexLayout> desiredLayout = nullptr;
		std::shared_ptr<const VertexLayout> meshLayout = nullptr;


#if SA_VULKAN

		uint32 GetBindingDescriptionNum() const;

		uint32 GetAttributeDescriptionNum() const;

		std::unique_ptr<VkVertexInputBindingDescription> GetBindingDescription() const noexcept;

		std::unique_ptr<VkVertexInputAttributeDescription[]> GetAttributeDescriptions() const noexcept;

#endif
	};
}

#endif // GUARD
