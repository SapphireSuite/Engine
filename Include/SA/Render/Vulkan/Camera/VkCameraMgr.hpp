// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_CAMERA_MGR_GUARD
#define SAPPHIRE_RENDER_VK_CAMERA_MGR_GUARD

#include <SA/Render/Vulkan/VkResourceMgr.hpp>

#include <SA/Render/Base/Camera/CameraUBO.hpp>

#include <SA/Render/Vulkan/Buffers/CGPU/VkCGPUBuffer.hpp>
#include <SA/Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorPool.hpp>
#include <SA/Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorSetLayout.hpp>

namespace Sa::Vk
{
	class CameraMgr : public ResourceMgr
	{
		std::vector<CGPUBuffer> mCameraBuffers;

		void FillDescriptorUpdater(DescriptorSet::Updater& _updater, uint32 _frame) override final;

	public:
		void Create(const Device& _device, uint32 _frameNum = 3u);
		void Destroy(const Device& _device) override final;

		void Update(const Device& _device, const std::vector<CameraUBO>& _cameras, uint32 _frame);
	};
}

#endif // GUARD
