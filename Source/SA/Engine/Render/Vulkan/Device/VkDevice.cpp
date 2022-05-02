// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Device/VkDeviceInfos.hpp>

namespace Sa::Vk
{
	void Device::Create(const DeviceInfos& _infos)
	{
		ARenderDevice::Create();
		
		SA_LOG(L"Render Device created.", Infos, SA/Engine/Render/Vulkan);
	}

	void Device::Destroy()
	{
		ARenderDevice::Destroy();

		WaitIdle();

		SA_LOG(L"Render Device destroyed.", Infos, SA/Engine/Render/Vulkan);
	}

	void Device::Clear()
	{
		ARenderDevice::Clear();

		WaitIdle();
		
		mContexts.Clear(DestroyFunctor<Context>());

		SA_LOG(L"Render Device cleared.", Infos, SA/Engine/Render/Vulkan);
	}


	void Device::WaitIdle() const
	{
		vkDeviceWaitIdle(mLogicalDevice);
	}


	ARenderContext* Device::CreateRenderContext()
	{
		CheckCreated();

		Context* const context = mContexts.Emplace();

		context->Create(*this);

		return context;
	}
	
	void Device::DestroyRenderContext(ARenderContext* _context)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _context);

		WaitIdle();

		mContexts.Erase(_context, DestroyFunctor<Context>());
	}
}
