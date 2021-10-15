// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_ENGINE_DESCRIPTOR_SET_LAYOUTS_GUARD
#define SAPPHIRE_RENDER_VK_ENGINE_DESCRIPTOR_SET_LAYOUTS_GUARD

#include <vector>
#include <set>

#include <SA/Core/Support/API/Vulkan.hpp>
#include <SA/Core/Types/Int.hpp>

namespace Sa::Vk
{
	class Device;

	class EngineDescriptorSetLayouts
	{
		void CreateCameraSetLayout(const Device& _device);
		void CreateModelSetLayout(const Device& _device);

	public:

		/// Set = 1
		VkDescriptorSetLayout camera;

		/// Set = 2
		VkDescriptorSetLayout model;


		void Create(const Device& _device);
		void Destroy(const Device& _device);

		const VkDescriptorSetLayout* Data() const;

		std::vector<VkDescriptorSetLayout> QuerySets(const std::set<uint32>& _setIDs) const;
	};
}

#endif // GUARD
