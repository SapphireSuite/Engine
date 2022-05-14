// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderStage.hpp>

#include <SA/Collections/Debug>

namespace SA
{
	ShaderStage ShaderStageFromFile(const std::string& _path)
	{
		const size_t extIndex = _path.find_last_of('.');
		SA_ASSERT(Default, SA/Engine/Render, extIndex != std::string::npos,
			L"Invalid shader stage name {"_L << _path << L"}");

		const std::string extension = _path.substr(extIndex + 1);

		if (extension == "vert")
			return ShaderStage::Vertex;
		else if (extension == "frag")
			return ShaderStage::Fragment;
		else if (extension == "comp")
			return ShaderStage::Compute;
		else if (extension == "geom")
			return ShaderStage::Geometry;
		//else if (extension == "tesc")
		//	return shaderc_glsl_tess_control_shader;
		//else if (extension == "tese")
		//	return shaderc_glsl_tess_evaluation_shader;
		else
		{
			SA_LOG(L"Invalid shader extension {" << extension << L"}", Error, SA/Engine/Render);
			return ShaderStage::Unknown;
		}
	}


#if SA_VULKAN

	namespace VK
	{
		VkShaderStageFlagBits API_GetShaderStage(ShaderStage _stage) noexcept
		{
			switch (_stage)
			{
				case ShaderStage::Vertex:
					return VK_SHADER_STAGE_VERTEX_BIT;
				case ShaderStage::Fragment:
					return VK_SHADER_STAGE_FRAGMENT_BIT;
				case ShaderStage::Geometry:
					return VK_SHADER_STAGE_GEOMETRY_BIT;
				case ShaderStage::Compute:
					return VK_SHADER_STAGE_COMPUTE_BIT;
				case ShaderStage::Unknown:
				default:
					SA_LOG("Vulkan API GetShaderStage [" << _stage << L"] default or unknown used!", Error, SA/Engine/Render);
					return VkShaderStageFlagBits(0);
			}
		}

		VkShaderStageFlags API_GetShaderStageFlags(Flags<ShaderStage> _flags) noexcept
		{
			VkShaderStageFlags result = 0;

			if (_flags & ShaderStage::Vertex)
				result |= VK_SHADER_STAGE_VERTEX_BIT;

			if (_flags & ShaderStage::Fragment)
				result |= VK_SHADER_STAGE_FRAGMENT_BIT;

			if (_flags & ShaderStage::Geometry)
				result |= VK_SHADER_STAGE_GEOMETRY_BIT;

			if (_flags & ShaderStage::Compute)
				result |= VK_SHADER_STAGE_COMPUTE_BIT;

			return result;
		}
	}

#endif
}
