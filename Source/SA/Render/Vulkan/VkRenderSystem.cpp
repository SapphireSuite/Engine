// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderSystem.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void RenderSystem::Create(const AWindowSystem& _winSys)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");

		SA_LOG(L"Render System created.", Infos, SA/Render/Vulkan);

		mInstance.Create(_winSys);
	}

	void RenderSystem::Destroy()
	{
		mInstance.Destroy();

		SA_LOG(L"Render System destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderDevice* RenderSystem::CreateDevice(const AGraphicDeviceInfos& _infos)
	{
		Device* device = mDevices.emplace_back(new Device());

		device->Create(_infos.As<GraphicDeviceInfos>());

		return device;
	}

	void RenderSystem::DestroyDevice(ARenderDevice* _device)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _device);

		for (auto it = mDevices.begin(); it != mDevices.end(); ++it)
		{
			if (_device == *it)
			{
				_device->Destroy();
				mDevices.erase(it);
				return;
			}
		}

		SA_LOG(L"Can't find device in RenderSystem", Error, SA/Render/Vulkan);
	}


	RenderSystem::operator const RenderInstance& () const
	{
		return mInstance;
	}
}

#endif
