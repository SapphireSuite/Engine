// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/ShaderStage.hpp>

#include <Collections/Debug>

namespace Sa
{
#if SA_VULKAN

	VkShaderStageFlagBits API_GetShaderStage(ShaderStage _stage) noexcept
	{
		switch (_stage)
		{
			case Sa::ShaderStage::Vertex:
				return VK_SHADER_STAGE_VERTEX_BIT;
			case Sa::ShaderStage::Fragment:
				return VK_SHADER_STAGE_FRAGMENT_BIT;
			case Sa::ShaderStage::Geometry:
				return VK_SHADER_STAGE_GEOMETRY_BIT;
			case Sa::ShaderStage::Compute:
				return VK_SHADER_STAGE_COMPUTE_BIT;
			case Sa::ShaderStage::Unknown:
			default:
				SA_LOG("Vulkan API GetShaderStage [" << _stage << L"] default or unknown used!", Error, SA/Render);
				return VkShaderStageFlagBits(0);
		}
	}

	VkShaderStageFlags API_GetShaderStageFlags(ShaderStage _type) noexcept
	{
		VkShaderStageFlags result = 0;

		if (_type & ShaderStage::Vertex)
			result |= VK_SHADER_STAGE_VERTEX_BIT;

		if (_type & ShaderStage::Fragment)
			result |= VK_SHADER_STAGE_FRAGMENT_BIT;

		if (_type & ShaderStage::Geometry)
			result |= VK_SHADER_STAGE_GEOMETRY_BIT;

		if (_type & ShaderStage::Compute)
			result |= VK_SHADER_STAGE_COMPUTE_BIT;

		return result;
	}

#endif
}
