// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_CAMERA_MGR_GUARD
#define SAPPHIRE_RENDER_VK_CAMERA_MGR_GUARD

#include <SA/Render/Base/Camera/CameraUBO.hpp>

#include <SA/Render/Vulkan/Buffers/CGPU/VkCGPUBuffer.hpp>
#include <SA/Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorPool.hpp>
#include <SA/Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorSetLayout.hpp>

namespace Sa::Vk
{
	class Device;

	class CameraMgr
	{
		std::vector<CGPUBuffer> mCameraBuffers;

		DescriptorPool mDescriptorPool;
		DescriptorSetLayout mDescriptorSetLayout;
		
		std::vector<DescriptorSet> mDescriptorSets;

	public:
		void Create(const Device& _device, uint32 _frameNum = 3u);
		void Destroy(const Device& _device);

		void Update(const Device& _device, const std::vector<CameraUBO>& _cameras, uint32 _frameNum);
	};
}

#endif // GUARD
