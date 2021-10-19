// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SHADER_GUARD
#define SAPPHIRE_RENDER_VK_SHADER_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Render/Base/Shader/AShader.hpp>

namespace Sa::Vk
{
	class Device;
	class ResourceInitializer;

	class Shader : public AShader
	{
		VkShaderModule mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawShader& _raw);
		void Destroy(const Device& _device);

		operator VkShaderModule() const;
	};
}

#endif // GUARD
