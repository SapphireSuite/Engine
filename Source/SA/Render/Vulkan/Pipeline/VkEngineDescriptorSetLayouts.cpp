// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/VkEngineDescriptorSetLayouts.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Debug/Debug.hpp>

namespace Sa::Vk
{
	void EngineDescriptorSetLayouts::Create(const Device& _device)
	{
		CreateCameraSetLayout(_device);
		CreateModelSetLayout(_device);

		SA_LOG(L"Render Engine descriptor set layouts created.", Infos, SA/Render/Vulkan);
	}
	
	void EngineDescriptorSetLayouts::Destroy(const Device& _device)
	{
		vkDestroyDescriptorSetLayout(_device, camera, nullptr);
		vkDestroyDescriptorSetLayout(_device, model, nullptr);
		
		SA_LOG(L"Render Engine descriptor set layouts destroyed.", Infos, SA/Render/Vulkan);
	}


	const VkDescriptorSetLayout* EngineDescriptorSetLayouts::Data() const
	{
		return &camera;
	}

	std::vector<VkDescriptorSetLayout> EngineDescriptorSetLayouts::QuerySets(const std::set<uint32>& _setIDs) const
	{
		std::vector<VkDescriptorSetLayout> res{ VK_NULL_HANDLE }; // Ensure first one is empty for user.

		for (auto id : _setIDs)
		{
			while (res.size() < id)
				res.emplace_back(VK_NULL_HANDLE);

			res.emplace_back(Data()[id - 1]); // Engine Set ID Start at 1.
		}

		return res;
	}


	void EngineDescriptorSetLayouts::CreateCameraSetLayout(const Device& _device)
	{
		constexpr uint32 size = 1u;
		VkDescriptorSetLayoutBinding descSetLayout[size]{};


		// Camera UBO
		descSetLayout[0].binding = 0;
		descSetLayout[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descSetLayout[0].descriptorCount = 1;
		descSetLayout[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		descSetLayout[0].pImmutableSamplers = nullptr;



		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
		descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutInfo.pNext = nullptr;
		descriptorSetLayoutInfo.flags = 0u;
		descriptorSetLayoutInfo.bindingCount = size;
		descriptorSetLayoutInfo.pBindings = descSetLayout;

		SA_VK_ASSERT(vkCreateDescriptorSetLayout(_device, &descriptorSetLayoutInfo, nullptr, &camera),
			L"Failed to create camera descriptor set layout!");
	}
	
	void EngineDescriptorSetLayouts::CreateModelSetLayout(const Device& _device)
	{
		constexpr uint32 size = 1u;
		VkDescriptorSetLayoutBinding descSetLayout[size]{};


		// Model UBO
		descSetLayout[0].binding = 0;
		descSetLayout[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descSetLayout[0].descriptorCount = 1;
		descSetLayout[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		descSetLayout[0].pImmutableSamplers = nullptr;



		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
		descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutInfo.pNext = nullptr;
		descriptorSetLayoutInfo.flags = 0u;
		descriptorSetLayoutInfo.bindingCount = size;
		descriptorSetLayoutInfo.pBindings = descSetLayout;

		SA_VK_ASSERT(vkCreateDescriptorSetLayout(_device, &descriptorSetLayoutInfo, nullptr, &model),
			L"Failed to create model descriptor set layout!");
	}
}
