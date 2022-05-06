// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_BINDING_TYPE_GUARD
#define SAPPHIRE_ENGINE_SHADER_BINDING_TYPE_GUARD

#include <cstdint>

#include <SA/Support/API/Vulkan.hpp>

namespace Sa
{
	enum class ShaderBindingType : uint8_t
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
