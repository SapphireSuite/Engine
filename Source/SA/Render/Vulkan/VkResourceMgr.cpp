// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkResourceMgr.hpp>

#include <Collections/Debug>

#include <Render/Vulkan/Buffers/CGPU/VkCGPUBuffer.hpp>

namespace Sa::Vk
{
	const DescriptorSet& ResourceMgr::GetDescriptorSet(uint32 _frame) const
	{
		SA_ASSERT(OutOfRange, SA/Render/Vulkan, _frame, 0u, (uint32)mDescriptorSets.size());

		return mDescriptorSets[_frame];
	}


	void ResourceMgr::Create(const Device& _device, const PipelineBindingSetDescriptor& _bindSetDesc, uint32 _frameNum)
	{
		mDescriptorPool.Create(_device, _bindSetDesc, _frameNum);
		mDescriptorSetLayout.Create(_device, _bindSetDesc);

		mDescriptorSets = mDescriptorPool.Allocate(_device, std::vector<DescriptorSetLayout>(_frameNum, mDescriptorSetLayout));


		// Update Descriptors
		for (uint32 i = 0; i < _frameNum; ++i)
		{
			DescriptorSet::Updater updater = mDescriptorSets[i].MakeUpdater();

			FillDescriptorUpdater(updater, i);

			updater.Submit(_device);
		}
	}
	
	void ResourceMgr::Destroy(const Device& _device)
	{
		// Not needed: Auto free on destroy.
		//mDescriptorPool.Free(_device, mDescriptorSets);

		mDescriptorPool.Destroy(_device);
		mDescriptorSetLayout.Destroy(_device);

		mDescriptorSets.clear();
	}

	
	void ResourceMgr::UpdateBuffer(const Device& _device, CGPUBuffer& _buffer, uint32 _binding, const void* _data, uint64 _octSize, uint32 _frame)
	{
		if (_buffer.GetCapacity() < _octSize)
		{
			const VkBufferUsageFlags usage = _buffer.GetUsage();

			// Realloc.
			_buffer.Destroy(_device);
			_buffer.Create(_device, usage, _octSize, _data);


			// Update Descriptor.
			DescriptorSet::Updater updater = mDescriptorSets[_frame].MakeUpdater();

			updater.Add(_binding, { &_buffer });

			updater.Submit(_device);
		}
		else
			_buffer.UpdateData(_device, _data, _octSize);
	}
}
