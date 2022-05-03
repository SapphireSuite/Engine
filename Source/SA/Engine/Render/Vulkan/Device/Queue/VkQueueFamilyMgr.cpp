// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Device/Queue/VkQueueFamilyMgr.hpp>

#include <SA/Collections/Debug>

namespace Sa::Vk
{
	Queue& QueueFamilyMgr::GetQueue(uint32_t _index)
	{
		SA_ASSERT(OutOfRange, SA/Engine/Render/Vulkan, _index, 0u, static_cast<uint32_t>(mQueues.size()));

		return mQueues[_index];
	}
	
	const Queue& QueueFamilyMgr::GetQueue(uint32_t _index) const
	{
		SA_ASSERT(OutOfRange, SA/Engine/Render/Vulkan, _index, 0u, static_cast<uint32_t>(mQueues.size()));

		return mQueues[_index];
	}


	void QueueFamilyMgr::Create(const Device& _device, const DeviceInfos::FamilyInfos& _famInfos)
	{
		mQueues.resize(_famInfos.queueInfos.size());

		for (uint32_t i = 0u; i < _famInfos.queueInfos.size(); ++i)
		{
			auto infos = _famInfos.queueInfos[i];

			mQueues[i].Create(_device, infos.familyIndex, infos.queueIndex);
		}

		SA_LOG(L"Queue Family Manager created", Infos, SA/Engine/Render/Vulkan);
	}

	void QueueFamilyMgr::Destroy(const Device& _device)
	{
		(void)_device;
		mQueues.clear();

		SA_LOG(L"Queue Family Manager destroyed", Infos, SA/Engine/Render/Vulkan);
	}


	Queue& QueueFamilyMgr::operator[](uint32_t _index)
	{
		return GetQueue(_index);
	}

	const Queue& QueueFamilyMgr::operator[](uint32_t _index) const
	{
		return GetQueue(_index);
	}
}
