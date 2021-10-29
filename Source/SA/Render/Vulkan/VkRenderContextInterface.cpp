// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderContextInterface.hpp>

#include <Render/Vulkan/VkRenderGraphicInterface.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

//#include <Render/Vulkan/Pipeline/VkPipeline.hpp>
//#include <Render/Vulkan/VkResourceInitializer.hpp>
//#include <Render/Vulkan/Shader/VkShader.hpp>
//#include <Render/Vulkan/Mesh/VkStaticMesh.hpp>
//#include <Render/Vulkan/Texture/VkTexture.hpp>
//#include <Render/Vulkan/Texture/VkCubemap.hpp>
//#include <Render/Vulkan/Material/VkMaterial.hpp>
//#include <Render/Vulkan/Camera/VkCamera.hpp>

namespace Sa::Vk
{
	void RenderContextInterface::Create(const RenderGraphicInterface* _graphics)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _graphics);

		mGraphics = _graphics;

		SA_LOG(L"Render Context Interface created.", Infos, SA/Render/Vulkan);
	}

	void RenderContextInterface::Destroy()
	{
		for (auto& surface : mSurfaces)
			surface.Destroy(GetDevice());

		mGraphics = nullptr;

		SA_LOG(L"Render Context  Interface destroyed.", Infos, SA/Render/Vulkan);
	}

	
	const Device& RenderContextInterface::GetDevice() const
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, mGraphics);

		return mGraphics->device;
	}


	RenderSurfaceHandle RenderContextInterface::CreateSurface(WindowSurfaceHandle _winHandle)
	{
		RenderSurfaceHandle handle = mSurfaces.EmplaceHandle();

		Surface& surface = mSurfaces[handle];

		surface.Create(GetDevice(), _winHandle);

		return handle;
	}

	void RenderContextInterface::DestroySurface(RenderSurfaceHandle& _handle)
	{
		Surface& surface = mSurfaces[_handle];

		if (surface.FrameBuffersValid())
			DestroyFrameBuffers(_handle);

		surface.Destroy(GetDevice());

		mSurfaces.EraseHandle(_handle);
		_handle.Reset();
	}


	RenderPassHandle RenderContextInterface::CreateRenderPass(const RenderPassDescriptor& _descriptor)
	{
		const RenderPassHandle handle = mRenderPasses.EmplaceHandle();

		RenderPass& renderPass = mRenderPasses[handle];

		renderPass.Create(GetDevice(), _descriptor);

		return handle;
	}

	void RenderContextInterface::DestroyRenderPass(RenderPassHandle& _handle)
	{
		RenderPass& renderPass = mRenderPasses[_handle];

		renderPass.Destroy(GetDevice());

		mRenderPasses.EraseHandle(_handle);
		_handle.Reset();
	}


	void RenderContextInterface::CreateFrameBuffers(const RenderSurfaceHandle& _surface,
		const RenderPassHandle& _pass,
		const RenderPassDescriptor& _descriptor)
	{
		Surface& surface = mSurfaces[_surface];
		RenderPass& renderPass = mRenderPasses[_pass];

		surface.CreateFrameBuffers(GetDevice(), renderPass, _descriptor);
	}

	void RenderContextInterface::DestroyFrameBuffers(const RenderSurfaceHandle& _surface)
	{
		Surface& surface = mSurfaces[_surface];

		surface.DestroyFrameBuffers(GetDevice());
	}


	//ARenderPipeline* RenderContextInterface::CreatePipeline(const RenderPipelineDescriptor& _desc)
	//{
	//	Pipeline* const pipeline = new Pipeline();

	//	pipeline->Create(mDevice, _desc, enDescSetLayouts);

	//	return pipeline;
	//}

	//void RenderContextInterface::DestroyPipeline(ARenderPipeline* _pipeline)
	//{
	//	Pipeline* const vkPipeline = _pipeline->AsPtr<Pipeline>();

	//	vkPipeline->Destroy(mDevice);

	//	delete vkPipeline;
	//}


