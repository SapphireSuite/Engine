// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Shader/VkShader.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Base/Shader/RawShader.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/VkResourceInitializer.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
	void Shader::Create(const Device& _device, ResourceInitializer& _init, const RawShader& _raw)
	{
		(void)_init;

		VkShaderModuleCreateInfo shaderModuleCreateInfo{};
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.pNext = nullptr;
		shaderModuleCreateInfo.flags = 0u;
		shaderModuleCreateInfo.codeSize = OctSizeOf(_raw.data);
		shaderModuleCreateInfo.pCode = _raw.data.data();

		SA_VK_ASSERT(vkCreateShaderModule(_device, &shaderModuleCreateInfo, nullptr, &mHandle), L"Failed to create shader module!");
		
		SA_LOG(L"Shader created.", Infos, SA/Render/Vulkan);
	}

	void Shader::Destroy(const Device& _device)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, mHandle, L"Destroy a null Shader!");

		vkDestroyShaderModule(_device, mHandle, nullptr);

		mHandle = VK_NULL_HANDLE;
		
		SA_LOG(L"Shader destroyed.", Infos, SA/Render/Vulkan);
	}


	Shader::operator VkShaderModule() const
	{
		return mHandle;
	}
}
