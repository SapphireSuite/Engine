// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD
#define SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD

#include <list>
#include <vector>

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class Device;
	class Buffer;
	class Texture;

	class DescriptorSet
	{
		VkDescriptorSet mHandle = VK_NULL_HANDLE;

		friend class DescriptorPool;


	public:
//{ Update

		class Updater
		{
			VkDescriptorSet mDescriptorSet = VK_NULL_HANDLE;

			std::vector<VkWriteDescriptorSet> mDescWrites;

			std::list<std::vector<VkDescriptorBufferInfo>> mBufferDescs;
			std::list<std::vector<VkDescriptorImageInfo>> mImageDescs;

			VkWriteDescriptorSet MakeDefaultWriteDescriptors(uint32 _binding);

		public:
			Updater(const DescriptorSet& _handle);

			void Add(uint32 _binding, const std::vector<const Buffer*>& _buffers);
			void Add(uint32 _binding, const std::vector<const Texture*>& _textures);

			void Submit(const Device& _device) const;
		};

		Updater MakeUpdater();

//}

		operator VkDescriptorSet() const noexcept;
	};
}

#endif // GUARD
