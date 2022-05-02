// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Device/VkContext.hpp>

#include <HI/Cast.hpp>

#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

namespace Sa::Vk
{
	void Context::Create(Device& _device)
	{
		ARenderContext::Create();

		mDevice = &_device;

		SA_LOG(L"Render Context created.", Infos, SA/Render/Vulkan);
	}

	void Context::Destroy()
	{
		ARenderContext::Destroy();

		SA_LOG(L"Render Context destroyed.", Infos, SA/Render/Vulkan);
	}


	void Context::Clear()
	{
		ARenderContext::Clear();

		SA_LOG(L"Render Context cleared.", Infos, SA/Render/Vulkan);
	}


	ARenderSurface* Context::CreateSurface(AWindowSurface* _winSurface)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _winSurface);

		Surface* const surface = mSurfaces.Emplace();

		surface->Create(*mDevice, CastRef<WindowSurface>(_winSurface));

		return surface;
	}

	void Context::DestroySurface(ARenderSurface* _surface)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _surface);
	
		mSurfaces.Erase(_surface, ContextObjDestroyer<Surface>{ *mDevice });
	}
}