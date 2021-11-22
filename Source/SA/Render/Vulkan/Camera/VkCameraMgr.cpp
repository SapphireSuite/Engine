// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Camera/VkCameraMgr.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Collections/Debug>

namespace Sa::Vk
{
	constexpr uint64 gBufferDefaultSize = 5u * sizeof(CameraUBO);
	constexpr VkBufferUsageFlagBits gBufferUsage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;


	void CameraMgr::Create(const Device& _device, uint32 _frameNum)
	{
		// Buffers.
		{
			mCameraBuffers.resize(_frameNum);

			for (auto& buffer : mCameraBuffers)
				buffer.Create(_device, gBufferUsage, gBufferDefaultSize);
		}


		ResourceMgr::Create(_device, PipelineBindingSetDescriptor::cameraBindSetDesc, _frameNum);


		SA_LOG(L"Camera Manager created.", Infos, SA/Render/Vulkan);
	}

	void CameraMgr::Destroy(const Device& _device)
	{
		ResourceMgr::Destroy(_device);

		// Buffers.
		{
			for (auto& buffer : mCameraBuffers)
				buffer.Destroy(_device);

			mCameraBuffers.clear();
		}

		SA_LOG(L"Camera Manager destroyed.", Infos, SA/Render/Vulkan);
	}


	void CameraMgr::FillDescriptorUpdater(DescriptorSet::Updater& _updater, uint32 _frame)
	{
		// TODO: Clean hard code.
		_updater.Add(0u, { &mCameraBuffers[_frame] });
	}

	void CameraMgr::Update(const Device& _device, const std::vector<CameraUBO>& _cameras, uint32 _frame)
	{
		SA_ASSERT(OutOfRange, SA/Render/Vulkan, _frame, 0u, (uint32)mCameraBuffers.size());

		CGPUBuffer& buffer = mCameraBuffers[_frame];

		UpdateBuffer(_device, buffer, 0u, _cameras.data(), OctSizeOf<uint64>(_cameras), _frame);
	}
}
