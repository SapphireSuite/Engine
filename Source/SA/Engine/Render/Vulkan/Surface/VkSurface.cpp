// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Surface/VkSurface.hpp>

#include <SA/Collections/Debug>

namespace Sa::Vk
{
	void Surface::Create(const Device& _device, const WindowSurface& _winSurface)
	{
		ARenderSurface::Create();
		
		SA_LOG(L"Render Surface created.", Infos, SA/Engine/Render/Vulkan);
	}
	void Surface::Destroy(const Device& _device)
	{
		ARenderSurface::Destroy();

		SA_LOG(L"Render Surface destroyed.", Infos, SA/Engine/Render/Vulkan);
	}
}
