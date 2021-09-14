// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Shader/VkShader.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void Shader::Create(const Device& _device, const RawShader& _rawShader)
	{
		VkShaderModuleCreateInfo shaderModuleCreateInfo{};
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.pNext = nullptr;
		shaderModuleCreateInfo.flags = 0u;
		shaderModuleCreateInfo.codeSize = OctSizeOf(_rawShader.data);
		shaderModuleCreateInfo.pCode = _rawShader.data.data();

		SA_VK_ASSERT(vkCreateShaderModule(_device, &shaderModuleCreateInfo, nullptr, &mHandle), L"Failed to create shader module!");
	}

	void Shader::Destroy(const Device& _device)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, mHandle, L"Destroy a null Shader!");

		vkDestroyShaderModule(_device, mHandle, nullptr);

		mHandle = VK_NULL_HANDLE;
	}


	Shader::operator VkShaderModule() const
	{
		return mHandle;
	}
}

#endif
