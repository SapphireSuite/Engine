// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Context/VkContext.hpp>

#include <HI/Cast.hpp>

#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

namespace Sa::Vk
{
	Context::Context(Device& _device) noexcept : mDevice{ _device }
	{
	}


	void Context::Create()
	{
		ARenderContext::Create();

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

		mResInits.Clear(ContextObjDestroyer<ResourceInitializer>{ mDevice });
		mRenderPasses.Clear(ContextObjDestroyer<RenderPass>{ mDevice });
		mSurfaces.Clear(ContextObjDestroyer<Surface>{ mDevice });

		SA_LOG(L"Render Context cleared.", Infos, SA/Engine/Render/Vulkan);
	}


//{ Surface

	ARenderSurface* Context::CreateSurface(AWindowSurface* _winSurface)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _winSurface);

		Surface* const surface = mSurfaces.Emplace();

		surface->Create(mDevice, CastRef<WindowSurface>(_winSurface));

		return surface;
	}

	void Context::DestroySurface(ARenderSurface* _surface)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _surface);
	
		mSurfaces.Erase(_surface, ContextObjDestroyer<Surface>{ mDevice });
	}


	void Context::CreateFrameBuffers(ARenderSurface* _surface, ARenderPass* _pass, const RenderPassDescriptor& _desc)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _surface);

		CastRef<Surface>(_surface).CreateFrameBuffers(mDevice, CastRef<RenderPass>(_pass), _desc);
	}
	
	void Context::DestroyFrameBuffers(ARenderSurface* _surface)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _surface);

		CastRef<Surface>(_surface).DestroyFrameBuffers(mDevice);
	}


	ARenderFrame& Context::BeginSurface(ARenderSurface* _surface)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _surface);

		return CastRef<Surface>(_surface).Begin(mDevice);
	}
	
	void Context::EndSurface(ARenderSurface* _surface)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _surface);

		CastRef<Surface>(_surface).End(mDevice);
	}

//}


	ARenderPass* Context::CreateRenderPass(const RenderPassDescriptor& _desc)
	{
		CheckCreated();

		RenderPass* const pass = mRenderPasses.Emplace();

		pass->Create(mDevice, _desc);

		return pass;
	}
	
	void Context::DestroyRenderPass(ARenderPass* _pass)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _pass);

		mRenderPasses.Erase(_pass, ContextObjDestroyer<RenderPass>{ mDevice });
	}



	ARenderResourceInitializer* Context::CreateResourceInitializer()
	{
		CheckCreated();

		ResourceInitializer* const resInit = mResInits.Emplace();

		resInit->Create(mDevice);

		return resInit;
	}

	void Context::DestroyResourceInitializer(ARenderResourceInitializer* _init)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _init);

		mResInits.Erase(_init, ContextObjDestroyer<ResourceInitializer>{ mDevice });
	}
	
	void Context::SubmitResourceInitializer(ARenderResourceInitializer* _init)
	{
		CheckCreated();

		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _init);

		CastRef<ResourceInitializer>(_init).Submit(mDevice);
	}
}