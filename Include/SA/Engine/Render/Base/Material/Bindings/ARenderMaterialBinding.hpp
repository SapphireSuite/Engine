// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_MATERIAL_BINDING_GUARD
#define SAPPHIRE_ENGINE_ARENDER_MATERIAL_BINDING_GUARD

#if SA_VULKAN

	#include <SA/Engine/Render/Vulkan/Material/VkMaterialBindRecorder.hpp>

#endif

namespace SA
{

	class ARenderMaterialBinding
	{
	public:
		virtual ~ARenderMaterialBinding() = default;

	#if SA_VULKAN

		virtual void FillVkDescriptorWrite(VK::MaterialBindRecorder& _rec, VkWriteDescriptorSet& _descWrite) = 0;

	#endif
	};
}

#endif // GUARD
