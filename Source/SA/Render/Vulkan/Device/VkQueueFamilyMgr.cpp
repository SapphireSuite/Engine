// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Device/VkQueueFamilyMgr.hpp>

#include <Core/Debug.hpp>

namespace Sa::Vk
{
	Queue& QueueFamilyMgr::GetQueue(uint32 _index)
	{
		SA_ASSERT(OutOfRange, SA/Render/Vulkan, _index, 0u, static_cast<uint32>(mQueues.size()));

		return mQueues[_index];
	}
	
	const Queue& QueueFamilyMgr::GetQueue(uint32 _index) const
	{
		SA_ASSERT(OutOfRange, SA/Render/Vulkan, _index, 0u, static_cast<uint32>(mQueues.size()));

		return mQueues[_index];
	}


	void QueueFamilyMgr::Create(const Device& _device, const GraphicDeviceInfos::FamilyInfos& _famInfos)
	{
		mQueues.resize(_famInfos.queueInfos.size());

		for (uint32 i = 0u; i < _famInfos.queueInfos.size(); ++i)
		{
			auto infos = _famInfos.queueInfos[i];

			mQueues[i].Create(_device, infos.familyIndex, infos.queueIndex);
		}

		SA_LOG(L"Queue Family Manager created", Infos, SA/Render/Vulkan);
	}

	void QueueFamilyMgr::Destroy(const Device& _device)
	{
		(void)_device;
		mQueues.clear();

		SA_LOG(L"Queue Family Manager destroyed", Infos, SA/Render/Vulkan);
	}
}
