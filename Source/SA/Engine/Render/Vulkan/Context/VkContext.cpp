// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Context/VkContext.hpp>

#include <HI/Cast.hpp>

#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

namespace SA::VK
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
		mStaticMeshes.Clear(ContextObjDestroyer<StaticMesh>{ mDevice });
		mTextures.Clear(ContextObjDestroyer<Texture>{ mDevice });
		mCubemaps.Clear(ContextObjDestroyer<Cubemap>{ mDevice });
		mPipelineLayouts.Clear(ContextObjDestroyer<PipelineLayout>{ mDevice });
		mPipelines.Clear(ContextObjDestroyer<Pipeline>{ mDevice });

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


//{ Resources

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


	AShader* Context::CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw)
	{
		CheckCreated();

		Shader* const shader = mShaders.Emplace();

		shader->Create(mDevice, CastRef<ResourceInitializer>(_init), _raw);

		return shader;
	}
	
	void Context::DestroyShader(AShader* _shader)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _shader);

		mShaders.Erase(_shader, ContextObjDestroyer<Shader>{ mDevice });
	}


	AStaticMesh* Context::CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw)
	{
		CheckCreated();

		StaticMesh* const mesh = mStaticMeshes.Emplace();

		mesh->Create(mDevice, CastRef<ResourceInitializer>(_init), _raw);

		return mesh;
	}

	void Context::DestroyStaticMesh(AStaticMesh* _mesh)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _mesh);

		mStaticMeshes.Erase(_mesh, ContextObjDestroyer<StaticMesh>{ mDevice });
	}

	
	ATexture* Context::CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw)
	{
		CheckCreated();

		Texture* const texture = mTextures.Emplace();

		texture->Create(mDevice, CastRef<ResourceInitializer>(_init), _raw);

		return texture;
	}
	
	void Context::DestroyTexture(ATexture* _texture)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _texture);

		mTextures.Erase(_texture, ContextObjDestroyer<Texture>{ mDevice });
	}

	
	ACubemap* Context::CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw)
	{
		CheckCreated();

		Cubemap* const cubemap = mCubemaps.Emplace();

		cubemap->Create(mDevice, CastRef<ResourceInitializer>(_init), _raw);

		return cubemap;
	}
	
	void Context::DestroyCubemap(ACubemap* _cubemap)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _cubemap);

		mCubemaps.Erase(_cubemap, ContextObjDestroyer<Cubemap>{ mDevice });
	}

	
	ARenderPipelineLayout* Context::CreatePipelineLayout(const RenderPipelineLayoutDescriptor& _desc)
	{
		CheckCreated();
		PipelineLayout* const pipLayout = mPipelineLayouts.Emplace();

		pipLayout->Create(mDevice, _desc);

		return pipLayout;
	}
	
	void Context::DestroyPipelineLayout(ARenderPipelineLayout* _pipLayout)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _pipLayout);

		mPipelineLayouts.Erase(_pipLayout, ContextObjDestroyer<PipelineLayout>{ mDevice });
	}


	ARenderPipeline* Context::CreatePipeline(const RenderPipelineDescriptor& _desc, const ARenderPipelineLayout* _pipLayout)
	{
		CheckCreated();

		Pipeline* const pipeline = mPipelines.Emplace();

		pipeline->Create(mDevice, _desc, CastRef<PipelineLayout>(_pipLayout));

		return pipeline;
	}
	
	void Context::DestroyPipeline(ARenderPipeline* _pipeline)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _pipeline);

		mPipelines.Erase(_pipeline, ContextObjDestroyer<Pipeline>{ mDevice });
	}

//}
}