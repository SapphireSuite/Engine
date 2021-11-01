// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderGraphicInterface.hpp>

#include <Render/Vulkan/VkRenderContextInterface.hpp>

namespace Sa::Vk
{
	const ARenderDevice* RenderGraphicInterface::GetDevice() const
	{
		return &device;
	}


	void RenderGraphicInterface::Create(const AGraphicDeviceInfos& _infos)
	{
		device.Create(_infos);

		SA_LOG(L"Render Graphic Interface created.", Infos, SA/Render/Vulkan);
	}

	void RenderGraphicInterface::Destroy()
	{
		device.Destroy();

		SA_LOG(L"Render Graphic Interface destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderContextInterface* RenderGraphicInterface::CreateContextInterface()
	{
		RenderContextInterface* const context = new RenderContextInterface();
		
		context->Create(this);

		return context;
	}
}
