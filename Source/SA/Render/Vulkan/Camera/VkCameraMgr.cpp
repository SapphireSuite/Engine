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


		// Descriptor Sets.
		{
			// TODO: Remove later.
			PipelineBindingSetDescriptor cameraBindSetDesc;
			auto& bind = cameraBindSetDesc.bindings.emplace_back();
			bind.type = ShaderBindingType::StorageBuffer;
			bind.stageFlags = ShaderStage::Vertex;
			//

			mDescriptorPool.Create(_device, cameraBindSetDesc, _frameNum);
			mDescriptorSetLayout.Create(_device, cameraBindSetDesc);

			mDescriptorSets = mDescriptorPool.Allocate(_device, std::vector<DescriptorSetLayout>(_frameNum, mDescriptorSetLayout));

			// Bind buffer to descriptor.
			for (uint32 i = 0; i < _frameNum; ++i)
			{
				DescriptorSet::Updater updater = mDescriptorSets[i].MakeUpdater();

				updater.Add(bind.binding, { &mCameraBuffers[i] });

				updater.Submit(_device);
			}
		}


		SA_LOG(L"Camera Manager created.", Infos, SA/Render/Vulkan);
	}

	void CameraMgr::Destroy(const Device& _device)
	{
		// Descriptor Sets.
		{
			// Not needed: Auto free on destroy.
			//mDescriptorPool.Free(_device, mDescriptorSets);
			mDescriptorPool.Destroy(_device);
			mDescriptorSetLayout.Destroy(_device);

			mDescriptorSets.clear();
		}

		// Buffers.
		{
			for (auto& buffer : mCameraBuffers)
				buffer.Destroy(_device);

			mCameraBuffers.clear();
		}

		SA_LOG(L"Camera Manager destroyed.", Infos, SA/Render/Vulkan);
	}


	void CameraMgr::Update(const Device& _device, const std::vector<CameraUBO>& _cameras, uint32 _frameNum)
	{
		SA_ASSERT(OutOfRange, SA/Render/Vulkan, _frameNum, 0u, (uint32)mCameraBuffers.size());

		CGPUBuffer& buffer = mCameraBuffers[_frameNum];


		const uint64 inOctSize = OctSizeOf<uint64>(_cameras);

		if (buffer.GetCapacity() < inOctSize)
		{
			// Realloc.
			buffer.Destroy(_device);
			buffer.Create(_device, gBufferUsage, inOctSize, _cameras.data());
		}
		else
			buffer.UpdateData(_device, _cameras.data(), inOctSize);
	}
}
