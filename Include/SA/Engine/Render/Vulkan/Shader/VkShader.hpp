// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_SHADER_GUARD
#define SAPPHIRE_ENGINE_VK_SHADER_GUARD

#include <SA/Engine/Render/Base/Shader/AShader.hpp>

#include <SA/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class Device;
	class ResourceInitializer;

    class Shader : public AShader
    {
		VkShaderModule mHandle = VK_NULL_HANDLE;

        using AShader::Create; // overloaded.
        using AShader::Destroy; // overloaded.

    public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawShader& _raw);
		void Destroy(const Device& _device);

		operator VkShaderModule() const;
    };
}

#endif // GUARD
