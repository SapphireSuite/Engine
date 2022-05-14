// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Device/Queue/VkQueueMgr.hpp>

#include <SA/Collections/Debug>

namespace SA::VK
{
	const QueueFamilyMgr& QueueMgr::GetQueueFamilyMgrFromType(QueueFamily _family) const
	{
		switch (_family)
		{
			case QueueFamily::Graphics:
				return graphics;
			case QueueFamily::Compute:
				return compute;
			case QueueFamily::Transfer:
				return transfer;
			case QueueFamily::Present:
				return present;
			default:
				SA_LOG("QueueFamily [" << _family << L"] not supported!", Error, SA/Engine/Render/Vulkan);
				return graphics;
		}
	}

	
	void QueueMgr::Create(const Device& _device, const DeviceInfos& _infos)
	{
		graphics.Create(_device, _infos.graphics);
		compute.Create(_device, _infos.compute);
		transfer.Create(_device, _infos.transfer);
		present.Create(_device, _infos.present);

		SA_LOG(L"Queue Mgr created", Infos, SA/Engine/Render/Vulkan);
	}
	
	void QueueMgr::Destroy(const Device& _device)
	{
		graphics.Destroy(_device);
		compute.Destroy(_device);
		transfer.Destroy(_device);
		present.Destroy(_device);

		SA_LOG(L"Queue Mgr destroyed", Infos, SA/Engine/Render/Vulkan);
	}
}