//{ Resources

	RenderResourceInitializerHandle RenderContextInterface::CreateResourceInitializer()
	{
		const RenderResourceInitializerHandle handle = mResInits.EmplaceHandle();

		ResourceInitializer& resInit = mResInits[handle];

		resInit.Create(GetDevice());

		return handle;
	}

	void RenderContextInterface::DestroyResourceInitializer(RenderResourceInitializerHandle& _init)
	{
		ResourceInitializer& resInit = mResInits[_init];

		resInit.Destroy(GetDevice());

		mResInits.EraseHandle(_init);
		_init.Reset();
	}

	void RenderContextInterface::SubmitResourceInitializer(const RenderResourceInitializerHandle& _init)
	{
		ResourceInitializer& resInit = mResInits[_init];

		resInit.Submit(GetDevice());
	}


	//ShaderHandle RenderContextInterface::CreateShader(const RenderResourceInitializerHandle& _init, const RawShader& _raw)
	//{
	//	const ShaderHandle handle = mShaders.EmplaceHandle();

	//	Shader& shader = mShaders[handle];
	//	ResourceInitializer& resInit = mResInits[_init];

	//	shader.Create(GetDevice(), resInit, _raw);

	//	return handle;
	//}

	//void RenderContextInterface::DestroyShader(ShaderHandle& _shader)
	//{
	//	Shader& shader = mShaders[_shader];

	//	shader.Destroy(GetDevice());

	//	mShaders.RemoveHandle(_shader);
	//	_shader.Reset();
	//}

	//
	//AStaticMesh* RenderContextInterface::CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw)
	//{
	//	StaticMesh* const mesh = new StaticMesh();

	//	mesh->Create(mDevice, _init->As<ResourceInitializer>(), _raw);

	//	return mesh;
	//}
	//
	//void RenderContextInterface::DestroyStaticMesh(AStaticMesh* _mesh)
	//{
	//	StaticMesh* const vkMesh = _mesh->AsPtr<StaticMesh>();

	//	vkMesh->Destroy(mDevice);

	//	delete vkMesh;
	//}


	//TextureHandle RenderContextInterface::CreateTexture(const RenderResourceInitializerHandle& _init, const RawTexture& _raw)
	//{
	//	const TextureHandle handle = mTextures.EmplaceHandle();

	//	Texture& texture = mTextures[handle];
	//	ResourceInitializer& resInit = mResInits[_init];

	//	texture.Create(GetDevice(), resInit, _raw);

	//	return handle;
	//}

	//void RenderContextInterface::DestroyTexture(TextureHandle& _texture)
	//{
	//	Texture& texture = mTextures[_texture];

	//	texture.Destroy(GetDevice());

	//	mTextures.RemoveHandle(_texture);
	//	_texture.Reset();
	//}


	//CubemapHandle RenderContextInterface::CreateCubemap(const RenderResourceInitializerHandle& _init, const RawCubemap& _raw)
	//{
	//	const CubemapHandle handle = mCubemaps.EmplaceHandle();

	//	Cubemap& cubemap = mCubemaps[handle];
	//	ResourceInitializer& resInit = mResInits[_init];

	//	cubemap.Create(GetDevice(), resInit, _raw);

	//	return handle;
	//}

	//void RenderContextInterface::DestroyCubemap(CubemapHandle& _cubemap)
	//{
	//	Cubemap& cubemap = mCubemaps[_cubemap];

	//	cubemap.Destroy(GetDevice());

	//	mCubemaps.RemoveHandle(_cubemap);
	//	_cubemap.Reset();
	//}


	//
	//ATexture* RenderContextInterface::CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw)
	//{
	//	Texture* const texture = new Texture();

	//	texture->Create(mDevice, _init->As<ResourceInitializer>(), _raw);

	//	return texture;
	//}
	//
	//void RenderContextInterface::DestroyTexture(ATexture* _texture)
	//{
	//	Texture* const vkTexture = _texture->AsPtr<Texture>();

	//	vkTexture->Destroy(mDevice);

	//	delete vkTexture;
	//}

	//
	//ACubemap* RenderContextInterface::CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw)
	//{
	//	Cubemap* const cubemap = new Cubemap();

	//	cubemap->Create(mDevice, _init->As<ResourceInitializer>(), _raw);

	//	return cubemap;
	//}
	//
	//void RenderContextInterface::DestroyCubemap(ACubemap* _cubemap)
	//{
	//	Cubemap* const vkCubemap = _cubemap->AsPtr<Cubemap>();

	//	vkCubemap->Destroy(mDevice);

	//	delete vkCubemap;
	//}

	//
	//ARenderMaterial* RenderContextInterface::CreateMaterial(const RenderMaterialCreateInfos& _infos)
	//{
	//	Material* const mat = new Material();

	//	mat->Create(mDevice, _infos);

	//	return mat;
	//}
	//
	//void RenderContextInterface::DestroyMaterial(ARenderMaterial* _material)
	//{
	//	Material* const vkMat = _material->AsPtr<Material>();

	//	vkMat->Destroy(mDevice);

	//	delete vkMat;
	//}

	//
	//ACamera* RenderContextInterface::CreateCamera()
	//{
	//	Camera* const camera = new Camera();

	//	camera->Create(mDevice);

	//	return camera;
	//}
	//
	//void RenderContextInterface::DestroyCamera(ACamera* _camera)
	//{
	//	Camera* const vkCamera = _camera->AsPtr<Camera>();

	//	vkCamera->Destroy(mDevice);

	//	delete vkCamera;
	//}

//}
}
