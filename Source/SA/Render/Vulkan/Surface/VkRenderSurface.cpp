// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Surface/VkRenderSurface.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	RenderSurface::RenderSurface(VkSurfaceKHR _handle) noexcept :
		mHandle{ _handle }
	{
	}

	void RenderSurface::Create(const RenderInstance& _inst)
	{
		SA_LOG(L"Render Surface created.", Infos, SA/Render/Vulkan);
	}
	
	void RenderSurface::Destroy(const RenderInstance& _inst)
	{
		SA_LOG(L"Render Surface destroyed.", Infos, SA/Render/Vulkan);
	}


	RenderSurface::operator VkSurfaceKHR() const noexcept
	{
		return mHandle;
	}
}

#endif
