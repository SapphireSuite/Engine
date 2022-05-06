// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderBindingType.hpp>

#include <SA/Collections/Debug>

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
					SA_LOG("ShaderBindingType [" << _type << L"] not supported yet!", Error, SA/Engine/Render);
					return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			}
		}
	}

#endif
}
