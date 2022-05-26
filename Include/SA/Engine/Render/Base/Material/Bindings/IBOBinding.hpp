// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_IBO_BINDING_GUARD
#define SAPPHIRE_ENGINE_IBO_BINDING_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Material/Bindings/ARenderMaterialBinding.hpp>

namespace SA
{
	class ATexture;

	class IBOBinding : public ARenderMaterialBinding
	{
	public:
		std::vector<const ATexture*> IBOs;

		IBOBinding(const ATexture* _IBO);
		IBOBinding(std::vector<const ATexture*> _IBOs) noexcept;

	#if SA_VULKAN

		void FillVkDescriptorWrite(VK::MaterialBindRecorder& _rec, VkWriteDescriptorSet& _descWrite) override final;

	#endif
	};
}

#endif // GUARD
