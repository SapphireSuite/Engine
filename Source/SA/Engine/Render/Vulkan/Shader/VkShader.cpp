// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Shader/VkShader.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace SA::VK
{
	void Shader::Create(const Device& _device, ResourceInitializer& _init, const RawShader& _raw)
	{
		AShader::Create();

		(void)_init;

		VkShaderModuleCreateInfo shaderModuleCreateInfo{};
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.pNext = nullptr;
		shaderModuleCreateInfo.flags = 0u;
		shaderModuleCreateInfo.codeSize = _raw.data.size() * sizeof(uint32_t);
		shaderModuleCreateInfo.pCode = _raw.data.data();

		SA_VK_ASSERT(vkCreateShaderModule(_device, &shaderModuleCreateInfo, nullptr, &mHandle), L"Failed to create shader module!");
		
		SA_LOG(L"Shader [" << mHandle << L"] created.", Infos, SA/EngineRender/Vulkan);
	}

	void Shader::Destroy(const Device& _device)
	{
		AShader::Destroy();

		vkDestroyShaderModule(_device, mHandle, nullptr);

		SA_LOG(L"Shader [" << mHandle << L"] destroyed.", Infos, SA/EngineRender/Vulkan);
		
		mHandle = VK_NULL_HANDLE;
	}


	Shader::operator VkShaderModule() const
	{
		return mHandle;
	}
}
