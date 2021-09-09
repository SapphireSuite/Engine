// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_BINDING_TYPE_GUARD
#define SAPPHIRE_RENDER_SHADER_BINDING_TYPE_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	enum class ShaderBindingType
	{
		UniformBuffer,

		StorageBuffer,

		ImageSampler2D,

		ImageSamplerCube,

		InputAttachment
	};

#if SA_VULKAN

	namespace Vk
	{
		VkDescriptorType API_GetDescriptorType(ShaderBindingType _type);
	}

#endif
}

#endif // GUARD
