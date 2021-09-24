// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Shader/VkShader.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/VkResourceContext.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void Shader::Create(const ARenderResourceContext* _context, const RawShader& _raw)
	{
		const Device& vkDevice = *_context->As<ResourceContext>().device;

		VkShaderModuleCreateInfo shaderModuleCreateInfo{};
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.pNext = nullptr;
		shaderModuleCreateInfo.flags = 0u;
		shaderModuleCreateInfo.codeSize = OctSizeOf(_raw.data);
		shaderModuleCreateInfo.pCode = _raw.data.data();

		SA_VK_ASSERT(vkCreateShaderModule(vkDevice, &shaderModuleCreateInfo, nullptr, &mHandle), L"Failed to create shader module!");
	}

	void Shader::Destroy(const ARenderDevice* _device)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, mHandle, L"Destroy a null Shader!");
		
		const Device& vkDevice = _device->As<Device>();

		vkDestroyShaderModule(vkDevice, mHandle, nullptr);

		mHandle = VK_NULL_HANDLE;
	}


	Shader::operator VkShaderModule() const
	{
		return mHandle;
	}
}

#endif
