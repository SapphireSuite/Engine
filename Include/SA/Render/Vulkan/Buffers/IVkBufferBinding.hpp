// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_IVK_BUFFER_BINDING_GUARD
#define SAPPHIRE_RENDER_IVK_BUFFER_BINDING_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class IBufferBinding : public Abstract
	{
	public:
		virtual VkDescriptorBufferInfo CreateDescriptorBufferInfo() const noexcept = 0;
	};
}

#endif

#endif // GUARD
