// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_ENGINE_SHADER_STAGE_GUARD
#define SAPPHIRE_ENGINE_SHADER_STAGE_GUARD

#include <SA/Flags/Flags.hpp>

#include <SA/Support/API/Vulkan.hpp>

namespace SA
{
	enum class ShaderStage : uint8_t
	{
		Unknown = 0,

		Vertex = 1 << 0,
		Fragment = 1 << 1,
		Geometry = 1 << 2,
		Compute = 1 << 3
	};

	SA_DEFINE_ENUM_FLAGS(ShaderStage);


	ShaderStage ShaderStageFromFile(const std::string& _path);


#if SA_VULKAN

	namespace VK
	{
		VkShaderStageFlagBits API_GetShaderStage(ShaderStage _type) noexcept;

		VkShaderStageFlags API_GetShaderStageFlags(Flags<ShaderStage> _flags) noexcept;
	}

#endif
}

#endif