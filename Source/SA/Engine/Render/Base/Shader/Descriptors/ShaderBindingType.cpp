// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderBindingType.hpp>

#include <SA/Collections/Debug>

namespace SA
{
#if SA_VULKAN

	namespace VK
	{
		VkDescriptorType API_GetDescriptorType(ShaderBindingType _type)
		{
			switch (_type)
			{
				case ShaderBindingType::UniformBuffer:
					return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				case ShaderBindingType::StorageBuffer:
					return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				case ShaderBindingType::ImageSampler2D:
				case ShaderBindingType::ImageSamplerCube:
					return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				case ShaderBindingType::InputAttachment:
					return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
				default:
					SA_LOG("ShaderBindingType [" << _type << L"] not supported yet!", Error, SA/Engine/Render);
					return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			}
		}
	}

#endif
}
