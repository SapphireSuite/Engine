// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_GRAPHIC_INTERFACE_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_GRAPHIC_INTERFACE_GUARD

#include <SA/Render/Base/ARenderGraphicInterface.hpp>

#include <SA/Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
	class RenderGraphicInterface : public ARenderGraphicInterface
	{
	public:
		Device device;

		const ARenderDevice* GetDevice() const override final;

		void Create(const AGraphicDeviceInfos& _infos) override final;
		void Destroy() override final;

		ARenderContextInterface* CreateContextInterface() override final;
	};
}

#endif // GUARD
