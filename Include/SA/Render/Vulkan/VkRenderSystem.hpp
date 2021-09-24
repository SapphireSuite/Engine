// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_VK_RENDER_SYSTEM_GUARD
#define SAPPHIRE_VK_RENDER_SYSTEM_GUARD

#include <SA/Render/Base/ARenderSystem.hpp>

#include <SA/Render/Vulkan/VkRenderInstance.hpp>
#include <SA/Render/Vulkan/Device/VkDevice.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class RenderSystem : public ARenderSystem
	{
		RenderInstance mInstance;

		std::vector<Device*> mDevices;

	public:
		void Create(const AWindowSystem& _winSys) override final;
		void Destroy() override final;

		ARenderDevice* CreateDevice(const AGraphicDeviceInfos& _infos) override final;
		void DestroyDevice(ARenderDevice* _device) override final;


		operator const RenderInstance& () const;
	};
}

#endif

#endif // GUARD
