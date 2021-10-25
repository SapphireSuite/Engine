// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderContextInterface.hpp>

#include <Render/Vulkan/VkRenderGraphicInterface.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

//#include <Render/Vulkan/Surface/VkWindowSurface.hpp>
//#include <Render/Vulkan/Surface/VkSurface.hpp>
//#include <Render/Vulkan/Pass/VkRenderPass.hpp>
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
		const RenderSurfaceHandle handle = mSurfaces.EmplaceHandle();

		mSurfaces[handle].Create(GetDevice(), _winHandle);

		return handle;
	}

	void RenderContextInterface::DestroySurface(RenderSurfaceHandle _handle)
	{
		mSurfaces[_handle].Destroy(GetDevice());

		mSurfaces.RemoveHandle(_handle);
	}


	//ARenderPass* RenderContextInterface::CreateRenderPass(const RenderPassDescriptor& _descriptor)
	//{
	//	RenderPass* const pass = new RenderPass();

	//	pass->Create(mDevice, _descriptor);

	//	return pass;
	//}
	//
	//void RenderContextInterface::DestroyRenderPass(ARenderPass* _pass)
	//{
	//	RenderPass* const vkPass = _pass->AsPtr<RenderPass>();

	//	vkPass->Destroy(mDevice);

	//	delete vkPass;
	//}


	//void RenderContextInterface::CreateFrameBuffers(ARenderSurface* _surface, ARenderPass* _pass, const RenderPassDescriptor& _descriptor)
	//{
	//	_surface->As<Surface>().CreateFrameBuffers(mDevice, _pass->As<RenderPass>(), _descriptor);
	//}

	//void RenderContextInterface::DestroyFrameBuffers(ARenderSurface* _surface)
	//{
	//	_surface->As<Surface>().DestroyFrameBuffers(mDevice);
	//}


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

	//ARenderResourceInitializer* RenderContextInterface::CreateResourceInitializer()
	//{
	//	ResourceInitializer* const init = new ResourceInitializer();

	//	init->Create(mDevice);

	//	return init;
	//}

	//void RenderContextInterface::DestroyResourceInitializer(ARenderResourceInitializer* _init)
	//{
	//	ResourceInitializer* const vkInit = _init->AsPtr<ResourceInitializer>();

	//	vkInit->Destroy(mDevice);

	//	delete vkInit;
	//}

	//void RenderContextInterface::SubmitResourceInitializer(ARenderResourceInitializer* _init)
	//{
	//	SA_ASSERT(Nullptr, SA/Render/Vulkan, _init);

	//	_init->As<ResourceInitializer>().Submit(mDevice);
	//}


	//AShader* RenderContextInterface::CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw)
	//{
	//	Shader* const shader = new Shader();

	//	shader->Create(mDevice, _init->As<ResourceInitializer>(), _raw);

	//	return shader;
	//}

	//void RenderContextInterface::DestroyShader(AShader* _shader)
	//{
	//	Shader* const vkShader = _shader->AsPtr<Shader>();

	//	vkShader->Destroy(mDevice);

	//	delete vkShader;
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
