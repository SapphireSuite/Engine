// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_STAGE_GUARD
#define SAPPHIRE_RENDER_SHADER_STAGE_GUARD

#include <SA/Core/Types/Variadics/Flags.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	enum class ShaderStage : uint8
	{
		Unknown = 0,

		Vertex = 1 << 0,
		Fragment = 1 << 1,
		Geometry = 1 << 2,
		Compute = 1 << 3
	};

	SA_DEFINE_ENUM_FLAGS(ShaderStage);


#if SA_VULKAN

	namespace Vk
	{
		VkShaderStageFlagBits API_GetShaderStage(ShaderStage _type) noexcept;

		VkShaderStageFlags API_GetShaderStageFlags(Flags<ShaderStage> _flags) noexcept;
	}

#endif
}

#endif