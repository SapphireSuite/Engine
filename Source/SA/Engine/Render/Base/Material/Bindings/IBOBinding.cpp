// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/Bindings/IBOBinding.hpp>

#if SA_VULKAN

	#include <HI/Cast.hpp>

	#include <Render/Vulkan/Texture/VkTexture.hpp>

#endif

namespace SA
{
	IBOBinding::IBOBinding(const ATexture* _IBO) :
		IBOs{ _IBO }
	{

	}
	
	IBOBinding::IBOBinding(std::vector<const ATexture*> _IBOs) noexcept :
		IBOs{ std::move(_IBOs) }
	{
	}


#if SA_VULKAN

	void IBOBinding::FillVkDescriptorWrite(VK::MaterialBindRecorder& _rec, VkWriteDescriptorSet& _descWrite)
	{
		std::vector<VkDescriptorImageInfo>& descs = _rec.imageDescs.emplace_back();
		descs.reserve(IBOs.size());

		for (auto it = IBOs.begin(); it != IBOs.end(); ++it)
			descs.emplace_back(CastRef<VK::Texture>(*it).CreateDescriptorImageInfo());

		_descWrite.descriptorCount = (uint32_t)IBOs.size();
		_descWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		_descWrite.pImageInfo = descs.data();
	}

#endif
}
