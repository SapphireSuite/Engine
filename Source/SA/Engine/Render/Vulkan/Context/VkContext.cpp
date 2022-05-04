// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Context/VkContext.hpp>

#include <HI/Cast.hpp>

#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

namespace Sa::Vk
{
	void Context::Create(Device& _device)
	{
		ARenderContext::Create();

		mDevice = &_device;

		SA_LOG(L"Render Context created.", Infos, SA/Engine/Render/Vulkan);
	}

	void Context::Destroy()
	{
		ARenderContext::Destroy();

		SA_LOG(L"Render Context destroyed.", Infos, SA/Engine/Render/Vulkan);
	}


	void Context::Clear()
	{
		ARenderContext::Clear();

		mResInits.Clear(ContextObjDestroyer<ResourceInitializer>{ *mDevice });
		mRenderPasses.Clear(ContextObjDestroyer<RenderPass>{ *mDevice });
		mSurfaces.Clear(ContextObjDestroyer<Surface>{ *mDevice });

		SA_LOG(L"Render Context cleared.", Infos, SA/Engine/Render/Vulkan);
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


	ARenderPass* Context::CreateRenderPass(const RenderPassDescriptor& _desc)
	{
		CheckCreated();

		RenderPass* const pass = mRenderPasses.Emplace();

		pass->Create(*mDevice, _desc);

		return pass;
	}
	
	void Context::DestroyRenderPass(ARenderPass* _pass)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _pass);

		mRenderPasses.Erase(_pass, ContextObjDestroyer<RenderPass>{ *mDevice });
	}


	void Context::CreateFrameBuffers(ARenderSurface* _surface, ARenderPass* _pass, const RenderPassDescriptor& _desc)
	{
		CastRef<Surface>(_surface).CreateFrameBuffers(*mDevice, CastRef<RenderPass>(_pass), _desc);
	}
	
	void Context::DestroyFrameBuffers(ARenderSurface* _surface)
	{
		CastRef<Surface>(_surface).DestroyFrameBuffers(*mDevice);
	}


	ARenderResourceInitializer* Context::CreateResourceInitializer()
	{
		CheckCreated();

		ResourceInitializer* const resInit = mResInits.Emplace();

		resInit->Create(*mDevice);

		return resInit;
	}

	void Context::DestroyResourceInitializer(ARenderResourceInitializer* _resInit)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _resInit);

		mResInits.Erase(_resInit, ContextObjDestroyer<ResourceInitializer>{ *mDevice });
	}
}