// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/ShaderBindingType.hpp>

#include <Collections/Debug>

namespace Sa
{
#if SA_VULKAN

	namespace Vk
	{
		VkDescriptorType API_GetDescriptorType(ShaderBindingType _type)
		{
			switch (_type)
			{
				case Sa::ShaderBindingType::UniformBuffer:
					return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				case Sa::ShaderBindingType::StorageBuffer:
					return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				case Sa::ShaderBindingType::ImageSampler2D:
				case Sa::ShaderBindingType::ImageSamplerCube:
					return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				case Sa::ShaderBindingType::InputAttachment:
					return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
				default:
					SA_LOG("ShaderBindingType [" << _type << L"] not supported yet!", Error, SA/Render/Vulkan);
					return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			}
		}
	}

#endif
}
